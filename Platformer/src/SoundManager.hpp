#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_DEBUG.hpp"
#include <map>
#include <string>
#include <vector>
#include <ResourceManager.hpp>

using namespace std;

/**
 * @brief Class SoundManager
 *
 * Private members:
 * Default Constructors and Deconstructors
 * Copy and Move functions to be avoided
 *
 * Public members:
 *
 *
 
 *
 */
class SoundManager
{
private:
    SoundManager() = default; // Private Singleton
    ~SoundManager() = default;
    SoundManager(SoundManager const &) = delete;   // Avoid copy constructor.
    void operator=(SoundManager const &) = delete; // Don't allow copy assignment.
    SoundManager(SoundManager &&) = delete;        // Avoid move constructor.
    void operator=(SoundManager &&) = delete;      // Don't allow move assignment.

    Mix_Chunk* playerJumpSFX;
    Mix_Chunk* crunchSFX;
    Mix_Music* music;

    std::map<int, std::string> sfx;

public:


    // returns a BlockManager
    static SoundManager &getInstance();

    // 'equivalent' to our constructor
    // do anything needed to initialize
    void startUp();

    // 'equivalent' to our destructor
    // make sure that any allocated resources are freed
    void shutDown();

    // resets the sound
    void reset();

    // plays a one time non-looping .wav file
    // takes in an int to represent the index of the effect in the stored sfx
    void playSoundEffect(int i);

};

#endif
