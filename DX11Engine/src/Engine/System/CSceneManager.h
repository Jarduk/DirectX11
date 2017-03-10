#pragma once

#include "TSingleton.h"
#include "ApplicationSettings.h"
#include "IScene.h"
#include "CTimer.h"
#include "CLog.h"
#include "CRenderer.h"

#include <map>
#include <list>

namespace Engine
{
    class CSceneManager : public TSingleton<CSceneManager>
    {
#pragma region Variables
    private:

        bool m_Quit = false;
        bool m_Initialized = false;

        Settings::ApplicationSettings m_ApplicationSettings;

        std::map<const char*, IScene*> m_Scenes;

        IScene* m_pActiveScene = nullptr;
        IScene* m_pSceneToActivate = nullptr;

        CRenderer m_Renderer;
        WNDCLASS m_WC;

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the scene manager
        */
        CSceneManager();

       /*!
        *@brief Destructor for the scene manager
        */
        ~CSceneManager();

       /*!
        *@brief Initialize the engine. has to be called before Run()
        *
        *@param Settings::ApplicationSettings a_settings - Application settings for initializing the engine 
        *
        *@returns True if succeed and false if an error occurs. Error will be displayed in LogEngine.txt
        */
        bool Initialize(Settings::ApplicationSettings a_settings);

       /*!
        *@brief Starts the main loop with the given settings
        */
        void Run();

       /*!
        *@brief Adds a scene to the scene manager
        *
        *@param const char* a_sceneName - Identifier of the scene
        *@param IScene* a_scene - Pointer to the scene
        */
        void AddScene(const char* a_sceneName, IScene* a_scene);

       /*!
        *@brief Removes the scene from the scene manager
        *
        *@param const char* a_sceneName - Identifier of the scene
        *
        *@returns Returns true if succeed and false if scene was not found
        */
        bool RemoveScene(const char* a_sceneName);

       /*!
        *@brief Sets scene active
        *
        *@param const char* a_sceneName - Identifier of the scene
        *
        *@returns Returns true if succeed and false if scene was not found
        */
        bool ActivateScene(const char* a_sceneName);

       /*!
        *@brief Gets a pointer to the DX11 renderer
        *
        *@returns Returns a pointer to the renderer
        */
        CRenderer* GetRenderer();

        /*!
        @brief Shuts down the engine
        */
        void Quit();

    private:

#pragma endregion
    };
}