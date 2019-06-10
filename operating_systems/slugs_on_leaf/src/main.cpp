#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "ExecutionManager.h"
#include "ncurses.h"

int main(int argc, char *argv[])
{
    const pair_size_t PITCH_TOP_LEFT_CORNER(0, 0);
    const double SLUG_SPAWN_RATIO_PER_SEC = 0.1; // 1 = 1 slug per 1 second
    const double LEAF_HEAL_RATIO_PER_SEC = 0.1; // 1 = 100% health, 0.1 = 10% health per 1 second
    int pitch_x, pitch_y;

    initscr();
    getmaxyx(stdscr, pitch_y, pitch_x);

    ExecutionManager executionManager(
                PITCH_TOP_LEFT_CORNER, std::make_pair<size_t, size_t>(pitch_x, pitch_y),
                SLUG_SPAWN_RATIO_PER_SEC, LEAF_HEAL_RATIO_PER_SEC);
    executionManager.execute();

    return 0;
}
