#include "Framework.h"
#include "UIStateManager.h"

UIStateManager* UIStateManager::m_instance = nullptr;

void UIStateManager::Update()
{
	// È­¸éÀüÈ¯
	{
		if (_fade != FADE_STATE::NONE)
			_fadeTime += DELTATIME;

		float alpha;
		switch (_fade)
		{
		case FADE_STATE::FADE_IN: alpha = LERP(0.0f, 1.0f, _fadeTime / _fadeMaxTime); break;
		case FADE_STATE::FADE_OUT: alpha = LERP(1.0f, 0.0f, _fadeTime / _fadeMaxTime); break;
		case FADE_STATE::FADE_PEAK: alpha = 1.0f; break;
		default: alpha = 0.0f;
		}
		_fadeRect->SetColor({ 0.0f, 0.0f, 0.0f, alpha });

		if (_fadeTime >= _fadeMaxTime || _fade == FADE_STATE::FADE_PEAK)
		{
			_fadeTime = 0.0f;
			switch (_fade)
			{
			case FADE_STATE::FADE_IN:
				_fade = FADE_STATE::FADE_PEAK;
				break;
			case FADE_STATE::FADE_PEAK:
				MAPMANAGER->ChangeMap(_nextScene, _nextPlayerPos, true);
				_fade = FADE_STATE::FADE_OUT;
				break;
			case FADE_STATE::FADE_OUT:
				_fade = FADE_STATE::NONE;
				break;
			}
		}
	}

	// ´ÙÀÌ¾ó·Î±× ÅØ½ºÆ®
	{
		if (_textTimer <= 0.0f)
			_dialogText = L"";
		else
			_textTimer -= DELTATIME;

		size_t start = 0;
		size_t end = 0;
		size_t length = 0;
		_drWidth = 0;
		_drHeight = 0;
		if (_dialogText != L"")
		{
			do
			{
				end = _dialogText.find(L"\n", start);
				if (end == string::npos) end = _dialogText.length();
				length = _dialogText.substr(start, end - start).length();
				if (length > _drWidth) _drWidth = length;
				_drHeight++;
				start = end + 1;
			} while (end != _dialogText.length());
		}
	}

	_dialogRect->SetScale({ static_cast<float>(_drWidth) * 13.0f + 5.0f, static_cast<float>(_drHeight) * 17.0f + 4.0f });

	_playerHp->GetTransform()->m_scale.x = static_cast<float>(GET_PLAYER->GetHp());
	_playerEmptyHp->GetTransform()->m_scale.x = static_cast<float>(GET_PLAYER->GetMaxHp());

	_dialogRect->Update();
	_fadeRect->Update();
	_playerEmptyHp->Update();
	_playerHp->Update();

	_enemyEmptyHp->Update();
	_enemyHp->Update();
	_enemyIcon->Update();


	_atkIconRect->Update();
	_iconAtkActions[GET_PLAYER->GetWeapon()]->Update();
	_weaponIcon->SetAction(_iconAtkActions[GET_PLAYER->GetWeapon()]->GetCurClip());
	_weaponIcon->Update();

	_defIconRect->Update();
	_iconDefActions[GET_PLAYER->GetArmor()]->Update();
	_armorIcon->SetAction(_iconDefActions[GET_PLAYER->GetArmor()]->GetCurClip());
	_armorIcon->Update();
}

void UIStateManager::Render()
{
	DirectWrite::Get()->GetDC()->BeginDraw();

	_playerEmptyHp->Render();
	_playerHp->Render();

	_enemyEmptyHp->Render();
	_enemyHp->Render();
	_enemyIcon->Render();

	if (_dialogText != L"") _dialogRect->Render();

	DirectWrite::Get()->RenderText(L"hp", { 10,0,50,10 }, 15.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"±Ã¼­", { 0.0f,0.0f,0.0f,1.0f }, DWRITE_FONT_WEIGHT_BOLD);
	DirectWrite::Get()->RenderText(L"Money", { 5,25,55,45 }, 12.0f, DWRITE_TEXT_ALIGNMENT_TRAILING, L"±Ã¼­", { 0.0f,0.0f,0.0f,1.0f }, DWRITE_FONT_WEIGHT_BOLD);
	DirectWrite::Get()->RenderText(to_wstring(_gold) + L" gold", { 60,26,500,50 }, 12.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"µ¸¿ò");
	DirectWrite::Get()->RenderText(to_wstring(GET_TIMER->GetFPS()) + L"fps", { 12,60,50,100 }, 12.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"µ¸¿ò");

	DirectWrite::Get()->RenderText(L"Weapon", { 25 - 30,110,25 + 30,130 }, 11.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"µ¸¿ò");
	DirectWrite::Get()->RenderText(L"Armor", { 70 - 30,110,70 + 30,130 }, 11.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"µ¸¿ò");

	DirectWrite::Get()->RenderText(_dialogText, { 0,60,WINWIDTH,WINHEIGHT }, 13.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"¸¼Àº °íµñ", { 1,1,1,1 });

	DirectWrite::Get()->GetDC()->EndDraw();

	_fadeRect->Render();

	_atkIconRect->Render();
	_weaponIcon->Render();

	_defIconRect->Render();
	_armorIcon->Render();
}

void UIStateManager::Initialize()
{
	_acquire_status = AcquireStatus::NONE;
	_gold = 0;

	if (OBJECT->FindPlayer())
		GET_PLAYER->All_Initialize();
}

