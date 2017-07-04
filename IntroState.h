
#ifndef __IntroState__
#define __IntroState__

#include "GameState.h"
#include "PlayState.h"
#include <iostream>


class IntroState : public GameState
{
    
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const {return s_introID;}
    
private:
    static const std::string s_introID;
    SDL_Renderer *m_pRenderer;
    
};

#endif /* defined(__IntroState__) */
