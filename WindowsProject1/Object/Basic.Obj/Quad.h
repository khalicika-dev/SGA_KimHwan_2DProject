#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring file, float width = 0.0f, float height = 0.0f);
	Quad(Float4 color, bool fill, float width = 0.0f, float height = 0.0f);
	virtual ~Quad();

	virtual void Update();
	virtual void Render();

	virtual void CreateData();

	Transform* GetTransform() { return m_trans.get(); }
	void SetTransform(Transform& trans) { m_trans = make_shared<Transform>(trans); }
	const Vector2 GetSize() { return m_size * m_trans->m_scale; }
	void SetScale(Vector2 scale) { m_trans->m_scale = scale; }
	void SetPSShader(PixelShader* pixelShader) { m_pixelShader = pixelShader; }
	void SetColor(Float4 color) { if (m_type == QuadType::COLORFILL) m_colorBuffer->data.color = color; }
protected:
	enum class QuadType
	{
		TEXTURE,
		COLORRECT,
		COLORFILL
	}m_type;
	// 내용은 기본적으로 4개의 정점을 가지고 있는 어떤 한 면
	// 텍스처를 들고 있어서 쿼드에 스스로 맵핑
	// 트랜스폼 들고 있어서 움직이거나 스스로 변환이 가능
	class Texture* m_texture;

	shared_ptr<Transform> m_trans;

	shared_ptr<VertexBuffer>	m_vertexBuffer;
	shared_ptr<IndexBuffer>		m_indexBuffer;
	shared_ptr<ColorBuffer>		m_colorBuffer;

	Vector2 m_size;

	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;

	vector<VertexUV> m_verticesUV;
	vector<Vertex> m_vertices;
	vector<UINT> m_indices;
};

