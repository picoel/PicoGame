#pragma once
#include <list>
#include <deque>

namespace PicoEngine
{
	template<typename T>
	using list = std::list<T>;

	template<typename T>
	using deque = std::deque<T>;
}