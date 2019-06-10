#include <algorithm>
#include <random>
#include "assets/Leaf.h"
#include "helpers/Randomizer.h"
#include "ExecutionManager.h"
#include "SlugManager.h"

ExecutionManager::ExecutionManager(pair_size_t pitch_corner, pair_size_t pitch_edges,
                                   double spawn_ratio, double heal_ratio) :
    PITCH_CORNER(pitch_corner), PITCH_EDGES(pitch_edges),
    SLUG_SPAWN_RATIO(spawn_ratio), LEAF_HEAL_RATIO(heal_ratio)
{
}


void ExecutionManager::execute()
{
    uint startingColonyCounter = 50;

    bool interruptExecution = false;
    std::shared_ptr<assets::Leaf> leafPtr = std::make_shared<assets::Leaf>(
                PITCH_CORNER, PITCH_EDGES);
    std::shared_ptr<SlugManager> slugManagerPtr = std::make_shared<SlugManager>(PITCH_CORNER, PITCH_EDGES, leafPtr);
    ncurses::Drawer drawer(PITCH_CORNER, PITCH_EDGES, leafPtr);

    drawer.run();
    drawer.controlInput(interruptExecution);

    leafPtr->executeRegeneration();

    while(startingColonyCounter > 0)
    {
        slugManagerPtr->spawnSlug();
        startingColonyCounter--;
    }

    while(not interruptExecution)
    {
        slugManagerPtr->spawnSlug();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
//    std::vector<std::unique_ptr<assets::Ball>> basket;
//    bool stopProgram = false;
//    const BoundariesGuard GUARD(PITCH_CORNER, PITCH_EDGES);
//    const assets::Swamp SWAMP(PITCH_CORNER, PITCH_EDGES);


//    while(not stopProgram)
//    {
//        double speed = helpers::Randomizer::drawSpeed();
//        Direction direction = helpers::Randomizer::drawDirection();
//        adjustSpeed(direction, speed);

//        std::unique_ptr<assets::Ball> ballPtr = std::make_unique<assets::Ball>(helpers::Randomizer::drawPointInside(PITCH_CORNER, PITCH_EDGES),
//                                                               direction, speed, GUARD, SWAMP);
//        ballPtr->execute();
//        basket.emplace_back(std::move(ballPtr));
//        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(round(1000.0 / BALL_SPAWN_RATIO))));
//    }
}
