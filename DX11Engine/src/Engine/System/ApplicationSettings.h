#pragma once

#include <cstdint>
#include <string>
#include <Windows.h>

namespace Engine
{
    namespace Settings
    {  
      /*!
       *@brief Available resolutions for the engine
       */
        enum class EngineResolution : std::uint8_t
        {
            SVGA,   //  800 x  600
            HD,     // 1280 x  720
            FullHD, // 1920 x 1080
        };

       /*!
        *@brief Settings the scene manager needs for starting the engine
        */
        struct ApplicationSettings
        {
            EngineResolution resolution = EngineResolution::SVGA;
            bool windowed = false;
            unsigned int fps = 0;
            LPCWSTR windowTitle = L"";
            HINSTANCE instance = nullptr;
            HINSTANCE prevInstance = nullptr;
            LPSTR parameters = nullptr;
            HWND hwnd = nullptr;
        };
    }
}