#include "CCube.h"

Engine::CCube::CCube()
{
    Initialize();
}

Engine::CCube::~CCube()
{

}

void Engine::CCube::Initialize()
{
    // Fill vertex data
    m_Vertices.resize(24);

    //                 Position                 Normal                  Color                        // Front Face
    m_Vertices[0]  = { -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f, 1.0f };    // F BL
    m_Vertices[1]  = { -0.5f,  0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f, 1.0f };    // F TL
    m_Vertices[2]  = {  0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f, 1.0f };    // F BR
    m_Vertices[3]  = {  0.5f,  0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f, 1.0f };    // F TR

                                                                                                     // Left Face
    m_Vertices[4]  = { -0.5f, -0.5f,  0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f };    // B BL
    m_Vertices[5]  = { -0.5f,  0.5f,  0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f };    // B TL
    m_Vertices[6]  = { -0.5f, -0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f };    // F BL
    m_Vertices[7]  = { -0.5f,  0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f };    // F TL

                                                                                                     // Back Face
    m_Vertices[8]  = {  0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f };    // B BR
    m_Vertices[9]  = {  0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f };    // B TR
    m_Vertices[10] = { -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f };    // B BL
    m_Vertices[11] = { -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f };    // B TL

                                                                                                     // Right Face
    m_Vertices[12] = { 0.5f, -0.5f, -0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, 1.0f };    // F BR
    m_Vertices[13] = { 0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, 1.0f };    // F TR
    m_Vertices[14] = { 0.5f, -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, 1.0f };    // B BR
    m_Vertices[15] = { 0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, 1.0f };    // B TR

                                                                                                     // Bottom Face  
    m_Vertices[16] = { -0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.0f };    // B BL
    m_Vertices[17] = { -0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.0f };    // F BL
    m_Vertices[18] = {  0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.0f };    // B BR
    m_Vertices[19] = {  0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.0f };    // F BR

                                                                                                     // Top Face
    m_Vertices[20] = { -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f };    // F TL
    m_Vertices[21] = { -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f };    // B TL
    m_Vertices[22] = {  0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f };    // F TR
    m_Vertices[23] = {  0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f };    // B TR
}