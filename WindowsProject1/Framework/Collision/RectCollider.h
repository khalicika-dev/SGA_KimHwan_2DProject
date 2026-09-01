#pragma once


class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 direction[2];
		float length[2];
	};

public:
	RectCollider(Vector2 size);
	RectCollider(Vector2 size, Transform* target);
	virtual ~RectCollider();

	virtual void Update() override;

	virtual Vector2 GetSize() override { return m_size; }

	virtual void CreateData() override;

	bool AABB(RectCollider* rect);
	bool OBB(RectCollider* rect);

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

	ObbDesc GetObb();

	void SetSize(float w = 0.0f, float h = 0.0f);

	virtual bool IsCollision(Vector2 worldPos) override;
	virtual bool IsCollision(class RectCollider* rect) override;
	virtual bool IsCollision(class CircleCollider* circle) override;

	float Left()	{ return GetWorldPos().x - GetWorldSizeXY().x * 0.5f; }
	float Right()	{ return GetWorldPos().x + GetWorldSizeXY().x * 0.5f; }
	float Top()		{ return GetWorldPos().y + GetWorldSizeXY().y * 0.5f; }
	float Bottom()	{ return GetWorldPos().y - GetWorldSizeXY().y * 0.5f; }

private:
	Float2 GetWorldSizeXY();	// 월드좌표를 구한다
	// Obb
	// AABB(Axis-Aligned Bounding Box)
	bool m_isObb;
	Vector2 m_size;
};
