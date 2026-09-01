#pragma once
class BlendState
{
public:
	BlendState();
	~BlendState();

	void SetState();

	void Alpha();
	void Additive();

	void Changed();
private:
	ID3D11BlendState* m_state;
	D3D11_BLEND_DESC m_desc;
};

