#pragma once

#include "IShape.h"

namespace Engine
{
    class CCube : public IShape
    {
#pragma region Variables
    private:

#pragma endregion
#pragma region Methods
    public:

       /*!
        *@brief Constructor for the cube
        */
        CCube();
        
       /*!
        *@brief Destructor for the cube
        */
        ~CCube();

    private:

        void Initialize();

#pragma endregion
    };
}