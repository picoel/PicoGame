#pragma once
#include "PicoEngine/GameObject/GameObject.h"

namespace PicoEngine
{
	class GameObjectControl
	{
	public:
		GameObjectControl();
		virtual ~GameObjectControl();
	};

	template<class T, class... Args>
	T* CreateGameObject(Args... args)
	{
		T* ret = new T( args... );
		return ret;
	}

	template<class T>
	bool DestoryGameObject( T* _obj )
	{
		delete _obj;
		return true;
	}
}