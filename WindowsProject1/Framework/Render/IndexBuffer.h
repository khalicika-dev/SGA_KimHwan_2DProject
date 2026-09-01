#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void Update(void* data, UINT count);

	void Set();
private:
	ID3D11Buffer* m_iBuffer;
};

