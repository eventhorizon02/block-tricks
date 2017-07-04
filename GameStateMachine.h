
#ifndef __GameStateMachine__
#define __GameStateMachine__


#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    
    void pushState(GameState *pState);
    void changeState(GameState *pState);
    void popState();
    
    void update();
    void render();
    std::string returnCurrentState();
    
private:
    std::vector<GameState*> m_gameStates;
};

#endif /* defined(__Block_Tricks__GameStateMachine__) */
