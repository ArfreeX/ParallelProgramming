#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include <stack>
#include "../assets/Slug.h"

namespace helpers
{


class Randomizer
{
public:
    Randomizer();

    static double drawSpeed();
    static Direction drawDirection();
    static std::stack<Direction> drawDirectionStack();
    static pair_size_t drawPointInside(pair_size_t hookPoint, pair_size_t boundaries);
    static std::random_device randomGenerator;
};

} // namespace helpers
#endif // RANDOMIZER_H
