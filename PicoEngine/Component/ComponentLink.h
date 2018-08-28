#pragma once

namespace PicoEngine
{
	class ComponentLink
	{
	public:
		ComponentLink() : ComponentLink( nullptr ){}

	private:
		ComponentLink( IComponent* _pcComponent )
			: m_pcComponent( _pcComponent )
			, m_pcChildLinkMap()
			, m_mutexChildLinkMap()
		{
		}

	public:
		~ComponentLink()
		{
			SafeDelete( m_pcComponent );
			for( auto& rpcLink : m_pcChildLinkMap )
			{
				SafeDelete( rpcLink.second );
			}
			m_pcChildLinkMap.clear();
		}

		IComponent* GetComponent() const { return m_pcComponent; }

		template<class T, class... Args>
		bool AddChild( Args&&... args )
		{
			lock_guard<shared_mutex> lock( m_mutexChildLinkMap );

			const ClassIDType id = ClassID<T>::Get();
			auto itFind = m_pcChildLinkMap.find( id );
			assert( itFind == m_pcChildLinkMap.end() );
			if( itFind != m_pcChildLinkMap.end() )
			{
				SafeDelete( itFind->second );
			}
			m_pcChildLinkMap[id] = new ComponentLink( new T( args... ) );

			return true;
		}

		template<class T>
		ComponentLink* GetChild() const
		{
			shared_lock<shared_mutex> lock( m_mutexChildLinkMap );
			
			const ClassIDType id = ClassID<T>::Get();
			auto itFind = m_pcChildLinkMap.find( id );
			return itFind == m_pcChildLinkMap.end() ? nullptr : itFind->second;
		}

	private:
		IComponent* m_pcComponent;
		const ComponentLink* m_pcParentLink;
		unorderd_map<ClassIDType, ComponentLink*> m_pcChildLinkMap;
		shared_mutex m_mutexChildLinkMap;
	};
}