#pragma once

// include the basic windows header files and the Direct3D header files
//#include <windows.h>
#include <D3D11.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>

// include the Direct3D Library file
#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "D3DCompiler.lib")

#include "ApplicationSettings.h"
#include "CLog.h"
#include "..\\RenderObjects.h"

#include <vector>

namespace Engine
{
    class CRenderer
    {
        struct S_VSConstantBuffer
        {
            DirectX::XMMATRIX World;
            DirectX::XMMATRIX View;
            DirectX::XMMATRIX Projection;
        };
        
        struct S_PSConstantBuffer
        {
            DirectX::XMVECTOR ViewDirection;
            DirectX::XMVECTOR PointLightPosition;
            DirectX::XMVECTOR AmbientLight;
            DirectX::XMVECTOR LightColor;
            float  PointLightRange;
        };

#pragma region Variables
    private:

        ID3D11Device* m_pDevice = nullptr;
        IDXGISwapChain* m_pSwapChain = nullptr;
        ID3D11DeviceContext* m_pContext = nullptr;
        ID3D11RenderTargetView* m_pBackBufferView = nullptr;
        ID3D11DepthStencilView* m_pDepthStencilBuffer = nullptr;

        ID3D11Buffer *m_pVertexBuffer = nullptr;
        ID3D11Buffer* m_pVSConstantBuffer = nullptr;
        ID3D11Buffer* m_pPSConstantBuffer = nullptr;

        D3D11_MAPPED_SUBRESOURCE m_MappedSubResource;
        
        SIZE m_Resolution;
        float m_BackgroundColor[4] = { 0 };

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the renderer
        */
        CRenderer();

       /*!
        *@brief Destructor for the renderer
        */
        ~CRenderer();

       /*!
        *@brief Initializes the renderer
        *
        *@param Settings::ApplicationSettings a_settings - Application settings for initializing the renderer 
        *
        *@returns Returns true if succeed and false if an error occures
        */
        bool Initialize(Settings::ApplicationSettings* a_settings);

       /*!
        *@brief Begin rendering the frame
        *
        *@param unsigned int a_clearColor - Clear color for the background
        *@param Engine::CCamera* a_camera - Pointer to the camera with view and projection matrix
        */
        void Begin(unsigned int a_clearColor, Engine::CCamera * a_camera);

       /*!
        *@brief Begin rendering the frame
        *
        *@param unsigned int a_clearColor - Clear color for the background
        *@param DirectX::XMMATRIX* a_view - View matrix of the camera
        *@param DirectX::XMMATRIX* a_projection - Projection matrix of the camera
        */
        void Begin(unsigned int a_clearColor, DirectX::XMMATRIX* a_view, DirectX::XMVECTOR* a_lookDirection,  DirectX::XMMATRIX* a_projection);
        
       /*!
        *@brief Ends rendering the frame and displays it
        */
        void End();

       /*!
        *@brief Draw vertices to the backbuffer
        *
        *@param std::vector<Vertex>* a_vertices - Pointer to the vertices to draw
        *@param DirectX::XMMATRIX* a_world - Pointer to the world matrix of the object
        *@param RenderTopology a_renderTopology - Topology how to handle the vertices (optional)
        */
        void Draw(std::vector<Vertex>* a_vertices, DirectX::XMMATRIX* a_world, RenderTopology a_renderTopology = RenderTopology::TriangleStrip);

       /*!
        *@brief Draw a shape to the backbuffer
        *
        *@param IShape* a_shape - Pointer to the shape to draw
        */
        void Draw(IShape* a_shape);

       /*!
        *@brief Sets the light to the scene to render
        *
        *@param CLight* a_light - Pointer to the light
        */
        void SetLight(CLight* a_light);

       /*!
        *@brief Gets the Resolution of the window
        *
        *@returns Returns the Resolution as SIZE
        */
        SIZE GetResolution();

    private:

        bool InitializeDirectX(Settings::ApplicationSettings* a_settings);
        bool InitializeShader();

#pragma endregion
    };
}