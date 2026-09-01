#pragma once
class Item : public GameObject
{
public:
	enum ActionType
	{
		NONE = 0,
		WEAPON_NORMAL = 1 << 0,
		ARMOR_NORMAL = 1 << 1
	};

	Item();
	~Item();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	void SetItemType(ActionType type);
private:
	Sprite* _sprite;
	Action* _action;
	ActionType _curAction;

	Collider* _col;
};

