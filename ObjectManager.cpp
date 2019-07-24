#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"

void ObjectManager::Update()
{
	for (auto iter = objectList.begin(); iter != objectList.end();)
	{
		GameObject* object = *iter;

		if (object->isDie == true)
		{
			object->Destroy();
			object->ComDestroy();

			SAFE_DELETE(object);

			iter = objectList.erase(iter);
		}
		else
		{
			if (object->isActive == true)
			{
				object->Update();
				object->ComUpdate();
			}

			iter++;
		}
	}
}

void ObjectManager::Reset()
{
	ClearObjectList();
}

void ObjectManager::ClearObjectList()
{
	for (auto iter : objectList)
	{
		iter->ComDestroy();
		iter->Destroy();
		SAFE_DELETE(iter);
	}

	objectList.clear();
}
