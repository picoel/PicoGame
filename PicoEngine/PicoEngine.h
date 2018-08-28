#pragma once

namespace PicoEngine
{
	class Manager final
	{
		friend Singleton<Manager>;

	private:
		Manager()
			: m_pcSystemMap()
			, m_mutexSystemMap()
		{
			AddSystem<DeltaTime>();
			Singleton<GameObjectControl>::CreateInstance();

		}
		~Manager()
		{
			for( auto& rpcSystem : m_pcSystemMap )
			{

				delete rpcSystem.second;
			}
			m_pcSystemMap.clear();
			Singleton<GameObjectControl>::DestoryInstance();
		}

	public:

		void MainLoop()
		{
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
			}

			{
				GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
				if( pcControl )
				{
					pcControl->Update();
				}
			}

			{
				shared_lock<shared_mutex> lock( m_mutexSystemMap );
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
		void AddSystem( Args&&... args )
		{
			lock_guard<shared_mutex> lock( m_mutexSystemMap );

			const ClassIDType id = ClassID<T>::Get();
			auto itFind = m_pcSystemMap.find( id );
			assert( itFind == m_pcSystemMap.end() );
			if( itFind != m_pcSystemMap.end() )
			{
				SafeDelete( itFind->second );
			}

			m_pcSystemMap[id] = new T( args... );
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
	};

	float64 GetDeltaTime()
	{
		Manager* pcManager = Singleton<Manager>::GetInstance();
		if( pcManager == nullptr )
		{
			return 0.0f;
		}

		const DeltaTime* pcDelta = pcManager->GetSystem<DeltaTime>();
		if( pcDelta == nullptr )
		{
			return 0.0f;
		}

		return pcDelta->GetDeltaTime();
	}
}
