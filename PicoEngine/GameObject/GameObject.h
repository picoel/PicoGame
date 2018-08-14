#pragma once

namespace PicoEngine
{
	class GameObject
	{
	public:
		GameObject(){}
		virtual ~GameObject(){}

		virtual void Update(){}
	};
}