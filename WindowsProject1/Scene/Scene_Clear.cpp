#include "Framework.h"
#include "Scene_Clear.h"

Scene_Clear::Scene_Clear()
{
	_background = make_shared<Quad>(L"Resource/Textures/Title.png");
	_logo1 = make_shared<Quad>(L"Resource/Textures/Logo_Clear.png");
	_logo2 = make_shared<Quad>(L"Resource/Textures/Logo_Ending.png");

	_btn_main = make_shared<Button>(L"Resource/Textures/Btn_main.png");
	_btn_main->SetDelegate(bind(&Scene_Clear::BtnEvent_Main, this));
}

Scene_Clear::~Scene_Clear()
{
}

void Scene_Clear::Update()
{
}

void Scene_Clear::Render()
{
}

void Scene_Clear::PostUpdate()
{
	_background->Update();
	_logo1->Update();
	_logo2->Update();
	_btn_main->Update();
}

void Scene_Clear::PostRender()
{
	_background->Render();
	_logo1->Render();
	_logo2->Render();
	_btn_main->Render();
}

void Scene_Clear::ChangeScene()
{
	_background->GetTransform()->m_pos = { CENTER_X,CENTER_Y };
	_logo1->GetTransform()->m_pos = { CENTER_X, WINHEIGHT - 135.0f };
	_logo2->GetTransform()->m_pos = { CENTER_X, WINHEIGHT - 205.0f };
	_btn_main->GetTransform()->m_pos = { CENTER_X, 50.0f };
}

void Scene_Clear::BtnEvent_Main()
{
	MAPMANAGER->ChangeMap(MAP::TITLE, { 0.0f, 0.0f }, true);
}
