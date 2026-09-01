#pragma once
class Scene_Map2 : public Scene
{
public:
	// 해당 맵의 백그라운드정보
	virtual vector<shared_ptr<MapData>> Backgrounds() {
		vector<shared_ptr<MapData>> bg;
		bg.push_back(make_shared<MapData>(L"Map2", Vector2(0, 0)));
		return bg;
	}
	// 해당 맵의 지형정보
	virtual vector<shared_ptr<TerrainData>> Terrains() {
		vector<shared_ptr<TerrainData>> tr;
		Vector2 pts1[] = {
			{-535.0f, 670.0f},
			{-535.0f, -405.0f},
			{143.0f, -405.0f},
			{170.0f, -525.0f},
			{285.0f, -525.0f},
			{330.0f, -435.0f},
			{460.0f, -460.0f},
			{1000.0f, -460.0f}
		};
		/*0*/ tr.push_back(make_shared<TerrainData>(pts1[0], pts1[1], LineCollider::DIRECTION::LWALL, -1, 1, LineCollider::ATTRIBUTE::INVISIBLE));
		/*1*/ tr.push_back(make_shared<TerrainData>(pts1[1], pts1[2], LineCollider::DIRECTION::FLOOR, 0, 2));
		/*2*/ tr.push_back(make_shared<TerrainData>(pts1[2], pts1[3], LineCollider::DIRECTION::LWALL, 1, 3));
		/*3*/ tr.push_back(make_shared<TerrainData>(pts1[3], pts1[4], LineCollider::DIRECTION::FLOOR, 2, 4));
		/*4*/ tr.push_back(make_shared<TerrainData>(pts1[4], pts1[5], LineCollider::DIRECTION::RWALL, 3, 5));
		/*5*/ tr.push_back(make_shared<TerrainData>(pts1[5], pts1[6], LineCollider::DIRECTION::FLOOR, 4, 6));
		/*6*/ tr.push_back(make_shared<TerrainData>(pts1[6], pts1[7], LineCollider::DIRECTION::FLOOR, 5, -1));

		Vector2 pts2[] = {
			{-445.0f, -245.0f},
			{-345.0f, -245.0f},
			{-280.0f, -205.0f},
			{425.0f, -205.0f}
		};
		/*7*/ tr.push_back(make_shared<TerrainData>(pts2[0], pts2[1], LineCollider::DIRECTION::FLOOR, -1, 8));
		/*8*/ tr.push_back(make_shared<TerrainData>(pts2[1], pts2[2], LineCollider::DIRECTION::FLOOR, 7, 9));
		/*9*/ tr.push_back(make_shared<TerrainData>(pts2[2], pts2[3], LineCollider::DIRECTION::FLOOR, 8, -1));

		Vector2 pts3[] = {
			{292.0f, -90.0f},
			{540.0f, -90.0f},
			{655.0f, 140.0f}
		};
		/*10*/ tr.push_back(make_shared<TerrainData>(pts3[0], pts3[1], LineCollider::DIRECTION::FLOOR, -1, 11));
		/*11*/ tr.push_back(make_shared<TerrainData>(pts3[1], pts3[2], LineCollider::DIRECTION::RWALL, 10, -1));

		Vector2 pts4[] = {
			{-150.0f, 20.0f},
			{270.0f, 20.0f},
		};
		/*12*/ tr.push_back(make_shared<TerrainData>(pts4[0], pts4[1], LineCollider::DIRECTION::FLOOR, -1, -1));

		Vector2 pts5[] = {
			{10.0f, 165.0f},
			{110.0f, 165.0f},
			{242.0f, 240.0f},
			{1000.0f, 240.0f},
		};
		/*13*/ tr.push_back(make_shared<TerrainData>(pts5[0], pts5[1], LineCollider::DIRECTION::FLOOR, -1, 14));
		/*14*/ tr.push_back(make_shared<TerrainData>(pts5[1], pts5[2], LineCollider::DIRECTION::FLOOR, 13, 15));
		/*15*/ tr.push_back(make_shared<TerrainData>(pts5[2], pts5[3], LineCollider::DIRECTION::FLOOR, 14, -1));

		return tr;
	}
public:
	Scene_Map2();
	virtual ~Scene_Map2();

	void Update() override;
	void Render() override;
	void PostUpdate() override;
	void PostRender() override;
	void ChangeScene() override;
};

