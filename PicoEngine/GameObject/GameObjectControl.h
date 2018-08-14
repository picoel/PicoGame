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

	template<typename T>
	T* CreateGameObject()
	{
		T* ret = new T();
		return ret;
	}

	template<typename T>
	yBool DestoryGameObject( T* _obj )
	{
		delete _obj;
	}
}