#pragma once
class ShaderManager
{
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new ShaderManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static ShaderManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
	}

	VertexShader* AddVS(wstring file);
	PixelShader* AddPS(wstring file);

private:
	ShaderManager();
	~ShaderManager();
	map<wstring, Shader*> m_shaders;

	static ShaderManager* m_instance;
};

