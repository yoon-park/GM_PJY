#pragma once
#include <Windows.h>
#include <assert.h>

// memory leak check
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

// �޼����ڽ� �˾�, ���α׷� ���� �ߴ�
#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "ġ���� ����", MB_OK); assert(false);