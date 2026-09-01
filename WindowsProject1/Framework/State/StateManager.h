#pragma once
class StateManager
{
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new StateManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static StateManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
	}

	SamplerState* GetSampler() { return m_samplerState; }
	BlendState* GetAlphaBlend() { return m_alphaState; }
	BlendState* GetAdditiveBlend() { return m_additiveState; }
	RasterizerState* GetCullMode() { return m_cullState; }

private:
	StateManager();
	~StateManager();

	SamplerState* m_samplerState;
	BlendState* m_alphaState;
	BlendState* m_additiveState;
	RasterizerState* m_cullState;

	static StateManager* m_instance;
};

