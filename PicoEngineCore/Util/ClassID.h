#pragma once
#include "PicoEngineCore/Util/Type.h"

namespace PicoEngine
{
	using ClassIDType = uint64;

	template<class T>
	class ClassID
	{
	private:
		const static std::uint8_t sc_uDummy;

	public:
		static ClassIDType Get(){ return reinterpret_cast<ClassIDType>( &sc_uDummy ); }
	};

	template<class T>
	const std::uint8_t ClassID<T>::sc_uDummy = 0;
}
