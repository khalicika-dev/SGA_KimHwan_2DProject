#pragma once
class Scene_Map1 : public Scene
{
public:
	// 해당 맵의 백그라운드정보
	virtual vector<shared_ptr<MapData>> Backgrounds() {
		vector<shared_ptr<MapData>> bg;
		bg.push_back(make_shared<MapData>(L"Map1", Vector2(0, 0)));
		return bg;
	}
	// 해당 맵의 지형정보
	virtual vector<shared_ptr<TerrainData>> Terrains() {
		vector<shared_ptr<TerrainData>> tr;
		Vector2 pts[] = {
			{-1000.0f, -370.0f},
			{665.0f, -370.0f},
			{665.0f, 400.0f}
		};
		/*0*/ tr.push_back(make_shared<TerrainData>(pts[0], pts[1], LineCollider::DIRECTION::FLOOR, -1, 1));
		/*1*/ tr.push_back(make_shared<TerrainData>(pts[1], pts[2], LineCollider::DIRECTION::RWALL, 0, -1, LineCollider::ATTRIBUTE::INVISIBLE));
		return tr;
	}
public:
	Scene_Map1();
	virtual ~Scene_Map1();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
};

