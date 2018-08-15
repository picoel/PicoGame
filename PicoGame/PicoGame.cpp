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
	{
		std::cout << "TestObject" << _string << _value << std::endl;
	}
	virtual ~TestObject()
	{
		std::cout << "Destory TestObject" << std::endl;
	}
};

int main()
{
	TestObject* pcObj = CreateGameObject<TestObject>( "Test", ClassID<TestObject>::Get() );
	DestoryGameObject( pcObj );
    return 0;
}

