#include "Framework.h"
#include "Timer.h"

Timer* Timer::m_instance = nullptr;

Timer::Timer()
	: m_frameRate(0)
	, m_frameCount(0)
	, m_timeElapsed(0)
	, m_oneSecCount(0)
	, m_runTime(0)
	, m_lockFPS(0)
{
	// 1초동안 CPU의 진동수를 반환하는 함수
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_periodFrequency); // 큰수

	// 현재 CPU 진동수
	QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);

	m_timeScale = 1.0 / (double)m_periodFrequency;
}

Timer::~Timer()
{

}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
	// (지금까지 진동한 횟수 - 처음에 진동한 횟수) * (1/초당진동한 횟수)
	m_timeElapsed = (double)(m_curTime - m_lastTime) * m_timeScale;

	if (m_lockFPS != 0)
	{
		while (m_timeElapsed < 1.0 / m_lockFPS)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
			m_timeElapsed = (double)(m_curTime - m_lastTime) * m_timeScale;
		}
	}

	m_lastTime = m_curTime;

	// FPS (Frame Per Second)
	m_frameCount++;
	m_oneSecCount += m_timeElapsed;

	if (m_oneSecCount >= 1)
	{
		m_frameRate = m_frameCount;
		m_frameCount = 0;
		m_oneSecCount = 0;
	}
	m_runTime += m_timeElapsed;
}
