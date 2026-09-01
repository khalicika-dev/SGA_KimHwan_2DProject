#include "Framework.h"
#include "Player.h"

Player::Player()
	: _sprite(nullptr)
	, _curAction(ActionType::IDLE)
	, _oldAction(ActionType::IDLE)
	, _isAttack(false)
	, _invincible(false)
	, _resurrection(false)
	, _invincible_mapChange(false)
, GameObject()
{
	_sprite = new Sprite(L"Resource/Sprites/KOGsprite.png");
	_col = new RectCollider({ 20.0f,71.0f }, _sprite->GetTransform());
	SpriteInit();	// 스프라이트 정의
	
	_weapon = new Player_Weapon();

	// 방어구 정의
	{
		_armorData.emplace(ArmorType::NONE, ArmorData(0, 0));
		_armorData.emplace(ArmorType::NORMAL, ArmorData(120, 10));
	}
	All_Initialize();
}

Player::~Player()
{
	for (auto& action : _actions)
		delete action.second;
	delete _sprite;
	delete _weapon;
	delete _col;
}

void Player::Update()
{
	_oldPos = _position;
	_oldAction = _curAction;

	if (_curAction != ActionType::ATTACK && _curAction != ActionType::ATTACK_AIR)
		_isAttack = false;

	if (!_isAir && _curAction == ActionType::DEATH_AIR)
		SetActionType(ActionType::DEATH, true);

	if (_curAction == ActionType::DEATH || _curAction == ActionType::DEATH_AIR)
	{
		UISTATE->SetDialogText(L"죽고 말았다...\n'D'키를 누르면 집에서 부활합니다.", 100.0f);
		if (KEYPRESS('D') && !UISTATE->IsFading())	// D키를 눌러서 부활지점으로 이동
		{
			_resurrection = true;
			MAPMANAGER->ChangeMap(MAP::STAGE1, { 265.0f,-365.0f });
		}
	}

	// 점프키
	if (KEYPRESS(VK_SPACE) && !_isAir)
	{
		SetActionType(ActionType::JUMP_READY);
	}

	// 공격부문
	if (KEYPRESS('A') && _movable && !_isAttack && _curAction != ActionType::JUMP_READY && _curAction != ActionType::HIT && _curAction != ActionType::HIT_AIR)
	{
		if (_isAir)
		{
			_isAttack = true;
			SetActionType(ActionType::ATTACK_AIR);
			_actions[ActionType::ATTACK_AIR]->Play();
		}
		else
		{
			_movable = false;
			_isAttack = true;
			SetActionType(ActionType::ATTACK);
			_actions[ActionType::ATTACK]->Play();
		}
	}

	// x축 이동부문
	if (KEYPRESS(VK_LEFT) && _movable)
	{
		if(_curAction != ActionType::ATTACK_AIR)
			_sprite->GetTransform()->m_scale.x = -1.0f;
		if (_moveSpeed > _minMoveSpeed) _moveSpeed = _minMoveSpeed;
		_moveSpeed -= _moveAccel * DELTATIME;
		if (_moveSpeed < -_maxMoveSpeed) _moveSpeed = -_maxMoveSpeed;

	}
	else if (KEYPRESS(VK_RIGHT) && _movable)
	{
		if (_curAction != ActionType::ATTACK_AIR)
			_sprite->GetTransform()->m_scale.x = 1.0f;
		if (_moveSpeed < -_minMoveSpeed) _moveSpeed = -_minMoveSpeed;
		_moveSpeed += _moveAccel * DELTATIME;
		if (_moveSpeed > _maxMoveSpeed) _moveSpeed = _maxMoveSpeed;
	}
	else
	{
		if (_moveSpeed > 0.0f)
		{
			if (_moveSpeed > _minMoveSpeed) _moveSpeed = _minMoveSpeed;
			if (_curAction != ActionType::DEATH_AIR) _moveSpeed -= _moveAccel * DELTATIME;
			if (_moveSpeed < 0.0f) _moveSpeed = 0.0f;
		}
		else if (_moveSpeed < 0.0f)
		{
			if (_moveSpeed < -_minMoveSpeed) _moveSpeed = -_minMoveSpeed;
			if (_curAction != ActionType::DEATH_AIR) _moveSpeed += _moveAccel * DELTATIME;
			if (_moveSpeed > 0.0f) _moveSpeed = 0.0f;
		}
	}

	//x축 이동
	_position.x += _moveSpeed * DELTATIME;

	//y축 이동(자유낙하)
	_jumpSpeed -= _jumpAccel * DELTATIME;
	if (_jumpSpeed < _minJumpSpeed) _jumpSpeed = _minJumpSpeed;
	_position.y += _jumpSpeed * DELTATIME;

	// 지형충돌검사
	CollideProcess();

	// 문제1: 작은 경사를 지날때 지형충돌이 확실하게 일어나지 않는 문제
	// 문제2: 방향을 틀 때 땅을 뚫고 떨어지는 현상

	if (_isAir)
		SetActionType(ActionType::JUMP);
	else
	{
		if (_curAction == ActionType::ATTACK_AIR)
			ClipEndEvent();
	}
	if (_movable && !_isAttack && !_isAir)
		abs(_moveSpeed) > 0.0f ? abs(_moveSpeed) > abs(_minMoveSpeed) ? SetActionType(ActionType::RUN) : SetActionType(ActionType::WALK) : SetActionType(ActionType::IDLE);

	if (_isWall)
		_moveSpeed = 0.0f;


	_actions[_curAction]->Update();
	if (_curAction != _oldAction) 
		_actions[_curAction]->Play();
	_sprite->SetAction(_actions[_curAction]->GetCurClip());
	_sprite->GetTransform()->m_pos = { _position.x, _position.y + _actions[_curAction]->GetCurClip().size.y / 2.0f };

	_sprite->Update();
	dynamic_cast<RectCollider*>(_col)->SetSize(20.0f, _actions[_curAction]->GetCurClip().size.y);
	_col->SetEnable(!_invincible && !_invincible_mapChange);
	_col->Update();

	_weapon->Update(_isAttack, GetPosition(), _sprite->GetTransform()->m_scale, _actions[_curAction], _isAir);
	_invincible_mapChange = false;
}

