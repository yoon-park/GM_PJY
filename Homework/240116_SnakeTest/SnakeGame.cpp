// [SnakeGame/SnakeGame.cpp]
#include <iostream>

#include <ConsoleEngine/EngineCore.h>
#include "Head.h"
#include "BodyManager.h"
#include "GlobalValue.h"

int main()
{
    EngineCore EngineCore;
    EngineCore.Init({ 10, 10 });

    {
        GBodyManager = EngineCore.CreateManager<BodyManager>(0);
    }

    {
        Head* NewPlayer = EngineCore.CreateObject<Head>();
        NewPlayer->SetPos({ EngineCore.Screen.GetScreenX() / 2, EngineCore.Screen.GetScreenY() - 2 });
    }

    EngineCore.Start();
}