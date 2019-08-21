#include "stdafx.h"

BoxCollider2D::BoxCollider2D(GameObject* object) : Component(object)
{
}

BoxCollider2D::BoxCollider2D(GameObject* gameObject, function<void(GameObject*, BoxRect)> mColliderfunc) : Component(gameObject)
{
	this->mColliderfunc = mColliderfunc;
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Start()
{
}

void BoxCollider2D::Update(float DeltaTime)
{
}

void BoxCollider2D::LateUpdate()
{
	for (auto iter : ObjectManager::GetInstance()->GetObjectByCollisionLayers(gameObject->CollisionByLayer)) {
		if (iter == gameObject) continue;
		if (!iter->Active) continue;
		if (shared_ptr<BoxCollider2D> box = iter->GetComponent<BoxCollider2D>()) {
			BoxRect mMyRect, mTargetRect;
			mMyRect = mRect + gameObject->transform.GetPosition();
			mTargetRect = box->mRect + box->gameObject->transform.GetPosition();
			BoxRect ret;
			if (mMyRect.IsCollision(mTargetRect, &ret)) {
				//Collision
				if (mColliderfunc)
					mColliderfunc(iter, ret);
			}
		}
	}
}

void BoxCollider2D::Render()
{
#ifdef _SHOW_MASK
	BoxRect bRect = mRect + gameObject->transform.GetPosition();
	float mx = bRect.minX;
	float my = bRect.minY;
	float mx2 = bRect.maxX;
	float my2 = bRect.maxY;
	DirectX::GetInstance()->DrawLine(mx, my, mx, my2, 0xffff0000);
	DirectX::GetInstance()->DrawLine(mx2, my2, mx, my2, 0xffff0000);
	DirectX::GetInstance()->DrawLine(mx2, my2, mx2, my, 0xffff0000);
	DirectX::GetInstance()->DrawLine(mx, my, mx2, my, 0xffff0000);
#endif
}

void BoxCollider2D::End()
{
}

bool BoxCollider2D::IsCollision(BoxCollider2D* collider, BoxRect* ret)
{
	BoxRect mMyRect, mTargetRect;
	mMyRect = mRect + gameObject->transform.GetPosition();
	mTargetRect = collider->mRect + collider->gameObject->transform.GetPosition();
	return mMyRect.IsCollision(mTargetRect, ret);
}
