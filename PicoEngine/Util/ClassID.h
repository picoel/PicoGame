#pragma once
#include <cstdint>

namespace PicoEngine
{
	using ClassIDType = std::uintptr_t;

	template<class T>
	class ClassID
	{
	private:
		const static std::uint8_t sc_uDummy;

	public:
		using ClassIDType = std::uintptr_t;
		static ClassIDType Get(){ return reinterpret_cast<ClassIDType>( &sc_uDummy ); }
	};

	template<class T>
	const std::uint8_t ClassID<T>::sc_uDummy = 0;
}
