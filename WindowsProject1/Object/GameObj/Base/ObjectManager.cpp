#include "Framework.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::m_instance = nullptr;

void ObjectManager::Update(ObjectType type, UINT num)
{
	GameObject* obj = Find(type, num);
	if (!obj || !obj->GetActive()) return;
	obj->Update();
}

void ObjectManager::Render(ObjectType type, UINT num)
{
	GameObject* obj = Find(type, num);
	if (!obj || !obj->GetActive()) return;
	obj->Render();
}

void ObjectManager::Prepare(ObjectType type, UINT num)
{
	GameObject* obj = nullptr;
	string name;
	name = to_string(static_cast<int>(type)) + to_string(num);
	if (m_objects.count(name) != 0)
	{
		m_objects[name]->SetActive(true);
		m_objects[name]->Init();
		return;
	}
	switch (type)
	{
	case ObjectType::PLAYER: obj = new Player(); break;
	case ObjectType::ITEM: obj = new Item(); break;
	case ObjectType::M_FLOWER: obj = new Monster_Flower(); break;
	case ObjectType::M_BOSS_FLOWER: obj = new Monster_BossFlower(); break;
	default: assert(false);
	}
	obj->SetActive(true);
	m_objects.emplace(name, obj);
}

GameObject* ObjectManager::Find(ObjectType type, UINT num)
{
	GameObject* obj = nullptr;
	string name = Type2Name(type, num);
	if(m_objects.count(name))
		obj = m_objects[name];
	return obj;
}

Player* ObjectManager::FindPlayer()
{
	return dynamic_cast<Player*>(Find(ObjectType::PLAYER, 0));
}


void ObjectManager::Particles_Update()
{
	for (auto& item : m_particles)
	{
		if (item.second->GetActive())
			item.second->Update();
	}
}

void ObjectManager::Particles_Render()
{
	for (auto& item : m_particles)
	{
		if (item.second->GetActive())
			item.second->Render();
	}
}

void ObjectManager::All_Particle_ActiveOff()
{
	for (auto& item : m_particles)
		item.second->SetActive(false);
}

shared_ptr<GameObject> ObjectManager::Generate(ParticleType type, Vector2 pos, float angle, bool isStore)
{
	wstring path;
	UINT mx = 0, my = 0;
	vector<float> spd;
	shared_ptr<GameObject> temp;

	// 기존의 객체를 찾아서 재활용한다
	if (!m_particles.empty() && !isStore)
	{
		auto range = m_particles.equal_range(type);
		for (auto iter = range.first; iter != range.second; iter++)
		{
			if (!iter->second->GetActive())
			{
				iter->second->SetActive(true);
				iter->second->SetPosition(pos);
				iter->second->SetAngle(angle);
				iter->second->Init();
				return iter->second;
			}
		}
	}

	// 기존의 객체가 없으면 새로 만든다
	// isStore면 존재유무에 관계없이 새로 만든다. 주로 오브젝트 풀을 미리 담을때 사용
	switch (type)
	{
	case ParticleType::BLOODING:	temp = make_shared<Blooding>(pos); break;
	case ParticleType::GOLD:		temp = make_shared<Gold>(pos); break;
	default: return nullptr;
	}

	if (!isStore) temp->SetActive(true);
	m_particles.emplace(type, temp);
	return temp;
}

ObjectManager::ObjectManager()
	: _pickable(true)
{
	for (int i = 0; i < 100; i++) Generate(ParticleType::BLOODING, { 0.0f,0.0f }, 0.0f, true);
	for (int i = 0; i < 50; i++) Generate(ParticleType::GOLD, { 0.0f,0.0f }, 0.0f, true);
}

ObjectManager::~ObjectManager()
{
	// 사용된 오브젝트들 제거
	for (auto& obj : m_objects)
		delete obj.second;
	m_objects.clear();
}