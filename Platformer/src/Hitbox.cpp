#include "Hitbox.hpp"



/**
 * @brief Construct a new Hitbox:: Hitbox object
 * 
 * @param l: type float
 * @param w: type float
 * @param x: type float
 * @param y: type float
 */
Hitbox::Hitbox(float l, float w, float x, float y)
{
    this->length = l;
    this->width = w;
    this->posX = x;
    this->posY = y;
}


// return true on collision
bool Hitbox::checkCollision(Hitbox* hit)
{
 
    //posX, posY, hit->posX, hit->posY

    if (hit->posX < posX + width &&
        hit->posX + hit->width > posX &&
        hit->posY < posY + length &&
        hit->length + hit->posY > posY){

            return true;
        }
        else{
            return false;
        }
}

// changes the position of the hitbox, called to match the position of the player
void Hitbox::updatePosition(float x, float y){

    posX = x;
    posY = y;
}
