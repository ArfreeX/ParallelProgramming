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


Slug::Slug(double speed, pair_size_t initialPosition, Direction initialDirection, std::shared_ptr<assets::Leaf> const leafPtr)
    : position(initialPosition), direction(initialDirection), LEAF_PTR(leafPtr)
{
    speedDelay = std::chrono::milliseconds(static_cast<int>((round(1000 / speed))));
    transformed = false;
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
    threadRunning = true;
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


bool Slug::isTransformed()
{
    return transformed;
}


void Slug::killThread()
{
    LEAF_PTR->slugKilled(position);
    threadRunning = false;
}


void Slug::movement()
{
    while(not stopThread && threadRunning)
    {
    positionChange();

    if(not transformed)
    {
        slugTransformationRoll();
    }
    else
    {
        infectedTimer -= speedDelay;
        definitiveTimer -= speedDelay;

        if(infectedTimer <= std::chrono::milliseconds(0) or
                definitiveTimer <= std::chrono::milliseconds(0))
        {
            killThread();
        }
    }

    std::this_thread::sleep_for(speedDelay);
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
        if(not LEAF_PTR->moveAllowed(this, previousPosition))
        {
            position = previousPosition;
        }
    }while(position == previousPosition && not directionStack.empty());

    if(position == previousPosition)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}


void Slug::increaseTimerAfterKilling()
{
    infectedTimer += std::chrono::milliseconds(60000);
    speedDelay /= 2;

    if(speedDelay < std::chrono::milliseconds(100))
    {
        speedDelay = std::chrono::milliseconds(100);
    }
}

void Slug::slugTransformationRoll()
{
    transformed = helpers::Randomizer::rollSlugTransformation();

    if(transformed)
    {
        definitiveTimer = std::chrono::milliseconds(40000);
        infectedTimer = std::chrono::milliseconds(10000);
    }
}

} // namespace assets
