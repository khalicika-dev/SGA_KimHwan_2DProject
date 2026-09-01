#pragma once
class Effect
{
public:
	Effect(wstring textureFile, UINT maxFrameX, UINT maxFrameY, vector<float> speed);
	virtual ~Effect();

	void Update();
	void Render();

	void Play(Vector2 pos, float angle, Vector2 scale);
	void End();

	void SetAdditive(bool value) { _isAdditive = value; }
	void SetScale(Vector2 scale) { _sprite->SetScale(scale); }
	void SetPosition(Vector2 pos) { _sprite->SetPosition(pos); }
	bool IsPlay() { return _action->IsPlay(); }

	bool _isActive;
private:
	Sprite* _sprite;
	Action* _action;

	bool _isAdditive;
};

