#include "CRenderer.h"

Engine::CRenderer::CRenderer()
{

}

Engine::CRenderer::~CRenderer()
{

}

bool Engine::CRenderer::Initialize(Settings::ApplicationSettings* a_settings)
{
    // get the resolution in pixel
    switch (a_settings->resolution)
    {
    case Settings::EngineResolution::SVGA:
        m_Resolution.cx = 800;
        m_Resolution.cy = 600;
        break;
    case Settings::EngineResolution::HD:
        m_Resolution.cx = 1280;
        m_Resolution.cy = 720;
        break;
    case Settings::EngineResolution::FullHD:
        m_Resolution.cx = 1920;
        m_Resolution.cy = 1080;
        break;
    }

    if (!InitializeDirectX(a_settings)) return false;

    if (!InitializeShader()) return false;

    return true;
}

bool Engine::CRenderer::InitializeDirectX(Settings::ApplicationSettings* a_settings)
{
    // get pointer to log
    CLog* pLog = CLog::Instance();
    
    // create the device and swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = a_settings->hwnd;
    swapChainDesc.Windowed = a_settings->windowed;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Width = m_Resolution.cx;
    swapChainDesc.BufferDesc.Height = m_Resolution.cy;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
        NULL, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pContext)))
    {
        // print error message to logfile
        pLog->Write(2, 8);
        return false;
    }

    // create the rendertargetview
    ID3D11Texture2D* backBuffer = nullptr;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

    if (FAILED(m_pDevice->CreateRenderTargetView(backBuffer, NULL, &m_pBackBufferView)))
    {
        // print error message to logfile
        pLog->Write(2, 9);
        return false;
    }

    backBuffer->Release();
    backBuffer = nullptr;

    // create depth stencil buffer and view
    D3D11_TEXTURE2D_DESC depthBufferDescription = { 0 };
    depthBufferDescription.Width = m_Resolution.cx;
    depthBufferDescription.Height = m_Resolution.cy;
    depthBufferDescription.MipLevels = 1;
    depthBufferDescription.ArraySize = 1;
    depthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDescription.SampleDesc.Count = 1;
    depthBufferDescription.SampleDesc.Quality = 0;
    depthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDescription.CPUAccessFlags = 0;
    depthBufferDescription.MiscFlags = 0;

    ID3D11Texture2D* depthStencilBuffer = nullptr;
    m_pDevice->CreateTexture2D(&depthBufferDescription, NULL, &depthStencilBuffer);

    if (FAILED(m_pDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &m_pDepthStencilBuffer)))
    {
        // print error message to logfile
        pLog->Write(2, 10);
        return false;
    };

    depthStencilBuffer->Release();
    depthStencilBuffer = nullptr;

    // set rendertarget and depth stencil buffer
    m_pContext->OMSetRenderTargets(1, &m_pBackBufferView, m_pDepthStencilBuffer);

    // create and set viewport
    D3D11_VIEWPORT viewPort;

    viewPort.Width = (float)m_Resolution.cx;
    viewPort.Height = (float)m_Resolution.cy;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    m_pContext->RSSetViewports(1, &viewPort);

    return true;
}

