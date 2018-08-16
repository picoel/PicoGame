#pragma once
#include <mutex>
#include <shared_mutex>

namespace PicoEngine
{
	using mutex = std::mutex;
	using shared_timed_mutex = std::shared_timed_mutex;
	using shared_mutex = std::shared_mutex;

	template<class T>
	using lock_guard = std::lock_guard<T>;
	template<class T>
	using unique_lock = std::unique_lock<T>;
	template<class T>
	using shared_lock = std::shared_lock<T>;
}