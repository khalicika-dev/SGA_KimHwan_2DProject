#include "Framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring file)
{
    m_texture = Texture::Add(file);

	m_vertexShader = SHADER->AddVS(L"TextureVertexShader");
	m_pixelShader = SHADER->AddPS(L"ActionShader");

	_actionBuffer = new ActionBuffer();
    _actionBuffer->data.maxSize = m_texture->GetSize();

    m_trans = make_shared<Transform>();
    m_size = m_texture->GetSize();

	CreateData();

	m_vertexBuffer = make_shared<VertexBuffer>(&m_verticesUV[0], sizeof(VertexUV), m_verticesUV.size());
	m_indexBuffer = make_shared<IndexBuffer>(&m_indices[0], m_indices.size());
}

Sprite::~Sprite()
{
	delete _actionBuffer;
}

void Sprite::Render()
{
	_actionBuffer->SetPSBuffer(0);
	
	Quad::Render();
}

void Sprite::CreateData()
{
    m_verticesUV.emplace_back(0, 0, 0, 0);
    m_verticesUV.emplace_back(0, 0, 1, 0);
    m_verticesUV.emplace_back(0, 0, 0, 1);
    m_verticesUV.emplace_back(0, 0, 1, 1);

    m_indices.emplace_back(0);
    m_indices.emplace_back(1);
    m_indices.emplace_back(2);

    m_indices.emplace_back(2);
    m_indices.emplace_back(1);
    m_indices.emplace_back(3);
}

void Sprite::SetAction(Action::Clip clip)
{

    _actionBuffer->data.startPos = clip.startPos;
    _actionBuffer->data.size = clip.size;

    Vector2 halfSize = clip.size * 0.5f;
    Vector2 pivot = clip.pivot;
    m_verticesUV[0].pos = { -halfSize.x,halfSize.y,0.0f };
    m_verticesUV[1].pos = { halfSize.x,halfSize.y,0.0f };
    m_verticesUV[2].pos = { -halfSize.x,-halfSize.y,0.0f };
    m_verticesUV[3].pos = { halfSize.x,-halfSize.y,0.0f };
    for (int i = 0; i < 4; i++)
    {
        m_verticesUV[i].pos.x -= clip.pivot.x * fabs(m_trans.get()->m_scale.x);
        m_verticesUV[i].pos.y -= clip.pivot.y * fabs(m_trans.get()->m_scale.y);
    }
    m_vertexBuffer->Update(&m_verticesUV[0], sizeof(VertexUV), m_verticesUV.size());

    int invert = m_trans->m_scale.x < 0.0f ? 1 : 0;
    m_indices[1] = 1 + invert;
    m_indices[2] = 2 - invert;
    m_indices[3] = 2 + invert;
    m_indices[5] = 3 - invert;
    m_indexBuffer->Update(&m_indices[0], m_indices.size());
}
