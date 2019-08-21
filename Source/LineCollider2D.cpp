#include "stdafx.h"

LineCollider2D::LineCollider2D(GameObject* gameObject) : Component(gameObject)
{
}

LineCollider2D::LineCollider2D(GameObject* gameObject, function<void(GameObject*, D3DXVECTOR2)> mColliderfunc) : Component(gameObject)
{
	this->mColliderfunc = mColliderfunc;
}

LineCollider2D::~LineCollider2D()
{
}

void LineCollider2D::Start()
{
}

void LineCollider2D::Update(float DeltaTime)
{
}

void LineCollider2D::LateUpdate()
{
	for (auto iter : ObjectManager::GetInstance()->GetObjectByCollisionLayers(gameObject->CollisionByLayer)) {
		if (iter == gameObject) continue;
		if (iter->TAG == gameObject->TAG) continue;
		if (!iter->Active) continue;
		if (shared_ptr<LineCollider2D> line = iter->GetComponent<LineCollider2D>()) {
			LineRect mMyRect, mTargetRect;
			D3DXVECTOR2 ret;
			mMyRect = mRect + gameObject->transform.GetPosition();
			mTargetRect = line->mRect + line->gameObject->transform.GetPosition();
			if (mMyRect.IsCollision(mTargetRect, &ret)) {
				//Collision
				if (mColliderfunc)
					mColliderfunc(iter, ret);
			}
		}
	}
}

void LineCollider2D::Render()
{
#ifdef _SHOW_MASK
	D3DXVECTOR2 gameObjectPosition = gameObject->transform.GetPosition();
	float mx = mRect.p1.x + gameObjectPosition.x;
	float my = mRect.p1.y + gameObjectPosition.y;
	float mx2 = mRect.p2.x + gameObjectPosition.x;
	float my2 = mRect.p2.y + gameObjectPosition.y;
	DirectX::GetInstance()->DrawLine(mx, my, mx2, my2, 0xffff0000);
#endif
}

void LineCollider2D::End()
{
}
