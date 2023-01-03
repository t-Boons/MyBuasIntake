// 2023 Tygo Boons

#pragma once

namespace Utils
{
	class Random
	{
	public:
		// Randomizes the random seed.
		static void RandomizeSeed();

		// Returns a random value between minimum and maximum range.
		static float Range(float min, float max);

		// Returns a random value between minimum and maximum range.
		static int Range(int min, int max);

		// Returns true or false depending on a percentage chance.
		static bool Chance(float percentage);
	};
}