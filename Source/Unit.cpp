#include "stdafx.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::Start()
{
	for (int i = 0; i < State::SzState; i++) {
		for (int j = 0; j < Dir::SzDir; j++) {
			char filePath[MAX_PATH];
			sprintf(filePath, "./Asset/Unit/Resources/%s/%s/%d/", UnitName.c_str(), GetStateName((State)i).c_str(), j);
		}
	}

	SelectedCircle = shared_ptr<Sprite2D>(new Sprite2D(this, "./Asset/Unit/Selected"));
	SelectedCircle->Enable = false;
}

void Unit::Update(float DeltaTime)
{

	if (mState != mNextState) {
		mSpr[mState][mDir]->Enable = false;
		mState = mNextState;
		mSpr[mState][mDir]->Enable = true;
	}
	if (mDir != mNextDir) {
		mSpr[mState][mDir]->Enable = false;
		mDir = mNextDir;
		mSpr[mState][mDir]->Enable = true;
	}
}

void Unit::LateUpdate()
{
	SelectedCircle->Enable = Selected;
}

void Unit::Render()
{
}

void Unit::End()
{
	SelectedCircle.reset();
}

std::string GetStateName(Unit::State state)
{
	static std::string strings[Unit::State::SzState] = {
		"Idle",
		"Walk",
		"Attack"
	};
	return strings[state];
}
