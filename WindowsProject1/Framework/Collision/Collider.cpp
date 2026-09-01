#include "Framework.h"

Collider::Collider()
: m_event(nullptr)
, m_isEnable(true)
{
}

Collider::Collider(Transform* target)
: m_event(nullptr)
, m_isEnable(true)
{
	SetParent(target);
}

Collider::~Collider()
{
	delete m_vertexBuffer;
	delete m_colorBuffer;
}

void Collider::Update()
{
	if (m_isActive == false)
		return;

	Transform::UpdateWorld();
}

void Collider::Render()
{
	if (m_isActive == false || !DEBUG->GetShowCollider())
		return;

	Transform::SetWorldBuffer();
	m_vertexBuffer->Set();
	IASetPT(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

	m_colorBuffer->Update();
	m_colorBuffer->SetPSBuffer(0);

	m_vertexShader->Set();
	m_pixelShader->Set();

	DEVICE_CONTEXT->Draw(m_vertices.size(), 0);
}

void Collider::CreateData()
{
	m_vertexShader = SHADER->AddVS(L"VertexShader");
	m_pixelShader = SHADER->AddPS(L"ColorShader");

	m_vertexBuffer = new VertexBuffer(&m_vertices[0], sizeof(Vertex), m_vertices.size());

	m_colorBuffer = new ColorBuffer();
	m_colorBuffer->data.color = { 0,1,0,1 };
}

bool Collider::IsCollision(Collider* col)
{
	if (m_isActive == false || m_isEnable == false || col->m_isEnable == false)
		return false;

	switch (col->m_type)
	{
	case Collider::Type::CIRCLE:
	{
		CircleCollider* circle = dynamic_cast<CircleCollider*>(col);
		return IsCollision(circle);
	}
	break;
	case Collider::Type::RECT:
	{
		RectCollider* rect = dynamic_cast<RectCollider*>(col);
		return IsCollision(rect);
	}
	break;
	default:
		break;
	}
}