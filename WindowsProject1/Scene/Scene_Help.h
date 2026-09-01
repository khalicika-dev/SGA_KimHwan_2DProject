#pragma once
class Scene_Help : public Scene
{
public:
	// 해당 맵의 백그라운드정보
	virtual vector<shared_ptr<MapData>> Backgrounds() {
		vector<shared_ptr<MapData>> bg;
		bg.push_back(make_shared<MapData>(L"MapTutorial", Vector2(0, 0)));
		return bg;
	}
	// 해당 맵의 지형정보
	virtual vector<shared_ptr<TerrainData>> Terrains() {
		vector<shared_ptr<TerrainData>> tr;
		Vector2 pts[] = {
			{-116.0f + 10.0f, 117.0f},
			{-116.0f + 10.0f, -117.0f},
			{116.0f - 10.0f, -117.0f},
			{116.0f - 10.0f, 117.0f}
		};
		/*0*/ tr.push_back(make_shared<TerrainData>(pts[0], pts[1], LineCollider::DIRECTION::LWALL, -1, 1));
		/*1*/ tr.push_back(make_shared<TerrainData>(pts[1], pts[2], LineCollider::DIRECTION::FLOOR, 0, 2));
		/*2*/ tr.push_back(make_shared<TerrainData>(pts[2], pts[3], LineCollider::DIRECTION::RWALL, 1, -1));
		return tr;
	}
public:
	Scene_Help();
	virtual ~Scene_Help();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
private:
	shared_ptr<Button> _btn_main;

	void BtnEvent_Main();
};