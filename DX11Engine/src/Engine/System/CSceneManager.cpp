#include "CSceneManager.h"

namespace Engine
{
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_KEYDOWN:
            switch (wParam)
            {
                // shutdown engine if escape was pressed
            case VK_ESCAPE:
                PostQuitMessage(0);
                CSceneManager::Instance()->Quit();
                break;
            }
            break;

            // shutdown engine if render window was deleted
        case WM_DESTROY:
            PostQuitMessage(0);
            CSceneManager::Instance()->Quit();
            break;
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

Engine::CSceneManager::CSceneManager()
{

}

Engine::CSceneManager::~CSceneManager()
{

}

bool Engine::CSceneManager::Initialize(Settings::ApplicationSettings a_settings)
{
    m_Initialized = true;

    // save the settings
    m_ApplicationSettings = a_settings;

    // get the resolution in pixel
    int resolution[2];
    switch (m_ApplicationSettings.resolution)
    {
    case Settings::EngineResolution::SVGA:
    {
        resolution[0] = 800;
        resolution[1] = 600;
        break;
    }
    case Settings::EngineResolution::HD:
    {
        resolution[0] = 1280;
        resolution[1] = 720;
        break;
    }
    case Settings::EngineResolution::FullHD:
    {
        resolution[0] = 1920;
        resolution[1] = 1080;
        break;
    }
    default:
        m_Initialized = false;
        break;
    }

    // create the window
    ZeroMemory(&m_WC, sizeof(WNDCLASS));
    m_WC.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    m_WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    m_WC.hInstance = m_ApplicationSettings.instance;
    m_WC.lpfnWndProc = WndProc;
    m_WC.lpszClassName = m_ApplicationSettings.windowTitle;
    m_WC.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&m_WC);

    m_ApplicationSettings.hwnd = CreateWindow(m_WC.lpszClassName, m_WC.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, resolution[0], resolution[1], NULL, NULL, m_ApplicationSettings.instance, NULL);

    ShowWindow(m_ApplicationSettings.hwnd, 1);
    UpdateWindow(m_ApplicationSettings.hwnd);

    // create the window
    if(m_Renderer.Initialize(&m_ApplicationSettings))
        return true;
    else return false;
}

void Engine::CSceneManager::Run()
{
    // shutdown engine if not initialized
    if (!m_Initialized)
    {
        // print error message to logfile
        CLog::Instance()->Write(2, 0);

        m_Quit = true;
    }

    // shutdown engine if no scene is active
    if (m_pSceneToActivate == nullptr && !m_Quit)
    {
        // print error message to logfile
        CLog::Instance()->Write(2, 1);

        m_Quit = true;
    }
    
    // timer and variables for framelock and getting deltatime
    CTimer timer;
    double renderTime = 1.0 / m_ApplicationSettings.fps;
    double currentRenderTime = renderTime;

    // if no framelimit is set render every loop
    if (m_ApplicationSettings.fps == 0)
        renderTime = 0;

    MSG msg = { 0 };

    // game loop
    while (!m_Quit)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // set new scene active
        if (m_pSceneToActivate != nullptr)
        {
            m_pActiveScene = m_pSceneToActivate;
            m_pSceneToActivate = nullptr;
        }

        // update deltatime
        timer.Update();

        // update scene
        m_pActiveScene->Update(timer.GetDeltaTime());

        if (currentRenderTime >= renderTime)
        {
            // render scene and update currentRenderTime
            m_pActiveScene->Render(); 
            currentRenderTime -= renderTime;
        }
        // increase currentRenderTime
        currentRenderTime += timer.GetDeltaTime();
    }
}

void Engine::CSceneManager::AddScene(const char * a_sceneName, IScene * a_scene)
{
    // insert scene and scene identifier in scene map
    m_Scenes.insert(std::pair<const char*, IScene*>(a_sceneName, a_scene));
}

bool Engine::CSceneManager::RemoveScene(const char * a_sceneName)
{
    // delete scene if a scene with this identifier is in scene map
    std::map<const char*, IScene*>::iterator itr = m_Scenes.find(a_sceneName);
    if(itr != m_Scenes.end())
    {
        m_Scenes.erase(a_sceneName);
        return true;
    }

    // print error message to logfile
    std::string tmp = "[CSceneManager.cpp] RemoveScene() - Scene not found: ";
    tmp += a_sceneName;
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Engine, tmp.c_str());

    return false;
}

bool Engine::CSceneManager::ActivateScene(const char * a_sceneName)
{
    // set scene active if a scene with this identifier is in scene map
    std::map<const char*, IScene*>::iterator itr = m_Scenes.find(a_sceneName);
    if (itr != m_Scenes.end())
    {
            m_pSceneToActivate = itr->second;
        return true;
    }

    // print error message to logfile
    std::string tmp = "[CSceneManager.cpp] ActivateScene() - Scene not found: ";
    tmp += a_sceneName;
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Engine, tmp.c_str());

    return false;
}

Engine::CRenderer * Engine::CSceneManager::GetRenderer()
{
    return &m_Renderer;
}

void Engine::CSceneManager::Quit()
{
    m_Quit = true;
}
