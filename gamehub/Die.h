#pragma once
#include <random>

class Die
{
public:
	Die();

	unsigned Roll();
private:
	std::uniform_int_distribution<unsigned> m_Distribution;
	std::mt19937 m_RandomGenerator;
};

