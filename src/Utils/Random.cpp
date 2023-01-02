// 2023 Tygo Boons

#include "mypch.h"
#include "Random.h"

namespace Utils
{
    float Random::Range(float min, float max)
    {
        // Create random value between range.
        return min + (rand() % 1000 / 1000.0f) * (max - min);
    }
}