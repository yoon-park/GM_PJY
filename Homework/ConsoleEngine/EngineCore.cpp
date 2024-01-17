// [ConsoleEngine/EngineCore.cpp]
#include "EngineCore.h"

#include "EngineDebug.h"
#include "time.h"

void EngineCore::Init(int2 _ScreenSize)
{
    LeakCheck;

    Screen.CreateScreen(_ScreenSize.X, _ScreenSize.Y);
    srand(time(0));
}

void EngineCore::Start()
{
    while (EngineUpdate)
    {
        Sleep(100);

        {
            std::map<int, ConsoleUpdater*>::iterator OrderStartIter = AllManager.begin();
            std::map<int, ConsoleUpdater*>::iterator OrderEndIter = AllManager.end();
            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                ConsoleUpdater* Object = OrderStartIter->second;
                if (nullptr == Object)
                {
                    MsgBoxAssert("������Ʈ�� nullptr�� ��찡 �����մϴ�.");
                }

                Object->Update();
            }
        }

        // ������Ʈ
        {
            std::map<int, std::list<ConsoleObject*>>::iterator OrderStartIter = AllUpdateObject.begin();
            std::map<int, std::list<ConsoleObject*>>::iterator OrderEndIter = AllUpdateObject.end();

            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                std::list<ConsoleObject*>& ObjectList = OrderStartIter->second;

                std::list<ConsoleObject*>::iterator StartIter = ObjectList.begin();
                std::list<ConsoleObject*>::iterator EndIter = ObjectList.end();
                for (; StartIter != EndIter; ++StartIter)
                {
                    ConsoleObject* Object = *StartIter;

                    if (nullptr == Object)
                    {
                        MsgBoxAssert("������Ʈ�� nullptr�� ��찡 �����մϴ�.");
                    }

                    Object->Update();
                }
            }
        }

        // ������
        {
            std::map<int, std::list<ConsoleObject*>>::iterator OrderStartIter = AllRenderObject.begin();
            std::map<int, std::list<ConsoleObject*>>::iterator OrderEndIter = AllRenderObject.end();

            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                std::list<ConsoleObject*>& ObjectList = OrderStartIter->second;

                std::list<ConsoleObject*>::iterator StartIter = ObjectList.begin();
                std::list<ConsoleObject*>::iterator EndIter = ObjectList.end();
                for (; StartIter != EndIter; ++StartIter)
                {
                    ConsoleObject* Object = *StartIter;

                    if (nullptr == Object)
                    {
                        MsgBoxAssert("������Ʈ�� nullptr�� ��찡 �����մϴ�.");
                    }

                    Screen.SetChar(Object);
                }
            }
        }

        Screen.PrintScreen();

        //// ���� ������ ����
        {
            std::map<int, std::list<ConsoleObject*>>::iterator OrderStartIter = AllRenderObject.begin();
            std::map<int, std::list<ConsoleObject*>>::iterator OrderEndIter = AllRenderObject.end();

            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                std::list<ConsoleObject*>& ObjectList = OrderStartIter->second;

                std::list<ConsoleObject*>::iterator StartIter = ObjectList.begin();
                std::list<ConsoleObject*>::iterator EndIter = ObjectList.end();

                for (; StartIter != EndIter; )
                {
                    ConsoleObject* Object = *StartIter;

                    if (false == Object->IsPendingKill())
                    {
                        ++StartIter;
                        continue;
                    }

                    if (nullptr == Object)
                    {
                        MsgBoxAssert("������Ʈ�� nullptr�� ��찡 �����մϴ�.");
                    }

                    StartIter = ObjectList.erase(StartIter);
                }
            }
        }

        //// ������Ʈ ������ ����
        {
            std::map<int, std::list<ConsoleObject*>>::iterator OrderStartIter = AllUpdateObject.begin();
            std::map<int, std::list<ConsoleObject*>>::iterator OrderEndIter = AllUpdateObject.end();

            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                std::list<ConsoleObject*>& ObjectList = OrderStartIter->second;

                std::list<ConsoleObject*>::iterator StartIter = ObjectList.begin();
                std::list<ConsoleObject*>::iterator EndIter = ObjectList.end();

                for (; StartIter != EndIter; )
                {
                    ConsoleObject* Object = *StartIter;

                    if (false == Object->IsPendingKill())
                    {
                        ++StartIter;
                        continue;
                    }

                    if (nullptr == Object)
                    {
                        MsgBoxAssert("������Ʈ�� nullptr�� ��찡 �����մϴ�.");
                    }

                    delete Object;
                    Object = nullptr;

                    StartIter = ObjectList.erase(StartIter);
                }
            }
        }
    }

    {
        {
            std::map<int, std::list<ConsoleObject*>>::iterator OrderStartIter = AllUpdateObject.begin();
            std::map<int, std::list<ConsoleObject*>>::iterator OrderEndIter = AllUpdateObject.end();

            for (; OrderStartIter != OrderEndIter; ++OrderStartIter)
            {
                std::list<ConsoleObject*>& ObjectList = OrderStartIter->second;

                std::list<ConsoleObject*>::iterator StartIter = ObjectList.begin();
                std::list<ConsoleObject*>::iterator EndIter = ObjectList.end();

                for (; StartIter != EndIter; ++StartIter)
                {
                    ConsoleObject* Object = *StartIter;
                    if (nullptr != Object)
                    {
                        delete Object;
                        Object = nullptr;
                    }
                }
            }
        }

        AllUpdateObject.clear();
    }
}