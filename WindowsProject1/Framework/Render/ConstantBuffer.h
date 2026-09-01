#pragma once
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	void Update();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	ID3D11Buffer* m_constantBuffer;
	D3D11_MAPPED_SUBRESOURCE m_subResource;

	void* m_data;
	UINT m_dataSize;
};

