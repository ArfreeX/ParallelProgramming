#ifndef LEAF_H
#define LEAF_H

#include <vector>
#include <thread>


enum LeafPointState
{
    EATEN,
    REGENERATING,
    FULL,
    SLUG,
    INFECTED_SLUG,
    LAST_ELEMENT
};

using pair_size_t = std::pair<size_t, size_t> ;

namespace assets
{

class Leaf
{
public:
    Leaf(pair_size_t leftPitchCorner, pair_size_t pitchSizes);
    ~Leaf();

    bool moveAllowed(pair_size_t position, pair_size_t previousPosition);
    bool spawnAllowed(pair_size_t position);
    std::vector<std::vector<LeafPointState>> getLeafState();
private:
    const pair_size_t LEFT_PITCH_CORNER;
    const pair_size_t PITCH_SIZES;

    std::thread thread;

    std::vector<std::vector<LeafPointState>> leafPointsState;
};

} // namespace assets

#endif // LEAF_H
