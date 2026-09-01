#pragma once
class Gold : public GameObject
{
public:
	enum class ActionType
	{
		SMALL,
		MEDIUM,
		LARGE
	};

	Gold(Vector2 pos);
	virtual ~Gold();

	void SpriteInit();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetGold(int value) { _gold = value; }
	void SetMoveSpeed(float value) { _moveSpeed = value; }
private:
	Sprite* _sprite;
	Collider* _col;
	map<ActionType, Action*> _actions;
	ActionType _curAction;
	ActionType _oldAction;

	int _gold;

	const float _moveAccel = 2000.0f;		// 땅에 떨어졌을 때의 제동속도

	const float _jumpAccel = 1600.0f;		// 낙하가속도
	const float _minJumpSpeed = -700.0f;	// 최대 낙하속도
};

