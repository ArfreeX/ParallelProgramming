#include "Leaf.h"

namespace assets
{


Leaf::Leaf(pair_size_t leftPitchCorner, pair_size_t pitchSizes) :
    LEFT_PITCH_CORNER(leftPitchCorner), PITCH_SIZES(pitchSizes)
{
    leafPointsState.resize(PITCH_SIZES.first);
    for(auto & row : leafPointsState)
    {
        row.resize(PITCH_SIZES.second);
        std::fill(row.begin(), row.end(), LeafPointState::FULL);
    }
}

Leaf::~Leaf()
{
    //thread.join();
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

bool Leaf::moveAllowed(pair_size_t position, pair_size_t previousPosition)
{
    if(position.first < PITCH_SIZES.first and position.second < PITCH_SIZES.second
            and leafPointsState[position.first][position.second] == LeafPointState::FULL)
    {
        leafPointsState[previousPosition.first][previousPosition.second] = LeafPointState::EATEN;
        leafPointsState[position.first][position.second] = LeafPointState::SLUG;
        return true;
    }

    return false;
}


std::vector<std::vector<LeafPointState>> Leaf::getLeafState()
{
    return leafPointsState;
}

} // namespace assets
