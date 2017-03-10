#pragma once

namespace Engine
{
    template <typename T>
    class TSingleton
    {
    public:

        TSingleton()
        {

        }

       /*!
        *@brief Creates an instance when first called and returns a pointer to it.
        *
        *@returns Pointer to the instance
        */
        static T* Instance()
        {
            static T instance;
            return &instance;
        }
    };
}