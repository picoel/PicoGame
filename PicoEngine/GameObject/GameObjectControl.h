#pragma once
#include "PicoEngineCore/System/System.h"

namespace PicoEngine
{
	class GameObjectControl : public ISystem
	{
	public:
		GameObjectControl()
			: m_pcObjList()
			, m_pcAddObjQue()
			, m_mutexAddObjQue()
			, m_pcDelObjQue()
			, m_mutexDelObjQue()
		{
		}
		virtual ~GameObjectControl()
		{
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

			m_pcObjList.remove( nullptr );
			for( auto& rpcObj : m_pcObjList )
			{
				if( rpcObj->IsMarkedDelete() )
				{
					continue;
				}

				rpcObj->Update();
			}
		}

		virtual void LoopLast() override {}

	private:
		void AddObject()
		{
			lock_guard<mutex> lock( m_mutexAddObjQue );
			while( !m_pcAddObjQue.empty() )
			{
				GameObject* pcObj = m_pcAddObjQue.front();
				m_pcAddObjQue.pop_front();
				m_pcObjList.push_back( pcObj );
			}
		}

		void DeleteObject()
		{
			lock_guard<mutex> lock( m_mutexDelObjQue );
			while( !m_pcDelObjQue.empty() )
			{
				GameObject* pcObj = m_pcDelObjQue.front();
				m_pcDelObjQue.pop_front();
				m_pcObjList.remove( pcObj );
				SafeDelete( pcObj );
			}
		}

	private:
		list<GameObject*> m_pcObjList;

		deque<GameObject*> m_pcAddObjQue;
		mutex m_mutexAddObjQue;

		deque<GameObject*> m_pcDelObjQue;
		mutex m_mutexDelObjQue;
	};
}