#pragma once
class Scene_Map3 : public Scene
{
public:
	// 해당 맵의 백그라운드정보
	virtual vector<shared_ptr<MapData>> Backgrounds() {
		vector<shared_ptr<MapData>> bg;
		bg.push_back(make_shared<MapData>(L"Map3", Vector2(0, 0)));
		return bg;
	}
	// 해당 맵의 지형정보
	virtual vector<shared_ptr<TerrainData>> Terrains() {
		vector<shared_ptr<TerrainData>> tr;
		Vector2 pts1[] = {
			{-1000.0f, -355.0f},
			{-315.0f, -355.0f},
			{270.0f, -205.0f},
			{1000.0f, -205.0f}
		};
		/*0*/ tr.push_back(make_shared<TerrainData>(pts1[0], pts1[1], LineCollider::DIRECTION::FLOOR, -1, 1));
		/*1*/ tr.push_back(make_shared<TerrainData>(pts1[1], pts1[2], LineCollider::DIRECTION::FLOOR, 0, 2));
		/*2*/ tr.push_back(make_shared<TerrainData>(pts1[2], pts1[3], LineCollider::DIRECTION::FLOOR, 1, -1));

		return tr;
	}
public:
	Scene_Map3();
	virtual ~Scene_Map3();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
};

