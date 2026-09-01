#include "Framework.h"
#include "Gold.h"

Gold::Gold(Vector2 pos)
: _sprite(nullptr)
, _curAction(ActionType::SMALL)
, _oldAction(ActionType::SMALL)
, GameObject()
{
	_sprite = new Sprite(L"Resource/Sprites/GoldSprite.png");
	_col = new RectCollider({ 1.0f,1.0f }, _sprite->GetTransform());
	_position = pos;

	SpriteInit();
	Init();
}

Gold::~Gold()
{
	for (auto& action : _actions)
		delete action.second;
	delete _sprite;
	delete _col;
}

void Gold::SpriteInit()
{
	vector<Action::Clip> clips;
	ActionType actionType;	// 한 액션의 타입

	{
		actionType = ActionType::SMALL;
		clips.push_back({0.0f,0.0f,27.0f, 11.0f, 1.0f * FRAME });
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::MEDIUM;
		clips.push_back({ 0.0f,11.0f,33.0f, 36.0f, 1.0f * FRAME });
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
	{
		actionType = ActionType::LARGE;
		clips.push_back({ 33.0f,0.0f,112.0f, 80.0f, 1.0f * FRAME });
		_actions.emplace(actionType, new Action(clips, Action::END));
	}
	clips.clear();
	vector<Action::Clip>().swap(clips);
}

void Gold::Init()
{
	_gold = 0;
	_moveSpeed = 0.0f;
	_jumpSpeed = Math::Random(200.0f, 500.0f);
}

void Gold::Update()
{
	_oldPos = _position;
	_oldAction = _curAction;

	if (_gold < 50)
		_curAction = ActionType::SMALL;
	else if(_gold < 1000)
		_curAction = ActionType::MEDIUM;
	else
		_curAction = ActionType::LARGE;

	if (_moveSpeed > 0.0f)
	{
		_sprite->GetTransform()->m_scale.x = 1.0f;
		if (!_isAir)
		{
			_moveSpeed -= _moveAccel * DELTATIME;
			if (_moveSpeed < 0.0f) _moveSpeed = 0.0f;
		}
	}
	else if (_moveSpeed < 0.0f)
	{
		_sprite->GetTransform()->m_scale.x = -1.0f;
		if (!_isAir)
		{
			_moveSpeed += _moveAccel * DELTATIME;
			if (_moveSpeed > 0.0f) _moveSpeed = 0.0f;
		}
	}

	// 피격판정
	if (_col->IsCollision(GET_PLAYER->GetCollider()))
	{
		UISTATE->AddGold(_gold);
		SetActive(false);
	}
	else {
		_col->SetColor({ 0, 1, 0, 1 });
	}

	//x축 이동
	_position.x += _moveSpeed * DELTATIME;

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
	dynamic_cast<RectCollider*>(_col)->SetSize(_actions[_curAction]->GetCurClip().size.x, _actions[_curAction]->GetCurClip().size.y);
	_col->Update();
}

void Gold::Render()
{
	_sprite->Render();
	_col->Render();
}
