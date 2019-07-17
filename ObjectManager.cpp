#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"

void ObjectManager::Update()
{
	renderList.clear();

	for (auto iter = objectList.begin(); iter != objectList.end();)
	{
		GameObject* object = *iter;

		if (object->isDie == true)
		{
			object->Destroy();
			SAFE_DELETE(object);

			iter = objectList.erase(iter);
		}
		else
		{
			if (object->isActive == true)
			{
				object->Update();
			
				if (object->isDisplay)
				{
					renderList.push_back(object);
				}
			}

			iter++;
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : renderList)
	{
		iter->Render();
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
		iter->Destroy();
		SAFE_DELETE(iter);
	}

	objectList.clear();
	renderList.clear();
}
