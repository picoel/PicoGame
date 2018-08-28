#pragma once
#include "PicoEngine/Include.h"
namespace PicoEngine
{
	bool Initialize()
	{
		Singleton<Manager>::CreateInstance();
		Manager* pcManager = Singleton<Manager>::GetInstance();
		assert( pcManager );
		if( pcManager == nullptr )
		{
			return false;
		}

		pcManager->RegisterSystem<Time>();
		pcManager->RegisterSystem<GameObjectControl>();

		return true;
	}

	bool Finalize()
	{
		Singleton<Manager>::DestoryInstance();
		return true;
	}

	float64 GetDeltaTime()
	{
		const Time* pcTime = GetSystem<Time>();
		return pcTime->GetDeltaTime<std::chrono::microseconds>();
	}
}
