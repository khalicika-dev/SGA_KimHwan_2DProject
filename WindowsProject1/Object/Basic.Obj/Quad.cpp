#include "Framework.h"
#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(wstring file, float width, float height)
    : m_size(width, height)
    , m_type(QuadType::TEXTURE)
{
	m_texture = Texture::Add(file);

    m_vertexShader = SHADER->AddVS(L"TextureVertexShader");
    m_pixelShader = SHADER->AddPS(L"TextureShader");

	CreateData();

    m_vertexBuffer = make_shared<VertexBuffer>(&m_verticesUV[0], sizeof(VertexUV), m_verticesUV.size());
    m_indexBuffer = make_shared<IndexBuffer>(&m_indices[0], m_indices.size());

    m_trans = make_shared<Transform>();
    m_size = m_texture->GetSize();
}

Quad::Quad(Float4 color, bool fill, float width, float height)
    : m_size(width, height)
    , m_type(fill ? QuadType::COLORFILL : QuadType::COLORRECT)
{
    m_vertexShader = SHADER->AddVS(L"VertexShader");
    m_pixelShader = SHADER->AddPS(L"ColorShader");

    CreateData();

    if (m_type == QuadType::COLORRECT)
    {
        m_vertexBuffer = make_shared<VertexBuffer>(&m_vertices[0], sizeof(Vertex), m_vertices.size());
    }
    else
    {
        m_vertexBuffer = make_shared<VertexBuffer>(&m_verticesUV[0], sizeof(VertexUV), m_verticesUV.size());
        m_indexBuffer = make_shared<IndexBuffer>(&m_indices[0], m_indices.size());
    }
    m_colorBuffer = make_shared<ColorBuffer>();
    m_colorBuffer->data.color = color;

    m_trans = make_shared<Transform>();
    m_size = { width,height };
}

Quad::~Quad()
{
}

void Quad::Update()
{
    if (m_trans->m_isActive == false)
        return;

    m_trans->UpdateWorld();
}

void Quad::Render()
{
    //t - SRV(셰이더 리소스 뷰)
    //s - 샘플러
    //u - UAV(순서가 지정되지 않은 액세스 뷰)
    //b - CBV(상수 버퍼 보기)

    if (m_trans->m_isActive == false)
        return;

    AlphaBlendState->SetState();
    CullModeState->SetState();

    m_trans->SetWorldBuffer();

    m_vertexBuffer->Set();
    if (m_type == QuadType::COLORRECT)
        IASetPT(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
    else
    {
        m_indexBuffer->Set();
        IASetPT();
    }

    if (m_type == QuadType::TEXTURE)
    {
        m_texture->Set(0);
        SAMPLER->SetState();
    }
    else
    {
        m_colorBuffer->SetPSBuffer(0);
    }

    m_vertexShader->Set();
    m_pixelShader->Set();

    if (m_type == QuadType::COLORRECT)
        DEVICE_CONTEXT->Draw(m_vertices.size(), 0);
    else
        DEVICE_CONTEXT->DrawIndexed(m_indices.size(), 0, 0);
}

void Quad::CreateData()
{

    if (m_size.x == 0.0f && m_size.y == 0.0f)
    {
        m_size = m_texture->GetSize();
    }
    Vector2 halfSize = m_size * 0.5f;

    if (m_type == QuadType::COLORRECT)
    {
        m_vertices.emplace_back(-halfSize.x, -halfSize.y);
        m_vertices.emplace_back(halfSize.x, -halfSize.y);
        m_vertices.emplace_back(halfSize.x, halfSize.y);
        m_vertices.emplace_back(-halfSize.x, halfSize.y);
        m_vertices.emplace_back(-halfSize.x, -halfSize.y);
    }
    else
    {
        m_verticesUV.emplace_back(-halfSize.x, halfSize.y, 0, 0);
        m_verticesUV.emplace_back(halfSize.x, halfSize.y, 1, 0);
        m_verticesUV.emplace_back(-halfSize.x, -halfSize.y, 0, 1);
        m_verticesUV.emplace_back(halfSize.x, -halfSize.y, 1, 1);

        m_indices.emplace_back(0);
        m_indices.emplace_back(1);
        m_indices.emplace_back(2);

        m_indices.emplace_back(2);
        m_indices.emplace_back(1);
        m_indices.emplace_back(3);
    }
}
