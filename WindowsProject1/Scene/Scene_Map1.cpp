#include "Framework.h"
#include "Scene_Map1.h"

Scene_Map1::Scene_Map1()
{
}

Scene_Map1::~Scene_Map1()
{
}

void Scene_Map1::Update()
{
	if (GET_PLAYER->GetPosition().x <= -480.0f)
		MAPMANAGER->ChangeMap(MAP::STAGE2, { 540.0f,-457.0f });

	OBJECT->Update(OBJTYPE::PLAYER, 0);
}

void Scene_Map1::Render()
{
	OBJECT->Render(OBJTYPE::PLAYER, 0);
}

void Scene_Map1::PostUpdate()
{
	UI_UPDATE();
}

void Scene_Map1::PostRender()
{
	UI_RENDER();	// UI를 표시하겠다
}

void Scene_Map1::ChangeScene()
{
	GET_PLAYER->SetPosition({ 265.0f,-365.0f });
	CAMERA->SetTarget(GET_PLAYER);
	CAMERA->SetRightTop({ 715.0f,500.0f });
	CAMERA->SetLeftBottom({ -870.0f,-520.0f });
}
