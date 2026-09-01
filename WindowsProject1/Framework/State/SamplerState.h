#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void SetState(UINT slot = 0);

private:
	ID3D11SamplerState* m_samplerState;
	D3D11_SAMPLER_DESC m_desc;
};

