#include "CLog.h"

Engine::CLog::CLog()
{
    Initialize();
}

Engine::CLog::~CLog()
{
    m_ApplicationLog.close();
    m_EngineLog.close();
}

bool Engine::CLog::Initialize()
{
    SaveModulPath();

    // open logfiles
    m_ApplicationLog.open(m_modulPath + m_Path + "LogApplication.txt");
    m_EngineLog.open(m_modulPath + m_Path + "LogEngine.txt");

    // get Time and Date
    std::time_t t = time(0);
    struct tm now;
    localtime_s(&now, &t);

    std::string tmp = ":";
    if (now.tm_min < 10) tmp += "0";

    std::string time = "Date: " + std::to_string(now.tm_mday) + "." + std::to_string(now.tm_mon + 1) + "." + std::to_string(now.tm_year + 1900) + "\n" +
        "Time: " + std::to_string(now.tm_hour) + tmp + std::to_string(now.tm_min) + "\n________________\n\n";

    // write time and date to the logfiles
    Write(1, time.c_str());
    Write(2, time.c_str());

    // load logstrings from file
    if (!LoadLogStrings()) return false;
    return true;
}

bool Engine::CLog::Write(ELogTarget a_target, const char* a_message)
{
    switch (a_target)
    {
        case Engine::CLog::ELogTarget::Console:
        {
            std::cout << a_message << std::endl;
            break;
        }
        case Engine::CLog::ELogTarget::Application:
        {
            m_ApplicationLog << a_message << "\n";
        #ifdef _DEBUG
            m_ApplicationLog.flush();
        #endif
            break;
        }
        case Engine::CLog::ELogTarget::Engine:
        {
            m_EngineLog << a_message << "\n";
        #ifdef _DEBUG
            m_EngineLog.flush();
        #endif
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool Engine::CLog::Write(unsigned int a_target, const char *a_message)
{
    switch (a_target)
    {
        case 0:
        {
            std::cout << a_message << std::endl;
            break;
        }
        case 1:
        {
            m_ApplicationLog << a_message << "\n";
        #ifdef _DEBUG
            m_ApplicationLog.flush();
        #endif
            break;
        }
        case 2:
        {
            m_EngineLog << a_message << "\n";
        #ifdef _DEBUG
            m_EngineLog.flush();
        #endif
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool Engine::CLog::Write(ELogTarget a_target, int a_messageID)
{
    switch (a_target)
    {
        case Engine::CLog::ELogTarget::Console:
        {
            std::cout << m_LogStrings[a_messageID].c_str() << std::endl;
            break;
        }
        case Engine::CLog::ELogTarget::Application:
        {
            m_ApplicationLog << m_LogStrings[a_messageID].c_str() << "\n";
        #ifdef _DEBUG
            m_ApplicationLog.flush();
        #endif
            break;
        }
        case Engine::CLog::ELogTarget::Engine:
        {
            m_EngineLog << m_LogStrings[a_messageID].c_str() << "\n";
        #ifdef _DEBUG
            m_EngineLog.flush();
        #endif
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool Engine::CLog::Write(unsigned int a_target, int a_messageID)
{
    switch (a_target)
    {
        case 0:
        {
            std::cout << m_LogStrings[a_messageID].c_str() << std::endl;
            break;
        }
        case 1:
        {
            m_ApplicationLog << m_LogStrings[a_messageID].c_str() << "\n";
        #ifdef _DEBUG
            m_ApplicationLog.flush();
        #endif
            break;
        }
        case 2:
        {
            m_EngineLog << m_LogStrings[a_messageID].c_str() << "\n";
        #ifdef _DEBUG
            m_EngineLog.flush();
        #endif
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

void Engine::CLog::Flush()
{
    m_ApplicationLog.flush();
    m_EngineLog.flush();
}

std::string Engine::CLog::GetModulPath()
{
    return m_modulPath;
}

bool Engine::CLog::LoadLogStrings()
{
    // Load and save log strings saved in the LogStrings.txt
    std::ifstream in;
    in.open(m_modulPath + m_Path + "LogStrings.txt");
    if (!in.is_open()) return false;

    unsigned int index = 0;

    while (!in.eof())
    {
        char buffer[1024];

        in.getline(buffer, 1024);
        m_LogStrings[index++] = buffer;
    }
    return true;
}

void Engine::CLog::SaveModulPath()
{
    // Save path to the application.exe
    char modulFilePath[MAX_PATH] = "";
    GetModuleFileNameA(NULL, modulFilePath, MAX_PATH);

    m_modulPath = modulFilePath;
    size_t stringPosition = m_modulPath.find_last_of(m_FindPath);
    m_modulPath.resize(stringPosition);
}