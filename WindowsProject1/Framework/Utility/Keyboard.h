#pragma once

#define KEYMAX 255

class Keyboard
{
private:
	enum
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	Keyboard();
	~Keyboard();
public:
	static void Create()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Keyboard();
		}
	}

	static Keyboard* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
		return nullptr;
	}

	static void Delete()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
		}
		m_instance = nullptr;
	}

	void Update();

	bool Down(UINT key)		{ return m_mapState[key] == DOWN; }
	bool Up(UINT key)		{ return m_mapState[key] == UP; }
	bool Press(UINT key)	{ return m_mapState[key] == PRESS; }

private:
	static Keyboard* m_instance;


	byte m_curState[KEYMAX];
	byte m_oldState[KEYMAX];
	byte m_mapState[KEYMAX];
};

