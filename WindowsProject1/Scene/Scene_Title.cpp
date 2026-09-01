#include "Framework.h"
#include "Scene_Title.h"

Scene_Title::Scene_Title()
{
	_background = make_shared<Quad>(L"Resource/Textures/Title.png");
	_logo = make_shared<Quad>(L"Resource/Textures/Logo.png");

	_btn_start = make_shared<Button>(L"Resource/Textures/Btn_gamestart.png");
	_btn_start->SetDelegate(bind(&Scene_Title::BtnEvent_Start, this));

	_btn_help = make_shared<Button>(L"Resource/Textures/Btn_help.png");
	_btn_help->SetDelegate(bind(&Scene_Title::BtnEvent_Help, this));
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Update()
{
}

void Scene_Title::Render()
{
}

void Scene_Title::PostUpdate()
{
	_background->Update();
	_logo->Update();
	_btn_start->Update();
	_btn_help->Update();
}

void Scene_Title::PostRender()
{
	DirectWrite::Get()->GetDC()->BeginDraw();

	_background->Render();
	_logo->Render();
	_btn_start->Render();
	_btn_help->Render();


	//DirectWrite::Get()->RenderText(L"game start", { 0,WINHEIGHT / 2 + 50, WINWIDTH, WINHEIGHT / 2 + 50 }, 25.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"±Ã¼­", { 0.0f,0.0f,0.0f,1.0f });
	//DirectWrite::Get()->RenderText(L"help", { 0,WINHEIGHT / 2 + 100, WINWIDTH, WINHEIGHT / 2 + 100 }, 25.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"±Ã¼­", { 0.0f,0.0f,0.0f,1.0f });
	DirectWrite::Get()->RenderText(L"2022³â ¼­¿ï°ÔÀÓ¾ÆÄ«µ¥¹Ì ±èÈ¯ÇÐ»ý ÀÛÇ°\n(ÇÃ·¡½Ã°ÔÀÓ-°« ¿Àºê °î±ªÀÌ ¸ðÀÛ)", { 0, WINHEIGHT - 35, WINWIDTH - 5, WINHEIGHT }, 12.0f, DWRITE_TEXT_ALIGNMENT_TRAILING);

	DirectWrite::Get()->GetDC()->EndDraw();
}

void Scene_Title::ChangeScene()
{
	_background->GetTransform()->m_pos = { CENTER_X,CENTER_Y };
	_logo->GetTransform()->m_pos = { CENTER_X, CENTER_Y + 90.0f };
	_btn_start->GetTransform()->m_pos = { CENTER_X,CENTER_Y - 50.0f };
	_btn_help->GetTransform()->m_pos = { CENTER_X,CENTER_Y - 100.0f };
}

void Scene_Title::BtnEvent_Start()
{
	UISTATE->Initialize();
	MAPMANAGER->ChangeMap(MAP::STAGE1, { 265.0f,-365.0f }, true);
}

void Scene_Title::BtnEvent_Help()
{
	UISTATE->Initialize();
	MAPMANAGER->ChangeMap(MAP::TITLE_HELP, { 0.0f, -115.0f }, true);
}
