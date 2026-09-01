#pragma once
class Transform
{
public:
	Transform(string tag = "Untagged");
	virtual ~Transform();


	virtual void SetParent(Transform* transform) { m_parent = transform; }
	void SetWorldBuffer(UINT slot = 0);
	Matrix* GetMatrix() { return &m_matrix; }
	Vector2 GetWorldPos();
	void UpdateWorld();

public:
	bool m_isActive;
	string		m_tag;

	Vector2		m_scale;
	float		m_angle;
	Vector2		m_pos;
	Vector2		m_pivot;

protected:
	Matrix m_matrix;
	Float4x4 _matWorld;

	Transform* m_parent;

	MatrixBuffer* m_worldBuffer;

	Matrix S, R, T, P, IP;
};

