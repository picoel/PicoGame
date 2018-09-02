#pragma once
#include "PicoEngine/Include.h"
namespace PicoEngine
{
	static inline bool Initialize()
	{
		Singleton<Manager>::CreateInstance();
		Manager* pcManager = Singleton<Manager>::GetInstance();
		assert( pcManager );
		if( pcManager == nullptr )
		{
			return false;
		}

		pcManager->RegisterSystem<Time>();
		pcManager->RegisterSystem<WorkerThreadSystem>( 4 );
		pcManager->RegisterSystem<SyncWorkerThreadSystem>( 4 );
		pcManager->RegisterSystem<SceneControl>();
		pcManager->RegisterSystem<GameObjectControl>();

		return true;
	}

	static inline bool Finalize()
	{
		Singleton<Manager>::DestoryInstance();
		return true;
	}

	template<typename T>
	std::future<T> RequestTask( std::function<T()> _func )
	{
		WorkerThreadSystem* pcWorkerThreadSystem = GetSystem<WorkerThreadSystem>();
		assert( pcWorkerThreadSystem );
		if( pcWorkerThreadSystem == nullptr )
		{
			return std::future<T>();
		}

		return pcWorkerThreadSystem->Request( _func );
	}

	template<typename T>
	std::future<T> RequestSyncTask( std::function<T()> _func )
	{
		WorkerThreadSystem* pcWorkerThreadSystem = GetSystem<SyncWorkerThreadSystem>();
		assert( pcWorkerThreadSystem );
		if( pcWorkerThreadSystem == nullptr )
		{
			return std::future<T>();
		}

		return pcWorkerThreadSystem->Request( _func );
	}

	static inline real64 GetDeltaTime()
	{
		const Time* pcTime = GetSystem<Time>();
		return pcTime->GetDeltaTime<std::chrono::microseconds>();
	}
}
