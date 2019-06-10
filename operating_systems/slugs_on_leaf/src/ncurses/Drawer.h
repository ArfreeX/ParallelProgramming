#ifndef DRAWER_H
#define DRAWER_H

#include <iostream>
#include <thread>

#include "../assets/Leaf.h"


namespace ncurses
{

class Drawer
{
public:
    Drawer(pair_size_t leftCorner, pair_size_t sizes, std::shared_ptr<assets::Leaf> const leafPtr);
    ~Drawer();
    void run();
    void controlInput(bool &interruptExecution);

private:
    void initColoring();
    void drawerLoop();
    void controlInputLoop(bool &stopProgram);

    void refreshFrame();
    void drawPicture();
    void drawSlug(pair_size_t position);
    void drawLeafEaten(pair_size_t position);
    void drawLeafFull(pair_size_t position);
    void drawLeafRegenerating(pair_size_t position);
    void drawInfectedSlug(pair_size_t position);

    const pair_size_t LEFT_CORNER;
    const pair_size_t SIZES;
    const std::shared_ptr<assets::Leaf> LEAF_PTR;

    std::thread drawerThread;
    bool interruptDrawer = false;
};

} // namespace ncurses
#endif // DRAWER_H
