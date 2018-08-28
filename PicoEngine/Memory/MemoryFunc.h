#pragma once

namespace PicoEngine
{
	template<class T>
	inline void SafeDelete( T*& _ptr )
	{
		static_assert( sizeof( T ), "type must be complete." );
		delete _ptr;
		_ptr = nullptr;
	}

	template<class T>
	inline void SafeDeleteArray( T*& _ptr )
	{
		static_assert( sizeof( T ), "type must be complete." );
		delete[] _ptr;
		_ptr = nullptr;
	}
}