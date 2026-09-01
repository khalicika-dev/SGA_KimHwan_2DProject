#include "Framework.h"
#include "Scene_Help.h"

Scene_Help::Scene_Help()
{
	//_box = make_shared<Quad>(L"Resource/Textures/IdleBox.png");

	_btn_main = make_shared<Button>(L"Resource/Textures/Btn_main.png");
	_btn_main->SetDelegate(bind(&Scene_Help::BtnEvent_Main, this));
}

Scene_Help::~Scene_Help()
{
}

void Scene_Help::Update()
{
	OBJECT->Update(OBJTYPE::PLAYER, 0);
	OBJECT->Update(OBJTYPE::ITEM, 0);
}

void Scene_Help::Render()
{
	OBJECT->Render(OBJTYPE::PLAYER, 0);
	OBJECT->Render(OBJTYPE::ITEM, 0);
}

void Scene_Help::PostUpdate()
{
	_btn_main->Update();
}

void Scene_Help::PostRender()
{
	DirectWrite::Get()->GetDC()->BeginDraw();

	//_box->Render();
	_btn_main->Render();

	//DirectWrite::Get()->RenderText(L"game start", { 0,WINHEIGHT / 2 + 50, WINWIDTH, WINHEIGHT / 2 + 50 }, 25.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"궁서", { 0.0f,0.0f,0.0f,1.0f });
	//DirectWrite::Get()->RenderText(L"help", { 0,WINHEIGHT / 2 + 100, WINWIDTH, WINHEIGHT / 2 + 100 }, 25.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"궁서", { 0.0f,0.0f,0.0f,1.0f });
	DirectWrite::Get()->RenderText(L"기본 조작법", { 50, 40, WINWIDTH, 40 }, 30.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"맑은 고딕", { 0.4f,0.4f,0.4f,1.0f }, DWRITE_FONT_WEIGHT_BOLD);
	DirectWrite::Get()->RenderText(L"캐릭터 조작", { 95, 100, WINWIDTH, 100 }, 20.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"맑은 고딕", { 0.4f,0.4f,0.4f,1.0f }, DWRITE_FONT_WEIGHT_BOLD);
	DirectWrite::Get()->RenderText(L"이동: 방향키 (← or →)\n공격: A\n점프 : SPACE BAR\n상호작용 : D", { 95, 130, WINWIDTH, 130 }, 15.0f, DWRITE_TEXT_ALIGNMENT_LEADING , L"맑은 고딕", { 0.4f,0.4f,0.4f,1.0f });

	DirectWrite::Get()->RenderText(L"그 외", { 95, 225, WINWIDTH, 225 }, 20.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"맑은 고딕", { 0.4f,0.4f,0.4f,1.0f }, DWRITE_FONT_WEIGHT_BOLD);
	DirectWrite::Get()->RenderText(L"히트박스 표시: F1", { 95, 255, WINWIDTH, 255 }, 15.0f, DWRITE_TEXT_ALIGNMENT_LEADING , L"맑은 고딕", { 0.4f,0.4f,0.4f,1.0f });
	//
	// 이동: 방향키 (← or →)
	// 공격: A
	// 점프 : SPACE BAR
	// 상호작용 : D
	// 
	// 그 외
	// 히트박스 표시 : F1
	//

	DirectWrite::Get()->GetDC()->EndDraw();
}

void Scene_Help::ChangeScene()
{
	OBJECT->Prepare(OBJTYPE::ITEM, 0);
	GET_PLAYER->SetPosition({ 0.0f, -115.0f });
	CAMERA->SetTarget(nullptr);
	CAMERA->SetPosition({ WINWIDTH - 212.5,WINHEIGHT - 182.5 });
	_btn_main->GetTransform()->m_pos = { CENTER_X, 40.0f };
	dynamic_cast<Item*>(OBJECT->Find(OBJTYPE::ITEM, 0))->SetItemType(Item::ActionType::WEAPON_NORMAL);
	OBJECT->Find(OBJTYPE::ITEM, 0)->SetPosition({ -100.0f,-117.0f });
}

void Scene_Help::BtnEvent_Main()
{
	MAPMANAGER->ChangeMap(MAP::TITLE, { 0.0f, 0.0f }, true);
}
