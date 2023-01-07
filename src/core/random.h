#pragma once

#include <core/types.h>
#include <random>

class Random {
public:
	static void init()
	{
		m_randomGen.seed(std::random_device()());
	}

	static float get_float()
	{
		return (float)m_dist(m_randomGen) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	static std::mt19937 m_randomGen;
	static std::uniform_int_distribution<std::mt19937::result_type> m_dist;
};

