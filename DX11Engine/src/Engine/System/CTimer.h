#pragma once

#include <chrono>

namespace Engine
{
    class CTimer
    {
#pragma region Variables
    private:

        std::chrono::time_point<std::chrono::high_resolution_clock> m_CurrentUpdate;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastUpdate;
        double m_DeltaTime;

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the timer
        */
        CTimer();

        /*!
        *@brief Destructor for the timer
        */
        ~CTimer();

       /*!
        *@brief Updates the timing values
        */
        void Update();

       /*!
        *@brief Gets the time difference between the last update calls
        *
        *@returns double - the time difference between the last update calls in seconds
        */
        double GetDeltaTime();

    private:

#pragma endregion
    };
}