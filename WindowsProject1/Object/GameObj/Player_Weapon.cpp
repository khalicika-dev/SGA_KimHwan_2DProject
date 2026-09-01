#include "framework.h"
#include "Player_Weapon.h"

Player_Weapon::Player_Weapon()
: _attacked(false)
{
	_sprite = new Sprite(L"Resource/Sprites/SpriteWeapon.png");
	_col = new RectCollider({ 1.0f,1.0f }, _sprite->GetTransform());
	Init();
}

Player_Weapon::~Player_Weapon()
{
	for (auto& action : _actions)
		delete action.second;
	delete _sprite;
	delete _col;
}

void Player_Weapon::Update(bool visible, Vector2 pos, Vector2 scale, Action* curAction, bool isAir)
{
	if (!visible)
	{
		_col->SetEnable(false);
		return;
	}
	UINT curFrame = curAction->GetCurClipNo();

	Vector2 groundhandPos[] = {
		{-33.0f,46.0f},
		{-31.0f,47.0f},
		{29.0f,16.0f},
		{30.0f,15.0f}
	};
	Vector2 airhandPos[] = {
		{-19.0f,33.5f},
		{-19.0f,36.5f},
		{11.0f,16.0f},
		{11.0f,16.0f}
	};
	Vector2* handPos = isAir ? &airhandPos[0] : &groundhandPos[0];
	_sprite->GetTransform()->m_scale = scale;
	_sprite->GetTransform()->m_pivot.x = (-_actions[_curWeapon]->GetCurClip().size.x / 2.0f + _weaponData[_curWeapon]._pivot.x);
	_sprite->GetTransform()->m_pivot.y = (-_actions[_curWeapon]->GetCurClip().size.y / 2.0f + _weaponData[_curWeapon]._pivot.y);
	_sprite->GetTransform()->m_pos = { pos.x + handPos[curFrame].x * (scale.x >= 0.0f ? 1.0f : -1.0f) - _sprite->GetTransform()->m_pivot.x - (curAction->GetCurClip().pivot.x * scale.x),
		pos.y + handPos[curFrame].y - _sprite->GetTransform()->m_pivot.y };
	_sprite->GetTransform()->m_angle = (isAir ? _weaponData[_curWeapon]._airAngle[curFrame] : _weaponData[_curWeapon]._angle[curFrame]) * (PI / 180.0f) * (scale.x >= 0.0f ? 1.0f : -1.0f);

	_actions[_curWeapon]->gotoStop(curFrame == 2 ? 1 : 0);
	if (curFrame == 2)
	{
		if (!_attacked)
		{
			_col->SetEnable(true);
			_attacked = true;
		}
		else
			_col->SetEnable(false);
	}
	else
	{
		_col->SetEnable(false);
		_attacked = false;
	}
	
	_sprite->SetAction(_actions[_curWeapon]->GetCurClip());
	_sprite->Update();
	dynamic_cast<RectCollider*>(_col)->SetSize(_actions[_curWeapon]->GetCurClip().size.x, _actions[_curWeapon]->GetCurClip().size.y);
	_col->Update();
}

void Player_Weapon::Render(bool visible)
{
	if (!visible) return;

	if (_curWeapon != WeaponType::FIST)
		_sprite->Render();
	_col->Render();
}

void Player_Weapon::ChangeWeapon(WeaponType weapon)
{
	_curWeapon = weapon;
}

void Player_Weapon::Init()
{
	vector<Action::Clip> clips;
	Vector2	framePos = { 0.0f,0.0f };	// 클립프레임을 생성하고자 하는 스프라이트의 위치
	Vector2	frameSize = { 0.0f,0.0f };	// 한 클립의 프레임 폭
	Vector2 framePivot = { 0.0f,0.0f };	// 무기의 회전 기준점(클립의 좌하단을 원점으로 계산)
	vector<float> frameAngle(4);		// 무기의 회전각도
	vector<float> frameAirAngle(4);		// 무기의 공중회전각도
	WeaponType weaponType;	// 한 액션의 타입

	framePos.x += 0.0f;
	framePos.y = 0.0f;
	{
		weaponType = WeaponType::NORMAL;
		frameSize = { 83.0f, 70.0f };
		framePivot = { 49.0f, 15.0f };
		frameAngle = { 172.0f, 170.0f, -86.0f, -88.0f };
		frameAirAngle = { 165.0f, 170.0f, -103.0f, -105.0f };
		framePos.y -= frameSize.y;
		clips.push_back({ framePos.x,framePos.y += frameSize.y,frameSize.x, frameSize.y, 1.0f * FRAME });
		clips.push_back({ framePos.x,framePos.y += frameSize.y,frameSize.x, frameSize.y, 1.0f * FRAME });
		framePos.y += frameSize.y;
		framePos.x += frameSize.x;
		framePos.y = 0.0f;
		_actions.emplace(weaponType, new Action(clips, Action::END));
		_weaponData.emplace(weaponType, WeaponData(true, framePivot, frameAngle, frameAirAngle, 2.5f, 20, 25, 10.0f));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);	// 벡터 기본생성자와 swap을 하여 clips의 capacity를 0으로 만들어 메모리를 해제한다.
	{
		weaponType = WeaponType::STONE;
		frameSize = { 44.0f, 24.0f };
		framePivot = { 9.0f, 18.0f };
		frameAngle = { 0.0f, 0.0f, 100.0f, 100.0f };
		frameAirAngle = { -22.5f, -18.0f, -86.0f, -80.0f };
		framePos.y -= frameSize.y;
		clips.push_back({ framePos.x,framePos.y += frameSize.y,frameSize.x, frameSize.y, 1.0f * FRAME });
		clips.push_back({ framePos.x,framePos.y += frameSize.y,frameSize.x, frameSize.y, 1.0f * FRAME });
		framePos.y += frameSize.y;
		framePos.x += frameSize.x;
		framePos.y = 0.0f;
		_actions.emplace(weaponType, new Action(clips, Action::END));
		_weaponData.emplace(weaponType, WeaponData(false, framePivot, frameAngle, frameAirAngle, 6.0f, 20, 25, 18.0f));

		weaponType = WeaponType::FIST;
		_actions.emplace(weaponType, new Action(clips, Action::END));
		_weaponData.emplace(weaponType, WeaponData(false, framePivot, frameAngle, frameAirAngle, 2.0f, 9, 13, 8.0f));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
}