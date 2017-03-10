#include "CLight.h"

Engine::CLight::CLight()
{

}

Engine::CLight::CLight(DirectX::XMVECTOR a_position, float a_range, DirectX::XMVECTOR a_lightColor, DirectX::XMVECTOR a_ambientColor)
{
    m_Position = a_position;
    m_Range = a_range;
    m_LightColor = a_lightColor;
    m_AmbientColor = a_ambientColor;
}

Engine::CLight::~CLight()
{

}

void Engine::CLight::SetPosition(DirectX::XMVECTOR a_position)
{
    m_Position = a_position;
}

void Engine::CLight::SetLightRange(float a_range)
{
    m_Range = a_range;
}

void Engine::CLight::SetLightColor(DirectX::XMVECTOR a_color)
{
    m_LightColor = a_color;
}

void Engine::CLight::SetAmbientColor(DirectX::XMVECTOR a_color)
{
    m_AmbientColor = a_color;
}

DirectX::XMVECTOR Engine::CLight::GetLightPosition()
{
    return m_Position;
}

float Engine::CLight::GetLightRange()
{
    return m_Range;
}

DirectX::XMVECTOR Engine::CLight::GetLightColor()
{
    return m_LightColor;
}

DirectX::XMVECTOR Engine::CLight::GetAmbientColor()
{
    return m_AmbientColor;
}
