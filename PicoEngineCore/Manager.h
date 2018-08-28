#pragma once
#include <algorithm>
#include <cassert>
#include "PicoEngineCore/Util/ClassID.h"
#include "PicoEngineCore/Util/Singleton.h"
#include "PicoEngineCore/Util/Mutex.h"
#include "PicoEngineCore/Util/List.h"
#include "PicoEngineCore/Util/Util.h"
#include "PicoEngineCore/System/System.h"
namespace PicoEngine
{
	class Manager final
	{
		friend Singleton<Manager>;

	private:
		Manager()
			: m_pcSystemMap()
			, m_mutexSystemMap()
			, m_stRegisterSystemQue()
			, m_mutexRegisterSystemQue()
		{
		}
		~Manager()
		{
			lock_guard<shared_mutex> lock1( m_mutexSystemMap );
			lock_guard<shared_mutex> lock2( m_mutexRegisterSystemQue );
			for( auto& rstPair : m_pcSystemMap )
			{
				SafeDelete( rstPair.second );
			}
			m_pcSystemMap.clear();

			for( auto& rstPair : m_stRegisterSystemQue )
			{
				SafeDelete( rstPair.second );
			}
			m_stRegisterSystemQue.clear();
		}

	public:

		void MainLoop()
		{
			{
				lock_guard<shared_mutex> lock1( m_mutexSystemMap );
				lock_guard<shared_mutex> lock2( m_mutexRegisterSystemQue );
				while( !m_stRegisterSystemQue.empty() )
				{
					auto& rstPair = m_stRegisterSystemQue.front();
					
					auto itFind = m_pcSystemMap.find( rstPair.first );
					assert( itFind == m_pcSystemMap.end() );
					if( itFind == m_pcSystemMap.end() )
					{
						m_pcSystemMap.insert( rstPair );
					}
					else
					{
						SafeDelete( rstPair.second );	// failsafe
					}

					m_stRegisterSystemQue.pop_front();
				}
			}

			{
				shared_lock<shared_mutex> lock( m_mutexSystemMap );
				std::for_each( m_pcSystemMap.begin(), m_pcSystemMap.end(),
					[]( auto& rstPair )
					{
						if( rstPair.second )
						{
							rstPair.second->LoopFirst();
						}
					}
				);

				std::for_each( m_pcSystemMap.begin(), m_pcSystemMap.end(),
					[]( auto& rstPair )
					{
						if( rstPair.second )
						{
							rstPair.second->LoopMiddle();
						}
					}
				);

				std::for_each( m_pcSystemMap.begin(), m_pcSystemMap.end(),
					[]( auto& rstPair )
					{
						if( rstPair.second )
						{
							rstPair.second->LoopLast();
						}
					}
				);
			}

		}

		template<class T, class... Args>
		void RegisterSystem( Args&&... args )
		{
			lock_guard<shared_mutex> lock( m_mutexSystemMap );

			const ClassIDType id = ClassID<T>::Get();
			auto itFind = m_pcSystemMap.find( id );
			assert( itFind == m_pcSystemMap.end() );
			if( itFind == m_pcSystemMap.end() )
			{
				m_pcSystemMap[id] = new T( args... );
			}
		}

		template<class T, class... Args>
		void RequestRegisterSystem( Args&&... args )
		{
			lock_guard<shared_mutex> lock( m_mutexRegisterSystemQue );
			m_stRegisterSystemQue.emplace_back( std::make_pair( ClassID<T>::Get(), new T( args... ) ) );
		}

		template<class T>
		T* GetSystem()
		{
			shared_lock<shared_mutex> lock( m_mutexSystemMap );

			const ClassIDType id = ClassID<T>::Get();
			auto itFind = m_pcSystemMap.find( id );
			return itFind == m_pcSystemMap.end() ? nullptr : static_cast<T*>( itFind->second );
		}

	private:
		unorderd_map<ClassIDType, ISystem*> m_pcSystemMap;
		shared_mutex m_mutexSystemMap;

		deque< std::pair<ClassIDType, ISystem*> > m_stRegisterSystemQue;
		shared_mutex m_mutexRegisterSystemQue;
	};

	template<class T>
	T* GetSystem()
	{
		Manager* pcManager = Singleton<Manager>::GetInstance();
		if( pcManager == nullptr )
		{
			return nullptr;
		}

		return pcManager->GetSystem<T>();
	}
}
