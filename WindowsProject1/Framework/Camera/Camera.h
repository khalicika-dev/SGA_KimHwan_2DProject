#pragma once

// ViewBuffer
class Camera : public Transform
{
private:
	Camera();
	virtual ~Camera();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Camera();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if (_instance == nullptr)
			return nullptr;

		return _instance;
	}

	void Update();
	void PostUpdate();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 0.0f);

	void SetTarget(class GameObject* value) { _target = value; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }
	void SetPosition(Vector2 value) { _originPos = value; }

	Vector2 GetMouseWorldPos();
private:
	void FreeMode();
	void FollowMode();
	void Shake();

	float _speed;

	class GameObject* _target;
	Vector2 _offset;

	Vector2 _leftBottom;
	Vector2 _rightTop;

	float _duration;
	float _reduceDamping;
	float _magnitude;

	Vector2 _originPos;

	shared_ptr<Transform> _postCamera;	// UI시점용 카메라
	static Camera* _instance;
};

