
#include "Game.h"

#include <iostream>

using namespace std;

Game* Game::s_pInstance = NULL;


Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false)

{
    }

Game::~Game()
{
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer = NULL;
    m_pWindow = NULL;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    
    int flags = 0;
    
    if(fullscreen)
    flags = SDL_WINDOW_FULLSCREEN;
    
    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if(m_pWindow != 0) // window init success
        {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
            
            if(m_pRenderer != 0) // renderer init success
            
                SDL_SetRenderDrawColor(m_pRenderer, 211,211,211,255);
            else return false; // renderer init fail
        }
        else return false; // window init fail
        
    }
    else return false; // SDL init fail
    
    TextureManager::Instance()->load("backround.png", "backround",m_pRenderer);
    SoundManager::Instance()->initAll();
    
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new IntroState());
    currentState = m_pGameStateMachine->returnCurrentState(); // get the current state the game is in
    
    rowsCleared = 0;
    
    m_bRunning = true; // everything inited successfully, start the main loop
    
    return true;
}



void Game::render()
{
   m_pGameStateMachine->render();
    
}

void Game::update()
{
    m_pGameStateMachine->update();
    currentState = m_pGameStateMachine->returnCurrentState(); // get the current state the game is in
    
    if (rowsCleared >=9999)// limit the score to avoid text going off screen
        rowsCleared = 9999;
    
}

void Game::handleEvents()
{
    
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            m_bRunning = false;
    }

}

void Game::clean()
{
    cout << "cleaning game\n";
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

// return the delay time between block drops

Uint32 Game::returnDelayTime()
{
    Uint32 delayTime = 800 - rowsCleared * 10;
    
    if (delayTime <= 50)
        delayTime = 50;
    
    return delayTime;
}


// callback function

void Game::keyBoardCallback()
{
    if (!BrickMap::SharedMap()->needsFlashing)
    InputManager::SharedManager()->handleMovement();
}





















