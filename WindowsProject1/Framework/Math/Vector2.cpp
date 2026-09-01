#include "Framework.h"
#include "Vector2.h"

Vector2::Vector2()
	: Float2(0,0)
{
}

Vector2::Vector2(float x, float y)
	: Float2(x,y)
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
	return Vector2(x + value.x, y + value.y);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
	(*this) = (*this) + value;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& value) const
{
	return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const Vector2& value) const
{
	return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

float Vector2::Length() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2::Normalize()
{
	float length = Length();
	if (length == 0) return;

	x /= length;
	y /= length;
}

Vector2 Vector2::Normal() const
{
	float length = Length();
	if (length == 0) return Vector2(x, y);
	return Vector2(x / length, y / length);
}

float Vector2::Dot(const Vector2 value) const
{
	return (x * value.x + y * value.y);
}

float Vector2::Cross(const Vector2 value) const
{
	return (x * value.y - y * value.x);
}

float Vector2::Angle(const Vector2& dest)
{
	float tempDot = this->Dot(dest);
	float cosTheta = tempDot / (this->Length() * dest.Length());

	return acosf(cosTheta);
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2)
{
	return (v2 - v1).Length();
}

Vector2 Vector2::TransformCoord(const Vector2& v, const Matrix& mat)
{
	XMVECTOR temp = XMLoadFloat2(&v);

	temp = XMVector2Transform(temp, mat);
	Vector2 result;
	XMStoreFloat2(&result, temp);

	return result;
}

//본질적으로 바로 위의 operator*와 같지만 순서가 다르다
Vector2 operator*(const float f, const Vector2& value)
{
	return value * f;
}
