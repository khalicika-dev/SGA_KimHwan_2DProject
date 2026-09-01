#pragma once
class Blooding : public GameObject
{
public:
	Blooding(Vector2 pos);
	virtual ~Blooding();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	enum class STATE
	{
		SPLATTER,
		STAIN
	}_state;

	float _time;

	// SPLATTER 관련 멤버변수
	shared_ptr<Transform> m_trans;
	VertexShader* m_vertexShader;	//Line을 Draw하는 셰이더, 버퍼
	PixelShader* m_pixelShader;
	VertexBuffer* m_vertexBuffer;
	ColorBuffer* m_colorBuffer;

	vector<Vertex> m_vertices; // 파티클을 이룰 점의 위치
	UINT _vtxNum;	// 파티클을 이루는 버텍스 개수
	const UINT _vtxMaxNum = 5;	// 버텍스의 최대 개수
	bool _isCollided;	//파티클 이동중 지형충돌여부
	float _xspeed;	// x좌표 이동량
	float _yspeed;	// y좌표 이동량
	const float _yaccel = 1600.0f;	// y좌표 가속도
	const float _ymin	= -700.0f;	// 최대 낙하속도
	const float _spltEndTime = 5.0f;	// 파티클이 증발하는 시간

	// STAIN 관련 멤버변수
	Sprite* _sprite;
	Action* _action;

	float _endTime;	// 얼룩이 사라지기 시작하는 시간
	const float _minTime = 1.0f;	// 얼룩이 사라지기 시작하는 최소시간
	const float _maxTime = 2.0f;	// 얼룩이 사라지기 시작하는 최대시간
	const float _clearTime = 0.3f;	// 얼룩이 완전히 사라지기까지 걸리는 시간
	bool _isDisappearing;	// 최대시간을 경과하여 얼룩이 사라지고 있는가?
};

