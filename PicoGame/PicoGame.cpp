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

class TestScene : public IScene
{
public:
	TestScene(){}
	virtual ~TestScene(){}

	virtual void Initialize() override
	{
		CreateGameObject<TestObject>( strTest, ClassID<TestObject>::Get() );
	}

	virtual void Update()
	{
	}
};

int main()
{
	Initialize();
	ChangeScene<TestScene>();

	Manager* pcManager = Singleton<Manager>::GetInstance();
	while( true )
	{
		pcManager->MainLoop();
	}

	Finalize();
    return 0;
}

