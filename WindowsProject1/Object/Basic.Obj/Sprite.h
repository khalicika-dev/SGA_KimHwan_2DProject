#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file);
	~Sprite();

	virtual void Render() override;
	virtual void CreateData() override;

	Vector2 GetSize() { return m_texture->GetSize(); }

	void SetAction(Action::Clip clip);
	void SetPosition(Vector2 pos) { m_trans->m_pos = pos; }
	void SetAlpha(float value) { _actionBuffer->data.alpha = value; }
private:
	ActionBuffer* _actionBuffer;
};

