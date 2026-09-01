#pragma once

class CircleCollider : public Collider
{
public:
	CircleCollider(float radius);
	CircleCollider(float radius, Transform* target);
	virtual ~CircleCollider();

	virtual void Update() override;

	virtual Vector2 GetSize() override { return { 2.0f * m_radius, 2.0f * m_radius }; }

	virtual void CreateData() override;

	virtual bool IsCollision(Vector2 worldPos) override;
	virtual bool IsCollision(class RectCollider* rect) override;
	virtual bool IsCollision(class CircleCollider* circle) override;

	float Radius() { return m_radius * m_scale.x; }
private:
	float GetWorldRadius();

	float m_originRadius;
	float m_radius;
	int m_sliceCount;
	bool m_changed;
};
