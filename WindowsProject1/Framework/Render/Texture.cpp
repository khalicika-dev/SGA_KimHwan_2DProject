#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::m_texturesMap;

Texture::Texture(ID3D11ShaderResourceView* shaderResourceView, ScratchImage& image)
	: m_shaderResourceView(shaderResourceView)
	, m_image(std::move(image))	// lvalue->rvalue로 전환
{
}

Texture::~Texture()
{
	m_shaderResourceView->Release();
}

Texture* Texture::Add(wstring file)
{
    // 만약에 m_texturesMap에 file이란 이름의 키와 값이 있다면
    // 걔를 리턴해주세요
    if (m_texturesMap.count(file) > 0)
        return m_texturesMap[file];

    ScratchImage image;

    LoadFromWICFile(&file[0], WIC_FLAGS_NONE, nullptr, image);
    ID3D11ShaderResourceView* shaderResourceView;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &shaderResourceView);

    Texture* texture = new Texture(shaderResourceView, image);
    texture->m_file = file;

    m_texturesMap[file] = texture;

    return m_texturesMap[file];
}

void Texture::Delete()
{
	for (auto texture : m_texturesMap)
	{
		delete texture.second;
	}
}

void Texture::Set(UINT slot)
{
	DEVICE_CONTEXT->PSSetShaderResources(slot, 1, &m_shaderResourceView);
}

Vector2 Texture::GetSize()
{
	return Vector2(m_image.GetMetadata().width, m_image.GetMetadata().height);
}
