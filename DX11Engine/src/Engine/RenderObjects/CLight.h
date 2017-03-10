#pragma once

#include <DirectXMath.h>

namespace Engine
{
    class CLight
    {
#pragma region Variables
    private:

        DirectX::XMVECTOR m_Position = DirectX::XMVECTOR{ 0,0,0 };
        DirectX::XMVECTOR m_LightColor = DirectX::XMVECTOR{ 0, 0, 0, 0 };
        DirectX::XMVECTOR m_AmbientColor = DirectX::XMVECTOR{ 0, 0, 0, 0 };
        float m_Range = 0.0f;

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the light
        */
        CLight();

       /*!
        *@brief Constructor for the light        
        *
        *@param DirectX::XMVECTOR a_position - The position of the light
        *@param float a_range - The range of the light
        *@param DirectX::XMVECTOR a_color - The color of the light
        */
        CLight(DirectX::XMVECTOR a_position, float a_range, DirectX::XMVECTOR a_lightColor, DirectX::XMVECTOR a_ambientColor);
        
       /*!
        *@brief Destructor for the light
        */
        ~CLight();

       /*!
        *@brief Sets the position of the light
        *
        *@param DirectX::XMVECTOR a_position - The position of the light
        */
        void SetPosition(DirectX::XMVECTOR a_position);

       /*!
        *@brief Sets the range of the light
        *
        *@param float a_range - The range of the light
        */
        void SetLightRange(float a_range);

       /*!
        *@brief Sets the color of the light
        *
        *@param DirectX::XMVECTOR a_color - The color of the light. Alpha is the intensity
        */
        void SetLightColor(DirectX::XMVECTOR a_color);

       /*!
        *@brief Sets ambient light color
        *
        *@param DirectX::XMVECTOR a_color - The ambient light color. Alpha is the intensity
        */
        void SetAmbientColor(DirectX::XMVECTOR a_color);

       /*!
        *@brief Gets the position of the light
        *
        *@returns Returns the position as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetLightPosition();

       /*!
        *@brief Gets the range of the light
        *
        *@returns Returns the range as float
        */
        float GetLightRange();

       /*!
        *@brief Gets the color of the light
        *
        *@returns Returns the color as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetLightColor();


       /*!
        *@brief Gets the ambient light color
        *
        *@returns Returns the color as DirectX::XMVECTOR
        */
        DirectX::XMVECTOR GetAmbientColor();

    private:

#pragma endregion
    };
}