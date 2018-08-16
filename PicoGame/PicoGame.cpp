// PicoGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "PicoEngine/GameObject/GameObjectControl.h"
#include "PicoEngine/Util/ClassID.h"

using namespace PicoEngine;

class TestObject : public GameObject
{
public:
	TestObject( std::string _string, ClassIDType _value )
		: m_count(0)
	{
		std::cout << "TestObject" << _string << _value << std::endl;
	}
	virtual ~TestObject()
	{
		std::cout << "Destory TestObject" << std::endl;
	}

	virtual void Update() override
	{
		std::cout << "Frm :" << m_count << std::endl;
		++m_count;

		if( 30 < m_count )
		{
			DestoryGameObject( this );
		}
	}

private:
	std::uint32_t m_count;
};

int main()
{
	Singleton<GameObjectControl>::CreateInstance();
	GameObjectControl* pcControl = Singleton<GameObjectControl>::GetInstance();
	TestObject* pcObj = CreateGameObject<TestObject>( "Test", ClassID<TestObject>::Get() );
	while( true )
	{
		pcControl->Update();
	}
    return 0;
}

