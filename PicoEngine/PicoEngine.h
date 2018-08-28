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

		pcManager->RegisterSystem<DeltaTime>();
		pcManager->RegisterSystem<GameObjectControl>();

		return true;
	}

	bool Finalize()
	{
		Singleton<Manager>::DestoryInstance();
		return true;
	}
}
