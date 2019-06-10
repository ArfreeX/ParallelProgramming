#ifndef LEAF_H
#define LEAF_H

#include <list>
#include <vector>
#include <thread>
#include <mutex>


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

    void executeRegeneration();
    bool moveAllowed(pair_size_t position, pair_size_t previousPosition, bool transformed);
    bool spawnAllowed(pair_size_t position);
    void slugKilled(pair_size_t position);

    std::vector<std::vector<LeafPointState>> getLeafState();

private:
    void regeneration();
    void pointHealed(pair_size_t point);
    void pointRegenerating(pair_size_t point);
    void pointEated(pair_size_t point);
    void pointNotEated(pair_size_t point);

    static std::mutex leafMutex;
    const pair_size_t LEFT_PITCH_CORNER;
    const pair_size_t PITCH_SIZES;

    std::thread thread;
    bool regenerationProcess;
    std::vector<std::vector<LeafPointState>> leafPointsState;
    std::list<std::pair<pair_size_t, std::chrono::seconds>> regeneratingPoints;
};

} // namespace assets

#endif // LEAF_H
