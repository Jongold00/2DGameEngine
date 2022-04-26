// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#ifndef SDL_GRAPHICS_PROGRAM_HPP
#define SDL_GRAPHICS_PROGRAM_HPP

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
#include <SDL.h>
#include "SDL_DEBUG.hpp"
#include "TinyMath.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "SoundManager.hpp"

/**
 * @file SDLGraphicsProgram.hpp
 * @brief Header for SDLGraphicsProgram class
 */

/**
 * @brief SDLGraphicsProgram class which sets up a full graphics program
 * @class SDLGraphicsProgram
 * 
 */

// This class sets up a full graphics program
class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Desctructor
    ~SDLGraphicsProgram();
    // Per frame update
    void update(bool moveLeft, bool moveRight, bool allDestroyed, bool langCheck);
    // Renders shapes to the screen
    void render();
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Get Pointer to Renderer
    SDL_Renderer* getSDLRenderer();

    int GetScreenHeight();
    int GetScreenWidth();

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // SDL Renderer
    SDL_Renderer* gRenderer = NULL;

    

};

#endif
