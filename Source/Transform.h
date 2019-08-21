#pragma once

class GameObject;

struct Transform {
	D3DXVECTOR2 Position = { 0.0f, 0.0f };
	D3DXVECTOR2 Scale = { 1.0f, 1.0f };
	D3DXVECTOR2 Anchor = { 0.5f, 0.5f };

	float RotateAngle = 0.0f;

	shared_ptr<GameObject> parent;

	D3DXVECTOR2 GetPosition();
	void SetParent(GameObject* target);
	void Translate(D3DXVECTOR2 TranslatePosition);
	void Transformation(D3DXVECTOR2 TransformationPosition);
	void TransformationNoParent(D3DXVECTOR2 TransformationPosition);
};