#pragma once

namespace PicoEngine
{
	class GameObject
	{
	public:
		GameObject()
			: m_bMarkDelete( false )
		{
		}
		virtual ~GameObject(){}

		virtual void Update(){}

		void SetMarkDelete(){ m_bMarkDelete = true; }
		bool IsMarkedDelete() const{ return m_bMarkDelete; }

		bool m_bMarkDelete;
	};
}