#pragma once
class Action
{
public:
	struct Clip
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 pivot;
		float speed;

		Clip(float x, float y, float w, float h, float speed = 0.1f, float px = 0.0f, float py = 0.0f)
			: startPos(x, y)
			, size(w, h)
			, speed(speed)
			, pivot(px, py)
		{

		}
	};

	enum Type
	{
		END,		// 한번만 재생함
		LOOP,		// 재생을 반복함
		PINGPONG	// 재생/역재생을 반복함
	};

	Action(vector<Clip> clips, Type type = LOOP, Delegate endEvent = nullptr);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void gotoStop(UINT ClipNo);

	void SetEvent(Delegate event) { _endEvent = event; }

	Clip GetCurClip() { return _clips[_curClipNo]; }		// 현재 재생중인 클립을 가져온다
	Clip GetClip(UINT clipNo) { return _clips[clipNo]; }	// 액션의 특정클립을 가져온다
	UINT GetCurClipNo() { return _curClipNo; }				// 현재 재생중인 클립의 프레임을 가져온다.
	bool IsPlay() { return _isPlay; }
	void SetClipSpeed(UINT ClipNo, float value) { _clips[ClipNo].speed = value; }
private:
	vector<Clip> _clips; // 몇번부터 몇번까지 돌건지 저장

	Type _repeatType; // 한번 재생 or 핑퐁 or 무한반복
	
	bool _isPlay; // 재생할 것인가

	UINT _curClipNo;	//지금 재생되고 있는 클립 넘버 저장

	// time에 경과된 시간을 더해서 speed를 넘기면
	// 실행되게끔
	float _time;

	bool _isReverse;

	Delegate _endEvent;	// 애니메이션이 끝나면 호출할 함수
};

