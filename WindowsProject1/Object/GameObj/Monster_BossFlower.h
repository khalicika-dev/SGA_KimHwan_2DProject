#pragma once
class Monster_BossFlower : public GameObject
{
public:
	enum class ActionType
	{
		IDLE,
		ATTACK
	};

	Monster_BossFlower();
	virtual ~Monster_BossFlower();

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

	const float _speedValue = 60.0f;	// 기본

	const float _jumpAccel = 1800.0f;		// 낙하가속도
	const float _maxJumpSpeed = 400.0f;		// 점프 도약높이
	const float _minJumpSpeed = -600.0f;	// 최대 낙하속도

	float _updateTimer;	// 행동변경주기
	const float _minUpdateTime = 2.0f;
	const float _maxUpdateTime = 2.5f;

	float _skillTimer; // 특수행동주기
	const float _minSkillTime = 3.0f;
	const float _maxSkillTime = 3.5f;
};

