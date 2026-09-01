#include "Framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	m_desc = {};
	m_desc.CullMode = D3D11_CULL_NONE;
	m_desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&m_desc, &m_state);
}

RasterizerState::~RasterizerState()
{
	m_state->Release();
}

void RasterizerState::SetState()
{
	DEVICE_CONTEXT->RSSetState(m_state);
}
