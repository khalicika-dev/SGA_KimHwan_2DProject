#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
	: m_data(data)
	, m_dataSize(dataSize)
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    // D3D11_USAGE_DEFAULT = 0 // GPU에서 읽고쓰기 가능
    // D3D11_USAGE_IMMUTABLE = 1 // GPU에서 읽기만 가능
    // D3D11_USAGE_DYNAMIC = 2 // CPU에서 쓰기 가능, GPU 읽기(Map, UnMap 사용가능)
    // D3D11_USAGE_STAGING = 3 // GPU에서 CPU로 이동(읽기만 가능)
    bd.ByteWidth = dataSize;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

    DEVICE->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
    m_constantBuffer->Release();
}

void ConstantBuffer::Update()
{
    DEVICE_CONTEXT->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_subResource);
    memcpy(m_subResource.pData, m_data, m_dataSize);
    DEVICE_CONTEXT->Unmap(m_constantBuffer, 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
    DEVICE_CONTEXT->VSSetConstantBuffers(slot, 1, &m_constantBuffer);
    Update();
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    DEVICE_CONTEXT->PSSetConstantBuffers(slot, 1, &m_constantBuffer);
    Update();
}
