#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "base/SDLGraphicsProgram.hpp"



class Camera : public GameObject 
{
    private:

        
    public:

        Camera(int x, int y, int w, int h, shared_ptr<GameObject> player);
        ~Camera() = default;

        static const int CAMERA_TAG = 1000;

};

#endif