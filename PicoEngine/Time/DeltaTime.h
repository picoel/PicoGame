#pragma once
#include <chrono>

namespace PicoEngine
{
	class DeltaTime : public ISystem
	{
	public:
		DeltaTime()
			: ISystem()
			, m_preTime( std::chrono::system_clock::now() )
			, m_deltaTime( 0.0f )
		{
		}
		virtual ~DeltaTime()
		{
		}

		virtual void LoopFirst() override
		{
			const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			const uint64 micro = std::chrono::duration_cast<std::chrono::microseconds>( now - m_preTime ).count();
			m_deltaTime = static_cast<float64>(micro) / ( 1000 * 1000 );
			m_preTime = now;
		}

		virtual void LoopLast() override {}

		float64 GetDeltaTime() const { return m_deltaTime; }

	private:
		std::chrono::system_clock::time_point m_preTime;
		float64 m_deltaTime;
	};
}