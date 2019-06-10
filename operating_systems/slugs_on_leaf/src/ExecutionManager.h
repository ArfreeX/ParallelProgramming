#pragma once
#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "ncurses/Drawer.h"

class ExecutionManager
{
public:
    ExecutionManager(pair_size_t pitch_corner, pair_size_t pitch_edges, double spawn_ratio, double heal_ratio);

    void execute();

private:
    const pair_size_t PITCH_CORNER;
    const pair_size_t PITCH_EDGES;
    const double SLUG_SPAWN_RATIO;
    const double LEAF_HEAL_RATIO;
};

#endif // EXECUTIONMANAGER_H
