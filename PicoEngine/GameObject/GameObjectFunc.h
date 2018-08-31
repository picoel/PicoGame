#pragma once
#include "PicoEngineCore/Manager.h"

namespace PicoEngine
{
	template<class T, class... Args>
	GameObjectHandle<T> CreateGameObject( Args&&... args )
	{
		T* pcObj = new T( args... );
		GameObjectHandle<T> handle( pcObj );

		GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl )
		{
			pcControl->AddRequestGameObject( *handle );
		}

		return handle;
	}

	template<class T>
	bool DestoryGameObject( GameObjectHandle<T>& _rHandle )
	{
		GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl )
		{
			pcControl->RemoveRequestObject( *_rHandle );
		}
		else
		{
			GameObject* pcObj = *_rHandle;
			SafeDelete( pcObj );	// failsafe
		}

		_rHandle.Invalid();
		return true;
	}

	template<class T>
	bool SuicideGameObject( T* _pcObj )
	{
		GameObjectHandle<T> temp( _pcObj );
		return DestoryGameObject( temp );
	}

	template<class T>
	bool IsValidHandle( const GameObjectHandle<T>& _rHandle )
	{
		bool ret = false;
		const GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl )
		{
			ret = pcControl->IsExistObject( *_rHandle );
		}
		return ret;
	}
}