#pragma once
class Monster_Flower : public GameObject
{
public:
	enum class ActionType
	{
		IDLE
	};

	Monster_Flower();
	virtual ~Monster_Flower();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	void SpriteInit();

	void SetActionType(ActionType type);

	virtual void DecreaseHp(int value) override;
private:
	void ClipEndEvent();
private:
	Sprite* _sprite;
	map<ActionType, Action*> _actions;
	ActionType _curAction;
	ActionType _oldAction;

	Collider* _col;

	const float _speedValue = 55.0f;	// 기본
	float _airMoveSpeed;

	const float _jumpAccel = 1200.0f;		// 낙하가속도
	const float _maxJumpSpeed = 600.0f;		// 점프 도약높이
	const float _minJumpSpeed = -400.0f;	// 최대 낙하속도

	float _updateTimer;	// 행동변경주기
	const float _minUpdateTime = 2.0f;
	const float _maxUpdateTime = 2.5f;
};

