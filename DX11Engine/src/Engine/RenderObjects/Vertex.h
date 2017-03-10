#pragma once

namespace Engine
{
   /*!
    *@brief Standard vertex for the renderer
    */
    struct Vertex
    {
        float Position[3];
        float Normal[3];
        float Color[4];
    };

   /*!
    *@brief Topology how to handle the vertices
    */
    enum class RenderTopology : char
    {
        Triangles,
        TriangleStrip
    };
}