bool Engine::CRenderer::InitializeShader()
{
    // get pointer to log
    CLog* pLog = CLog::Instance();

    // load and compile the two shaders
    ID3DBlob *VS, *PS;

    std::string shaderPath = CLog::Instance()->GetModulPath();
    shaderPath += "\\data\\Shader\\shader.shader";

    if (FAILED(D3DCompileFromFile(std::wstring(shaderPath.begin(), shaderPath.end()).c_str(), 0, 0, "VS_Main", "vs_5_0", 0, 0, &VS, 0)))
    {
        // print error message to logfile
        pLog->Write(2, 3);
        return false;
    }
    if (FAILED(D3DCompileFromFile(std::wstring(shaderPath.begin(), shaderPath.end()).c_str(), 0, 0, "PS_Main", "ps_5_0", 0, 0, &PS, 0)))
    {
        // print error message to logfile
        pLog->Write(2, 4);
        return false;
    }

    // encapsulate both shaders into shader objects
    ID3D11VertexShader *m_pVS = nullptr;
    ID3D11PixelShader *m_pPS = nullptr;

    m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS);
    m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS);

    // set the shader objects
    m_pContext->VSSetShader(m_pVS, NULL, 0);
    m_pContext->PSSetShader(m_pPS, NULL, 0);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC VSied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    ID3D11InputLayout *m_pVSLayout = nullptr;

    m_pDevice->CreateInputLayout(VSied, ARRAYSIZE(VSied), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pVSLayout);
    m_pContext->IASetInputLayout(m_pVSLayout);

    // create a vertex buffer
    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(BufferDesc));

    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.ByteWidth = sizeof(Vertex) * 100;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, NULL, &m_pVertexBuffer)))
    {
        // print error message to logfile
        pLog->Write(2, 5);
        return false;
    }

    UINT m_Stride = sizeof(Vertex);
    UINT m_Offset = 0;

    m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_Stride, &m_Offset);

    // fill in a constant buffer description for the vertex shader.
    D3D11_BUFFER_DESC VSBufferDesc;
    VSBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    VSBufferDesc.ByteWidth = sizeof(S_VSConstantBuffer);
    VSBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    VSBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    VSBufferDesc.MiscFlags = 0;
    VSBufferDesc.StructureByteStride = 0;

    // create the constant buffer.
    if (FAILED(m_pDevice->CreateBuffer(&VSBufferDesc, 0, &m_pVSConstantBuffer)))
    {
        // print error message to logfile
        pLog->Write(2, 6);
        return false;
    }

    // set constant buffer
    m_pContext->VSSetConstantBuffers(0, 1, &m_pVSConstantBuffer);

    // fill in a constant buffer description for the pixel shader.
    D3D11_BUFFER_DESC PSBufferDesc;
    PSBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    PSBufferDesc.ByteWidth = sizeof(S_PSConstantBuffer);
    PSBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    PSBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    PSBufferDesc.MiscFlags = 0;
    PSBufferDesc.StructureByteStride = 0;

    // create the constant buffer.
    if(FAILED(m_pDevice->CreateBuffer(&PSBufferDesc, 0, &m_pPSConstantBuffer)))
    {
        // print error message to logfile
        pLog->Write(2, 7);
        return false;
    }

    // set constant buffer
    m_pContext->PSSetConstantBuffers(0, 1, &m_pPSConstantBuffer);

    return true;
}

void Engine::CRenderer::Begin(unsigned int a_clearColor, Engine::CCamera* a_camera)
{
    Begin(a_clearColor, &a_camera->GetView(), &a_camera->GetLookDirection(), &a_camera->GetProjection());
}

