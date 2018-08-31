// PicoGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace PicoEngine;

namespace
{
	std::string strTest( "Test" );
}

class TestObject : public GameObject
{
public:
	TestObject()
	{
	}
	virtual ~TestObject()
	{
	}

	virtual void Update() override
	{
	}
};

class TestScene : public IScene
{
public:
	TestScene()
		: IScene()
		, m_uCount( 0 )
	{
	}
	virtual ~TestScene(){}

	virtual void Initialize() override
	{
		for( uint64 ii = 0; ii < 100; ++ii )
		{
			CreateGameObject<TestObject>();
		}
	}

	virtual void Update() override
	{
		std::cout << "Delta Time, " << GetDeltaTime() << std::endl;

		++m_uCount;
		if( 10 < m_uCount )
		{
			ChangeScene<TestScene>();
		}
	}

	virtual void Finalize() override
	{
		DestroyAllGameObject();
	}

private:
	uint64 m_uCount;
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

