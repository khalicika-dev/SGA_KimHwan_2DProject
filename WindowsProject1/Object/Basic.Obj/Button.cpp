#include "Framework.h"
#include "Button.h"

Button::Button(wstring file)
	: _collider(nullptr)
	, _delegate(nullptr)
	, _colorBuffer(nullptr)
	, _state(State::NONE)
	, _pressed(false)
	, Quad(file)
{
	Vector2 size = Quad::GetSize();
	_collider = new RectCollider(size, this->m_trans.get());
	_colorBuffer = new ColorBuffer();

	SetPSShader(SHADER->AddPS(L"ButtonShader"));
}

Button::~Button()
{
	delete _collider;
	delete _colorBuffer;
}

void Button::Update()
{
	Quad::Update();
	_collider->Update();

	if (_collider->IsCollision(mousePos))
	{
		_state = State::OVER;
		if ((KEYDOWN(VK_LBUTTON) && !_pressed) || _pressed)
		{
			_state = State::DOWN;
			_pressed = true;
		}

		if (KEYUP(VK_LBUTTON))
		{
			if (_state == State::DOWN && _pressed)
			{
				if (_delegate != nullptr)
					_delegate();
				_pressed = false;
			}
		}
	}
	else
	{
		_state = State::NONE;
		if (KEYUP(VK_LBUTTON))
		{
			_pressed = false;
		}
	}

	switch (_state)
	{
	case Button::State::NONE:
		_collider->SetColor({ 0,1,0,1 });
		_colorBuffer->data.color = Float4(0.2f, 0.2f, 0.2f, 1.0f);
		break;
	case Button::State::DOWN:
		_collider->SetColor({ 1,0,0,1 });
		_colorBuffer->data.color = Float4(0.1f, 0.1f, 0.1f, 1.0f);
		break;
	case Button::State::OVER:
		_collider->SetColor({ 1,0.5,0,1 });
		_colorBuffer->data.color = Float4(0.3f, 0.3f, 0.3f, 1.0f);
		break;
	default:
		break;
	}
}

void Button::Render()
{
	AlphaBlendState->SetState();
	_colorBuffer->SetPSBuffer(0);
	Quad::Render();

	_collider->Render();
}
