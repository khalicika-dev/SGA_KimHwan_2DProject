#include "Framework.h"
#include "Scene_Map3.h"

Scene_Map3::Scene_Map3()
{
}

Scene_Map3::~Scene_Map3()
{
}

void Scene_Map3::Update()
{
	// ¸ÊÀÌµ¿
	if (GET_PLAYER->GetPosition().x <= -635.0f)
		MAPMANAGER->ChangeMap(MAP::STAGE2, { 580.0f, 242.0f });
	if (GET_PLAYER->GetPosition().x >= 625.0f)
		MAPMANAGER->ChangeMap(MAP::STAGE4, { -500.0f, -78.0f });

	OBJECT->Update(OBJTYPE::PLAYER, 0);
	OBJECT->Update(OBJTYPE::M_FLOWER, 0);
	OBJECT->Update(OBJTYPE::M_FLOWER, 1);
	OBJECT->Update(OBJTYPE::M_FLOWER, 2);
	OBJECT->Update(OBJTYPE::ITEM, 0);
	OBJECT->Update(OBJTYPE::ITEM, 1);
}

void Scene_Map3::Render()
{
	OBJECT->Render(OBJTYPE::PLAYER, 0);
	OBJECT->Render(OBJTYPE::M_FLOWER, 0);
	OBJECT->Render(OBJTYPE::M_FLOWER, 1);
	OBJECT->Render(OBJTYPE::M_FLOWER, 2);
	OBJECT->Render(OBJTYPE::ITEM, 0);
	OBJECT->Render(OBJTYPE::ITEM, 1);
}

void Scene_Map3::PostUpdate()
{
	UI_UPDATE();
}

void Scene_Map3::PostRender()
{
	UI_RENDER();
}

void Scene_Map3::ChangeScene()
{
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 0);
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 1);
	OBJECT->Prepare(OBJTYPE::M_FLOWER, 2);
	OBJECT->Prepare(OBJTYPE::ITEM, 0);
	OBJECT->Prepare(OBJTYPE::ITEM, 1);
	GET_PLAYER->SetPosition({ -580.0f,-352.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 0)->SetPosition({ -245.0f,-335.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 1)->SetPosition({ 0.0f,-270.0f });
	OBJECT->Find(OBJTYPE::M_FLOWER, 2)->SetPosition({ 250.0f,-205.0f });
	dynamic_cast<Item*>(OBJECT->Find(OBJTYPE::ITEM, 0))->SetItemType(Item::ActionType::WEAPON_NORMAL);
	OBJECT->Find(OBJTYPE::ITEM, 0)->SetPosition({ 462.0f,-205.0f });
	dynamic_cast<Item*>(OBJECT->Find(OBJTYPE::ITEM, 1))->SetItemType(Item::ActionType::ARMOR_NORMAL);
	OBJECT->Find(OBJTYPE::ITEM, 1)->SetPosition({ 405.0f,-205.0f });
	CAMERA->SetTarget(GET_PLAYER);
	CAMERA->SetRightTop({ 665.0f,570.0f });
	CAMERA->SetLeftBottom({ -635.0f,-510.0f });
}
