#pragma once

#include <DirectXMath.h>

namespace Engine
{
    class CCamera
    {
    public:

        struct CAMERA_DESC
        {
            float FieldOfView = 0;
            float Resolution[2] = { 0, 0 };
            float NearPlane = 0;
            float FarPlane = 0;
        };

#pragma region Variables
    private:

        CAMERA_DESC m_CameraSettings;

        DirectX::XMVECTOR m_Position = { 0.0f, 0.0f, -1.0f };
        DirectX::XMVECTOR m_Target = { 0.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR m_LookDirection = { 0.0f, 0.0f, 1.0f };
        DirectX::XMVECTOR m_Up = { 0.0f, 1.0f, 0.0f };

        DirectX::XMMATRIX m_View = DirectX::XMMatrixIdentity();
        DirectX::XMMATRIX m_Projection = DirectX::XMMatrixIdentity();

#pragma endregion
#pragma region Methods
    public:
       /*!
        *@brief Constructor for the camera
        */
        CCamera();
        
       /*!
        *@brief Destructor for the camera
        */
        ~CCamera();

       /*!
        *@brief Initialize the camera
        *
        *@param CAMERA_DESC a_cameraSettings - Camera settings for initializing the camera
        */
        void Initialize(CAMERA_DESC a_cameraSettings);

       /*!
        *@brief Initialize the camera
        *
        *@param CAMERA_DESC a_cameraSettings - Camera settings for initializing the camera
        *@param DirectX::XMFLOAT3 a_position - Position of the camera
        *@param DirectX::XMFLOAT3 a_target - View target of the camera
        */
        void Initialize(CAMERA_DESC a_cameraSettings, DirectX::XMFLOAT3 a_position, DirectX::XMFLOAT3 a_target);

       /*!
        *@brief Sets the position of the camera
        *
        *@param float x, y, z - Position of the camera
        */
        void SetPosition(float x, float y, float z);

       /*!
        *@brief Sets the view target
        *
        *@param float x, y, z - View target of the camera
        */
        void SetTarget(float x, float y, float z);

       /*!
        *@brief Gets the position of the camera
        *
        *@returns Returns the position as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetPosition();

       /*!
        *@brief Gets the view target position
        *
        *@returns Returns the position as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetTarget();
        
       /*!
        *@brief Gets the up vector
        *
        *@returns Returns the up vector as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetUp();
        
       /*!
        *@brief Gets the look vector
        *
        *@returns Returns the look vector as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetLookDirection();

       /*!
        *@brief Gets the view matrix
        *
        *@returns Returns the view matrix as DirectX::XMMATRIX
        */
        DirectX::XMMATRIX GetView();
        
       /*!
        *@brief Gets the projection matrix
        *
        *@returns Returns the projection matrix as DirectX::XMMATRIX
        */
        DirectX::XMMATRIX GetProjection();

    private:

        inline void CalculateUpVector();
        inline void CalculateLook();
        inline void CalculateView();
        inline void CalculateProjection();

#pragma endregion
    };
}
