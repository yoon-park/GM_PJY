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
		MsgBoxAssert("��ũ���� X ũ�Ⱑ 0�̱� ������ �ֽܼ�ũ���� ������ �� �����ϴ�.");
	}

	if (_ScreenY <= 0)
	{
		MsgBoxAssert("��ũ���� Y ũ�Ⱑ 0�̱� ������ �ֽܼ�ũ���� ������ �� �����ϴ�.");
	}

	ScreenX = _ScreenX;
	ScreenY = _ScreenY;

	if (ScreenData.size() != 0)
	{
		MsgBoxAssert("�̹� �ֽܼ�ũ���� �����Ͽ� ��ũ�� ������ �����߽��ϴ�.");
	}

	ScreenData.resize(ScreenY);

	if (ScreenData.size() == 0)
	{
		MsgBoxAssert("��ũ�� ������ �����߽��ϴ�. if (ScreenData == nullptr)");
	}

	for (int y = 0; y < ScreenY; y++)
	{
		ScreenData[y].resize(ScreenX + 2);

		if (ScreenData[y].size() == 0)
		{
			MsgBoxAssert("��ũ�� ������ �����߽��ϴ�. if (ScreenData[y] == nullptr)");
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
			MsgBoxAssert("�������� ���� ������ ����Ϸ��� �߽��ϴ�");
		}

		std::vector<char>& Vector = ScreenData[y];
		char& FirstChar = Vector[0];
		char* PrintPtr = &FirstChar;
		printf_s(PrintPtr);
	}

	ClearScreen();
}