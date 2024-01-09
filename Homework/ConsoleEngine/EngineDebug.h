#pragma once
#include <Windows.h>
#include <assert.h>

// memory leak check
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

// 메세지박스 팝업, 프로그램 강제 중단
#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "치명적 에러", MB_OK); assert(false);