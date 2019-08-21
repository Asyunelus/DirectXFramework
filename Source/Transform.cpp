#include "stdafx.h"

D3DXVECTOR2 Transform::GetPosition() {
	if (parent.use_count() > 0) {
		return parent->transform.GetPosition() + Position;
	}
	return Position;
}

void Transform::SetParent(GameObject* target) {
	if (parent.use_count() > 0) {
		Position += parent->transform.GetPosition();
	}

	if (target != nullptr) {
		parent.reset(target);
		Position -= parent->transform.GetPosition();
	} else {
		parent.reset();
	}
}

void Transform::Translate(D3DXVECTOR2 TranslatePosition) {
	Position += TranslatePosition;
}

void Transform::Transformation(D3DXVECTOR2 TransformationPosition)
{
	if (parent.use_count() > 0) {
		Position = TransformationPosition - parent->transform.GetPosition();
	} else {
		Position = TransformationPosition;
	}
}

void Transform::TransformationNoParent(D3DXVECTOR2 TransformationPosition)
{
	Position = TransformationPosition;
}
