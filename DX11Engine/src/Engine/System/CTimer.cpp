#include "CTimer.h"

Engine::CTimer::CTimer()
{
    m_LastUpdate = std::chrono::high_resolution_clock::now();
    m_CurrentUpdate = m_LastUpdate;
}

Engine::CTimer::~CTimer()
{

}

void Engine::CTimer::Update()
{
    m_LastUpdate = m_CurrentUpdate;
    m_CurrentUpdate = std::chrono::high_resolution_clock::now();

    // calculate delta time in seconds
    m_DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_CurrentUpdate - m_LastUpdate).count() / 1000000000.f;
}

double Engine::CTimer::GetDeltaTime()
{
    return (double)m_DeltaTime;
}
