#pragma once
#include "PicoEngineCore/Manager.h"
#include "PicoEngine/Scene/SceneControl.h"

namespace
{
	template<class T, class... Args>
	void ChangeScene( Args... args )
	{
		SceneControl* pcSceneControl = GetSystem<SceneControl>();
		if( pcSceneControl == nullptr )
		{
			return;
		}

		pcSceneControl->ChangeScene<T>( args... );
	}
}