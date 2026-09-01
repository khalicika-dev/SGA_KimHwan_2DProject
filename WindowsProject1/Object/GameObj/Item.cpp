#include "Framework.h"
#include "Item.h"

Item::Item()
	: _sprite(nullptr)
	, _curAction(ActionType::NONE)
	, GameObject()
{
	_sprite = new Sprite(L"Resource/Sprites/ItemSprite.png");
	_col = new RectCollider({ 1.0f,1.0f }, _sprite->GetTransform());
	Init();	// 스프라이트 정의
}

Item::~Item()
{
	delete _sprite;
	if (_action != nullptr) delete _action;
	delete _col;
}

void Item::Update()
{
	_oldPos = _position;

	if (UISTATE->IsAcquired(static_cast<UIStateManager::AcquireStatus>(_curAction)))
		return;

	// 피격판정
	if (_col->IsCollision(GET_PLAYER->GetCollider()) && OBJECT->GetPickable())
	{
		_col->SetColor({ 1, 0, 0, 1 });
		OBJECT->SetPickable(false);
		if (KEYDOWN('D') && GET_PLAYER->GetMovable())
		{
			UISTATE->Acquire(static_cast<UIStateManager::AcquireStatus>(_curAction));
			switch(_curAction)
			{
			case ActionType::WEAPON_NORMAL:
				GET_PLAYER->SetWeapon(Player_Weapon::WeaponType::NORMAL);
				UISTATE->SetDialogText(L"'곡괭이'를 얻었다");
				break;
			case ActionType::ARMOR_NORMAL:
				GET_PLAYER->SetArmor(Player::ArmorType::NORMAL);
				UISTATE->SetDialogText(L"'평범한 갑옷'을 얻었다");
				break;
			}
		}
	}
	else {
		_col->SetColor({ 0, 1, 0, 1 });
	}

	switch (_curAction)
	{
	case ActionType::WEAPON_NORMAL:
		_sprite->GetTransform()->m_angle = (15.0f) * (PI / 180.0f);
		break;
	case ActionType::ARMOR_NORMAL:
		break;
	}
	_action->Update();
	_sprite->SetAction(_action->GetCurClip());
	_sprite->GetTransform()->m_pos = { _position.x, _position.y + _action->GetCurClip().size.y / 2.0f };

	_sprite->Update();
	dynamic_cast<RectCollider*>(_col)->SetSize(_action->GetCurClip().size.x, _action->GetCurClip().size.y);
	_col->Update();
}

void Item::Render()
{
	if (UISTATE->IsAcquired(static_cast<UIStateManager::AcquireStatus>(_curAction)))
		return;

	_sprite->Render();
	_col->Render();
}

void Item::Init()
{
	SetItemType(ActionType::NONE);	// 스프라이트 정의
}

void Item::SetItemType(ActionType type)
{
	vector<Action::Clip> clips;
	if (_action != nullptr) delete _action;

	switch(type)
	{
	case ActionType::NONE:
		clips.push_back({ 48.0f, 0.0f, 22.0f, 24.0f, 1.0f * FRAME });
		_action = new Action(clips, Action::END);
		break;
	case ActionType::WEAPON_NORMAL:
		clips.push_back({ 0.0f, 0.0f, 48.0f, 69.0f, 1.0f * FRAME });
		_action = new Action(clips, Action::END);
		break;
	case ActionType::ARMOR_NORMAL:
		clips.push_back({ 48.0f, 24.0f, 22.0f, 24.0f, 1.0f * FRAME });
		_action = new Action(clips, Action::END);
		break;
	}
	_curAction = type;
}
