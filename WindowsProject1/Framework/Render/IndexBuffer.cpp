#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
{
	D3D11_BUFFER_DESC bd = {};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;               // GPU로 데이터가 넘어간후 변경 할 수 있음
	bd.ByteWidth = sizeof(UINT) * count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &m_iBuffer);
}

IndexBuffer::~IndexBuffer()
{
	m_iBuffer->Release();
}

void IndexBuffer::Set()
{
	Device::Get()->GetDeviceContext()->IASetIndexBuffer(m_iBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::Update(void* data, UINT count)
{
	D3D11_MAPPED_SUBRESOURCE mr;
	ZeroMemory(&mr, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DEVICE_CONTEXT->Map(m_iBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mr);
	memcpy(mr.pData, data, sizeof(UINT) * count);
	DEVICE_CONTEXT->Unmap(m_iBuffer, 0);
}