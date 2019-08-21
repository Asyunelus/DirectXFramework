#pragma once
class MouseDragObject : public GameObject
{
	CUSTOMVERTEX Vertex[4];
	D3DXVECTOR2 mStartPosition, mNowPosition;
	std::vector<int> ColVector;
	std::vector<Unit*> SelectedList;
	bool IsDrag = false;
public:
	MouseDragObject();
	virtual ~MouseDragObject();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

