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
		RequestTask<void>( 
			[]()
			{
				uint64 rand = GetRandRangeInt( 1, 100 );
				std::this_thread::sleep_for( std::chrono::milliseconds( rand ) );
				CreateGameObject<TestObject>(); 
			} 
		);
		SuicideGameObject( this );
	}
};

class TestScene : public IScene
{
public:
	TestScene()
		: IScene()
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
	}

	virtual void Finalize() override
	{
		DestroyAllGameObject();
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

