#ifndef SLUG_H
#define SLUG_H

#include <atomic>
#include <future>
#include <mutex>
#include <thread>
#include "Leaf.h"



enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};


namespace assets
{

class Slug
{
public:
    Slug(pair_size_t initialPosition, Direction initialDirection, std::shared_ptr<assets::Leaf> const leafPtr);
    ~Slug();

    static void stopSlugs();

    void execute();
    pair_size_t getPosition();
    void killThread();

private:
    void movement();
    void positionChange();
    void slugTransformationRoll();

    static std::mutex slugMutex;
    static std::atomic<bool> stopThread;
    static bool ready;

    std::shared_ptr<assets::Leaf> const LEAF_PTR;

    std::thread thread;

    pair_size_t position;
    Direction direction;
    double speed;
    bool transformed;
    bool threadRunning;

    std::chrono::seconds infectedTimer;
};

} // namespace assets
#endif // SLUG_H
