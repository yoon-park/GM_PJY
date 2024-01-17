// [ConsoleEngine/ConsoleObject.h]
#pragma once
#include "ConsoleMath.h"
#include "ConsoleUpdater.h"

class ConsoleObject : public ConsoleUpdater
{
	friend class EngineCore;

public:
	ConsoleObject();
	ConsoleObject(const int2& _StartPos, char _RenderChar);
	virtual ~ConsoleObject();

	int2 GetPos() const;
	char GetRenderChar() const;

	inline void SetPos(const int2& _Pos)
	{
		Pos = _Pos;
	}

	inline void AddPos(const int2& _Dir)
	{
		Pos += _Dir;
	}

	inline void SetRenderChar(char _Ch)
	{
		RenderChar = _Ch;
	}

	template<typename EnumType>
	ConsoleObject* Collision(EnumType _UpdateOrder)
	{
		return Collision(static_cast<int>(_UpdateOrder));
	}

	ConsoleObject* Collision(int _UpdateOrder);

protected:

private:
	int2 Pos = { 0, 0 };
	char RenderChar = '@';
};