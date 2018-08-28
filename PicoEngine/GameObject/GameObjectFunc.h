#pragma once

namespace PicoEngine
{
	template<class T, class... Args>
	GameObjectHandle<T> CreateGameObject(Args&&... args)
	{
		T* pcObj = new T( args... );
		GameObjectHandle<T> handle( pcObj );

		GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
		if( pcControl )
		{
			pcControl->AddRequestGameObject( *handle );
		}

		return handle;
	}

	template<class T>
	bool DestoryGameObject( GameObjectHandle<T>& _rHandle )
	{
		GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
		if( pcControl )
		{
			pcControl->RemoveRequestObject( *_rHandle );
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
}