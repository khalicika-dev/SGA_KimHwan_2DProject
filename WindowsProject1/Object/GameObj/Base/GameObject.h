#pragma once
class GameObject
{
public:
	enum class ActionType
	{
		NONE
	};

	GameObject();
	virtual ~GameObject() {}

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual Collider* GetCollider() { return nullptr; }
	virtual Collider* GetAttackCollider() { return nullptr; }

	bool GetActive() { return _isActive; }
	void SetActive(bool value) { _isActive = value; }
	void SetPosition(Vector2 position) { _position = position; _oldPos = position; }	// 오브젝트의 위치를 해당지점으로 초기화
	void MovePosition(Vector2 position) { _position = position; }						// 오브젝트를 해당지점으로 이동 (지형의 영향을 받음)
	void SetAngle(float angle) { _angle = angle; }
	Vector2 GetPosition() { return _position; }
	bool GetMovable() { return _movable; }

	int GetHp() { return _hp; }
	int GetMaxHp() { return _maxHp; }
	virtual void DecreaseHp(int value) {}
protected:
	bool _isActive;
	Vector2 _position;	// 캐릭터의 현재위치
	Vector2 _oldPos;	// 캐릭터의 이전위치
	float _angle;

	bool _movable;
	float _moveSpeed;
	bool _isWall;	// 벽에 부딫혔는가?

	bool _isAir;	// 바닥에 닿지않고 공중에 떠있는가?
	float _jumpSpeed;

	void CollideProcess();

	int _hp;
	int _maxHp;

	// 몬스터전용
	float _attackTime;					// 플레이어가 피격되었을때 공격히트박스가 재활성되는 시간
	float _maxAttackTime;	// 재활성 최대시간
};

