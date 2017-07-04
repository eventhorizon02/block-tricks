
#ifndef __GameState__
#define __GameState__

#include <string>

class GameState
{
public:
    
    virtual ~GameState() {}
        
    virtual void update() = 0;
    
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual std::string getStateID() const = 0;
    
};

#endif /* defined(__GameState__) */