void Player::Render()
{
	_sprite->Render();
	_col->Render();

	_weapon->Render(_isAttack && (_curAction == ActionType::ATTACK || _curAction == ActionType::ATTACK_AIR));
}

void Player::Init()
{
	_curAction = ActionType::IDLE;
	_oldAction = ActionType::IDLE;
	_moveSpeed = 0.0f;
	_jumpSpeed = 0.0f;
	_isAir = false;
	_movable = true;
	_isAttack = false;
	_invincible = false;
	_resurrection = false;
	_hp = _maxHp;
	UISTATE->SetDialogText(L"");
}

void Player::All_Initialize()
{
	_maxHp = _defaultHp;
	SetWeapon(Player_Weapon::WeaponType::FIST);
	SetArmor(ArmorType::NONE);
	Init();
}

void Player::SpriteInit()
{
	vector<Action::Clip> clips;
	Vector2	framePos = { 0.0f,0.0f };	// 클립프레임을 생성하고자 하는 스프라이트의 위치
	float	frameWidth = 0.0f;			// 한 클립의 프레임 폭
	float	frameRowHeight[] = { 71.0f,66.0f,64.0f,99.0f,86.0f };	// 스프라이트 각 1행의 높이
	ActionType actionType;	// 한 액션의 타입

	framePos.x = 0.0f;
	framePos.y += 0.0f;
	#pragma region 스프라이트 1행
	{
		actionType = ActionType::IDLE;
		frameWidth = 20.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 71.0f, 56.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 71.0f, 6.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 71.0f, 33.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::PINGPONG));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);	// 벡터 기본생성자와 swap을 하여 clips의 capacity를 0으로 만들어 메모리를 해제한다.
	{
		actionType = ActionType::WALK;
		frameWidth = 23.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 70.0f, 9.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 69.0f, 10.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 68.0f, 11.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::PINGPONG));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::RUN;
		frameWidth = 66.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 67.0f, 5.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 67.0f, 6.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 67.0f, 6.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::LOOP));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::JUMP_READY;
		frameWidth = 35.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 43.0f, 8.0f * FRAME });
		framePos.x += frameWidth;
		
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Player::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::JUMP;
		frameWidth = 72.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 64.0f, 27.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 64.0f, 1.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion

	framePos.x = 0.0f;
	framePos.y += frameRowHeight[0];
	#pragma region 스프라이트 2행
	{
		actionType = ActionType::CHARGE;
		frameWidth = 79.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 61.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 56.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 49.0f, 2.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::LOOP));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::CHARGE_HIT;
		frameWidth = 49.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 59.0f, 1.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::HIT;
		frameWidth = 46.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 66.0f, 4.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 65.0f, 4.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Player::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::HIT_AIR;
		frameWidth = 59.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 59.0f, 5.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 58.0f, 5.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Player::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion

	framePos.x = 0.0f;
	framePos.y += frameRowHeight[1];
	#pragma region 스프라이트 3행
	{
		actionType = ActionType::ATTACK;
		frameWidth = 70.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 62.0f, 10.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 64.0f, 10.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 46.0f, 10.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 45.0f, 10.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Player::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::ATTACK_AIR;
		frameWidth = 42.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 49.0f, 10.0f * FRAME, 5.0f, 0.0f });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 53.0f, 10.0f * FRAME, 5.0f, 0.0f });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 48.0f, 10.0f * FRAME, -25.0f, 0.0f });
		clips.push_back({ framePos.x,framePos.y,frameWidth, 48.0f, 10.0f * FRAME, -25.0f, 0.0f });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Player::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::CHARGE_SLASH;
		frameWidth = 60.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 40.0f, 6.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::DEATH_AIR;
		frameWidth = 67.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 47.0f, 1.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion

	framePos.x = 0.0f;
	framePos.y += frameRowHeight[2];
	#pragma region 스프라이트 4행
	{
		actionType = ActionType::RAISE;
		frameWidth = 68.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 44.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 41.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 58.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 97.0f, 2.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::RAISE_AIR;
		frameWidth = 49.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 52.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 55.0f, 2.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 67.0f, 2.0f * FRAME });
		clips.push_back(_actions[ActionType::RAISE]->GetClip(3));
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion

	framePos.x = 0.0f;
	framePos.y += frameRowHeight[3];
	#pragma region 스프라이트 5행
	{
		actionType = ActionType::GOG;
		frameWidth = 76.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 43.0f, 21.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 46.0f, 9.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 71.0f, 12.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 82.0f, 18.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 86.0f, 19.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 85.0f, 11.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 34.0f, 40.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion

	framePos = { 0.0f,0.0f };
	#pragma region 스프라이트 특수
	{
		actionType = ActionType::DEATH;
		frameWidth = 72.0f;
		clips.push_back({ 272.0f,268.0f,frameWidth, 32.0f, 4.0f * FRAME });
		clips.push_back({ 344.0f,268.0f,frameWidth, 32.0f, 4.0f * FRAME });
		clips.push_back({ 416.0f,268.0f,frameWidth, 32.0f, 1.0f * FRAME });
		clips.push_back({ 419.0f,236.0f,frameWidth, 32.0f, 1.0f * FRAME });
		clips.push_back({ 419.0f,204.0f,frameWidth, 32.0f, 1.0f * FRAME });
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::CLIMB;
		frameWidth = 31.0f;
		clips.push_back({ 502.0f,184.0f,frameWidth, 79.0f, 1.0f * FRAME });
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	#pragma endregion
}

void Player::SetActionType(ActionType type, bool force)
{
	// force가 true면 무조건 변환한다.
	if (force)
	{
		_curAction = type;
		return;
	}

	if (_curAction == ActionType::DEATH || _curAction == ActionType::DEATH_AIR)
		return;

	// 피격모션중에는 다른 모션으로 변환이 불가능하다
	if ((_curAction == ActionType::HIT || _curAction == ActionType::HIT_AIR) && !_movable)
		return;

	// 점프준비중일때는 점프를 제외한 모든 값을 받지않는다
	if (_curAction == ActionType::JUMP_READY && type != ActionType::JUMP)
		return;
	if (_isAttack && type == ActionType::JUMP)
		return;

	if ((_curAction == ActionType::ATTACK || _curAction == ActionType::ATTACK_AIR) && !_movable)
		return;
	_curAction = type;
}

void Player::SetAttackSpeed(float value)
{
	// 지상공격
	for (int i = 0; i < 4; i++) _actions[ActionType::ATTACK]->SetClipSpeed(i, value * FRAME);
	
	// 공중공격
	const float airDelay = 1.5f;
	for (int i = 0; i < 4; i++) _actions[ActionType::ATTACK_AIR]->SetClipSpeed(i, value * airDelay * FRAME);
	
	_attackSpeed = value;
}

void Player::SetWeapon(Player_Weapon::WeaponType type)
{
	_weapon->ChangeWeapon(type);
	SetAttackSpeed(_weapon->_weaponData[type]._speed);
}

void Player::SetArmor(ArmorType type)
{
	_curArmor = type;
	_maxHp = _defaultHp + _armorData[type]._hp;
	_hp += _armorData[type]._hp;
}

void Player::Hit(Vector2 mobPos, int damage, int knockback)
{
	CAMERA->ShakeStart(1.0f, 0.2f, 0.1f);
	_moveSpeed = (_position.x >= mobPos.x ? 1.0f : -1.0f) * knockback;
	_movable = false;
	DecreaseHp(damage);
	if (_hp <= 0)
		return;
	if (_isAir)
	{
		_jumpSpeed = 300.0f;
		SetActionType(ActionType::HIT_AIR, true);
		_actions[ActionType::HIT_AIR]->Play();
	}
	else
	{
		SetActionType(ActionType::HIT, true);
		_actions[ActionType::HIT]->Play();
	}
}

void Player::DecreaseHp(int value)
{
	int damage = value - _armorData[_curArmor]._def;
	if (damage < 0) damage = 0;
	_hp -= damage;
	if (_hp <= 0)
	{
		_hp = 0;
		_movable = false;
		_invincible = true;
		_jumpSpeed = 300.0f;
		if (_isAir)
			SetActionType(ActionType::DEATH_AIR, true);
		else
			SetActionType(ActionType::DEATH, true);
	}
}

void Player::ClipEndEvent()
{
	switch (_curAction)
	{
	case ActionType::JUMP_READY:
		_jumpSpeed = _maxJumpSpeed;
		_isAir = true;
		SetActionType(ActionType::JUMP);
		break;
	default:
		_movable = true;
		_isAttack = false;
	}
}