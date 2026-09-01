#pragma once

// is a 관계인지
// has a 관계인지

class Collider : public Transform
{
public:
	Collider();
	Collider(Transform* target);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();

	virtual Vector2 GetSize() { return { 0.0f,0.0f }; }

	virtual void CreateData();

	bool IsCollision(Collider* col);

	virtual bool IsCollision(Vector2 worldPos) abstract;
	virtual bool IsCollision(class RectCollider* rect) abstract;
	virtual bool IsCollision(class CircleCollider* circle) abstract;

	void SetColor(Float4 color) { m_colorBuffer->data.color = color; }
	void SetEnable(bool value) { m_isEnable = value; }
protected:
	enum class Type
	{
		CIRCLE,
		RECT,
		LINE
	}m_type;

	bool m_isEnable;		// 충돌이 가능한 상태(Active와 차이점: isCollider 발동유무만 조절가능)
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;

	VertexBuffer* m_vertexBuffer;
	ColorBuffer* m_colorBuffer;
	vector<Vertex> m_vertices;

	// 어떤 콜라이더는 충돌해도 그냥 아무것도 안하고 싶음
	// 어떤 콜라이더는 충돌했을 때 터지는 이펙트
	// 어떤 콜라이더는 제가 마우스로 클릭(점과 콜라이더 충돌)이 일어나면 창이 닫힘
	// => 함수 포인터 nullptr로 들고 있다가
	// => 다른 함수포인터를 넣어주면 되겠다.
	Delegate m_event;
};
