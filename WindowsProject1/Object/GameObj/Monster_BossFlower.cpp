#include "Framework.h"
#include "Monster_BossFlower.h"

Monster_BossFlower::Monster_BossFlower()
	: _sprite(nullptr)
	, _curAction(ActionType::IDLE)
	, _oldAction(ActionType::IDLE)
	, GameObject()
{
	_sprite = new Sprite(L"Resource/Sprites/SpriteFlowerBoss.png");
	_col = new RectCollider({ 1.0f,1.0f });
	SpriteInit();	// 스프라이트 정의
	_maxHp = 500;
	_maxAttackTime = 1.0f;
	Init();	// 스프라이트 정의
}

Monster_BossFlower::~Monster_BossFlower()
{
	for (auto& action : _actions)
		delete action.second;
	delete _sprite;
	delete _col;
}

void Monster_BossFlower::Update()
{
	_oldPos = _position;
	_oldAction = _curAction;

	// 공격판정
	if (_col->IsCollision(GET_PLAYER->GetCollider()) && _attackTime <= 0.0f)
	{
		_attackTime = DELTATIME;
		GET_PLAYER->Hit(_position, 85);
	}
	else if (_attackTime > 0.0f)
	{
		_attackTime += DELTATIME;
		if (_attackTime >= _maxAttackTime)
			_attackTime = 0.0f;
	}

	// 업데이트 주기가 되면 이동방향을 업데이트한다
	if (_updateTimer <= 0.0f)
	{
		_updateTimer = Math::Random(_minUpdateTime, _maxUpdateTime);
		
		// x축 이동부문
		if (_position.x >= OBJECT->Find(OBJTYPE::PLAYER, 0)->GetPosition().x && !_isAir && _curAction == ActionType::IDLE)
		{
			_sprite->GetTransform()->m_scale.x = 1.0f;
			_moveSpeed = -_speedValue;
		}
		else if (_position.x < OBJECT->Find(OBJTYPE::PLAYER, 0)->GetPosition().x && !_isAir && _curAction == ActionType::IDLE)
		{
			_sprite->GetTransform()->m_scale.x = -1.0f;
			_moveSpeed = _speedValue;
		}
	}
	else
	{
		_updateTimer -= DELTATIME;
	}

	// 특수행동 주기가 되면 특수행동을 실행한다.
	if (_skillTimer <= 0.0f && _curAction == ActionType::IDLE)
	{
		_skillTimer = Math::Random(_minSkillTime, _maxSkillTime);
		SetActionType(ActionType::ATTACK);
	}
	else if(_curAction == ActionType::IDLE)
	{
		_skillTimer -= DELTATIME;
	}

	// 피격판정
	if (_col->IsCollision(GET_PLAYER->GetAttackCollider()))
	{
		_col->SetColor({ 1, 0, 0, 1 });
		CAMERA->ShakeStart(0.3f, 0.1f);
		EFFECT->Play(GET_PLAYER->GetHitEffect(), _sprite->GetTransform()->m_pos, Math::Random(0.0f, 360.0f));
		UINT bldCount = Math::Random(1, 3);
		for (int i = 0; i < bldCount; i++)
			OBJECT->Generate(PTCTYPE::BLOODING, _sprite->GetTransform()->m_pos, 0.0f);
		DecreaseHp(GET_PLAYER->GetDamage());
	}
	else {
		_col->SetColor({ 0, 1, 0, 1 });
	}

	//x축 이동
	if(_curAction == ActionType::IDLE) _position.x += _moveSpeed * DELTATIME;

	//y축 이동(자유낙하)
	_jumpSpeed -= _jumpAccel * DELTATIME;
	if (_jumpSpeed < _minJumpSpeed) _jumpSpeed = _minJumpSpeed;
	_position.y += _jumpSpeed * DELTATIME;

	// 지형충돌검사
	CollideProcess();

	if (_curAction != _oldAction) _actions[_curAction]->Play();

	_actions[_curAction]->Update();
	_sprite->SetAction(_actions[_curAction]->GetCurClip());
	_sprite->GetTransform()->m_pos = { _position.x, _position.y + _actions[_curAction]->GetCurClip().size.y / 2.0f };

	_sprite->Update();
	dynamic_cast<RectCollider*>(_col)->SetSize(_actions[_curAction]->GetCurClip().size.x - 20.0f, _actions[_curAction]->GetCurClip().size.y / 2.0f);
	_col->m_pos = _position + Vector2(0.0f, _col->GetSize().y / 2.0f) + _actions[_curAction]->GetCurClip().pivot * (_sprite->GetTransform()->m_scale.x >= 0.0f ? -1.0f : 1.0f);
	_col->Update();
}

