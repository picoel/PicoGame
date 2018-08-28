#pragma once

namespace PicoEngine
{
	class IComponent
	{
	public:
		IComponent(){}
		virtual ~IComponent(){}

		virtual void Update() = 0;
	};


}
