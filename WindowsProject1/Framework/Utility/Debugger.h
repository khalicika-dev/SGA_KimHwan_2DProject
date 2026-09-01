#pragma once
class Debugger
{
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new Debugger();
	}
	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}
	static Debugger* Get()
	{
		if (m_instance == nullptr)
			return nullptr;
		return m_instance;
	}

	void Update();
	bool GetShowCollider() { return _ShowCollider; }
private:
	Debugger();
	~Debugger();
	static Debugger* m_instance;

	bool _IsActive;
	bool _ShowCollider;
};

