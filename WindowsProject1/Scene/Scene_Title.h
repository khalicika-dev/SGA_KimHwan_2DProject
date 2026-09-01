#pragma once
class Scene_Title : public Scene
{
public:
	Scene_Title();
	virtual ~Scene_Title();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
private:
	shared_ptr<Quad> _background;
	shared_ptr<Quad> _logo;

	shared_ptr<Button> _btn_start;
	shared_ptr<Button> _btn_help;

	void BtnEvent_Start();
	void BtnEvent_Help();
};

