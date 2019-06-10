#include "Leaf.h"
#include "Slug.h"

namespace assets
{

std::mutex Leaf::leafMutex;

Leaf::Leaf(pair_size_t leftPitchCorner, pair_size_t pitchSizes) :
    LEFT_PITCH_CORNER(leftPitchCorner), PITCH_SIZES(pitchSizes)
{
    leafPointsState.resize(PITCH_SIZES.first);
    for(auto & row : leafPointsState)
    {
        row.resize(PITCH_SIZES.second);
        std::fill(row.begin(), row.end(), LeafPointState::FULL);
    }

    slugsOnLeaf.resize(PITCH_SIZES.first);
    for(auto & row : slugsOnLeaf)
    {
        row.resize(PITCH_SIZES.second);
        std::fill(row.begin(), row.end(), nullptr);
    }
}

Leaf::~Leaf()
{
    if(regenerationProcess)
    {
        regenerationProcess = false;
    }
    thread.join();
}


void Leaf::executeRegeneration()
{
    regenerationProcess = true;
    thread = std::thread(&Leaf::regeneration, this);
}


void Leaf::regeneration()
{
    while(regenerationProcess)
    {
        for(auto iterator = regeneratingPoints.begin(); iterator != regeneratingPoints.end();)
        {
            auto & element = (*iterator);
            element.second--;

            if(element.second < std::chrono::seconds(5))
            {
                if(element.second < std::chrono::seconds(0))
                {
                    pointHealed(element.first);
                    iterator = regeneratingPoints.erase(iterator);
                }
                else
                {
                    pointRegenerating(element.first);
                    iterator++;
                }
            }
            else
            {
                iterator++;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}


void Leaf::slugKilled(pair_size_t point)
{
    leafPointsState[point.first][point.second] = LeafPointState::FULL;
}


void Leaf::pointHealed(pair_size_t point)
{
    std::lock_guard<std::mutex> guard(leafMutex);
    leafPointsState[point.first][point.second] = LeafPointState::FULL;
}


void Leaf::pointRegenerating(pair_size_t point)
{
    std::lock_guard<std::mutex> guard(leafMutex);
    leafPointsState[point.first][point.second] = LeafPointState::REGENERATING;
}


void Leaf::pointEated(pair_size_t point)
{
    leafPointsState[point.first][point.second] = LeafPointState::EATEN;
    regeneratingPoints.push_back(std::make_pair(
                                     std::make_pair(point.first, point.second),
                                     std::chrono::seconds(20)));
}


void Leaf::pointNotEated(pair_size_t point)
{
    leafPointsState[point.first][point.second] = LeafPointState::FULL;
}


bool Leaf::spawnAllowed(pair_size_t position)
{
    if(leafPointsState[position.first][position.second] == LeafPointState::FULL)
    {
        leafPointsState[position.first][position.second] = LeafPointState::SLUG;
        return true;
    }

    return false;
}

bool Leaf::moveAllowed(Slug* slug, pair_size_t previousPosition)
{
    std::lock_guard<std::mutex> guardLeaf(leafMutex);
    auto position = slug->getPosition();

    if(position.first < PITCH_SIZES.first and position.second < PITCH_SIZES.second)
    {
        if(slug->isTransformed())
        {
            if(leafPointsState[position.first][position.second] == LeafPointState::FULL or
                    leafPointsState[position.first][position.second] == LeafPointState::SLUG)
            {
                pointNotEated(previousPosition);
                leafPointsState[position.first][position.second] = LeafPointState::INFECTED_SLUG;

                if(slugsOnLeaf[position.first][position.second])
                {
                    slugsOnLeaf[position.first][position.second]->killThread();
                    slug->increaseTimerAfterKilling();
                }

                slugsOnLeaf[previousPosition.first][previousPosition.second] = nullptr;
                slugsOnLeaf[position.first][position.second] = slug;
                        return true;
            }
        }
        else
        {
            if(leafPointsState[position.first][position.second] == LeafPointState::FULL)
            {
                pointEated(previousPosition);
                leafPointsState[position.first][position.second] = LeafPointState::SLUG;

                slugsOnLeaf[previousPosition.first][previousPosition.second] = nullptr;
                slugsOnLeaf[position.first][position.second] = slug;

                return true;
            }

        }

    }

    return false;
}


std::vector<std::vector<LeafPointState>> Leaf::getLeafState()
{
    return leafPointsState;
}

} // namespace assets
