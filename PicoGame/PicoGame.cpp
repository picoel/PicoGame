// PicoGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "PicoEngine/PicoEngine.h"

using namespace PicoEngine;

namespace
{
	std::string strTest( "Test" );
}

class TestObject : public GameObject
{
public:
	TestObject( const std::string& _string, ClassIDType _value )
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
		++m_count;
		std::cout << m_count << std::endl;
		if( m_count == 20 )
		{
			CreateGameObject<TestObject>( strTest, ClassID<TestObject>::Get() );
		}
		if( m_count == 30 )
		{
			SuicideGameObject( this );
		}
	}

private:
	std::uint32_t m_count;
};

int main()
{
	Initialize();
	Manager* pcManager = Singleton<Manager>::GetInstance();

	GameObjectHandle<TestObject> pcObj = CreateGameObject<TestObject>( strTest, ClassID<TestObject>::Get() );
	while( true )
	{
		pcManager->MainLoop();
	}

	Finalize();
    return 0;
}

