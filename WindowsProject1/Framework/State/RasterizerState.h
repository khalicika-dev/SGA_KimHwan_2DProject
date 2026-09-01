#pragma once
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();

private:
	ID3D11RasterizerState* m_state;
	D3D11_RASTERIZER_DESC m_desc;
};

