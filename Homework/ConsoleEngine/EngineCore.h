// [ConsoleEngine/EngineCore.h]
#pragma once
#include <map>
#include <list>

#include "ConsoleScreen.h"
#include "ConsoleObject.h"

class EngineCore
{
	friend class ConsoleObject;

public:
	ConsoleScreen Screen = ConsoleScreen();

	void Init(int2 _ScreenSize);
	void Start();

	template<typename ObjectType, typename EnumType>
	ObjectType* CreateObject(EnumType _Order)
	{
		return CreateObject<ObjectType>(_Order, _Order);
	}

	template<typename ObjectType, typename UpdateEnumType, typename RenderEnumType>
	ObjectType* CreateObject(UpdateEnumType _UpdateOrder, RenderEnumType _RenderOrder)
	{
		return CreateObject<ObjectType>(static_cast<int>(_UpdateOrder), static_cast<int>(_RenderOrder));
	}

	template<typename ObjectType>
	ObjectType* CreateObject(int _UpdateOrder = 0, int _RenderOrder = 0)
	{
		ObjectType* NewObject = new ObjectType();
		NewObject->ConsoleUpdater::SetCore(this);
		AllUpdateObject[_UpdateOrder].push_back(NewObject);
		AllRenderObject[_RenderOrder].push_back(NewObject);
		return NewObject;
	}

	template<typename ObjectType>
	ObjectType* CreateManager(int _UpdateOrder)
	{
		if (true == AllManager.contains(_UpdateOrder))
		{
			MsgBoxAssert("�̹� �����ϴ� ������ �Ŵ����� �� ������� �߽��ϴ�.");
			return nullptr;
		}

		ObjectType* NewObject = new ObjectType();
		NewObject->ConsoleUpdater::SetCore(this);
		AllManager[_UpdateOrder] = NewObject;
		return NewObject;
	}

	void EngineEnd()
	{
		EngineUpdate = false;
	}

	template<typename EnumType>
	std::list<ConsoleObject*> GetUpdateGroup(EnumType _Order)
	{
		return GetUpdateGroup(static_cast<int>(_Order));
	}

	std::list<ConsoleObject*> GetUpdateGroup(int _Order = 0)
	{
		return AllUpdateObject[_Order];
	}

protected:


private:
	std::map<int, ConsoleUpdater*> AllManager;

	std::map<int, std::list<ConsoleObject*>> AllUpdateObject;
	std::map<int, std::list<ConsoleObject*>> AllRenderObject;
	bool EngineUpdate = true;
};