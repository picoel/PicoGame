#pragma once
#include <list>
#include <deque>
#include <unordered_map>

namespace PicoEngine
{
	template<class T>
	using list = std::list<T, allocator<T> >;

	template<class T>
	using deque = std::deque<T, allocator<T> >;

	template<class Key, class Value, class Hash = std::hash<Key>, class Pred = std::equal_to<Key> >
	using unorderd_map = std::unordered_map<Key, Value, Hash, Pred, allocator<std::pair<Key, Value> > >;

	template<class T, usize N>
	constexpr usize Length( T( &array )[N] )
	{
		return N;
	}
}