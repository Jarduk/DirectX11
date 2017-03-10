#pragma once

class IScene
{
public:

    IScene() {}
    ~IScene() {}

   /*!
    *@brief Resets the scene to its starting values
    */
    virtual void Initialize() = 0;

   /*!
    *@brief Calls the update function of the scene
    *
    *@param double a_deltaTime - the time difference between the last update calls in seconds
    */
    virtual void Update(double a_deltaTime) = 0;

   /*!
    *@brief Calls the render function of the scene
    */
    virtual void Render() = 0;

private:

};