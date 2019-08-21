#include "stdafx.h"

Component::Component(GameObject* parent)
{
	this->gameObject = parent;
}

Component::~Component()
{
}