// [ConsoleEngine/ConsoleScreen.h]
#pragma once
#include <vector>

#include "EngineDebug.h"
#include "ConsoleMath.h"

class ConsoleScreen
{
public:
	ConsoleScreen();
	virtual ~ConsoleScreen();

	inline int GetScreenX()
	{
		return ScreenX;
	}

	inline int GetScreenY()
	{
		return ScreenY;
	}

	void SetChar(const class ConsoleObject& _Object);
	void SetChar(const class ConsoleObject* _Object);
	void SetChar(const int2& _Pos, char _Char);

	void CreateScreen(int _ScreenX, int _ScreenY);
	void ReleaseScreen();
	void ClearScreen();
	void PrintScreen();

protected:

private:
	int ScreenX = -1;
	int ScreenY = -1;

	std::vector<std::vector<char>> ScreenData;
};