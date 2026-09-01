#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
: m_size(size)
, m_isObb(true)
{
    CreateData();
}

RectCollider::RectCollider(Vector2 size, Transform* target)
: m_size(size)
, m_isObb(true)
, Collider(target)
{
    CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::CreateData()
{
    m_type = Type::RECT;

    float width = m_size.x * 0.5f;
    float height = m_size.y * 0.5f;

    m_vertices.emplace_back( -width, -height);
    m_vertices.emplace_back(  width, -height);
    m_vertices.emplace_back(  width,  height);
    m_vertices.emplace_back( -width,  height);
    m_vertices.emplace_back( -width, -height);

    Collider::CreateData();
}

void RectCollider::SetSize(float w, float h)
{
    if (w != 0.0f) m_size.x = w;
    if (h != 0.0f) m_size.y = h;

    float width = m_size.x * 0.5f;
    float height = m_size.y * 0.5f;

    m_vertices[0] = { -width, -height};
    m_vertices[1] = {  width, -height};
    m_vertices[2] = {  width,  height};
    m_vertices[3] = { -width,  height};
    m_vertices[4] = { -width, -height};

    m_vertexBuffer->Update(&m_vertices[0], sizeof(Vertex), m_vertices.size());
}

bool RectCollider::AABB(RectCollider* rect)
{
    if (Right() < rect->Left() || rect->Right() < Left() ||
        Top() < rect->Bottom() || rect->Top() < Bottom())
        return false;

    return true;
}

bool RectCollider::OBB(RectCollider* rect)
{
    // 각 사각형의 변의 정사영의 길이와 두 사각형의 중심의 정사영의 길이를 서로 비교하는 충돌판정법

    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    // 사각형의 각자의 단위벡터
    Vector2 nea1 = obbA.direction[0];
    Vector2 ea1 = nea1 * obbA.length[0];    // A 가로의 벡터를 구함
    Vector2 nea2 = obbA.direction[1];
    Vector2 ea2 = nea2 * obbA.length[1];    // B 세로의 벡터를 구함

    Vector2 neb1 = obbB.direction[0];
    Vector2 eb1 = neb1 * obbB.length[0];    // A 가로의 벡터를 구함
    Vector2 neb2 = obbB.direction[1];
    Vector2 eb2 = neb2 * obbB.length[1];    // B 세로의 벡터를 구함
    
    Vector2 distance = obbA.position - obbB.position;

    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1, eb1, eb2);
    float length = abs(distance.Dot(nea1));
    if (length > lengthA + lengthB)
        return false;

    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);
    length = abs(distance.Dot(nea2));
    if (length > lengthA + lengthB)
        return false;

    lengthA = eb1.Length();
    lengthB = SeparateAxis(neb1, ea1, ea2);
    length = abs(distance.Dot(neb1));
    if (length > lengthA + lengthB)
        return false;

    lengthA = eb2.Length();
    lengthB = SeparateAxis(neb2, ea1, ea2);
    length = abs(distance.Dot(neb2));
    if (length > lengthA + lengthB)
        return false;

    return true;
}

float RectCollider::SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{
    float r1 = abs(separate.Dot(e1));
    float r2 = abs(separate.Dot(e2));
    return r1 + r2;
}

RectCollider::ObbDesc RectCollider::GetObb()
{
    ObbDesc obbDesc;

    obbDesc.position = GetWorldPos();

    obbDesc.length[0] = GetWorldSizeXY().x * 0.5f;
    obbDesc.length[1] = GetWorldSizeXY().y * 0.5f;

    Float4x4 world;
    XMStoreFloat4x4(&world, m_matrix);

    obbDesc.direction[0] = { world._11,world._12 };
    obbDesc.direction[1] = { world._21,world._22 };

    obbDesc.direction[0].Normalize();
    obbDesc.direction[1].Normalize();

    return obbDesc;
}

bool RectCollider::IsCollision(Vector2 worldPos)
{
    ObbDesc obb = GetObb();
    Vector2 v =
    {
        (worldPos - obb.position).Dot(obb.direction[0]),
        (worldPos - obb.position).Dot(obb.direction[1])
    };

    if (abs(v.x) <= obb.length[0] && abs(v.y) <= obb.length[1])
        return true;
    return false;
}

bool RectCollider::IsCollision(RectCollider* rect)
{
    return OBB(rect);
}

bool RectCollider::IsCollision(CircleCollider* circle)
{
    return circle->IsCollision(this);
}

Float2 RectCollider::GetWorldSizeXY()
{
    if (m_parent != nullptr)
    {
        return m_size * m_scale * m_parent->m_scale;
    }

    return m_size * m_scale;
}
