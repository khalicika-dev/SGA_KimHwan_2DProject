#include "Framework.h"
#include "Program.h"

Program::Program()
{
	m_projectionBuffer = make_shared<MatrixBuffer>();

	//Matrix orthographic = XMMatrixOrthographicLH(
	//	(float)WINWIDTH, (float)WINHEIGHT, -1.0f, 1.0f);
	Matrix orthographic = XMMatrixOrthographicOffCenterLH(0, WINWIDTH, 0, WINHEIGHT, -1.0f, 1.0f);

	m_projectionBuffer->Set(orthographic);
	m_projectionBuffer->Update();

	MapManager::Create();
	ObjectManager::Create();
	UIStateManager::Create();

	CREATE_DEBUGGER();
	CREATE_KEYBOARD();
	CREATE_TIMER();
	
	GET_TIMER->SetLockFPS(60.0);

	PREPARE_PLAYER();
	//MAPMANAGER->ChangeMap(MAP::STAGE1, { 265.0f,-365.0f }, true);
	MAPMANAGER->ChangeMap(MAP::TITLE, { 0.0f, 0.0f }, true);
}

Program::~Program()
{
	DELETE_DEBUGGER();
	DELETE_KEYBOARD();
	DELETE_TIMER();

	MapManager::Delete();
	ObjectManager::Delete();
	UIStateManager::Delete();
}

void Program::Update()
{
	GET_KEYBOARD->Update();
	GET_TIMER->Update();
	DEBUG->Update();

	OBJECT->SetPickable(true);
	MAPMANAGER->Update();
	ObjectManager::Get()->Particles_Update();

	EFFECT->Update();

	MAPMANAGER->PostUpdate();
}

void Program::Render()
{
	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CAMERA->Update();
	m_projectionBuffer->SetVSBuffer(2);

	//ImGui::Text("FPS : %d", Timer::Get()->GetFPS());

	MAPMANAGER->Render();
	ObjectManager::Get()->Particles_Render();

	EFFECT->Render();

	CAMERA->PostUpdate();
	MAPMANAGER->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}