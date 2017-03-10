#include "CCamera.h"

Engine::CCamera::CCamera()
{

}

Engine::CCamera::~CCamera()
{

}

void Engine::CCamera::Initialize(CAMERA_DESC a_cameraSettings)
{
    // Save Camera settings
    m_CameraSettings = a_cameraSettings;

    // Calculate variables with the saved settings
    CalculateLook();
    CalculateUpVector();
    CalculateView();
    CalculateProjection();
}

void Engine::CCamera::Initialize(CAMERA_DESC a_cameraSettings, DirectX::XMFLOAT3 a_position, DirectX::XMFLOAT3 a_target)
{
    // Save Camera settings
    m_CameraSettings = a_cameraSettings;

    // Save given position and target
    m_Position = DirectX::XMLoadFloat3(&a_position);
    m_Target = DirectX::XMLoadFloat3(&a_target);

    // Calculate variables with the saved settings
    CalculateLook();
    CalculateUpVector();
    CalculateView();
    CalculateProjection();
}

void Engine::CCamera::SetPosition(float x, float y, float z)
{
    // Save given position
    m_Position.m128_f32[0] = x;
    m_Position.m128_f32[1] = y;
    m_Position.m128_f32[2] = z;

    // Calculate variables with the saved settings
    CalculateLook();
    CalculateUpVector();
    CalculateView();
}
void Engine::CCamera::SetTarget(float x, float y, float z)
{
    // Save given target
    m_Target.m128_f32[0] = x;
    m_Target.m128_f32[1] = y;
    m_Target.m128_f32[2] = z;

    // Calculate variables with the saved settings
    CalculateLook();
    CalculateUpVector();
    CalculateView();
}

DirectX::XMVECTOR Engine::CCamera::GetPosition()
{
    return m_Position;
}

DirectX::XMVECTOR Engine::CCamera::GetTarget()
{
    return m_Target;
}

DirectX::XMVECTOR Engine::CCamera::GetUp()
{
    return m_Up;
}

DirectX::XMVECTOR Engine::CCamera::GetLookDirection()
{
    return m_LookDirection;
}

DirectX::XMMATRIX Engine::CCamera::GetView()
{
    return m_View;
}

DirectX::XMMATRIX Engine::CCamera::GetProjection()
{
    return m_Projection;
}

void Engine::CCamera::CalculateUpVector()
{
    m_Up = DirectX::XMVector3Cross(DirectX::XMVector3Cross(m_LookDirection, DirectX::XMVECTOR{ 0.f,1.f,0.f }), m_LookDirection);
}

void Engine::CCamera::CalculateLook()
{
    m_LookDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(m_Target, m_Position));
}

void Engine::CCamera::CalculateView()
{
    m_View = DirectX::XMMatrixLookAtLH(m_Position, m_LookDirection, m_Up);
}

void Engine::CCamera::CalculateProjection()
{
    m_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_CameraSettings.FieldOfView),
        m_CameraSettings.Resolution[0] / m_CameraSettings.Resolution[1], m_CameraSettings.NearPlane, m_CameraSettings.FarPlane);
}