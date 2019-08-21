#pragma once

class GameObject {
public:
	std::string TAG = "";
	Transform transform;
	int Layer = 0;
	bool Active = true;
	bool Visible = true;
	vector<shared_ptr<Component>> Components;
	vector<int> CollisionByLayer;
	int CollisionLayer = COLLISION_LAYER_NULL;
public:
	template<class T>
	shared_ptr<T> GetComponent();
	template<class T>
	std::vector<shared_ptr<T>> GetComponents();
	shared_ptr<Component> AddComponent(shared_ptr<Component> component);
	bool HasComponents();
	void UpdateComponents(float DeltaTime);
	void LateUpdateComponents();
	void RenderComponents();

public:
	GameObject();
	virtual ~GameObject();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

template<class T>
inline shared_ptr<T> GameObject::GetComponent()
{
	for (auto iter : Components) {
		if (shared_ptr<T> result = dynamic_pointer_cast<T>(iter))
			return result;
	}

	return NULL;
}

template<class T>
inline std::vector<shared_ptr<T>> GameObject::GetComponents()
{
	std::vector<shared_ptr<T>> resultVector;
	for (auto iter : Components) {
		if (shared_ptr<T> result = dynamic_pointer_cast<T>(iter))
			resultVector.push_back(result);
	}

	return resultVector;
}
