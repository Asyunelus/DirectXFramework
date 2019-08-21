#pragma once

class LineCollider2D : public Component
{
public:
	std::string TAG = "";
	LineRect mRect;
	function<void(GameObject*, D3DXVECTOR2)> mColliderfunc;

public:
	LineCollider2D(GameObject* gameObject);
	LineCollider2D(GameObject* gameObject, function<void(GameObject*, D3DXVECTOR2)> mColliderfunc);
	virtual ~LineCollider2D();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

