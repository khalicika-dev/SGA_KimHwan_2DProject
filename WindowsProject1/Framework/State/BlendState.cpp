#include "Framework.h"
#include "BlendState.h"

BlendState::BlendState()
	: m_desc({})
{
	m_desc.AlphaToCoverageEnable = false;
	m_desc.IndependentBlendEnable = false;

	m_desc.RenderTarget[0].BlendEnable = true;	// 알파연산을 하겠다.
	m_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;	// 출력할 이미지에 출력할 이미지가 가지는 불투명도를 곱하겠다.
	m_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;			// 뒷배경에다가 출력할 이미지의 alpha의 역수를 곱하겠다.
	m_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;		// 알파연산을 덧셈으로 하겠다.

	m_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	m_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	m_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	m_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Changed();
}

BlendState::~BlendState()
{
	m_state->Release();
}

void BlendState::SetState()
{
	float blendFactor[] = { 0,0,0,0 };
	DEVICE_CONTEXT->OMSetBlendState(m_state, blendFactor, 0xffffffff);
}

void BlendState::Alpha()
{
	m_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Changed();
}

void BlendState::Additive()
{
	m_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	Changed();
}

void BlendState::Changed()
{
	if (m_state != nullptr)
		m_state->Release();
	DEVICE->CreateBlendState(&m_desc, &m_state);
}
