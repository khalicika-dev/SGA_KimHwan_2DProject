#pragma once
class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);

	Vector2 operator+ (const Vector2& value) const;
	Vector2& operator+= (const Vector2& value);
	Vector2 operator- (const Vector2& value) const;
	Vector2 operator* (const Vector2& value) const;
	Vector2 operator* (const float& value) const;

	friend Vector2 operator*(const float f, const Vector2& value);

	float Length() const;
	
	void Normalize();
	Vector2 Normal() const;

	float Dot(const Vector2 value) const;
	float Cross(const Vector2 value) const;

	float Angle(const Vector2& dest);
	float Angle() { return atan2(-y, x); }

	static float Distance(const Vector2& v1, const Vector2& v2);
	static Vector2 TransformCoord(const Vector2& v, const Matrix& mat);
};