void Monster_BossFlower::Render()
{
	_sprite->Render();
	_col->Render();
}

void Monster_BossFlower::Init()
{
	_curAction = ActionType::IDLE;
	_oldAction = ActionType::IDLE;
	_hp = _maxHp;
	_sprite->GetTransform()->m_scale.x = 1.0f;
	_moveSpeed = -_speedValue;
	_jumpSpeed = 0.0f;
	_isAir = false;
	_movable = true;
	_attackTime = 0.0f;
	_skillTimer = 0.0f;
	_updateTimer = Math::Random(_minUpdateTime, _maxUpdateTime);
}

void Monster_BossFlower::SpriteInit()
{
	vector<Action::Clip> clips;
	Vector2	framePos = { 0.0f,0.0f };	// 클립프레임을 생성하고자 하는 스프라이트의 위치
	float	frameWidth = 0.0f;			// 한 클립의 프레임 폭
	float	frameRowHeight[] = { 185.0f };	// 스프라이트 각 1행의 높이
	ActionType actionType;	// 한 액션의 타입

	framePos.x = 0.0f;
	framePos.y += 0.0f;
	{
		actionType = ActionType::IDLE;
		frameWidth = 138.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 35.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 35.0f * FRAME });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::LOOP));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);	// 벡터 기본생성자와 swap을 하여 clips의 capacity를 0으로 만들어 메모리를 해제한다.
	{
		actionType = ActionType::ATTACK;
		frameWidth = 138.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 6.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 4.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 3.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 3.0f * FRAME });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 185.0f, 24.0f * FRAME });
		framePos.x += frameWidth;

		framePos.x = 0.0f;
		framePos.y += frameRowHeight[0];
		frameWidth = 200.0f;
		framePos.x -= frameWidth;
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 105.0f, 2.0f * FRAME, 36.0f, 0.0f });
		clips.push_back({ framePos.x += frameWidth,framePos.y,frameWidth, 105.0f, 28.0f * FRAME, 36.0f, 0.0f });
		framePos.x += frameWidth;
		_actions.emplace(actionType, new Action(clips, Action::END, bind(&Monster_BossFlower::ClipEndEvent, this)));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
}

void Monster_BossFlower::SetActionType(ActionType type)
{
	_curAction = type;
}

void Monster_BossFlower::DecreaseHp(int value)
{
	_hp -= value;
	UISTATE->SetTargetHp(_hp, _maxHp);
	if (_hp <= 0)
	{
		EFFECT->Play(L"death_dust", _sprite->GetTransform()->m_pos, Math::Random(0.0f, 360.0f), { 2.0f,2.0f });
		for (int i = 0; i < 15; i++)
		{
			shared_ptr<Gold> temp = dynamic_pointer_cast<Gold>(OBJECT->Generate(PTCTYPE::GOLD, _sprite->GetTransform()->m_pos, 0.0f));
			temp->SetGold(Math::Random(25, 75));
			temp->SetMoveSpeed(Math::Random(-400.0f, 400.0f));
		}
		SetActive(false);
	}
}

void Monster_BossFlower::ClipEndEvent()
{
	SetActionType(ActionType::IDLE);
}