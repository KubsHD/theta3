/*****************************************************************//**
 * \file   random.h
 * \brief  Random number generator
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <core/types.h>
#include <random>

/// <summary>
/// Generates random numbers
/// </summary>
class Random {
public:

	/// <summary>
	/// Initialize the random generator
	/// </summary>
	static void init()
	{
		m_randomGen.seed(std::random_device()());
	}

	/// <summary>
	/// Get random float
	/// </summary>
	/// <returns></returns>
	static float get_float()
	{
		return (float)m_dist(m_randomGen) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	static std::mt19937 m_randomGen;
	static std::uniform_int_distribution<std::mt19937::result_type> m_dist;
};

