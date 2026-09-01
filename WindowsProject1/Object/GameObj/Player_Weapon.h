#pragma once
class Player_Weapon
{
public:
	enum class WeaponType
	{
		FIST,
		NORMAL,
		STONE
	};
	struct WeaponData
	{
		bool _isCutter;				// 날붙이(true)/둔기(false)판정
		Vector2 _pivot;				// 스프라이트 클립의 손잡이 위치
		vector<float> _angle;		// 클립의 회전각도
		vector<float> _airAngle;	// 클립의 공중회전각도
		float _speed;				// 무기의 고유 공격속도
		UINT _mindamage;			// 무기의 고유 최소공격력
		UINT _maxdamage;			// 무기의 고유 최대공격력
		float _knockback;			// 공격시 적을 밀쳐내는거리

		WeaponData(bool isCutter, Vector2 pivot, vector<float> angle, vector<float> airAngle, float speed = 2.0f, UINT mindamage = 1, UINT maxdamage = 1, float knockback = 3.0f)
			:_isCutter(isCutter), _pivot(pivot), _angle(angle), _airAngle(airAngle), _speed(speed), _mindamage(mindamage), _maxdamage(maxdamage), _knockback(knockback) {}
		WeaponData()
			:_isCutter(false), _pivot(0,0), _angle(vector<float>()), _airAngle(vector<float>()), _speed(0.0f), _mindamage(0.0f), _maxdamage(0.0f), _knockback(0.0f) {}
	};
	map<WeaponType, WeaponData> _weaponData;
	WeaponType _curWeapon;
public:
	Player_Weapon();
	~Player_Weapon();
	void Update(bool visible, Vector2 pos, Vector2 scale, Action* curAction, bool isAir);
	void Render(bool visible);
	void ChangeWeapon(WeaponType weapon);
	Collider* GetCollider() { return _col; }

private:
	void Init();
	Sprite* _sprite;
	map<WeaponType, Action*> _actions;
	Collider* _col;
	bool _attacked;
};