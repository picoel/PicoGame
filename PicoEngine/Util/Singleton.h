#pragma once

#include <functional>
#include <cassert>

namespace PicoEngine
{
	template<class T>
	class Singleton
	{
	public:
		template<class... Args>
		static void CreateInstance(Args... args)
		{
			assert( s_pInstance == nullptr );
			if( s_pInstance != nullptr )
			{
				return;
			}

			s_pInstance = new T( args... );
		}

		static void DestoryInstance()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		static T* GetInstance()
		{
			return s_pInstance;
		}

	private:
		static T* s_pInstance;
	};

	template<class T>
	T* Singleton<T>::s_pInstance = nullptr;
}
