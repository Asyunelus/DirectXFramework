#include "stdafx.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Start()
{
}

void ObjectManager::Update(float DeltaTime)
{
	ObjectIO();
	for (auto iter = GameObjects.begin(); iter != GameObjects.end();) {
		if (not (*iter)->Active) {
			(*iter)->End();
			SAFE_DELETE(*iter);
			iter = GameObjects.erase(iter);
		}
		else {
			if ((*iter)->HasComponents()) {
				(*iter)->UpdateComponents(DeltaTime);
			}
			(*iter)->Update(DeltaTime);
			iter++;
		}
	}
}

void ObjectManager::LateUpdate()
{

	for (auto iter = GameObjects.begin(); iter != GameObjects.end();) {
		if (not (*iter)->Active) {
			(*iter)->End();
			SAFE_DELETE(*iter);
			iter = GameObjects.erase(iter);
		}
		else {
			if ((*iter)->HasComponents()) {
				(*iter)->LateUpdateComponents();
			}
			(*iter)->LateUpdate();
			iter++;
		}
	}
}

void ObjectManager::Render()
{
	std::sort(GameObjects.begin(), GameObjects.end(), [](GameObject* obj1, GameObject* obj2) {
		return obj1->Layer < obj2->Layer;
		});

	for (auto iter : GameObjects) {
		if (iter->Visible) {
			if (iter->HasComponents()) {
				iter->RenderComponents();
			}
			iter->Render();
		}
	}
}

void ObjectManager::End()
{
}

void ObjectManager::ObjectIO()
{
	if (GameObjectAddQuery.size() > 0) {
		for (auto iter : GameObjectAddQuery) {
			iter->Start();
			GameObjects.push_back(iter);
		}
		GameObjectAddQuery.clear();
	}
}

void ObjectManager::ClearAll()
{
	ObjectIO();
	ClearGameObjects();
}

void ObjectManager::ClearGameObjects()
{
	for (auto iter = GameObjects.begin(); iter != GameObjects.end();) {
		iter = GameObjects.erase(iter);
	}
}

vector<GameObject*> ObjectManager::GetObjectByCollisionLayers(vector<int> layers)
{
	vector<GameObject*> result;
	if (layers.size() <= 0) return result;
	//1. Remove "COLLISION_LAYER_NULL" Layer
	auto iterator = layers.begin();
	for (; iterator != layers.end();) {
		if ((*iterator) == COLLISION_LAYER_NULL)
			iterator = layers.erase(iterator);
		else
			++iterator;
	}
	//2. Making Result Vector
	for (auto iter : GameObjects) {
		bool flag = false;
		for (auto layer : layers) {
			if (iter->CollisionLayer == layer) {
				flag = true;
				break;
			}
		}

		if (flag)
			result.push_back(iter);
	}
	return result;
}

vector<GameObject*> ObjectManager::GetObjectByCollisionLayer(int layer)
{
	vector<GameObject*> result;
	if (layer == COLLISION_LAYER_NULL) return result;
	for (auto iter : GameObjects) {
		bool flag = false;
		if (iter->CollisionLayer == layer)
			result.push_back(iter);
	}
	return result;
}
