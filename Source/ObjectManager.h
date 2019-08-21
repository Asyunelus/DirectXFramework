#pragma once
class ObjectManager : public SingleInstance<ObjectManager>
{
public:
	vector<GameObject*> GameObjectAddQuery;
	vector<GameObject*> GameObjects;

public:
	ObjectManager();
	~ObjectManager();

	void Start();
	void Update(float DeltaTime);
	void LateUpdate();
	void Render();
	void End();
	void ObjectIO();
	void ClearAll();
	void ClearGameObjects();

	vector<GameObject*> GetObjectByCollisionLayers(vector<int> layers);
	vector<GameObject*> GetObjectByCollisionLayer(int layer);
};

template<typename T = GameObject *>
T Instantiate(GameObject * obj)
{
	ObjectManager::GetInstance()->GameObjectAddQuery.push_back(obj);
	return static_cast<T>(obj);
}

template<class T = GameObject *>
std::vector<T> GetAllObjects() {
	std::vector<T> GameObjects;

	for (auto iter : ObjectManager::GetInstance()->GameObjects) {
		if (T obj = dynamic_cast<T>(iter)) {
			GameObjects.push_back(obj);
		}
	}

	return GameObjects;
}

bool IssetObjectByTag(std::string findTAG) {
	for (auto iter : ObjectManager::GetInstance()->GameObjects) {
		if (iter->TAG == findTAG)
			return true;
	}
	return false;
}

template<class T = GameObject*>
bool IssetObject() {
	for (auto iter : ObjectManager::GetInstance()->GameObjects) {
		if (T obj = dynamic_cast<T>(iter)) {
			return true;
		}
	}
	return false;
}