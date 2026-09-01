#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
    : m_stride(stride)
    , m_vbuffer(nullptr)
    , m_offset(0)
{
    D3D11_BUFFER_DESC bd = {};
    //bd.Usage = D3D11_USAGE_DEFAULT;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = stride * count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    DEVICE->CreateBuffer(&bd, &initData, &m_vbuffer);
}

VertexBuffer::~VertexBuffer()
{
    m_vbuffer->Release();
}

void VertexBuffer::Set()
{
    Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vbuffer, &m_stride, &m_offset);
}

void VertexBuffer::Update(void* data, UINT stride, UINT count)
{
    D3D11_MAPPED_SUBRESOURCE mr;
    ZeroMemory(&mr, sizeof(D3D11_MAPPED_SUBRESOURCE));

    DEVICE_CONTEXT->Map(m_vbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mr);
    memcpy(mr.pData, data, stride * count);
    DEVICE_CONTEXT->Unmap(m_vbuffer, 0);
}