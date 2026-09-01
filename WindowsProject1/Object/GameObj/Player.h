#pragma once
class Player : public GameObject
{
public:
	enum class ActionType
	{
		IDLE,
		WALK,
		RUN,
		JUMP_READY,
		JUMP,
		CHARGE,
		AIR_CHARGE,
		CHARGE_HIT,
		HIT,
		HIT_AIR,
		ATTACK,
		ATTACK_AIR,
		CHARGE_SLASH,
		DEATH_AIR,
		RAISE,
		RAISE_AIR,
		GOG,
		DEATH,
		CLIMB
	};
	enum class ArmorType
	{
		NONE,
		NORMAL
	};
	struct ArmorData
	{
		int _hp;		// 갑옷이 증가시켜주는 체력
		int _def;	// 갑옷이 받는 데미지를 경감시키는 정도(방어력)

		ArmorData(int hp, int def)
			:_hp(hp), _def(def) {}
		ArmorData()
			:_hp(0), _def(0) {}
	};
	map<ArmorType, ArmorData> _armorData;

	Player();
	virtual ~Player();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	void All_Initialize();
	void SpriteInit();
	virtual Collider* GetCollider() override { return _col; }
	virtual Collider* GetAttackCollider() override { return _weapon->GetCollider(); }
	Vector2 GetScale() { return _sprite->GetTransform()->m_scale; }

	void SetActionType(ActionType type, bool force = false);
	void SetAttackSpeed(float value);	// 공격속도를 클립에 반영하는 함수
	void SetWeapon(Player_Weapon::WeaponType type);	// 무기를 교체하는 함수
	void SetArmor(ArmorType type);
	UINT GetDamage() { return Math::Random(_weapon->_weaponData[_weapon->_curWeapon]._mindamage, _weapon->_weaponData[_weapon->_curWeapon]._maxdamage); }
	Player_Weapon::WeaponType GetWeapon() { return _weapon->_curWeapon; }
	ArmorType GetArmor() { return _curArmor; }
	float GetKnockback() { return _weapon->_weaponData[_weapon->_curWeapon]._knockback * (_sprite->GetTransform()->m_scale.x >= 0 ? 1 : -1); }
	wstring GetHitEffect() { return _weapon->_weaponData[_weapon->_curWeapon]._isCutter ? L"atk_slash" : L"atk_blow"; }

	void Hit(Vector2 mobPos, int damage, int knockback = 200.0f);
	virtual void DecreaseHp(int value) override;
	bool IsResurrecting() { return _resurrection; }
private:
	void ClipEndEvent();
private:
	Sprite* _sprite;
	Player_Weapon* _weapon;
	ArmorType _curArmor;
	map<ActionType, Action*> _actions;
	ActionType _curAction;
	ActionType _oldAction;

	Collider* _col;		// 피격 히트박스
	

	const float _moveAccel = 600.0f;	// 가속도
	const float _maxMoveSpeed = 400.0f;	// 최대 이동속도
	const float _minMoveSpeed = 200.0f; // 제동시 이동속도

	const float _jumpAccel = 1600.0f;		// 낙하가속도
	const float _maxJumpSpeed = 800.0f;		// 점프 도약높이
	const float _minJumpSpeed = -700.0f;	// 최대 낙하속도

	float _attackSpeed;

	bool _isAttack;	// 공격중인가?
	bool _invincible;	// 무적유무
	bool _resurrection;	// 부활중 유무
public:
	const int _defaultHp = 80.0f;
	bool _invincible_mapChange;	// 맵 이동 중일때 무적
};