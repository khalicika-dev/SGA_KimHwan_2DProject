#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count);
	~VertexBuffer();

	void Update(void* data, UINT stride, UINT count);

	void Set();
private:
	ID3D11Buffer* m_vbuffer;

	UINT m_stride;
	UINT m_offset;
};

