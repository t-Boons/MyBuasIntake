// 2023 Tygo Boons

#include "mypch.h"
#include "Random.h"
#include "glm/glm.hpp"

namespace Utils
{
    void Random::RandomizeSeed()
    {
        // Set random seed.
        srand(time(NULL));
    }

    float Random::Range(float min, float max)
    {
        // Create random value between range.
        return min + (rand() % 1000 / 1000.0f) * (max - min);
    }

    int Random::Range(int min, int max)
    {
        // Create random value between range.
        return static_cast<int>(min + (rand() % 1000 / 1000.0f) * (max - min));
    }

    bool Random::Chance(float percentage)
    {
        // Return true if percentage number is higher than the random number between 0 and 1
        percentage = glm::clamp(percentage, 0.0f, 1.0f);
        return Range(0.0f, 1.0f) <= percentage;
    }
}