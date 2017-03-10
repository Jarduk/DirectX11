#pragma once

#include <DirectXMath.h>
#include <vector>
#include "Vertex.h"

namespace Engine
{
    class IShape
    {
#pragma region Variables
    protected:

        std::vector<Vertex> m_Vertices;

        DirectX::XMMATRIX m_World = DirectX::XMMatrixIdentity();

        bool m_Transformed = false;
        DirectX::XMMATRIX m_RotatationMatrix = DirectX::XMMatrixIdentity();
        DirectX::XMMATRIX m_ScaleMatrix = DirectX::XMMatrixIdentity();
        DirectX::XMMATRIX m_TranslationMatrix = DirectX::XMMatrixIdentity();
        DirectX::XMFLOAT3 m_Pivot = DirectX::XMFLOAT3(0, 0, 0);

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the shape
        */
        IShape() {};

       /*!
        *@brief Destructor for the shape
        */
        ~IShape() {};

       /*!
        *@brief Scales the shape
        *
        *@param DirectX::XMFLOAT3 a_scaleFactor - Scale factor for the x, y and z side
        */
        virtual void Scale(DirectX::XMFLOAT3 a_scaleFactor)
        {
            m_ScaleMatrix *= DirectX::XMMatrixScaling(a_scaleFactor.x, a_scaleFactor.y, a_scaleFactor.z);
            m_Transformed = true;
        }

       /*!
        *@brief Scales the shape
        *
        *@param float a_scaleFactor - Scale factor for scaling the whole shape
        */
        virtual void Scale(float a_scaleFactor)
        {
            m_ScaleMatrix *= DirectX::XMMatrixScaling(a_scaleFactor, a_scaleFactor, a_scaleFactor);
            m_Transformed = true;
        }

       /*!
        *@brief Moves the shape
        *
        *@param DirectX::XMFLOAT3 a_translation - Direction and range to move the shape
        */
        virtual void Move(DirectX::XMFLOAT3 a_translation)
        {
            m_TranslationMatrix *= DirectX::XMMatrixTranslation(a_translation.x + m_Pivot.x, a_translation.y + m_Pivot.y, a_translation.z + m_Pivot.z);
            m_Transformed = true;
        }

       /*!
        *@brief Sets the position of the shape
        *
        *@param DirectX::XMFLOAT3 a_position - New position of the shape
        */
        virtual void SetPosition(DirectX::XMFLOAT3 a_position)
        {
            m_TranslationMatrix.r[3].m128_f32[0] = a_position.x + m_Pivot.x;
            m_TranslationMatrix.r[3].m128_f32[1] = a_position.y + m_Pivot.y;
            m_TranslationMatrix.r[3].m128_f32[2] = a_position.z + m_Pivot.z;
            m_Transformed = true;
        }

        /*!
        *@brief Sets the Pivot of the shape
        *
        *@param DirectX::XMFLOAT3 a_pivot - New position of the pivot
        */
        virtual void SetPivot(DirectX::XMFLOAT3 a_pivot)
        {
            m_Pivot = DirectX::XMFLOAT3(-a_pivot.x, -a_pivot.y, -a_pivot.z);
            m_TranslationMatrix *= DirectX::XMMatrixTranslation(m_Pivot.x, m_Pivot.y, m_Pivot.z);
            m_Transformed = true;
        }

       /*!
        *@brief Rotates the shape
        *
        *@param DirectX::XMFLOAT3 a_axis - The axis in which to rotate
        *@param float a_angle - the angle how far to rotate
        */
        virtual void Rotate(DirectX::XMFLOAT3 a_axis, float a_angle)
        {
            m_RotatationMatrix *= DirectX::XMMatrixRotationRollPitchYaw(a_axis.x * DirectX::XMConvertToRadians(a_angle), a_axis.y * DirectX::XMConvertToRadians(a_angle), a_axis.z * DirectX::XMConvertToRadians(a_angle));
            m_Transformed = true;
        }
        
       /*!
        *@brief Sets all transformations to initial value
        */
        virtual void ResetTransformation()
        {
            m_ScaleMatrix = m_TranslationMatrix = m_RotatationMatrix = DirectX::XMMatrixIdentity();
            m_Transformed = true;
        }

       /*!
        *@brief Gets the world matrix of the shape
        *
        *@returns Returns the matrix as DirectX::XMMATRIX
        */
        virtual DirectX::XMMATRIX GetWorld()
        {
            // if transformed calculate new world matrix
            if (m_Transformed)
            {
                m_World = m_ScaleMatrix * m_RotatationMatrix * m_TranslationMatrix;
                m_Transformed = false;
            }
            return m_World;
        }

       /*!
        *@brief Gets the vertices of the shape
        *
        *@returns Returns the vertices as std::vector<Vertex>
        */
        virtual std::vector<Vertex> GetVertices()
        {
            return m_Vertices;
        }
        
#pragma endregion
    };
}