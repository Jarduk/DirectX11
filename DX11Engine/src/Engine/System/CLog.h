#pragma once

#include "TSingleton.h"

#include <Windows.h>
#include <ctime>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace Engine
{
    class CLog : public Engine::TSingleton<CLog>
    {
    public:

        enum class ELogTarget : std::uint8_t
        {
            Console = 0,
            Application = 1,
            Engine = 2,
        };

#pragma region Variables
    private:

        std::string m_modulPath;

        std::ofstream m_ApplicationLog;
        std::ofstream m_EngineLog;

        std::string m_LogStrings[10];

        const std::string m_Path = "\\data\\Log\\";
        const std::string m_FindPath = "\\";

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the log
        */
        CLog();

       /*!
        *@brief Destructor for the log
        */
        virtual ~CLog();

       /*!
        *@brief Writes a message to the selected target
        *
        *@param ELogTarget a_target - The target where to write the message
        *@param const char* a_message - The actual message to write
        *
        *@returns Returns true if succeed and false if the target was not valid
        */
        bool Write(ELogTarget a_target, const char* a_message);

       /*!
        *@brief Writes a message to the selected target
        *
        *@param unsigned int a_target - The target where to write the message
        *@param const char* a_message - The actual message to write
        *
        *@returns Returns true if succeed and false if the target was not valid
        */
        bool Write(unsigned int a_target, const char* a_message);

       /*!
        *@brief Writes a message to the selected target
        *
        *@param ELogTarget a_target - The target where to write the message
        *@param int a_messageID - The ID of the message to write from the LogStrings.txt 
        *
        *@returns Returns true if succeed and false if the target was not valid
        */
        bool Write(ELogTarget a_target, int a_messageID);
        
       /*!
        *@brief Writes a message to the selected target
        *
        *@param unsigned int a_target - The target where to write the message
        *@param int a_messageID - The ID of the message to write from the LogStrings.txt 
        *
        *@returns Returns true if succeed and false if the target was not valid
        */
        bool Write(unsigned int a_target, int a_messageID);

        /*!
        @brief Fills the log files with the messages. Not needed in debug configuration.
        */
        void Flush();

       /*!
        *@brief Get the path to the application.exe
        *
        *@returns Returns path as std::string 
        */
        std::string GetModulPath();

    private:

        bool Initialize();
        bool LoadLogStrings();

        void SaveModulPath();

#pragma endregion
    };
}