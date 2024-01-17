// [SnakeGame/Head.cpp]
#include "Head.h"

#include <conio.h>

#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

/*
<과제>
1. 이번 입력 때 특정 방향으로 이동했다면, 다음 입력 때는 그 방향의
   정반대 방향으로 이동할 수 없다.
2. CurBody를 획득했다면, 그 다음부터 그 Body는 Head를 따라온다.
*/

void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	PrevPos = GetPos();

	int Select = _getch();

	switch (Select)
	{
	case 'A':
	case 'a':
		Dir = Left;
		break;
	case 'S':
	case 's':
		Dir = Down;
		break;
	case 'W':
	case 'w':
		Dir = Up;
		break;
	case 'D':
	case 'd':
		Dir = Right;
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	// <과제>
	if (Dir == (PrevDir * -1))
	{
		return;
	}

	AddPos(Dir);

	PrevDir = Dir;

	// <과제>
	for (int i = 0; i < Tail.size(); i++)
	{
		Tail[i]->PrevPos = Tail[i]->GetPos();
		Tail[i]->PrevDir = Tail[i]->GetDir();

		if (i == 0)
		{
			Tail[i]->SetPos(GetPrevPos());
			Tail[i]->SetDir(GetPrevDir());
		}
		else
		{
			Tail[i]->SetPos(Tail[i - 1]->GetPrevPos());
			Tail[i]->SetDir(Tail[i - 1]->GetPrevDir());
		}
	}

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	// <과제>
	if (CurBody->GetPos() == GetPos())
	{
		Tail.push_back(CurBody);
		CurBody->SetRenderChar('@');

		if (Tail.size() <= 1)
		{
			CurBody->SetPos(GetPos() - GetPrevDir());
		}
		else
		{
			CurBody->SetPos((Tail[Tail.size() - 2]->GetPos()) - (Tail[Tail.size() - 2]->GetPrevDir()));
		}

		BodyManager::ResetBody();
	}
}