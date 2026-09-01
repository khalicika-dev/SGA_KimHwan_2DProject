#pragma once
class MapManager
{
public:
	enum class MAPLIST
	{
		TITLE,
		TITLE_HELP,
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		CLEAR
	};

	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new MapManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static MapManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
		assert(false);
	}

	void Update();
	void Render();
	void PostUpdate();
	void PostRender();
	void ChangeMap(MAPLIST scene, Vector2 playerPos = { 0,0 }, bool instansly = false);
private:
	MapManager();
	~MapManager();
	void ClearBG();		// 보관된 배경데이터 삭제
	void ClearTR();		// 보관된 지형데이터 삭제

	static MapManager* m_instance;

	class Scene* m_oldScene;		// 이전 씬 (삭제될 씬)
	class Scene* m_curScene;		// 현재 씬
	class Scene* m_newScene;		// 새로운 씬 (임시로 저장 후 다음 업데이트때 현재 씬이 된다)

	vector<Quad*> m_backgrounds;			// 구현된 백그라운드정보
public:
	vector<LineCollider*> m_terrains;		// 구현된 지형정보
};