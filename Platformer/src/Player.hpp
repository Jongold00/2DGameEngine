#ifndef PLAYER
#define PLAYER

#include "ResourceManager.hpp"
#include "Hitbox.hpp"
#include "LevelLoader.hpp"
#include "SoundManager.hpp"
#include "base/GameObject.hpp"
#include "base/SpriteRenderComponent.hpp"
#include <algorithm>
#include "base/InputManager.hpp"


/**
 * 
 * @brief Player class
 * 
 */
class Player : public GameObject
{
private:
    float currentJumpForce;
    float gravityValue;


public:

    // current positions
    float x;
    float y;

    // textures for all states of player movement

    SDL_Texture *run_tex;
    SDL_Texture *idle_tex;
    SDL_Texture *fall_tex;
    SDL_Texture *jump_tex;
    SDL_Texture *current_tex;

    // use to change between sprites

    float xVel;
    float yVel;

    // constants for controlling movement

    float speed;
    float jumpHeight;
    int width;

    bool isGrounded;
    bool lookRight;

    // default constructor
   // Player() = default;
    Player(int x, int y, int w, int h);
    // default deconstructor
    ~Player() = default;

    SDL_Rect Src;
    SDL_Rect Dst;

  

    // constructor that sets texture and position of Player
    void init();

    // returns instance of the player
    //Player &getInstance();
    
    // render player function
    void render(SDL_Renderer *ren);

    // resets position of player
    void reset();

    // movement of the player function 
    void movePlayer(float moveX, float moveY); // called by processInput and processForces

    void processInput(bool moveLeft, bool moveRight, bool moveJump, float screenWidth); // does all input processing, only called from SDLGraphicsProgram

    void jump(); // updates the currentJumpForce

    void processForces(); // called every frame to update based on current forces

    void adjustSRC(int x, int y); // swaps sprites

    void update(Level & level) override; //!< Update the object.

    void death(Level & level, std::shared_ptr<GameObject> obj) override; //removes player when colliding with enemy

};

#endif