void UIStateManager::SetTargetHp(int hp, int maxHp)
{
	if (hp < 0) hp = 0;
	_enemyHp->GetTransform()->m_scale.x = (float)hp / (float)maxHp;
}

void UIStateManager::FadeScene(MAP targetScene, Vector2 playerPos)
{
	if (_fade != FADE_STATE::NONE)
		return;
	_nextScene = targetScene;
	_nextPlayerPos = playerPos;
	_fade = FADE_STATE::FADE_IN;
	_fadeTime = 0.0f;
}

bool UIStateManager::IsFading()
{
	return _fade != FADE_STATE::NONE;
}

void UIStateManager::SetDialogText(wstring text, float timer)
{
	_dialogText = text;
	if(timer > 0.0f)
		_textTimer = timer;
	else
	{
		_textTimer = text.length() + 3.0f;
	}
}

UIStateManager::UIStateManager()
: _fade(FADE_STATE::NONE)
, _acquire_status(AcquireStatus::NONE)
, _fadeTime(0.0f)
, _gold(0)
, _dialogText(L"")
, _drWidth(0)
, _drHeight(0)
, _textTimer(0.0f)
{
	_fadeRect = new Quad(Float4(0.0f, 0.0f, 0.0f, 0.0f), true, WINWIDTH * 1.5f, WINHEIGHT * 1.5f);
	_fadeRect->GetTransform()->m_pos = { CENTER_X,CENTER_Y };

	_playerEmptyHp = new Quad(Float4(0.0f, 0.0f, 0.0f, 0.3f), true, 1.0f, 5.0f);
	_playerHp = new Quad(Float4(156.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f), true, 1.0f, 5.0f);
	_playerEmptyHp->GetTransform()->m_pos = { 10.5f, WINHEIGHT - 21.5f };
	_playerHp->GetTransform()->m_pos = { 10.5f, WINHEIGHT - 21.5f };
	_playerHp->GetTransform()->m_pivot = { -1.0f / 2.0f,0.0f };
	_playerEmptyHp->GetTransform()->m_pivot = { -1.0f / 2.0f,0.0f };

	_enemyEmptyHp = new Quad(Float4(0.0f, 0.0f, 0.0f, 0.3f), true, 307.0f, 7.0f);
	_enemyHp = new Quad(Float4(156.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f), true, 307.0f, 7.0f);
	_enemyIcon = new Quad(L"Resource/Textures/Icon_Enemy.png");
	_enemyEmptyHp->GetTransform()->m_pos = { CENTER_X, 18.5f };
	_enemyHp->GetTransform()->m_pos = { CENTER_X, 18.5f };
	_enemyHp->GetTransform()->m_pivot = { -307.0f / 2.0f, 0.0f };
	_enemyHp->GetTransform()->m_scale.x = 0.0f;
	_enemyIcon->GetTransform()->m_pos = { CENTER_X - 152.0f, 19.5f };

	_dialogRect = new Quad(Float4(0.0f, 0.0f, 0.0f, 0.6f), true, 1.0f, 1.0f);
	_dialogRect->GetTransform()->m_pos = { CENTER_X, WINHEIGHT - 60.0f };
	_dialogRect->GetTransform()->m_pivot = { 0.0f,0.5f };

	_atkIconRect = new Quad(Float4(0, 0, 0, 1), false, 30.0f, 30.0f);
	_atkIconRect->GetTransform()->m_pos = { 25.0f, WINHEIGHT - 95.0f };
	_defIconRect = new Quad(Float4(0, 0, 0, 1), false, 30.0f, 30.0f);
	_defIconRect->GetTransform()->m_pos = { 70.0f, WINHEIGHT - 95.0f };

	_weaponIcon = new Sprite(L"Resource/Sprites/Icons(30x30).png");
	_weaponIcon->GetTransform()->m_pos = { 25.0f, WINHEIGHT - 95.0f };
	_armorIcon = new Sprite(L"Resource/Sprites/Icons(30x30).png");
	_armorIcon->GetTransform()->m_pos = { 70.0f, WINHEIGHT - 95.0f };
	SpriteInit_Icon();
}

UIStateManager::~UIStateManager()
{
	delete _fadeRect;
	delete _playerHp;
	delete _playerEmptyHp;
	delete _enemyHp;
	delete _enemyEmptyHp;
	delete _enemyIcon;
	delete _dialogRect;
	delete _atkIconRect;
	delete _defIconRect;
	delete _weaponIcon;
	delete _armorIcon;

	for (auto& iconAction : _iconAtkActions) delete iconAction.second;
	for (auto& iconAction : _iconDefActions) delete iconAction.second;
}

void UIStateManager::SpriteInit_Icon()
{
	float x = 0.0f;
	float y = 0.0f;
	float w = 30.0f;
	float h = 30.0f;

	// Weapon ºÎ¹®
	{
		x -= w;
		_iconAtkActions.emplace(Player_Weapon::WeaponType::FIST, new Action({ { x += w, y, w, h, 1.0f * FRAME } }, Action::END));
		_iconAtkActions.emplace(Player_Weapon::WeaponType::NORMAL, new Action({ { x += w, y, w, h, 1.0f * FRAME } }, Action::END));
	}
	x = 0.0f; y += h;

	//Armor ºÎ¹®
	{
		x -= w;
		_iconDefActions.emplace(Player::ArmorType::NONE, new Action({ { x += w, y, w, h, 1.0f * FRAME } }, Action::END));
		_iconDefActions.emplace(Player::ArmorType::NORMAL, new Action({ { x += w, y, w, h, 1.0f * FRAME } }, Action::END));
	}
}