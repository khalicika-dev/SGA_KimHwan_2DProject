#pragma once
class Scene_Map4 : public Scene
{
public:
	// 해당 맵의 백그라운드정보
	virtual vector<shared_ptr<MapData>> Backgrounds() {
		vector<shared_ptr<MapData>> bg;
		bg.push_back(make_shared<MapData>(L"Map4", Vector2(0, 0)));
		return bg;
	}
	// 해당 맵의 지형정보
	virtual vector<shared_ptr<TerrainData>> Terrains() {
		vector<shared_ptr<TerrainData>> tr;
		Vector2 pts1[] = {
			{-1000.0f, -80.0f},
			{1000.0f, -80.0f}
		};
		/*0*/ tr.push_back(make_shared<TerrainData>(pts1[0], pts1[1], LineCollider::DIRECTION::FLOOR, -1, -1));

		return tr;
	}
public:
	Scene_Map4();
	virtual ~Scene_Map4();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
};
