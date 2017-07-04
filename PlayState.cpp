

#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    InputManager::SharedManager()->isStatePlay = true;
    
    SoundManager::Instance()->update(); // allows the cycling of sound on and off by pressing the s key
    
    if ((InputManager::SharedManager()->isKeyDown(SDL_SCANCODE_ESCAPE)) &&( InputManager::SharedManager()->isPauseKeyUnlkd))
    Game::Instance()->m_pGameStateMachine->pushState(new PauseState);
    
    if (BrickMap::SharedMap()->isGameOver())
       Game::Instance()->m_pGameStateMachine->changeState(new GameOverState);
        
    if (!BrickMap::SharedMap()->needsFlashing)
        InputManager::SharedManager()->update();
    
       BrickMap::SharedMap()->update();
}

void PlayState::render()
{
    if (!BrickMap::SharedMap()->needsFlashing)
    {
        SDL_RenderClear(m_pRenderer);
        HudDisplay::sharedDisplay()->drawHud();
        BrickMap::SharedMap()->draw();
        
        SDL_RenderPresent(m_pRenderer);
    }
    else
        this->flashCompleted();
}

bool PlayState::onEnter()
{
    
    m_pRenderer = Game::Instance()->getRenderer();
    BrickMap::SharedMap()->init();  // initialize the tile map
    
    SoundManager::Instance()->playMusic("bg", -1);
    std::cout << "entering PlayState\n";
    
    return true;
}

bool PlayState::onExit()
{
    std::cout << "exiting PlayState\n";
    Mix_HaltMusic();
    return true;
}



// flash the completed rows before removing them

void PlayState::flashCompleted()
{
    SoundManager::Instance()->playSound("clear", 0);
    
    for (int i = 0; i <= 4; i++)
    {
        SDL_RenderClear(m_pRenderer);
        
        
        HudDisplay::sharedDisplay()->drawHud();
        
        if (i % 2 == 0)
        BrickMap::SharedMap()->drawWithout();
        
        else
        BrickMap::SharedMap()->drawWith();
        
        SDL_RenderPresent(m_pRenderer);
        SDL_Delay(200);
        
    }

    BrickMap::SharedMap()->needsFlashing = false;
    SoundManager::Instance()->playSound("crash", 0); // play crashing sound after whole map drops
}


























