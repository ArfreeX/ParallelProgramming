#include <ncurses.h>
#include <unistd.h>
#include "../helpers/Randomizer.h"
#include "../ncurses/Drawer.h"
#include "Slug.h"
#include <queue>


namespace assets
{

std::mutex Slug::slugMutex;
std::atomic<bool> Slug::stopThread;


Slug::Slug(pair_size_t initialPosition, Direction initialDirection, std::shared_ptr<assets::Leaf> const leafPtr)
    : position(initialPosition), direction(initialDirection), LEAF_PTR(leafPtr)
{
    speed = 1000.0 / 50;
}


Slug::~Slug()
{
    if(!stopThread)
    {
        stopThread = true;
    }
    thread.join();
}


void Slug::execute()
{
    thread = std::thread(&Slug::movement, this);
}


void Slug::stopSlugs() /*static*/
{
    if(!stopThread)
    {
        stopThread = true;
    }
}

pair_size_t Slug::getPosition()
{
    return position;
}

void Slug::movement()
{
    while(!stopThread)
    {
    positionChange();
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }
}

void Slug::positionChange()
{
    auto previousPosition = position;
    auto directionStack(helpers::Randomizer::drawDirectionStack());

    do {
        direction = directionStack.top();
        directionStack.pop();

        switch(direction)
        {
        case Direction::LEFT:
                position.first--;
            break;

        case Direction::RIGHT:
                position.first++;
            break;

        case Direction::UP:
                position.second--;
            break;

        case Direction::DOWN:
                position.second++;
            break;
        }

        std::lock_guard<std::mutex> guard(slugMutex);
        if(not LEAF_PTR->moveAllowed(position, previousPosition))
        {
            position = previousPosition;
        }
    }while(position == previousPosition && not directionStack.empty());

    if(position == previousPosition)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}


} // namespace assets
