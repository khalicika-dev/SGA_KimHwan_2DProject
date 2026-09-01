#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void Set();

	void CreateInputLayout();
private:
	ID3D11VertexShader* m_shader;
	ID3D11InputLayout* m_inputLayout;

	ID3DBlob* m_blob;

	ID3D11ShaderReflection* m_reflection;
};

