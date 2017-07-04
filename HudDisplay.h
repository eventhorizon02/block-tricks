

#ifndef __HudDisplay__
#define __HudDisplay__

#include "BrickMap.h"
#include "TextureManager.h"
#include "defs.h"


class HudDisplay
{
public:
    
    static HudDisplay* sharedDisplay()
    {
        if (s_pInstance == nullptr)
        {
            s_pInstance = new HudDisplay();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    void drawHud();
    
    
private:
    
    HudDisplay();
    ~HudDisplay() {}
    
    static HudDisplay* s_pInstance;
    SDL_Renderer *mapRenderer;
    SDL_Point blockDisplays[16]; // holds 16 positions to plot the next brick on hud
};

#endif /* defined(__HudDisplay__) */
