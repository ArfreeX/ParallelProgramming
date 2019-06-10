#include "helpers/Randomizer.h"
#include "SlugManager.h"


SlugManager::SlugManager(pair_size_t leftPitchCorner, pair_size_t pitchSizes, std::shared_ptr<assets::Leaf> const leafPtr) :
    LEFT_PITCH_CORNER(leftPitchCorner), PITCH_SIZES(pitchSizes), LEAF_PTR(leafPtr)
{

}

SlugManager::~SlugManager()
{

}

void SlugManager::spawnSlug()
{
    pair_size_t startingPos;
    do {
        startingPos = helpers::Randomizer::drawPointInside(LEFT_PITCH_CORNER, PITCH_SIZES);
    } while(not LEAF_PTR->spawnAllowed(startingPos));

    std::unique_ptr<assets::Slug> slugPtr = std::make_unique<assets::Slug>(
                helpers::Randomizer::drawSpeed(), startingPos, helpers::Randomizer::drawDirection(), LEAF_PTR);
    slugPtr->execute();
    slugColony.emplace_back(std::move(slugPtr));
}

std::vector<std::unique_ptr<assets::Slug>> const&  SlugManager::getColony()
{
    return slugColony;
}
