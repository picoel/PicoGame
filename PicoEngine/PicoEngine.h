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
		pcManager->RegisterSystem<WorkerThread>(4);
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
		WorkerThread* pcWorkerThread = GetSystem<WorkerThread>();
		assert( pcWorkerThread );
		if( pcWorkerThread == nullptr )
		{
			return std::future<T>();
		}

		return pcWorkerThread->Request( _func );
	}

	static inline real64 GetDeltaTime()
	{
		const Time* pcTime = GetSystem<Time>();
		return pcTime->GetDeltaTime<std::chrono::microseconds>();
	}
}
