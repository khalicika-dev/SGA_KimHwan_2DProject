#pragma once
class ObjectManager
{
public:
	// 씬에서 추가&설정하는 오브젝트들
	enum class ObjectType
	{
		PLAYER,
		ITEM,
		M_FLOWER,
		M_BOSS_FLOWER
	};

	// 오브젝트가 생성하는 오브젝트
	enum class ParticleType
	{
		BLOODING,
		GOLD
	};
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new ObjectManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static ObjectManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
		assert(false);
	}

	// 캐릭터 오브젝트 관련 함수
	void Update(ObjectType type, UINT num);
	void Render(ObjectType type, UINT num);
	void Prepare(ObjectType type, UINT num);
	class GameObject* Find(ObjectType type, UINT num);
	class Player* FindPlayer();	// Player를 바로 Find하는 함수
	bool GetPickable() { return _pickable; }
	void SetPickable(bool value) { _pickable = value; }

	// 투사체, 파티클 등 특수오브젝트 관련 함수
	void Particles_Update();
	void Particles_Render();
	void All_Particle_ActiveOff();
	shared_ptr<GameObject> Generate(ParticleType type, Vector2 pos, float angle, bool isMust = false);
private:
	ObjectManager();
	~ObjectManager();
	string Type2Name(ObjectType type, UINT num) { return to_string(static_cast<int>(type)) + to_string(num); }
	static ObjectManager* m_instance;

	map<string, class GameObject*> m_objects;		// 오브젝트를 보관
	multimap<ParticleType, shared_ptr<class GameObject>> m_particles;	// 특수오브젝트를 보관

	bool _pickable;
};