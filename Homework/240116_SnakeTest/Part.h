// [SnakeGame/Part.h]
#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:
	inline int2 GetDir()
	{
		return Dir;
	}

	inline int2 GetPrevDir()
	{
		return PrevDir;
	}

	inline int2 GetPrevPos()
	{
		return PrevPos;
	}

protected:
	// <°úÁ¦>
	int2 Dir;
	int2 PrevDir;
	int2 PrevPos;

	inline void SetDir(int2 _Dir)
	{
		Dir.X = _Dir.X;
		Dir.Y = _Dir.Y;
	}
};