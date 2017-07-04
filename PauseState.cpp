
#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    InputManager::SharedManager()->isStatePlay = false;
    InputManager::SharedManager()->update();
    
    if ((InputManager::SharedManager()->isKeyDown(SDL_SCANCODE_ESCAPE)) && ( InputManager::SharedManager()->isPauseKeyUnlkd) )
    
        Game::Instance()->m_pGameStateMachine->popState();
}

void PauseState::render()
{
    SDL_RenderClear(m_pRenderer);
    
    HudDisplay::sharedDisplay()->drawHud();
    
    TextureManager::Instance()->renderLabel("PAUSED!", MAP_SIZE_WIDTH / 2.3, WINDOW_HEIGHT/5.0);
    TextureManager::Instance()->renderLabel("PRESS ESC", MAP_SIZE_WIDTH / 2.9, WINDOW_HEIGHT/3.3);
    
    TextureManager::Instance()->renderLabel("TO RESUME", MAP_SIZE_WIDTH / 2.9, WINDOW_HEIGHT/2.5);
    
    SDL_RenderPresent(m_pRenderer);
}

bool PauseState::onEnter()
{
    std::cout << "entering PauseState\n";
    
     m_pRenderer = Game::Instance()->getRenderer();

     InputManager::SharedManager()->isPauseKeyUnlkd = false;
    
     Mix_HaltMusic();
     return true;
}

bool PauseState::onExit()
{
    std::cout << "exiting PauseState\n";
    
     InputManager::SharedManager()->isPauseKeyUnlkd = false;
    
    SoundManager::Instance()->playMusic("bg", -1);
    
     return true;
}