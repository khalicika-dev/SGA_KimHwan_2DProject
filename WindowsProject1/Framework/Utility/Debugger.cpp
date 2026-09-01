#include "Framework.h"
#include "Debugger.h"

Debugger* Debugger::m_instance = nullptr;

void Debugger::Update()
{
	if (!_IsActive) return;

	if (KEYDOWN(VK_F1))
		_ShowCollider = !_ShowCollider;
}

Debugger::Debugger()
: _IsActive(true)
, _ShowCollider(false)
{
}

Debugger::~Debugger()
{
}
