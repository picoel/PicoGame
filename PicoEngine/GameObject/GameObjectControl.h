#pragma once
#include "PicoEngine/Util/List.h"
#include "PicoEngine/Util/Mutex.h"
#include "PicoEngine/Util/Singleton.h"
#include "PicoEngine/GameObject/GameObject.h"

namespace PicoEngine
{
	class GameObjectControl
	{
		friend Singleton<GameObjectControl>;

	private:
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
				delete rpcObj;
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

		void Update()
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
				delete pcObj;
			}
		}

	private:
		list<GameObject*> m_pcObjList;

		deque<GameObject*> m_pcAddObjQue;
		mutex m_mutexAddObjQue;

		deque<GameObject*> m_pcDelObjQue;
		mutex m_mutexDelObjQue;
	};

	template<class T, class... Args>
	T* CreateGameObject(Args... args)
	{
		T* ret = new T( args... );

		GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
		if( pcControl )
		{
			pcControl->AddRequestGameObject( ret );
		}

		return ret;
	}

	template<class T>
	bool DestoryGameObject( T* _obj )
	{
		if( _obj == nullptr )
		{
			return false;
		}

		GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
		if( pcControl )
		{
			pcControl->RemoveRequestObject( _obj );
		}

		return true;
	}

	template<class T>
	bool SafeDestroyGameObject( T*& _obj )
	{
		DestoryGameObject( _obj );
		_obj = nullptr;
		return true;
	}
}