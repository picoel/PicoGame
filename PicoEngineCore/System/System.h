#pragma once

namespace PicoEngine
{
	class ISystem
	{
	public:
		ISystem(){}
		virtual ~ISystem(){}

		virtual void LoopFirst() = 0;
		virtual void LoopMiddle() = 0;
		virtual void LoopLast() = 0;
	};
}
