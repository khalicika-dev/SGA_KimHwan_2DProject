#pragma once
class Timer
{
private:
	Timer();
	~Timer();

	static Timer* m_instance;
public:
	static void Create()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Timer();
		}
	}
	static Timer* Get()
	{
		if (m_instance != nullptr)
		{
			return m_instance;
		}

		return nullptr;
	}

	static void Delete()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	void Update();
	void SetLockFPS(double value) { m_lockFPS = value; }

	int GetFPS() { return m_frameRate; }
	double GetElapsedTime() { return m_timeElapsed; }
	double GetRunTime() { return m_runTime; }

private:
	double m_timeScale;
	double m_timeElapsed;

	__int64 m_curTime;
	__int64 m_lastTime;
	__int64 m_periodFrequency;

	int m_frameRate;
	int m_frameCount;

	double m_oneSecCount;
	double m_runTime;

	double m_lockFPS;
};

