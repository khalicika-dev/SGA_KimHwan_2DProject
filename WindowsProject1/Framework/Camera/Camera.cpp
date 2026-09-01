#include "Framework.h"
#include "Camera.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
: _speed(10.0f)
, _target(nullptr)
, _offset(CENTER_X,CENTER_Y - 76.0f)
, _duration(0.0f)
, _reduceDamping(0.0f)
, _magnitude(0.0f)
, _originPos(0,0)
{
	_postCamera = make_shared<Transform>();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	
	//if (_target == nullptr)
	//	FreeMode();
	//else
	//	FollowMode();
	if (_target)
		FollowMode();
	m_pos = _originPos;

	Shake();

	Transform::UpdateWorld();
	Transform::SetWorldBuffer(1);
}

void Camera::PostUpdate()
{
	_postCamera->UpdateWorld();
	_postCamera->SetWorldBuffer(1);
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
	_magnitude = magnitude;
	_duration = duration;
	_reduceDamping = reduceDamping;
}

Vector2 Camera::GetMouseWorldPos()
{
	Matrix invView = XMMatrixInverse(nullptr, m_matrix);

	return Vector2::TransformCoord(mousePos, invView);
}

void Camera::FreeMode()
{
	if (KEYPRESS(VK_RBUTTON))
	{
		if (KEYPRESS('W')) _originPos.y -= _speed * DELTATIME;
		if (KEYPRESS('S')) _originPos.y += _speed * DELTATIME;
		if (KEYPRESS('A')) _originPos.x += _speed * DELTATIME;
		if (KEYPRESS('D')) _originPos.x -= _speed * DELTATIME;
	}
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target->GetPosition() - _offset;

	if (targetPos.x < _leftBottom.x)
		targetPos.x = _leftBottom.x;
	if (targetPos.x > _rightTop.x - WINWIDTH)
		targetPos.x = _rightTop.x - WINWIDTH;
	if (targetPos.y < _leftBottom.y)
		targetPos.y = _leftBottom.y;
	if (targetPos.y > _rightTop.y - WINHEIGHT)
		targetPos.y = _rightTop.y - WINHEIGHT;

	_originPos = LERP(_originPos, targetPos * -1, DELTATIME * _speed);
}

void Camera::Shake()
{
	if (_duration <= 0.0f)
		return;

	_duration -= DELTATIME;
	_magnitude -= DELTATIME * _reduceDamping;

	if (_magnitude < 0.0f)
	{
		_magnitude = 0.0f;
		_duration = 0.0f;
	}

	Vector2 temp;
	temp.x = Math::Random(-_magnitude, _magnitude);
	temp.y = Math::Random(-_magnitude, _magnitude);
	m_pos = _originPos + temp;

	if (_duration <= 0.0f)
	{
		m_pos = _originPos;
	}
}
