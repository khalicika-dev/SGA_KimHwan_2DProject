#include "framework.h"
#include "Blooding.h"

Blooding::Blooding(Vector2 pos)
: GameObject()
, _xspeed(0.0f)
, _yspeed(0.0f)
{
	_sprite = new Sprite(L"Resource/Sprites/Blooding(20x6).png");
	vector<Action::Clip> clips;
	for (int i = 0; i < 4; i++)
		clips.push_back({ 0.0f,(float)i * 6.0f,20.0f, 6.0f, 1.0f * FRAME });
	_action = new Action(clips, Action::END);

	m_trans = make_shared<Transform>();
	_position = pos;

	Init();

	m_vertexShader = SHADER->AddVS(L"VertexShader");
	m_pixelShader = SHADER->AddPS(L"ColorShader");

	m_vertexBuffer = new VertexBuffer(&m_vertices[0], sizeof(Vertex), m_vertices.size());

	m_colorBuffer = new ColorBuffer();
	m_colorBuffer->data.color = { 156.0f / 255.0f,48.0f / 255.0f,48.0f / 255.0f,1.0f };
}

Blooding::~Blooding()
{
	delete _sprite;
	delete _action;
	delete m_vertexBuffer;
	delete m_colorBuffer;
}

void Blooding::Init()
{
	_oldPos = _position;

	_state = STATE::SPLATTER;
	_isCollided = false;
	_vtxNum = Math::Random((UINT)2, _vtxMaxNum);

	m_trans->m_pos = _position;
	m_vertices.clear();
	vector<Vertex>().swap(m_vertices);
	for (int i = 0; i < _vtxNum; i++)
		m_vertices.emplace_back(0.0f, 0.0f);

	_xspeed = Math::Random(-300.0f, 300.0f);
	_yspeed = Math::Random(-50.0f, 600.0f);
	_time = 0.0f;
	_endTime = _minTime;
	_isDisappearing = false;
}

void Blooding::Update()
{
	if (_isCollided) _state = STATE::STAIN;
	_time += DELTATIME;

	switch (_state)
	{
	case STATE::SPLATTER:
		// 파티클이 날아가는 상태
		_oldPos = _position;
		_position.x += _xspeed * DELTATIME;

		_yspeed -= _yaccel * DELTATIME;
		if (_yspeed < _ymin) _yspeed = _ymin;
		_position.y += _yspeed * DELTATIME;

		m_trans->m_pos = _position;
		m_trans->UpdateWorld();

		for (int i = _vtxNum - 1; i > 0; i--)
		{
			m_vertices[i] = m_vertices[i - 1];
			m_vertices[i].pos.x -= _xspeed * DELTATIME;
			m_vertices[i].pos.y -= _yspeed * DELTATIME;
		}
		m_vertices[0] = { 0.0f, 0.0f };

		m_vertexBuffer->Update(&m_vertices[0], sizeof(Vertex), m_vertices.size());

		for (int i = 0; i < MAPMANAGER->m_terrains.size(); i++)
		{
			if (static_cast<UINT>(MAPMANAGER->m_terrains[i]->_attr) & static_cast<UINT>(LineCollider::ATTRIBUTE::INVISIBLE))
				continue;
			if (MAPMANAGER->m_terrains[i]->IsCollision(_oldPos, _position))
			{
				if (_yspeed > 0.0f && MAPMANAGER->m_terrains[i]->_direction == LineCollider::DIRECTION::FLOOR)
					continue;
				_time = 0.0f;
				_sprite->SetPosition(_position);
				_action->gotoStop(Math::Random(0, 3));
				_sprite->SetScale({ (float)_vtxNum / (float)_vtxMaxNum, (float)_vtxNum / (float)_vtxMaxNum });
				_endTime = Math::Random(_minTime, _maxTime);
				_isCollided = true;
				break;
			}
		}
		if (_time >= _spltEndTime)
		{
			_time = 0.0f;
			_isActive = false;
		}
		break;
	case STATE::STAIN:
		// 파티클이 충돌한 이후의 상태
		if (!_isDisappearing && _time >= _endTime)
		{
			_time = 0.0f;
			_isDisappearing = true;
		}
		else if (_isDisappearing && _time >= _clearTime)
		{
			_time = 0.0f;
			_isActive = false;
		}
		if (_isDisappearing) _sprite->SetAlpha(LERP(1.0f, 0.0f, _time / _clearTime));
		_action->Update();
		_sprite->SetAction(_action->GetCurClip());
		_sprite->Update();
		break;
	}
}

void Blooding::Render()
{
	switch (_state)
	{
	case STATE::SPLATTER:
		m_trans->SetWorldBuffer();

		m_vertexBuffer->Set();
		IASetPT(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		m_colorBuffer->Update();
		m_colorBuffer->SetPSBuffer(0);

		m_vertexShader->Set();
		m_pixelShader->Set();

		DEVICE_CONTEXT->Draw(m_vertices.size(), 0);
		break;
	case STATE::STAIN:
		_sprite->Render();
		break;
	}
}