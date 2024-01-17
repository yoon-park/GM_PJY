// [SnakeGame/Head.cpp]
#include "Head.h"

#include <conio.h>

#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

/*
<����>
1. �̹� �Է� �� Ư�� �������� �̵��ߴٸ�, ���� �Է� ���� �� ������
   ���ݴ� �������� �̵��� �� ����.
2. CurBody�� ȹ���ߴٸ�, �� �������� �� Body�� Head�� ����´�.
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

	// <����>
	if (Dir == (PrevDir * -1))
	{
		return;
	}

	AddPos(Dir);

	PrevDir = Dir;

	// <����>
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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	// <����>
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