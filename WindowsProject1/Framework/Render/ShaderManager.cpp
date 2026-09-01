#include "Framework.h"
#include "ShaderManager.h"

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
	for (auto shaderPair : m_shaders)
		delete shaderPair.second;
}

VertexShader* ShaderManager::AddVS(wstring file)
{
	if (m_shaders.count(file) > 0)
	{
		return dynamic_cast<VertexShader*>(m_shaders[file]);
	}

	VertexShader* vs = new VertexShader(file);
	m_shaders[file] = vs;

	return vs;
}

PixelShader* ShaderManager::AddPS(wstring file)
{
	if (m_shaders.count(file) > 0)
	{
		return dynamic_cast<PixelShader*>(m_shaders[file]);
	}

	PixelShader* ps = new PixelShader(file);
	m_shaders[file] = ps;

	return ps;
}
