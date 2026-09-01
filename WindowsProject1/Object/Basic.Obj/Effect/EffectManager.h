#pragma once
class EffectManager
{
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new EffectManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static EffectManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
	}

	void Update();
	void Render();
	void Play(wstring name, Vector2 pos, float angle, Vector2 scale = { 1.0f, 1.0f });
private:
	EffectManager();
	~EffectManager();

	static EffectManager* m_instance;
private:
	multimap<wstring, shared_ptr<Effect>> m_effects;
};