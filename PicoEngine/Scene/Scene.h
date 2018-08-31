#pragma once

namespace PicoEngine
{
	class IScene
	{
	protected:
		IScene(){}
	public:
		virtual ~IScene(){}

		virtual void Initialize() = 0;
		virtual void Update() = 0;
	};
}