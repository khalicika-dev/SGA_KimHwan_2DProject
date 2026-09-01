#include "Framework.h"
#include "Transform.h"

Transform::Transform(string tag)
: m_tag			(tag)
, m_pos			(0,0)
, m_angle		(0)
, m_scale		(1,1)
, m_pivot		(0,0)
, m_parent		(nullptr)
, m_worldBuffer	(nullptr)
, m_matrix		(XMMatrixIdentity())
, m_isActive	(true)
, _matWorld()
{
	m_matrix = XMMatrixIdentity();
	m_worldBuffer = new MatrixBuffer();
}

Transform::~Transform()
{
	delete m_worldBuffer;
}

Vector2 Transform::GetWorldPos()
{
	return Vector2(_matWorld._41, _matWorld._42);
}

void Transform::UpdateWorld()
{
	if (m_isActive == false)
		return;
	S = XMMatrixScaling(m_scale.x, m_scale.y, 1.0f);
	R = XMMatrixRotationZ(m_angle);
	T = XMMatrixTranslation(m_pos.x, m_pos.y, 0.0f);
	P = XMMatrixTranslation(m_pivot.x, m_pivot.y, 0.0f);
	IP = XMMatrixInverse(nullptr, P);

	m_matrix = IP * S * R * T * P;

	if (m_parent != nullptr)
		m_matrix *= (*m_parent->GetMatrix());

	XMStoreFloat4x4(&_matWorld, m_matrix);

	m_worldBuffer->Set(m_matrix);
	m_worldBuffer->Update();
}

void Transform::SetWorldBuffer(UINT slot)
{
	m_worldBuffer->SetVSBuffer(slot);
}
