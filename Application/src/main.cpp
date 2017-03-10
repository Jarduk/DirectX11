#pragma once

#include "Engine\Engine.h"

#include "CubeScene.h"

#include <Windows.h>

#if _DEBUG
//#include "vld.h"

int main(HINSTANCE a_instance, HINSTANCE a_prevInstance, LPSTR a_cmd)
#else
int WINAPI WinMain(HINSTANCE a_instance, HINSTANCE a_prevInstance, LPSTR a_cmd, int a_cmdShow)
#endif
{
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[main.cpp] main() - Application startup");

    // set engine settings
    Engine::Settings::ApplicationSettings settings;
    settings.resolution = Engine::Settings::EngineResolution::HD;
    settings.windowed = true;
    settings.fps = 60;
    settings.windowTitle = L"Cube Rotator";
    settings.instance = a_instance;
    settings.prevInstance = a_prevInstance;
    settings.parameters = a_cmd;
    
    // initialize engine with the settings
    if (Engine::CSceneManager::Instance()->Initialize(settings))
    {    
        // create cube scene
        CCubeScene cubeScene;

        // add scene and set it active
        Engine::CSceneManager::Instance()->AddScene("CubeScene", &cubeScene);
        Engine::CSceneManager::Instance()->ActivateScene("CubeScene");
        
        // run the engine
        Engine::CSceneManager::Instance()->Run();
    }
    else
    {
        Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[main.cpp] main() - SceneManager could not be initialized");
    }

    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[main.cpp] main() - Application shutdown");
    Engine::CLog::Instance()->Flush();
    return 0;
}