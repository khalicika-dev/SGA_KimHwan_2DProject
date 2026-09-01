#include "Framework.h"

CircleCollider::CircleCollider(float radius)
: m_radius(radius)
, m_sliceCount(20)
, m_originRadius(radius)
{
    CreateData();
}

CircleCollider::CircleCollider(float radius, Transform* target)
: m_radius(radius)
, m_sliceCount(20)
, Collider(target)
, m_originRadius(radius)
{
    CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    Collider::Update();
}

void CircleCollider::CreateData()
{
    m_type = Type::CIRCLE;

    float theta = 2.0f * PI / m_sliceCount;

    for (int i = 0; i <= m_sliceCount; i++) {
        float x = cos(theta * i) * m_radius;
        float y = sin(theta * i) * m_radius;
        m_vertices.emplace_back(x, y);
    }

    Collider::CreateData();
}

bool CircleCollider::IsCollision(Vector2 pos)
{
    float distance = (pos - this->GetWorldPos()).Length();

    return GetWorldRadius() >= distance;
}

bool CircleCollider::IsCollision(RectCollider* rect)
{
    Vector2 worldPos = this->GetWorldPos();
    RectCollider::ObbDesc obbDesc = rect->GetObb();

    // normal ea1 사각형의 각자의 단위벡터
    Vector2 nea1 = obbDesc.direction[0];
    Vector2 ea1 = nea1 * obbDesc.length[0];
    Vector2 nea2 = obbDesc.direction[1];
    Vector2 ea2 = nea2 * obbDesc.length[1];

    // 단위벡터에다 내적 걸면
    // 투영한 길이.
    float distance1 = abs((worldPos - obbDesc.position).Dot(nea1));
    float distance2 = abs((worldPos - obbDesc.position).Dot(nea2));

    // 1.두 점 사이의 x거리가 원반지름+(사각형가로변/2)보다 크다
    if (distance1 > obbDesc.length[0] + GetWorldRadius())
        return false;

    // 2.두 점 사이의 y거리가 원반지름+(사각형세로변/2)보다 크다
    if (distance2 > obbDesc.length[1] + GetWorldRadius())
        return false;

    // 3.두 점 사이의 x거리가 사각형가로변/2보다 작다
    if (distance1 < obbDesc.length[0])
        return true;

    // 4.두 점 사이의 y거리가 사각형세로변/2보다 작다
    if (distance2 < obbDesc.length[1])
        return true;

    // 극단적으로 사각형과 원의 중점이 일치하는 상황이 올 때?
    // 그 떄 distance1, 2 둘다 0이다.

    float x = distance1 - obbDesc.length[0];
    float y = distance2 - obbDesc.length[1];

    float edgeToCircle = pow(x, 2) + pow(y, 2);

    // 5.원의 중심으로부터 사각형 꼭지점까지의 거리가 원의 반지름보다 작으면 충돌한다.
    return edgeToCircle <= pow(GetWorldRadius(), 2);
}

bool CircleCollider::IsCollision(CircleCollider* circle)
{
    Vector2 worldPos = this->GetWorldPos();
    float distance = (circle->GetWorldPos() - worldPos).Length();

    return (GetWorldRadius() + circle->GetWorldRadius()) > distance;
}

float CircleCollider::GetWorldRadius()
{
    if (m_parent != nullptr)
        return m_radius * m_scale.x * m_parent->m_scale.x;

    return m_radius * m_scale.x;
}
