#pragma once
class Scene_Clear : public Scene
{
public:
	Scene_Clear();
	virtual ~Scene_Clear();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
private:
	shared_ptr<Quad> _background;
	shared_ptr<Quad> _logo1;
	shared_ptr<Quad> _logo2;

	shared_ptr<Button> _btn_main;

	void BtnEvent_Main();
};