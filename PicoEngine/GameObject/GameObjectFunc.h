#pragma once
#include "PicoEngineCore/Manager.h"

namespace PicoEngine
{
	template<class T>
	static inline bool IsValidHandle( const GameObjectHandle<T>& _rHandle )
	{
		bool ret = false;
		const GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl )
		{
			ret = pcControl->IsExistObject( *_rHandle );
		}
		return ret;
	}

	template<class T, class... Args>
	static inline GameObjectHandle<T> CreateGameObject( Args&&... args )
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
	static inline bool DestoryGameObject( GameObjectHandle<T>& _rHandle )
	{
		if( !IsValidHandle( _rHandle ) )
		{
			_rHandle.Invalid();
			return false;
		}

		GameObject* pcObj = *_rHandle;
		_rHandle.Invalid();
		if( pcObj == nullptr )
		{
			return false;
		}

		DestroyGameObject( pcObj );

		GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl )
		{
			pcControl->RemoveRequestObject( pcObj );
		}
		else
		{
			SafeDelete( pcObj );	// failsafe
		}

		return true;
	}

	static inline bool DestroyAllGameObject()
	{
		GameObjectControl* pcControl = GetSystem<GameObjectControl>();
		if( pcControl == nullptr )
		{
			return false;
		}

		return pcControl->RemoveAllObject();
	}

	template<class T>
	static inline bool SuicideGameObject( T* _pcObj )
	{
		GameObjectHandle<T> temp( _pcObj );
		return DestoryGameObject( temp );
	}
}