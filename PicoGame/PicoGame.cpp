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
	{
		std::cout << "TestObject" << _string << _value << std::endl;
	}
	virtual ~TestObject()
	{
		std::cout << "Destory TestObject" << std::endl;
	}

	virtual void Update() override
	{
		std::cout << GetDeltaTime() << std::endl;
	}
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

