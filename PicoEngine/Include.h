#pragma once

#include <algorithm>
#include <cassert>
#include <functional>

#include "PicoEngine/Util/Type.h"
#include "PicoEngine/Util/ClassID.h"

#include "PicoEngine/Memory/MemoryFunc.h"
#include "PicoEngine/Memory/Allocator.h"

#include "PicoEngine/Util/List.h"
#include "PicoEngine/Util/Mutex.h"
#include "PicoEngine/Util/Singleton.h"

#include "PicoEngine/System/System.h"

#include "PicoEngine/Component/Component.h"
#include "PicoEngine/Component/ComponentLink.h"

#include "PicoEngine/GameObject/GameObject.h"
#include "PicoEngine/GameObject/GameObjectHandle.h"
#include "PicoEngine/GameObject/GameObjectControl.h"
#include "PicoEngine/GameObject/GameObjectFunc.h"

#include "PicoEngine/Time/DeltaTime.h"

#include "PicoEngine/PicoEngine.h"