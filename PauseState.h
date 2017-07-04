
#ifndef __PauseState__
#define __PauseState__

#include "GameState.h"
#include <iostream>
#include "PauseState.h"
#include "InputManager.h"


class PauseState : public GameState
{
    
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const {return s_pauseID;}
    
private:
    static const std::string s_pauseID;
     SDL_Renderer *m_pRenderer;
    
};

#endif /* defined(__PauseState__) */
