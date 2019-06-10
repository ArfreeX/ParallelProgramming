#include <chrono>
#include <ncurses.h>
#include <mutex>
#include "Drawer.h"
#include <curses.h>
#include "../assets/Slug.h"

namespace  ncurses
{

Drawer::Drawer(pair_size_t leftCorner, pair_size_t sizes, std::shared_ptr<assets::Leaf> leafPtr) :
    LEFT_CORNER(leftCorner), SIZES(sizes), LEAF_PTR(leafPtr)
{
    initscr();
    curs_set(0);
    cbreak();

    if (has_colors() == FALSE)
    {
        throw std::runtime_error(
            "Your terminal doesn't support colors. This program will not start");
    }
    initColoring();
}


void Drawer::initColoring()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_RED);
}


Drawer::~Drawer()
{
    interruptDrawer = true;
    drawerThread.join();
    endwin();
}


void Drawer::run()
{
    drawerThread = std::thread(&Drawer::drawerLoop, this);
}


void Drawer::drawerLoop()
{
    while(not interruptDrawer)
    {
        refreshFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}


void Drawer::refreshFrame()
{
    erase();
    drawPicture();
    refresh();
}


void Drawer::drawPicture()
{
    auto leafStateVector = LEAF_PTR->getLeafState();
    if(leafStateVector.empty())
    {
        return;
    }
    for(uint i = 0; i < leafStateVector.size(); i++)
    {
        for(uint j = 0; j < leafStateVector[i].size(); j++)
        {
            switch(leafStateVector[i][j])
            {
            case LeafPointState::FULL:
                drawLeafFull(std::make_pair(i, j));
                break;

            case LeafPointState::SLUG:
                drawSlug(std::make_pair(i, j));
                break;

            case LeafPointState::INFECTED_SLUG:
                drawInfectedSlug(std::make_pair(i, j));
                break;

            case LeafPointState::EATEN:
                drawLeafEaten(std::make_pair(i, j));
                break;

            case LeafPointState::REGENERATING:
                drawLeafRegenerating(std::make_pair(i, j));
                break;

            default:
                break;
            }
        }
    }
}


void Drawer::controlInput(bool &interruptExecution)
{
    std::thread(&Drawer::controlInputLoop, this, std::ref(interruptExecution)).detach();
}


void Drawer::controlInputLoop(bool &interruptExecution)
{
    while(getch() != 'q')
    {
        erase();
    }
    interruptExecution = true;
    assets::Slug::stopSlugs();
}


void Drawer::drawSlug(pair_size_t position)
{
    mvaddch(position.second, position.first, ' ' | COLOR_PAIR(1));
}


void Drawer::drawLeafEaten(pair_size_t position)
{
    mvaddch(position.second, position.first, ' ' | COLOR_PAIR(2));
}


void Drawer::drawLeafFull(pair_size_t position)
{
    mvaddch(position.second, position.first, ' ' | COLOR_PAIR(3));
}


void Drawer::drawLeafRegenerating(pair_size_t position)
{
    mvaddch(position.second, position.first, ' ' | COLOR_PAIR(4));
}


void Drawer::drawInfectedSlug(pair_size_t position)
{
    mvaddch(position.second, position.first, ' ' | COLOR_PAIR(5));
}

}  // namespace ncurses
