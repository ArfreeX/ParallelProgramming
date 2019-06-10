#ifndef SLUGMANAGER_H
#define SLUGMANAGER_H

#include <vector>
#include "assets/Slug.h"


class SlugManager
{
public:
    SlugManager(pair_size_t leftPitchCorner, pair_size_t pitchSizes, std::shared_ptr<assets::Leaf> const leafPtr);
    ~SlugManager();

    void spawnSlug();
    std::vector<std::unique_ptr<assets::Slug>> const&  getColony();
private:
    std::vector<std::unique_ptr<assets::Slug>> slugColony;

    const pair_size_t LEFT_PITCH_CORNER;
    const pair_size_t PITCH_SIZES;
    const std::shared_ptr<assets::Leaf> LEAF_PTR;
};

#endif // SLUGMANAGER_H
