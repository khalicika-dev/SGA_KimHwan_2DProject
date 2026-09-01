#include "Framework.h"
#include "StateManager.h"

StateManager* StateManager::m_instance = nullptr;

StateManager::StateManager()
{
	m_samplerState = new SamplerState();
	m_alphaState = new BlendState();
	m_alphaState->Alpha();
	m_additiveState = new BlendState();
	m_additiveState->Additive();
	m_cullState = new RasterizerState();
}

StateManager::~StateManager()
{
	delete m_samplerState;
	delete m_alphaState;
	delete m_additiveState;
	delete m_cullState;
}
