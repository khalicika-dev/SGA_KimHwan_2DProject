#include "Framework.h"
#include "MapManager.h"

#include "Scene/Scene_Title.h"
#include "Scene/Scene_Help.h"
#include "Scene/Scene_Map1.h"
#include "Scene/Scene_Map2.h"
#include "Scene/Scene_Map3.h"
#include "Scene/Scene_Map4.h"
#include "Scene/Scene_Clear.h"

MapManager* MapManager::m_instance = nullptr;

void MapManager::Update()
{
	// Update, Render가 처음 시작되면 newScene이 현재 씬에 적용된다
	if (m_newScene) m_curScene = m_newScene;
	m_newScene = nullptr;

	for (auto& bg : m_backgrounds)
		bg->Update();
	for (auto& tr : m_terrains)
		tr->Update();
	m_curScene->Update();
}

void MapManager::Render()
{
	for (auto& bg : m_backgrounds)
		bg->Render();
	for (auto& tr : m_terrains)
		tr->Render();
	m_curScene->Render();
}

void MapManager::PostUpdate()
{
	m_curScene->PostUpdate();
}

void MapManager::PostRender()
{
	// 후처리
	m_curScene->PostRender();

	// 모든 Update, Render가 끝나면 oldScene은 삭제된다
	if (m_oldScene) delete m_oldScene;
	m_oldScene = nullptr;
}

void MapManager::ChangeMap(MAPLIST scene, Vector2 playerPos, bool instansly)
{
	if (!instansly)
	{
		UISTATE->FadeScene(scene, playerPos);
		return;
	}

	//if (m_curScene) delete m_curScene;
	m_oldScene = m_curScene;

	switch (scene)
	{
	case MAPLIST::TITLE: m_newScene = new Scene_Title(); break;
	case MAPLIST::TITLE_HELP: m_newScene = new Scene_Help(); break;
	case MAPLIST::STAGE1: m_newScene = new Scene_Map1(); break;
	case MAPLIST::STAGE2: m_newScene = new Scene_Map2(); break;
	case MAPLIST::STAGE3: m_newScene = new Scene_Map3(); break;
	case MAPLIST::STAGE4: m_newScene = new Scene_Map4(); break;
	case MAPLIST::CLEAR: m_newScene = new Scene_Clear(); break;
	}

	ClearBG();
	ClearTR();
	OBJECT->All_Particle_ActiveOff();

	// 현재 씬으로부터 배경정보를 불러들인다.
	vector<shared_ptr<Scene::MapData>> bg;
	bg = m_newScene->Backgrounds();
	for (int i = 0; i < bg.size(); i++)
	{
		m_backgrounds.push_back(new Quad(L"Resource/Textures/Map/" + bg[i]->_name + L".png"));
		m_backgrounds.back()->GetTransform()->m_pos = bg[i]->_pos;
	}

	// 현재 씬으로부터 지형정보를 불러들인다.
	vector<shared_ptr<Scene::TerrainData>> tr;
	tr = m_newScene->Terrains();
	for (int i = 0; i < tr.size(); i++)
		m_terrains.push_back(new LineCollider(tr[i]->_startPos, tr[i]->_endPos, tr[i]->_direction, tr[i]->_attr));
	for (int i = 0; i < tr.size(); i++)
	{
		m_terrains[i]->SetColor({ 1,0,1,1 });
		if (tr[i]->_prevNo >= 0) 
			m_terrains[i]->SetPrevCollider(m_terrains[tr[i]->_prevNo]);
		if (tr[i]->_nextNo >= 0) 
			m_terrains[i]->SetNextCollider(m_terrains[tr[i]->_nextNo]);
	}

	m_newScene->ChangeScene();
	if (OBJECT->FindPlayer())
	{
		GET_PLAYER->_invincible_mapChange = true;
		GET_PLAYER->SetPosition(playerPos);
		if (GET_PLAYER->IsResurrecting()) GET_PLAYER->Init();
	}
}

MapManager::MapManager()
	: m_oldScene(nullptr)
	, m_curScene(nullptr)
	, m_newScene(nullptr)
{
}

MapManager::~MapManager()
{
	if (m_oldScene) delete m_oldScene;
	if (m_curScene) delete m_curScene;
	if (m_newScene) delete m_newScene;

	// 사용된 backgrounds 제거
	ClearBG();

	// 사용된 LineColliders(지형) 제거
	ClearTR();
}

void MapManager::ClearBG()
{
	for (auto& background : m_backgrounds)
		delete background;
	m_backgrounds.clear();
}

void MapManager::ClearTR()
{
	for (auto& terrain : m_terrains)
		delete terrain;
	m_terrains.clear();
}

