// PicoGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "PicoEngine/PicoEngine.h"
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
		std::cout << GetDeltaTime() << std::endl;
	}

private:
	std::uint32_t m_count;
};

int main()
{
	Singleton<Manager>::CreateInstance();
	Manager* pcManager = Singleton<Manager>::GetInstance();

	TestObject* pcObj = CreateGameObject<TestObject>( "Test", ClassID<TestObject>::Get() );
	while( true )
	{
		pcManager->MainLoop();
	}
    return 0;
}

