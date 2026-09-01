#pragma once
class Button : public Quad
{
public:
	enum State
	{
		NONE,
		DOWN,
		OVER
	};

	Button(wstring file);
	virtual ~Button();

	void SetDelegate(Delegate delegate) { _delegate = delegate; }

	virtual void Update() override;
	virtual void Render() override;
private:
	Collider* _collider;
	Delegate _delegate;

	// 버튼일 때
	// 스프라이트 여러개로 만드느냐

	// 스프라이트 한개로 명암처리를 다르게 할 것인가
	ColorBuffer* _colorBuffer;

	State _state;
	bool _pressed;
};

