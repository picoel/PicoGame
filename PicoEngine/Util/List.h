#pragma once
#include <list>
#include <deque>
#include <unordered_map>

namespace PicoEngine
{
	template<typename T>
	using list = std::list<T>;

	template<typename T>
	using deque = std::deque<T>;

	template<typename Key, typename Value>
	using unorderd_map = std::unordered_map<Key, Value>;
}