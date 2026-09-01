#include "Framework.h"
#include "Scene_Map4.h"

Scene_Map4::Scene_Map4()
{
}

Scene_Map4::~Scene_Map4()
{
}

void Scene_Map4::Update()
{
	// 맵이동
	if (GET_PLAYER->GetPosition().x < -585.0f)
	{
		// 보스전 끝나기전까지는 이동불가
		// 보스전이 끝나면 이동가능
		if (OBJECT->Find(OBJTYPE::M_BOSS_FLOWER, 0)->GetActive())
			GET_PLAYER->MovePosition({ -585.0f, GET_PLAYER->GetPosition().y });
		else
			MAPMANAGER->ChangeMap(MAP::STAGE3, { 600.0f, -203.0f });
	}
	if (GET_PLAYER->GetPosition().x > 635.0f)
	{
		// 보스전 끝나기전까지는 이동불가
		// 보스전이 끝나면 이동가능
		if (OBJECT->Find(OBJTYPE::M_BOSS_FLOWER, 0)->GetActive())
			GET_PLAYER->MovePosition({ 635.0f, GET_PLAYER->GetPosition().y });
		else
			MAPMANAGER->ChangeMap(MAP::CLEAR, { 0.0f,0.0f });
	}
		

	OBJECT->Update(OBJTYPE::PLAYER, 0);
	OBJECT->Update(OBJTYPE::M_FLOWER, 0);
	OBJECT->Update(OBJTYPE::M_FLOWER, 1);
	OBJECT->Update(OBJTYPE::M_BOSS_FLOWER, 0);
}

void Scene_Map4::Render()
{
	OBJECT->Render(OBJTYPE::PLAYER, 0);
	OBJECT->Render(OBJTYPE::M_FLOWER, 0);
	OBJECT->Render(OBJTYPE::M_FLOWER, 1);
	OBJECT->Render(OBJTYPE::M_BOSS_FLOWER, 0);
}

void Scene_Map4::PostUpdate()
{
	UI_UPDATE();
}

void Scene_Map4::PostRender()
{
	UI_RENDER();
}

void Scene_Map4::ChangeScene()
{
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 0);
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 1);
	OBJECT->Prepare(OBJTYPE::M_BOSS_FLOWER, 0);
	GET_PLAYER->SetPosition({ -500.0f, -78.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 0)->SetPosition({ -10.0f,-78.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 1)->SetPosition({ 60.0f,-78.0f });
	OBJECT->Find(OBJTYPE::M_BOSS_FLOWER, 0)->SetPosition({ 40.0f,-78.0f });
	CAMERA->SetTarget(GET_PLAYER);
	CAMERA->SetRightTop({ 635.0f,600.0f });
	CAMERA->SetLeftBottom({ -585.0f,-270.0f });
}
