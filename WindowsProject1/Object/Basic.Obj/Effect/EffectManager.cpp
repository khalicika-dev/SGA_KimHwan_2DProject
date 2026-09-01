#include "Framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::m_instance = nullptr;

void EffectManager::Update()
{
	for (auto& eft : m_effects)
		eft.second->Update();
}

void EffectManager::Render()
{
	for (auto& eft : m_effects)
		eft.second->Render();
}

void EffectManager::Play(wstring name, Vector2 pos, float angle, Vector2 scale)
{
	wstring path;
	UINT mx = 0, my = 0;
	vector<float> spd;
	shared_ptr<Effect> temp;

	// 기존의 객체를 찾아서 재생한다
	if (!m_effects.empty())
	{
		auto range = m_effects.equal_range(name);
		for (auto iter = range.first; iter != range.second; iter++)
		{
			if (!iter->second->IsPlay())
			{
				iter->second->Play(pos, angle, scale);
				return;
			}
		}
	}

	// 새로 만들 객체의 이름을 찾는다. 소스가 없으면 리턴
	if (name == L"atk_blow") { mx = 3, my = 1, spd = { 5,3,2 }; }
	else if (name == L"atk_slash") { mx = 3, my = 1, spd = { 5,3,2 }; }
	else if (name == L"death_dust") { mx = 4, my = 2, spd = { 5,4,5,4,3,3,2,2 }; }
	else return;

	// 객체로 새로만들어 재생한다.
	path = L"Resource/Effects/" + name + L".png";
	temp = make_shared<Effect>(path, mx, my, spd);
	m_effects.emplace(name, temp);
	temp->Play(pos, angle, scale);
}

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{
	m_effects.clear();
}
