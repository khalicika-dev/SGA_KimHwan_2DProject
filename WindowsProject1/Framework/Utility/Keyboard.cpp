#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::m_instance = nullptr;

Keyboard::Keyboard()
	: m_curState{}
	, m_oldState{}
	, m_mapState{}
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	memcpy(m_oldState, m_curState, sizeof(m_oldState));

	GetKeyboardState(m_curState);

	for (int i = 0; i < KEYMAX; i++)
	{
		byte key = m_curState[i] & 0x80;
		m_curState[i] = key ? 1 : 0;

		int old = m_oldState[i];
		int cur = m_curState[i];

		if (old == 0 && cur == 1) m_mapState[i] = DOWN;
		else if (old == 1 && cur == 0) m_mapState[i] = UP;
		else if (old == 1 && cur == 1) m_mapState[i] = PRESS;
		else m_mapState[i] = NONE;
	}
}
