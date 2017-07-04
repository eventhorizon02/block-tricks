

#include "IntroState.h"

const std::string IntroState::s_introID = "INTRO";

void IntroState::update()
{
    InputManager::SharedManager()->update();
    if (InputManager::SharedManager()->isKeyDown(SDL_SCANCODE_RETURN))
        
        Game::Instance()->m_pGameStateMachine->changeState(new PlayState);
}

void IntroState::render()
{
    SDL_RenderClear(m_pRenderer);
    
    
    TextureManager::Instance()->renderLabel("WELCOME TO BLOCK TRICKS!", 10, 50);
    TextureManager::Instance()->renderLabel("GAME CONTROLS:", 120, 80);
    TextureManager::Instance()->renderLabel("LT ARW-MOVE BLOCK LEFT", 30, 130);
    TextureManager::Instance()->renderLabel("RT ARW-MOVE BLOCK RIGHT", 20, 160);
    TextureManager::Instance()->renderLabel("DN ARW-DROP BLOCK", 80, 190);
    TextureManager::Instance()->renderLabel("Z-ROTATE LEFT", 120, 220);
    TextureManager::Instance()->renderLabel("X-ROTATE RIGHT", 110, 250);
    TextureManager::Instance()->renderLabel("ESC-PAUSE GAME", 110, 300);
    TextureManager::Instance()->renderLabel("S-SOUND ON/OFF", 110, 330);
    
    TextureManager::Instance()->renderLabel("PRESS ENTER TO PLAY", MAP_SIZE_WIDTH / 4.5, WINDOW_HEIGHT/1.3);
    
    SDL_RenderPresent(m_pRenderer);
    
}

bool IntroState::onEnter()
{
    std::cout << "entering IntroState\n";
    
    m_pRenderer = Game::Instance()->getRenderer();
    
    return true;
}

bool IntroState::onExit()
{
    std::cout << "exiting IntroState\n";
    return true;
}