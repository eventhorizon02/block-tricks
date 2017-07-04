
#include "GameOverState.h"

const std::string GameOverState::s_gameOverID = "OVER";

void GameOverState::update()
{
   
   endTime = SDL_GetTicks();
    
    if ((endTime - startTime >= 75) && !isFull)
        this->fillMap();
    if ((endTime - startTime >= 75) && !seqComplete)
        this->clearMap();
    
    if (seqComplete)
    {
        if (InputManager::SharedManager()->isKeyDown(SDL_SCANCODE_RETURN))
            Game::Instance()->m_pGameStateMachine->changeState(new PlayState);
            
    }
}

void GameOverState::render()
{
    
    SDL_RenderClear(m_pRenderer);
    HudDisplay::sharedDisplay()->drawHud();
    BrickMap::SharedMap()->draw();
    
    if (seqComplete)
    {
        TextureManager::Instance()->renderLabel("GAME OVER!", MAP_SIZE_WIDTH / 3.3, WINDOW_HEIGHT/5.0);
        TextureManager::Instance()->renderLabel("PRESS", MAP_SIZE_WIDTH / 2.0, WINDOW_HEIGHT/3.3);
        TextureManager::Instance()->renderLabel("ENTER", MAP_SIZE_WIDTH / 2.0, WINDOW_HEIGHT/2.85);
        
        TextureManager::Instance()->renderLabel("TO PLAY", MAP_SIZE_WIDTH / 2.4, WINDOW_HEIGHT/2.5);
        TextureManager::Instance()->renderLabel("AGAIN", MAP_SIZE_WIDTH / 2.0, WINDOW_HEIGHT/2.2);
        
    }
    
    SDL_RenderPresent(m_pRenderer);
}

bool GameOverState::onEnter()
{
    std::cout << "entering GameOverState\n";
   
    m_pRenderer = Game::Instance()->getRenderer();
    
    startTime = SDL_GetTicks();
    fillRow = 0;
    isFull = false;
    seqComplete = false;
    
    return true;
}

bool GameOverState::onExit()
{
    std::cout << "exiting GameOverState\n";
    Game::Instance()->rowsCleared = 0;
    BrickMap::SharedMap()->init();
    return true;
}

void GameOverState::fillMap()
{
    BrickMap::SharedMap()->setRow(fillRow);
    SoundManager::Instance()->playSound("move", 0);
    fillRow++;
    startTime = SDL_GetTicks();
    if (fillRow >= MAP_HEIGHT)
        isFull = true;
}

void GameOverState::clearMap()
{
    BrickMap::SharedMap()->clearRow(fillRow);
    SoundManager::Instance()->playSound("move", 0);
    startTime = SDL_GetTicks();
    if (fillRow == 0)
        seqComplete = true;
    fillRow--;
}












