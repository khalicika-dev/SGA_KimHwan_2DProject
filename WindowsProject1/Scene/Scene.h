#pragma once
class Scene
{
public:
	struct MapData	// 백그라운드 데이터
	{
		wstring _name;
		Vector2 _pos;

		MapData(wstring name, Vector2 pos) 
			:_name(name), _pos(pos) {}
	};
	struct TerrainData	// 지형 Collider 데이터
	{
		// 지형데이터의 특징 :
		// 각 지형Collider마다 Floor, Wall등의 DIRECTION를 붙여 충돌시 어느쪽으로 밀려날지를 결정하게 한다.
		// 지형 연결시 왼쪽부터 오른쪽으로 순서대로 연결되어야 한다.
		Vector2 _startPos;	//시작점
		Vector2 _endPos;	//끝점
		LineCollider::DIRECTION _direction;	// 지형의 타입
		LineCollider::ATTRIBUTE _attr;		// 지형의 속성

		// 이어지는 다음 지형의 번호, 지형번호는 생성 시 0부터 시작하며 변수값이 -1이면 아무것도 연결하지 않는다.
		int _prevNo;
		int _nextNo;

		TerrainData(Vector2 startPos, Vector2 endPos, LineCollider::DIRECTION direction, int prevNo = -1, int nextNo = -1, LineCollider::ATTRIBUTE attr = LineCollider::ATTRIBUTE::NONE)
			: _startPos(startPos), _endPos(endPos), _direction(direction), _prevNo(prevNo), _nextNo(nextNo), _attr(attr) {}
	};
public:
	virtual vector<shared_ptr<MapData>> Backgrounds() { return vector<shared_ptr<MapData>>(); }
	virtual vector<shared_ptr<TerrainData>> Terrains() { return vector<shared_ptr<TerrainData>>(); }
public:
	virtual ~Scene() {}

	virtual void Update() abstract; // virtual void Update() = 0와 비슷함
	virtual void Render() abstract;
	virtual void ChangeScene() {}
	virtual void PostUpdate() {}
	virtual void PostRender() {}
};