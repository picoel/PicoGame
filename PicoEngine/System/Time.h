#pragma once
#include "PicoEngineCore/System/System.h"
#include "PicoEngineCore/Util/Type.h"

#include <chrono>

namespace PicoEngine
{
	template<class Duration>
	static inline real64 ConvertToSecond( uint64 _time )
	{
		static_assert( false, "undefined template." );
		return static_cast<real64>( _time );
	}

	template<>
	static inline real64 ConvertToSecond<std::chrono::seconds>( uint64 _time )
	{
		return static_cast<real64>( _time );
	}

	template<>
	static inline real64 ConvertToSecond<std::chrono::milliseconds>( uint64 _time )
	{
		return static_cast<real64>( _time ) / 1000.0f;
	}

	template<>
	static inline real64 ConvertToSecond<std::chrono::microseconds>( uint64 _time )
	{
		return static_cast<real64>( _time ) / ( 1000.0f * 1000.0f );
	}

	template<>
	static inline real64 ConvertToSecond<std::chrono::nanoseconds>( uint64 _time )
	{
		return static_cast<real64>( _time ) / ( 1000.0f * 1000.0f * 1000.0f );
	}

	class Time : public ISystem
	{
	public:
		Time()
			: ISystem()
			, m_tpStartup( std::chrono::system_clock::now() )
			, m_tpPreLoopFirst( m_tpStartup )
			, m_tpLoopFirst( m_tpStartup )
		{
		}

		virtual ~Time(){}

		virtual void LoopFirst() override
		{
			m_tpPreLoopFirst = m_tpLoopFirst;
			m_tpLoopFirst = std::chrono::system_clock::now();
		}

		virtual void LoopMiddle() override {}
		virtual void LoopLast() override {}

		template<class Duration>
		real64 GetDeltaTime() const
		{
			const uint64 delta = std::chrono::duration_cast<Duration>( m_tpLoopFirst - m_tpPreLoopFirst ).count();
			return ConvertToSecond<Duration>( delta );
		}

	private:
		std::chrono::system_clock::time_point m_tpStartup;
		std::chrono::system_clock::time_point m_tpPreLoopFirst;
		std::chrono::system_clock::time_point m_tpLoopFirst;
	};
}