#ifndef HITBOX
#define HITBOX

#include "ResourceManager.hpp"



class Hitbox
{
private:
public:
    float length;
    float width;
    float posX;
    float posY;

     // default constructor
    Hitbox() = default;
    // default deconstructor
    ~Hitbox() = default;

    // custom constructor for inputs
    Hitbox(float l, float w, float x, float y);

    // returns true is this hitbox overlaps with "hit"
    bool checkCollision(Hitbox* hit); 

    // updates the position of a hitbox
    void updatePosition(float x, float y);

};

#endif