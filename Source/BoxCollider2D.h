#pragma once

class BoxCollider2D : public Component
{
public:
	std::string TAG = "";
	BoxRect mRect;
	function<void(GameObject*, BoxRect)> mColliderfunc;

	shared_ptr<Sprite2D> mSpr[State::Skill][Dir::SzDir];

public:
	BoxCollider2D(GameObject* gameObject);
	BoxCollider2D(GameObject* gameObject, function<void(GameObject*, BoxRect)> mColliderfunc);
	virtual ~BoxCollider2D();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();

	bool IsCollision(BoxCollider2D* collider, BoxRect* ret);
};