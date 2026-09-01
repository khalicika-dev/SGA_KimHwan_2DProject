#include "Framework.h"
#include "LineCollider.h"

LineCollider::LineCollider(Vector2 v1, Vector2 v2, DIRECTION direction, ATTRIBUTE attr)
: _p1(v1)
, _p2(v2)
, _direction(direction)
, _attr(attr)
, _prev(nullptr)
, _next(nullptr)
{
    CreateData();
}

LineCollider::~LineCollider()
{
}

void LineCollider::Update()
{
	Collider::Update();
}

void LineCollider::CreateData()
{
    m_type = Type::LINE;

    m_vertices.emplace_back(_p1.x, _p1.y);
    m_vertices.emplace_back(_p2.x, _p2.y);

    Collider::CreateData();
}

bool LineCollider::IsCollision(Vector2 p1, Vector2 p2)
{

    // 1.두 선분의 외적이 0이 아니어야한다.
    if (fabs(p1.Cross(p2)) <= 0.01f)
        return false;

    // 2. 두 직선의 교점을 구한다.
    Vector2 v = GetCrossPT(p1, p2);

    // 3.두 직선의 교점이  각 선분의 범위에 있어야한다.
    const float epsilon1 = 0.3f;
    bool xcond, ycond;
    // 선분 [p1,p2]
    xcond = ycond = false;
    if ((v.x >= min(p1.x, p2.x) && v.x <= max(p1.x, p2.x)) ||
        (fabsf(v.x - p1.x) <= epsilon1 && fabsf(v.x - p2.x) <= epsilon1))
        xcond = true;
    if ((v.y >= min(p1.y, p2.y) && v.y <= max(p1.y, p2.y)) ||
        (fabsf(v.y - p1.y) <= epsilon1 && fabsf(v.y - p2.y) <= epsilon1))
        ycond = true;
    if (!xcond || !ycond) return false;

    // 선분 [_p1,_p2]
    const float epsilon2 = 0.1f;
    xcond = ycond = false;
    if ((v.x >= min(_p1.x, _p2.x) && v.x <= max(_p1.x, _p2.x)) ||
        (fabsf(v.x - _p1.x) <= epsilon2 && fabsf(v.x - _p2.x) <= epsilon2))
        xcond = true;
    if ((v.y >= min(_p1.y, _p2.y) && v.y <= max(_p1.y, _p2.y)) ||
        (fabsf(v.y - _p1.y) <= epsilon2 && fabsf(v.y - _p2.y) <= epsilon2))
        ycond = true;
    if (!xcond || !ycond) return false;

    return true;
}

bool LineCollider::IsCollision(Vector2 worldPos)
{
	return false;
}

bool LineCollider::IsCollision(RectCollider* rect)
{
	return false;
}

bool LineCollider::IsCollision(CircleCollider* circle)
{
	return false;
}

bool LineCollider::FloorCollision(Vector2 pos)
{
    if(_direction != LineCollider::DIRECTION::FLOOR)
        return false;

    Vector2 pt = GetCrossPT(pos, { pos.x,pos.y + 1 });
    if ((pt - pos).Length() <= 2.0f && pos.x >= min(_p1.x, _p2.x) && pos.x <= max(_p1.x, _p2.x))
        return true;
    return false;
}

Vector2 LineCollider::GetCollidePT(Vector2 pos)
{
    // DIRECTION이 WALL타입이라면 수평되는 교직선을, FLOOR라면 수직교직선을 생성하여 교점을 구한다.
    Vector2 pos2;
    pos2.x = pos.x + (_direction == LineCollider::DIRECTION::LWALL || _direction == LineCollider::DIRECTION::RWALL);
    pos2.y = pos.y + (_direction == LineCollider::DIRECTION::FLOOR);
    Vector2 solution = GetCrossPT(pos, pos2);

    if (_direction == LineCollider::DIRECTION::FLOOR)
    {
        //if (_prev && _prev->_direction == DIRECTION::LWALL && pos.x <= _prev->_p2.x)
        //    solution.x = pos.x + 30.1f;
        //else if (_next && _next->_direction != DIRECTION::RWALL && pos.x >= _next->_p1.x)
        //    solution.x = pos.x - 30.1f;
        //else
        //    solution.x = pos.x;
        solution.x = pos.x;
        solution.y += 0.1f;

        if (solution.x < min(_p1.x, _p2.x) && _prev && _prev->_direction == LineCollider::DIRECTION::FLOOR)
            solution = _prev->GetCollidePT(solution);
        if (solution.x > max(_p1.x, _p2.x) && _next && _next->_direction == LineCollider::DIRECTION::FLOOR)
            solution = _next->GetCollidePT(solution);
    }
    else
    {
        solution.x += 0.1f * (_direction == LineCollider::DIRECTION::LWALL ? 1.0f : -1.0f);
        solution.y = pos.y;

        if ((solution.y < min(_p1.y, _p2.y) && fabsf(min(_p1.y, _p2.y) - _p1.y) <= 0.01f) ||
            (solution.y > max(_p1.y, _p2.y) && fabsf(max(_p1.y, _p2.y) - _p1.y) <= 0.01f))
        {
            if (_prev)
            {
                //if (_prev->_direction == LineCollider::DIRECTION::FLOOR)
                //    solution = _prev->GetCollidePT(solution);
                //else
                    solution = _prev->GetCollidePT(solution);
            }
        }
        else if ((solution.y < min(_p1.y, _p2.y) && fabsf(min(_p1.y, _p2.y) - _p2.y) <= 0.01f) ||
            (solution.y > max(_p1.y, _p2.y) && fabsf(max(_p1.y, _p2.y) - _p2.y) <= 0.01f))
        {
            if (_next)
            {
                //if (_next->_direction == LineCollider::DIRECTION::FLOOR)
                //    solution = _next->GetCollidePT({ _p2.x + 0.1f, solution.y });
                //else
                    solution = _next->GetCollidePT(solution);
            }
        }
    }
    return solution;
}

Vector2 LineCollider::GetCrossPT(Vector2 p1, Vector2 p2)
{
    // 충돌비교대상의 점
    Float3 v1 = { p1.x,p1.y,1 };
    Float3 v2 = { p2.x,p2.y,1 };

    // 해당 콜라이더의 점
    Float3 _v1 = { _p1.x,_p1.y,1 };
    Float3 _v2 = { _p2.x,_p2.y,1 };

    // 두 직선의 교점
    Float3 v = Cross(Cross(v1, v2), Cross(_v1, _v2));

    Vector2 solution = { v.x / v.z, v.y / v.z };

    //오차 제거    
    if (p1.x == p2.x) solution.x = p1.x;
    if (p1.y == p2.y) solution.y = p1.y;

    if (_p1.x == _p2.x) solution.x = _p1.x;
    if (_p1.y == _p2.y) solution.y = _p1.y;
    return solution;
}

Float3 LineCollider::Cross(Float3 a, Float3 b)
{
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return { x,y,z };
}

float LineCollider::Length(Float3 v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}
