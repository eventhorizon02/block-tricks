

#ifndef __InputManager__
#define __InputManager__

#include <SDL2/SDL.h>
#include "defs.h" 
#include "BrickMap.h"



class InputManager
{
public:
    static InputManager *SharedManager()
    {
        if (t_iShared == NULL)
            t_iShared = new InputManager;
        
        return t_iShared;
    }
    
    void update();
    void clean();
    
    
    void handleMovement();
    
    void handleKeys();
    
    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;
    
    bool isPauseKeyUnlkd;
    
    bool isStatePlay; // are we in the play state
    
private:
    InputManager(){};
    ~InputManager(){};
    
    static InputManager *t_iShared;
    const Uint8 *m_keystate;
    bool isRotationUnlocked; // no continues rotation key holding
    void isRotationKeyReleased();
    
   
    void isPausingUnlocked();
};





#endif /* defined(__InputManager__) */
