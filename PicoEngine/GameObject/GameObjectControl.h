#pragma once
#include "PicoEngineCore/System/System.h"

namespace PicoEngine
{
	class GameObjectControl : public ISystem
	{
	public:
		GameObjectControl()
			: m_pcObjList()
			, m_mutexObjList()
			, m_pcAddObjQue()
			, m_mutexAddObjQue()
			, m_pcDelObjQue()
			, m_mutexDelObjQue()
		{
		}
		virtual ~GameObjectControl()
		{
			RemoveAllObject();
		}

	public:
		void AddRequestGameObject( GameObject* _pObj )
		{
			assert( _pObj );
			if( _pObj == nullptr )
			{
				return;
			}

			lock_guard<mutex> lock( m_mutexAddObjQue );
			m_pcAddObjQue.push_back( _pObj );
		}

		void RemoveRequestObject( GameObject* _pObj )
		{
			assert( _pObj );
			if( _pObj == nullptr )
			{
				return;
			}

			lock_guard<mutex> lock( m_mutexDelObjQue );
			m_pcDelObjQue.push_back( _pObj );
		}

		bool RemoveAllObject()
		{
			lock_guard<shared_mutex> lock1( m_mutexObjList );
			lock_guard<mutex> lock2( m_mutexAddObjQue );
			lock_guard<mutex> lock3( m_mutexDelObjQue );

			for( auto& rpcObj : m_pcObjList )
			{
				SafeDeleteGameObject( rpcObj );
			}
			m_pcObjList.clear();

			for( auto& rpcObj : m_pcAddObjQue )
			{
				SafeDeleteGameObject( rpcObj );
			}
			m_pcAddObjQue.clear();

			m_pcDelObjQue.clear();

			return true;
		}

		virtual void LoopFirst() override {}

		virtual void LoopMiddle() override
		{
			DeleteObject();
			AddObject();
			UpdateObject();
		}

		virtual void LoopLast() override {}

		bool IsExistObject( const GameObject* _pcObj ) const
		{
			shared_lock<shared_mutex> lock( m_mutexObjList );
			const auto itFind = std::find( m_pcObjList.cbegin(), m_pcObjList.cend(), _pcObj );
			return itFind == m_pcObjList.cend() ? false : true;
		}

	private:
		void AddObject()
		{
			lock_guard<shared_mutex> lock1( m_mutexObjList );
			lock_guard<mutex> lock2( m_mutexAddObjQue );
			while( !m_pcAddObjQue.empty() )
			{
				GameObject* pcObj = m_pcAddObjQue.front();
				m_pcAddObjQue.pop_front();
				m_pcObjList.push_back( pcObj );
			}
		}

		void DeleteObject()
		{
			lock_guard<shared_mutex> lock1( m_mutexObjList );
			lock_guard<mutex> lock2( m_mutexDelObjQue );

			while( !m_pcDelObjQue.empty() )
			{
				GameObject* pcObj = m_pcDelObjQue.front();
				m_pcDelObjQue.pop_front();
				if( pcObj )
				{
					auto itFind = std::find( m_pcObjList.begin(), m_pcObjList.end(), pcObj );
					
					if( itFind != m_pcObjList.end() )
					{
						m_pcObjList.erase( itFind );
						SafeDeleteGameObject( pcObj );
					}
				}
			}
		}

		void UpdateObject()
		{
			shared_lock<shared_mutex> lock( m_mutexObjList );
			for( auto& rpcObj : m_pcObjList )
			{
				if( rpcObj->IsDestroyed() )
				{
					continue;
				}

				rpcObj->Update();
			}
		}

	private:
		list<GameObject*> m_pcObjList;
		mutable shared_mutex m_mutexObjList;

		deque<GameObject*> m_pcAddObjQue;
		mutable mutex m_mutexAddObjQue;

		deque<GameObject*> m_pcDelObjQue;
		mutable mutex m_mutexDelObjQue;
	};
}