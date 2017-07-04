
#ifndef __PlayState__
#define __PlayState__

#include <iostream>
#include "GameState.h"
#include <SDL2/SDL.h>
#include "InputManager.h"
#include "Game.h"
#include "GameOverState.h"
#include "PauseState.h"

class PlayState : public GameState
{
    
public:
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const {return s_playID;}
    
private:
    static const std::string s_playID;
    void flashCompleted();
    SDL_Renderer *m_pRenderer;
    
};

#endif /* defined(__Block_Tricks__PlayState__) */
