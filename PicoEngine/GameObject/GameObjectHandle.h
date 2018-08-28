#pragma once

namespace PicoEngine
{
	class GameObject;

	template<class T>
	class GameObjectHandle
	{
	public:
		GameObjectHandle( T* _pcObj )
			: m_pcObj( _pcObj )
		{
		}

		GameObjectHandle( const GameObjectHandle<T>& _rcSrc )
			: m_pcObj( _rcSrc.m_pcObj )
		{
		}

		~GameObjectHandle()
		{
		}

		void Invalid()
		{
			m_pcObj = nullptr;
		}

		T* operator->()
		{
			return m_pcObj;
		}

		const T* operator->() const
		{
			return m_pcObj;
		}

		T* operator*()
		{
			return m_pcObj;
		}

		const T* operator*() const
		{
			return m_pcObj;
		}

	private:
		T* m_pcObj;
	};
}