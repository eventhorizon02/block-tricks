#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include "defs.h"


// callback functions

Uint32 keysTimerCallback(Uint32 interval, void *param);


SDL_TimerID my_keyes_id = SDL_AddTimer(75, keysTimerCallback, NULL);



int main(int argc, const char * argv[])
{
    Uint32 frameStart, frameTime;
    Game::Instance()->init("Block Tricks", 299, 290, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    while (Game::Instance()->running())
    {
        frameStart = SDL_GetTicks();
        
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();
        
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
        
    }
    
    Game::Instance()->clean();
    Game::Instance()->quit();
    
    return 0;
}

// callbacks


Uint32 keysTimerCallback(Uint32 interval, void *param)
{
    if (Game::Instance())
    {
        Game::Instance()->keyBoardCallback();
    }
    return interval;
}

