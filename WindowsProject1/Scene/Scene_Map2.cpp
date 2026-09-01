#include "Framework.h"
#include "Scene_Map2.h"

Scene_Map2::Scene_Map2()
{
}

Scene_Map2::~Scene_Map2()
{
}

void Scene_Map2::Update()
{
	if (GET_PLAYER->GetPosition().x >= 650.0f && GET_PLAYER->GetPosition().y <= 150.0f)
		MAPMANAGER->ChangeMap(MAP::STAGE1, { -380.0f,-365.0f });
	if (GET_PLAYER->GetPosition().x >= 650.0f && GET_PLAYER->GetPosition().y > 150.0f)
		MAPMANAGER->ChangeMap(MAP::STAGE3, { -580.0f,-352.0f });

	OBJECT->Update(OBJTYPE::PLAYER, 0);
	OBJECT->Update(OBJTYPE::M_FLOWER, 0);
}

void Scene_Map2::Render()
{
	OBJECT->Render(OBJTYPE::PLAYER, 0);
	OBJECT->Render(OBJTYPE::M_FLOWER, 0);
}

void Scene_Map2::PostUpdate()
{
	UI_UPDATE();
}

void Scene_Map2::PostRender()
{
	UI_RENDER();
}

void Scene_Map2::ChangeScene()
{
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 0);
	GET_PLAYER->SetPosition({ 540.0f,-457.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 0)->SetPosition({ 100.0f,-403.0f });
	CAMERA->SetTarget(GET_PLAYER);
	CAMERA->SetRightTop({ 635.0f,830.0f });
	CAMERA->SetLeftBottom({ -585.0f,-760.0f });
}
