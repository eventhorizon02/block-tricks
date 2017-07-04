

#ifndef __GameOverState__
#define __GameOverState__

#include "GameState.h"
#include <iostream>
#include "BrickMap.h"
#include "PlayState.h"


class GameOverState : public GameState
{
    
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const {return s_gameOverID;}
    
private:
    static const std::string s_gameOverID;
    SDL_Renderer *m_pRenderer;
    Uint32 startTime, endTime; // timing for the sequence of filling up the well
    void fillMap();
    void clearMap();
    int fillRow;
    bool isFull;
    bool seqComplete;
    
};

#endif /* defined(__GameOverState__) */
