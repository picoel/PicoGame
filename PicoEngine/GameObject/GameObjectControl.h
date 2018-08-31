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
			lock_guard<shared_mutex> lock( m_mutexObjList );
			for( auto& rpcObj : m_pcObjList )
			{
				SafeDelete( rpcObj );
			}
		}

	public:
		void AddRequestGameObject( GameObject* _pObj )
		{
			lock_guard<mutex> lock( m_mutexAddObjQue );
			m_pcAddObjQue.push_back( _pObj );
		}

		void RemoveRequestObject( GameObject* _pObj )
		{
			lock_guard<mutex> lock( m_mutexDelObjQue );
			_pObj->SetMarkDelete();
			m_pcDelObjQue.push_back( _pObj );
		}

		virtual void LoopFirst() override {}

		virtual void LoopMiddle() override
		{
			DeleteObject();
			AddObject();

			{
				shared_lock<shared_mutex> lock( m_mutexObjList );
				for( auto& rpcObj : m_pcObjList )
				{
					if( rpcObj->IsMarkedDelete() )
					{
						continue;
					}

					rpcObj->Update();
				}
			}
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

			bool bDeleted = false;
			while( !m_pcDelObjQue.empty() )
			{
				GameObject* pcObj = m_pcDelObjQue.front();
				m_pcDelObjQue.pop_front();
				m_pcObjList.remove( pcObj );
				SafeDelete( pcObj );

				bDeleted = true;
			}

			if( bDeleted )
			{
				m_pcObjList.remove( nullptr );
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