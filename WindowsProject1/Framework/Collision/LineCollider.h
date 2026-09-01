#pragma once
class LineCollider : public Collider
{
public:
	enum class DIRECTION
	{
		NONE,
		FLOOR,
		LWALL,
		RWALL,
	}_direction;

	enum class ATTRIBUTE
	{
		NONE		=	0,
		INVISIBLE	=	1
	}_attr;

public:
	LineCollider(Vector2 v1, Vector2 v2, DIRECTION direction, ATTRIBUTE attr);
	virtual ~LineCollider();

	virtual void Update() override;

	virtual void CreateData() override;

	bool IsCollision(Vector2 p1, Vector2 p2);
	virtual bool IsCollision(Vector2 worldPos) override;
	virtual bool IsCollision(class RectCollider* rect) override;
	virtual bool IsCollision(class CircleCollider* circle) override;

	bool FloorCollision(Vector2 pos);

	Vector2 GetCollidePT(Vector2 pos);
	void SetPrevCollider(LineCollider* value) { _prev = value; };
	void SetNextCollider(LineCollider* value) { _next = value; };
private:
	Vector2 GetCrossPT(Vector2 p1, Vector2 p2);
	Float3 Cross(Float3 a, Float3 b);
	float Length(Float3 v);

	Vector2 _p1, _p2;
	LineCollider* _prev;
	LineCollider* _next;
};