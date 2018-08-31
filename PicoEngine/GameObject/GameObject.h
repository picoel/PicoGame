#pragma once

namespace PicoEngine
{
	class GameObject
	{
	public:
		GameObject()
			: m_bDestroyed( false )
		{
		}
		virtual ~GameObject(){}

		virtual void Update(){}

		virtual void Destory(){}
		void SetDestroyed(){ m_bDestroyed = true; }
		bool IsDestroyed() const{ return m_bDestroyed; }

	private:
		bool m_bDestroyed;
	};

	static inline void DestroyGameObject( GameObject* _rpcObj )
	{
		if( _rpcObj == nullptr )
		{
			return;
		}

		if( !_rpcObj->IsDestroyed() )
		{
			_rpcObj->Destory();
			_rpcObj->SetDestroyed();
		}
	}

	static inline void SafeDeleteGameObject( GameObject*& _rpcObj )
	{
		if( _rpcObj == nullptr )
		{
			return;
		}

		DestroyGameObject( _rpcObj );
		SafeDelete( _rpcObj );
	}
}