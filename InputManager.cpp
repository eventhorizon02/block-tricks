
#include "InputManager.h"




InputManager *InputManager::t_iShared = NULL;


void InputManager::update()
{
    m_keystate = SDL_GetKeyboardState(0);
    this->isRotationKeyReleased();
    this->handleKeys();
    this->isPausingUnlocked();
}

bool InputManager::isKeyDown(SDL_Scancode key) const
{
    if (m_keystate != 0)
    {
      if (m_keystate[key])
      return true;
      
    }
    return false;
}


void InputManager::handleMovement()
{
    if (!isStatePlay) return; // do not let block move unless if we are in the play state
    
    if (isKeyDown(SDL_SCANCODE_DOWN)&& isRotationUnlocked)
    {
        if (!theMap->isClearBellow())
        {
            theMap->blockLanded();
            return;
        }
        theMap->moveDown();
    }
}


void InputManager:: handleKeys()
{
    if (!isStatePlay) return; // do not let block move unless if we are in the play state
    
    if (isKeyDown(SDL_SCANCODE_X) && isRotationUnlocked)
    {
        isRotationUnlocked = false;
        if (theMap->isClearToRotate(RIGHT))
            theMap->rotateRight();
            
        
    }else if (isKeyDown(SDL_SCANCODE_Z) && isRotationUnlocked)
    {
        isRotationUnlocked = false;
        if (theMap->isClearToRotate(LEFT))
            theMap->rotateLeft();
    }
    
    // just for now, will find better place for it
  else if (isKeyDown(SDL_SCANCODE_S)&& isRotationUnlocked)// toggle sound on and off
  {     isRotationUnlocked = false;
        SoundManager::Instance()->soundOn = !SoundManager::Instance()->soundOn;
      
  }else if (isKeyDown(SDL_SCANCODE_LEFT)&& isRotationUnlocked)
  {
      isRotationUnlocked = false;
      if (theMap->isLatMoveLegal(LEFT))
          theMap->moveLeft();
      
  }if (isKeyDown(SDL_SCANCODE_RIGHT)&& isRotationUnlocked)
  {
      isRotationUnlocked = false;
      if (theMap->isLatMoveLegal(RIGHT))
          theMap->moveRight();
  }

    
}



// if rotation keys are realeased unlock the bool flag

void InputManager::isRotationKeyReleased()
{
    if (!(m_keystate [SDL_SCANCODE_X]) && !( m_keystate [SDL_SCANCODE_Z]) && !( m_keystate [SDL_SCANCODE_S])&& !( m_keystate [SDL_SCANCODE_LEFT])&& !( m_keystate [SDL_SCANCODE_RIGHT]))
    
        isRotationUnlocked = true;
}

void InputManager::isPausingUnlocked()
{
    if (!(m_keystate [SDL_SCANCODE_ESCAPE]))
        {
            isPauseKeyUnlkd = true;
        }
}


void InputManager::clean()
{
    
}























