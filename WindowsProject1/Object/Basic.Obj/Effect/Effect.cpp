#include "Framework.h"
#include "Effect.h"

Effect::Effect(wstring textureFile, UINT maxFrameX, UINT maxFrameY, vector<float> speed)
: _isAdditive(false)
, _isActive(false)
{
	_sprite = new Sprite(textureFile);

	SetPosition({ 0,0 });

	vector<Action::Clip> clips;

	float sizeX = _sprite->GetSize().x / maxFrameX;
	float sizeY = _sprite->GetSize().y / maxFrameY;

	for (int i = 0; i < maxFrameY; i++)
	{
		for (int j = 0; j < maxFrameX; j++)
		{
			clips.emplace_back(j * sizeX, i * sizeY, sizeX, sizeY, static_cast<float>(speed[i * maxFrameX + j]) * FRAME);
		}
	}

	_action = new Action(clips, Action::END);

	_action->SetEvent(bind(&Effect::End, this));
}

Effect::~Effect()
{
	delete _sprite;
	delete _action;
}

void Effect::Update()
{
	if (_isActive == false)
		return;
	_action->Update();
	_sprite->SetAction(_action->GetCurClip());

	_sprite->Update();
}

void Effect::Render()
{
	if (!_isActive)
		return;

	if (_isAdditive)
		AdditiveBlendState->SetState();
	else
		AlphaBlendState->SetState();

	_sprite->Render();
}

void Effect::Play(Vector2 pos, float angle, Vector2 scale)
{
	_isActive = true;
	_sprite->SetPosition(pos);
	_sprite->GetTransform()->m_angle = angle * (PI / 180.0f);
	_sprite->GetTransform()->m_scale = scale;

	_action->Play();
}

void Effect::End()
{
	_isActive = false;
}
