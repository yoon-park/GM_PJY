// [ConsoleEngine/ConsoleScreen.cpp]
#include "ConsoleScreen.h"

#include <iostream>
#include <conio.h>

#include "ConsoleObject.h"

ConsoleScreen::ConsoleScreen()
{

}

ConsoleScreen::~ConsoleScreen()
{
	ReleaseScreen();
}

void ConsoleScreen::SetChar(const ConsoleObject& _Object)
{
	SetChar(_Object.GetPos(), _Object.GetRenderChar());
}

void ConsoleScreen::SetChar(const ConsoleObject* _Object)
{
	SetChar(_Object->GetPos(), _Object->GetRenderChar());
}

void ConsoleScreen::SetChar(const int2& _Pos, char _Char)
{
	if (_Pos.X < 0)
	{
		return;
	}

	if (_Pos.Y < 0)
	{
		return;
	}

	if (_Pos.X >= ScreenX)
	{
		return;
	}

	if (_Pos.Y >= ScreenY)
	{
		return;
	}

	ScreenData[_Pos.Y][_Pos.X] = _Char;
}

void ConsoleScreen::CreateScreen(int _ScreenX, int _ScreenY)
{
	ReleaseScreen();

	if (_ScreenX <= 0)
	{
		MsgBoxAssert("스크린의 X 크기가 0이기 때문에 콘솔스크린을 생성할 수 없습니다.");
	}

	if (_ScreenY <= 0)
	{
		MsgBoxAssert("스크린의 Y 크기가 0이기 때문에 콘솔스크린을 생성할 수 없습니다.");
	}

	ScreenX = _ScreenX;
	ScreenY = _ScreenY;

	if (ScreenData.size() != 0)
	{
		MsgBoxAssert("이미 콘솔스크린이 존재하여 스크린 생성에 실패했습니다.");
	}

	ScreenData.resize(ScreenY);

	if (ScreenData.size() == 0)
	{
		MsgBoxAssert("스크린 생성에 실패했습니다. if (ScreenData == nullptr)");
	}

	for (int y = 0; y < ScreenY; y++)
	{
		ScreenData[y].resize(ScreenX + 2);

		if (ScreenData[y].size() == 0)
		{
			MsgBoxAssert("스크린 생성에 실패했습니다. if (ScreenData[y] == nullptr)");
		}
	}

	ClearScreen();
}

void ConsoleScreen::ReleaseScreen()
{
	ScreenData.clear();
}

void ConsoleScreen::ClearScreen()
{
	for (int y = 0; y < ScreenY; y++)
	{
		for (int x = 0; x < ScreenX; x++)
		{
			ScreenData[y][x] = '*';
		}
		ScreenData[y][ScreenX] = '\n';
	}
}

void ConsoleScreen::PrintScreen()
{
	system("cls");

	for (int y = 0; y < ScreenY; y++)
	{
		if (ScreenData[y].size() == 0)
		{
			MsgBoxAssert("존재하지 않은 라인을 출력하려고 했습니다");
		}

		std::vector<char>& Vector = ScreenData[y];
		char& FirstChar = Vector[0];
		char* PrintPtr = &FirstChar;
		printf_s(PrintPtr);
	}

	ClearScreen();
}