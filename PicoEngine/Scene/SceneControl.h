#pragma once

#include "PicoEngineCore/System/System.h"
#include "PicoEngine/Scene/Scene.h"

#include <memory>

namespace PicoEngine
{
	class SceneControl : public ISystem
	{
	public:
		SceneControl()
		{
		}

		virtual ~SceneControl()
		{
			m_pcCurrent.reset();
			m_pcNext.reset();
		}

		virtual void LoopFirst() override
		{
			if( m_pcNext )
			{
				if( m_pcCurrent )
				{
					m_pcCurrent->Finalize();
					m_pcCurrent.reset();
				}
				m_pcCurrent = std::move( m_pcNext );
				m_pcCurrent->Initialize();
			}

			if( m_pcCurrent )
			{
				m_pcCurrent->Update();
			}
		}

		virtual void LoopMiddle(){}
		virtual void LoopLast(){}

		template<class T, class... Args>
		void ChangeScene( Args&&... args )
		{
			m_pcNext = std::make_unique<T>( args... );
		}

	private:
		std::unique_ptr<IScene> m_pcCurrent;
		std::unique_ptr<IScene> m_pcNext;
	};
}