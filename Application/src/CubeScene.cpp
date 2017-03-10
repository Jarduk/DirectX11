#include "CubeScene.h"

CCubeScene::CCubeScene()
{
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[CCubeScene.cpp] CCubeScene() - Constructor");
    Initialize();
}

CCubeScene::~CCubeScene()
{
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[CCubeScene.cpp] ~CCubeScene() - Destructor");
}

void CCubeScene::Initialize()
{
    Engine::CLog::Instance()->Write(Engine::CLog::ELogTarget::Application, "[CCubeScene.cpp] Initialize()");

    m_CubeList.push_back(Engine::CCube());
    m_CubeList.back().SetPosition(DirectX::XMFLOAT3(1, 0, 0));
    m_CubeList.push_back(Engine::CCube());
    m_CubeList.back().SetPosition(DirectX::XMFLOAT3(-1, 0, 0));

    // set camera settings
    Engine::CCamera::CAMERA_DESC cameraDesc;
    cameraDesc.FarPlane = 1000.f;
    cameraDesc.NearPlane = 0.1f;
    cameraDesc.FieldOfView = 80.f;
    cameraDesc.Resolution[0] = (float)Engine::CSceneManager::Instance()->GetRenderer()->GetResolution().cx;
    cameraDesc.Resolution[1] = (float)Engine::CSceneManager::Instance()->GetRenderer()->GetResolution().cy;

    // initialize camera with the settings
    m_Camera.Initialize(cameraDesc);

    // set camera position and view target
    m_Camera.SetPosition(0.0f, 1.0f, -1.5f);
    m_Camera.SetTarget(0.0f, 0.0f, 0.0f);

    // set light position, light range, light color and ambient color
    m_Light = Engine::CLight(DirectX::XMVECTOR{ 2.0f, 2.0f, -2.0f }, 15.f, DirectX::XMVECTOR{ 1.0f, 1.0f, 1.0f, 1.0f }, DirectX::XMVECTOR{ 1.0f, 1.0f, 1.0f, 0.1f });
}

void CCubeScene::Update(double a_deltaTime)
{
    // rotate cube by 360° per second around y axis
    m_CubeList[0].Rotate(DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), 360.0f * (float)a_deltaTime);
    m_CubeList[1].Rotate(DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), 360.0f * (float)a_deltaTime);
}

void CCubeScene::Render()
{
    // get pointer to the renderer
    Engine::CRenderer* pRenderer = Engine::CSceneManager::Instance()->GetRenderer();

    // begin rendering
    // set clear color, view matrix, look direction and projection matrix
    pRenderer->Begin(0x999999ff, &m_Camera);

    // pass the light and the cube to the renderer
    pRenderer->SetLight(&m_Light);
    for(int i = 0; i < m_CubeList.size(); i++)
        pRenderer->Draw(&m_CubeList[i]);
    
    // display rendered scene
    pRenderer->End();
}
