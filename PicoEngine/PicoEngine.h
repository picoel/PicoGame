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
		pcManager->RegisterSystem<SceneControl>();
		pcManager->RegisterSystem<GameObjectControl>();

		return true;
	}

	static inline bool Finalize()
	{
		Singleton<Manager>::DestoryInstance();
		return true;
	}

	static inline real64 GetDeltaTime()
	{
		const Time* pcTime = GetSystem<Time>();
		return pcTime->GetDeltaTime<std::chrono::microseconds>();
	}
}
