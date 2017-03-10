#pragma once

#include "Engine\Engine.h"

#include <vector>

class CCubeScene : public IScene
{
#pragma region Variables
private:

    Engine::CCamera m_Camera;
    std::vector<Engine::CCube> m_CubeList;

    Engine::CLight m_Light;

#pragma endregion
#pragma region Methods
public:

    CCubeScene();
    ~CCubeScene();

    void Initialize() override;

    void Update(double a_deltaTime) override;
    void Render() override;

private:

#pragma endregion
};