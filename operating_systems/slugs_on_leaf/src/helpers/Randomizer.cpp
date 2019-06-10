#include "Randomizer.h"


namespace helpers
{


std::random_device Randomizer::randomGenerator;


Randomizer::Randomizer()
{
}


double Randomizer::drawSpeed() /*static*/
{
    const int MIN_MOVES_PER_SECOND = 3;
    const int MAX_MOVES_PER_SECOND = 5;
    std::uniform_int_distribution<int> speed(MIN_MOVES_PER_SECOND, MAX_MOVES_PER_SECOND);

    return static_cast<int>(speed(randomGenerator));
}


Direction Randomizer::drawDirection() /*static*/
{
    std::uniform_int_distribution<int> direction(0, (Direction::NONE - 1));

    return Direction(direction(randomGenerator));
}


std::stack<Direction> Randomizer::drawDirectionStack() /*static*/
{
    std::stack<Direction> directionStack;
    std::vector<int> directionCounter(4, 0);
    std::uniform_int_distribution<int> direction(0, (Direction::NONE - 1));

    while(directionStack.size() < 4)
    {
        auto rolledDirection = (Direction) direction(randomGenerator);

        switch(rolledDirection)
        {
        case Direction::UP:
            if(directionCounter[0] == 0)
            {
                directionCounter[0]++;
                directionStack.push(rolledDirection);
            }
            break;
        case Direction::DOWN:
            if(directionCounter[1] == 0)
            {
                directionCounter[1]++;
                directionStack.push(rolledDirection);
            }
            break;
        case Direction::LEFT:
            if(directionCounter[2] == 0)
            {
                directionCounter[2]++;
                directionStack.push(rolledDirection);
            }
            break;
        case Direction::RIGHT:
            if(directionCounter[3] == 0)
            {
                directionCounter[3]++;
                directionStack.push(rolledDirection);
            }
            break;
        }
    };


    return directionStack;
}


pair_size_t Randomizer::drawPointInside(pair_size_t hookPoint, pair_size_t boundaries) /*static*/
{
    std::uniform_int_distribution<size_t> positionX(hookPoint.first + 2, boundaries.first - 3);
    std::uniform_int_distribution<size_t> positionY(hookPoint.second + 2, boundaries.second - 3);

    return std::make_pair(positionX(randomGenerator), positionY(randomGenerator));
}


} // namespace helpers
