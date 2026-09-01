#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void Set();
private:
	ID3D11PixelShader* m_pShader;
	ID3DBlob* m_blob;
};

