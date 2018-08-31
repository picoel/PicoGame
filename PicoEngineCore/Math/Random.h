#pragma once

#include <random>
#include <memory>

namespace PicoEngine
{
	using RandomEngine = std::mt19937_64;
	RandomEngine& GetRandomEngine()
	{
		std::random_device device;
		thread_local RandomEngine engine( device() );
		return engine;
	}

	template<typename T>
	T GetRandRangeInt( T _min, T _max )
	{
		std::uniform_int_distribution<T> distribution( _min, _max );
		RandomEngine& rEngine = GetRandomEngine();
		return distribution( rEngine );
	}

	template<typename T>
	T GetRandInt()
	{
		RandomEngine& rEngine = GetRandomEngine();
		return static_cast<T>( rEngine() );
	}

	template<typename T>
	T GetRandRangeReal( T _min, T _max )
	{
		std::uniform_real_distribution<T> distribution( _min, _max );
		RandomEngine& rEngine = GetRandomEngine();
		return distribution( rEngine );
	}

	template<typename T>
	T GetRandReal()
	{
		return GetRandRangeReal( 0.0f, 1.0f );
	}

}