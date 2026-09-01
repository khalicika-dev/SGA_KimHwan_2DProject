#pragma once

class UIStateManager
{
public:
	enum AcquireStatus
	{
		NONE = 0,
		WEAPON_NORMAL = 1 << 0,
		ARMOR_NORMAL = 1 << 1
	}_acquire_status;
public:
	static void Create()
	{
		if (m_instance == nullptr)
			m_instance = new UIStateManager();
	}

	static void Delete()
	{
		if (m_instance != nullptr)
			delete m_instance;
	}

	static UIStateManager* Get()
	{
		if (m_instance != nullptr)
			return m_instance;
		assert(false);
	}

	void Update();
	void Render();
	void Initialize();

	void SetTargetHp(int hp, int maxHp);
	void AddGold(int value) { _gold += value; }
	void FadeScene(MAP targetScene, Vector2 playerPos);
	void Acquire(AcquireStatus value) { _acquire_status = static_cast<AcquireStatus>(static_cast<int>(_acquire_status) | static_cast<int>(value)); }
	bool IsAcquired(AcquireStatus value) { return _acquire_status & value; }
	bool IsFading();

	void SetDialogText(wstring text, float timer = 0.0f);
private:
	enum class FADE_STATE
	{
		NONE,
		FADE_IN,
		FADE_PEAK,
		FADE_OUT
	}_fade;
	float _fadeTime;
	const float _fadeMaxTime = 0.25f;

	MAP _nextScene;
	Vector2 _nextPlayerPos;

	Quad* _fadeRect;
	Quad* _playerHp;
	Quad* _playerEmptyHp;

	Quad* _enemyHp;
	Quad* _enemyEmptyHp;
	Quad* _enemyIcon;

	Quad* _dialogRect;
	int _drWidth;
	int _drHeight;

	int _gold;
	wstring _dialogText;
	float _textTimer;

	//--아이콘 부문--
	Quad* _atkIconRect;
	Quad* _defIconRect;
	Sprite* _weaponIcon;
	Sprite* _armorIcon;
	map<Player_Weapon::WeaponType, Action*> _iconAtkActions;
	map<Player::ArmorType, Action*> _iconDefActions;
	//---------------
	
	UIStateManager();
	~UIStateManager();
	void SpriteInit_Icon();
	static UIStateManager* m_instance;
};