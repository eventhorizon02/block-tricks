

#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "BrickMap.h"
#include "HudDisplay.h"
#include "defs.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "IntroState.h"
#include "SoundManager.h"

class Game
{
public:
    
    static Game* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    
    int rowsCleared;
    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void keyBoardCallback(); // this function gets called on a callback from the timer
    void render();
    void update();
    void handleEvents();
    void clean();
    Uint32 returnDelayTime();
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
   
    bool running() { return m_bRunning; }
    
    void quit() { m_bRunning = false; }
    
    GameStateMachine *m_pGameStateMachine;
    std::string currentState;
    
    private:

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    bool m_bRunning;
    static Game* s_pInstance;
    
    Game();
    ~Game();
    
};

#endif /* defined(__Game__) */
