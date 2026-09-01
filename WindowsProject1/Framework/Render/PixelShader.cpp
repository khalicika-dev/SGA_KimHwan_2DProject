#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
	: m_blob(nullptr)
	, m_pShader(nullptr)
{
	wstring path = L"Shaders/" + file + L".hlsl";

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	D3DCompileFromFile(&path[0], nullptr, nullptr, "PS", "ps_5_0", flags, 0, &m_blob, nullptr);

	Device::Get()->GetDevice()->CreatePixelShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), nullptr, &m_pShader);
}

PixelShader::~PixelShader()
{
	m_pShader->Release();
	m_blob->Release();
}

void PixelShader::Set()
{
	Device::Get()->GetDeviceContext()->PSSetShader(m_pShader, nullptr, 0);
}