void Engine::CRenderer::Begin(unsigned int a_clearColor, DirectX::XMMATRIX* a_view, DirectX::XMVECTOR* a_lookDirection, DirectX::XMMATRIX* a_projection)
{
    m_BackgroundColor[0] = 1.0f / 255 * (0xff & (a_clearColor >> 24));
    m_BackgroundColor[1] = 1.0f / 255 * (0xff & (a_clearColor >> 16));
    m_BackgroundColor[2] = 1.0f / 255 * (0xff & (a_clearColor >> 8));
    m_BackgroundColor[3] = 1.0f / 255 * (0xff & a_clearColor);

    // clear backbuffer
    m_pContext->ClearRenderTargetView(m_pBackBufferView, m_BackgroundColor);

    // clear depth stencil buffer
    m_pContext->ClearDepthStencilView(m_pDepthStencilBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // fill the constant buffer for the vertex shader
    m_pContext->Map(m_pVSConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_MappedSubResource);
    S_VSConstantBuffer* VsConstData = (S_VSConstantBuffer*)m_MappedSubResource.pData;

    VsConstData->World = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
    VsConstData->View = DirectX::XMMatrixTranspose(*a_view);
    VsConstData->Projection = DirectX::XMMatrixTranspose(*a_projection);

    m_pContext->Unmap(m_pVSConstantBuffer, 0);

    // fill the constant buffer for the pixel shader
    m_pContext->Map(m_pPSConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_MappedSubResource);
    S_PSConstantBuffer* PsConstData = (S_PSConstantBuffer*)m_MappedSubResource.pData;

    PsConstData->ViewDirection = *a_lookDirection;
    PsConstData->AmbientLight = DirectX::XMVECTOR{ 0, 0, 0, 0 };
    PsConstData->LightColor = DirectX::XMVECTOR{ 0, 0, 0, 0 };
    PsConstData->PointLightPosition = DirectX::XMVECTOR{ 0, 0, 0 };
    PsConstData->PointLightRange = 0.0f;

    m_pContext->Unmap(m_pPSConstantBuffer, 0);
}

void Engine::CRenderer::End()
{
    // present the backbuffer
    m_pSwapChain->Present(0, 0);
}

void Engine::CRenderer::Draw(std::vector<Vertex>* a_vertices, DirectX::XMMATRIX* a_world, RenderTopology a_renderTopology)
{
    // fill the constant buffer for the vertex shader
    m_pContext->Map(m_pVSConstantBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &m_MappedSubResource);
    S_VSConstantBuffer* VsConstData = (S_VSConstantBuffer*)m_MappedSubResource.pData;

    VsConstData->World = DirectX::XMMatrixTranspose(*a_world);

    m_pContext->Unmap(m_pVSConstantBuffer, 0);

    // fill the vertex buffer
    m_pContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_NO_OVERWRITE, NULL, &m_MappedSubResource);
    memcpy(m_MappedSubResource.pData, &a_vertices->front(), sizeof(Vertex) * a_vertices->size());
    m_pContext->Unmap(m_pVertexBuffer, NULL);

    // set rendertopology
    switch (a_renderTopology)
    {
    case RenderTopology::Triangles:
        m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        break;
    case RenderTopology::TriangleStrip:
        m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        break;
    }

    // draw the vertices
    m_pContext->Draw((int)a_vertices->size(), 0);
}

void Engine::CRenderer::Draw(IShape* a_shape)
{
    // fill the constant buffer for the vertex shader
    m_pContext->Map(m_pVSConstantBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &m_MappedSubResource);
    S_VSConstantBuffer* VsConstData = (S_VSConstantBuffer*)m_MappedSubResource.pData;

    VsConstData->World = DirectX::XMMatrixTranspose(a_shape->GetWorld());

    m_pContext->Unmap(m_pVSConstantBuffer, 0);

    // fill the vertex buffer
    m_pContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_NO_OVERWRITE, NULL, &m_MappedSubResource);
    memcpy(m_MappedSubResource.pData, &a_shape->GetVertices().front(), sizeof(Vertex) * a_shape->GetVertices().size());
    m_pContext->Unmap(m_pVertexBuffer, NULL);

    // set rendertopology
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertices
    m_pContext->Draw((int)a_shape->GetVertices().size(), 0);
}

void Engine::CRenderer::SetLight(CLight * a_light)
{
    // fill the constant buffer for the pixel shader
    m_pContext->Map(m_pPSConstantBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &m_MappedSubResource);
    S_PSConstantBuffer* PsConstData = (S_PSConstantBuffer*)m_MappedSubResource.pData;

    PsConstData->AmbientLight = a_light->GetAmbientColor();
    PsConstData->LightColor = a_light->GetLightColor();
    PsConstData->PointLightPosition = a_light->GetLightPosition();
    PsConstData->PointLightRange = a_light->GetLightRange();

    m_pContext->Unmap(m_pPSConstantBuffer, 0);
}

SIZE Engine::CRenderer::GetResolution()
{
    return m_Resolution;
}
