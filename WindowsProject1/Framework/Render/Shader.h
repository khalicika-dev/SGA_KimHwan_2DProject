#pragma once
class Shader
{
public:
	Shader();
	virtual ~Shader();

	virtual void Set() abstract;

private:
	wstring m_file;
	ID3DBlob* m_blob;
};