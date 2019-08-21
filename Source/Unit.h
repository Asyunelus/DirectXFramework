#pragma once
class Unit : public GameObject
{
public:
	enum State {
		Idle,
		Walk,
		Attack,
		SzState
	};

	enum Dir {
		Top,
		TopRight,
		Right,
		BottomRight,
		Bottom,
		BottomLeft,
		Left,
		TopLeft,
		SzDir
	};

	State mState = State::Idle;
	State mNextState = State::Idle;
	Dir mDir = Dir::Top;
	Dir mNextDir = Dir::Top;

	shared_ptr<Sprite2D> mSpr[State::SzState][Dir::SzDir];

	std::string UnitName = "None";

public:
	//Only Check Render Selected
	bool Selected = false;
	shared_ptr<Sprite2D> SelectedCircle;
public:
	Unit();
	virtual ~Unit();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

extern std::string GetStateName(Unit::State state);