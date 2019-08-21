#include "stdafx.h"
#include "MouseDragObject.h"

MouseDragObject::MouseDragObject()
{
	Layer = 100;
	for (int i = 0; i < 4; i++) {
		Vertex[i] = { 0, 0, 0, 0, 0, 0 };
		Vertex[i].SetARGB(80, 43, 255, 43);
	}
	mStartPosition = mNowPosition = D3DXVECTOR2(0, 0);

	AddComponent(shared_ptr<BoxCollider2D>(new BoxCollider2D(this, [this](GameObject* obj, BoxRect overlap) {
		
	})));
}

MouseDragObject::~MouseDragObject()
{
}

void MouseDragObject::Start()
{
}

void MouseDragObject::Update(float DeltaTime)
{
	int LButtonState = KeyManager::GetInstance()->GetKeyState(VK_LBUTTON);
	if (LButtonState == Press) {
		mStartPosition = mNowPosition = KeyManager::GetInstance()->GetMousePosition() + Camera::GetInstance()->GetCameraPosition();
		GetComponent<BoxCollider2D>()->mRect.SetBox(mStartPosition.x, mStartPosition.y, mStartPosition.x, mStartPosition.y);
		IsDrag = true;
	}
	else if (LButtonState == Down) {
		mNowPosition = KeyManager::GetInstance()->GetMousePosition() + Camera::GetInstance()->GetCameraPosition();
		GetComponent<BoxCollider2D>()->mRect.SetBox(mStartPosition.x, mStartPosition.y, mNowPosition.x, mNowPosition.y);
	}
	else if (LButtonState == Up) {
		//1. NowSelected Objects's Selected = false
		if (SelectedList.size() > 0) {
			for (auto iter : SelectedList)
				iter->Selected = false;
			SelectedList.clear();
		}
		//2. Select Check
		if (shared_ptr<BoxCollider2D> Collider = GetComponent<BoxCollider2D>()) {
			for (auto iter : ObjectManager::GetInstance()->GetObjectByCollisionLayers(ColVector)) {
				if (shared_ptr<BoxCollider2D> ptr = iter->GetComponent<BoxCollider2D>()) {
					BoxRect ret;
					if (ptr->IsCollision(Collider.get(), &ret)) {
						Unit* unit = dynamic_cast<Unit*>(ptr->gameObject);
						unit->Selected = true;
						SelectedList.push_back(unit);
					}
				}
			}
		}
		//ClearPosition
		GetComponent<BoxCollider2D>()->mRect = BoxRect();
		mStartPosition = mNowPosition = D3DXVECTOR2(0, 0);
		IsDrag = false;
	}
}

void MouseDragObject::LateUpdate()
{
}

void MouseDragObject::Render()
{
	if (not IsDrag) return;
	D3DXVECTOR2 mSP = mStartPosition - Camera::GetInstance()->GetCameraPosition();
	D3DXVECTOR2 mNP = mNowPosition - Camera::GetInstance()->GetCameraPosition();
	Vertex[0].SetVtx(mSP.x, mSP.y, 0);
	Vertex[1].SetVtx(mSP.x, mNP.y, 0);
	Vertex[2].SetVtx(mNP.x, mSP.y, 0);
	Vertex[3].SetVtx(mNP.x, mNP.y, 0);


	D3DXMATRIX matPos, matWorld;

	//½ºÇÁ¶óÀÌÆ®ÀÇ À§Ä¡
	D3DXMatrixTranslation(&matPos, 0, 0, 0.0f);

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixTransformation2D(&matWorld, 0, 0.f, &transform.Scale, 0, 0, NULL);

	//Çà·Ä³¢¸® °ö¼À
	matWorld = matWorld * matPos;

	DirectX::GetInstance()->g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DirectX::GetInstance()->g_pd3dDevice->SetTexture(0, NULL);
	DirectX::GetInstance()->g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	DirectX::GetInstance()->g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2,
		(void*)Vertex, sizeof(CUSTOMVERTEX));
}

void MouseDragObject::End()
{
}
