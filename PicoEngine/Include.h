#pragma once

#include <algorithm>
#include <cassert>
#include <functional>

#include "PicoEngineCore/Util/Type.h"
#include "PicoEngineCore/Util/Util.h"
#include "PicoEngineCore/Util/ClassID.h"

#include "PicoEngineCore/Math/Random.h"

#include "PicoEngine/Memory/Allocator.h"

#include "PicoEngineCore/Util/List.h"
#include "PicoEngineCore/Util/Mutex.h"
#include "PicoEngineCore/Util/Singleton.h"

#include "PicoEngineCore/System/System.h"

#include "PicoEngine/Component/Component.h"
#include "PicoEngine/Component/ComponentLink.h"

#include "PicoEngine/GameObject/GameObject.h"
#include "PicoEngine/GameObject/GameObjectHandle.h"
#include "PicoEngine/GameObject/GameObjectControl.h"
#include "PicoEngine/GameObject/GameObjectFunc.h"

#include "PicoEngine/Scene/Scene.h"
#include "PicoEngine/Scene/SceneControl.h"
#include "PicoEngine/Scene/SceneFunc.h"

#include "PicoEngine/Thread/WorkerThread.h"

#include "PicoEngine/System/Time.h"

#include "PicoEngineCore/Manager.h"