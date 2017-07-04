
#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <string>
#include <map>
//#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Game.h"

class TextureManager
{
public:
    
    static TextureManager* Instance()
    {
        if(s_pInstance == nullptr)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
       
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
   
    std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }
    
     void renderLabel( std::string textureText, float x, float y); // draw text to the screen at assigned position
    
private:
    
    TextureManager() {}
    ~TextureManager() {}
    
    
    TTF_Font* font;
    TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);
    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_pInstance;
};


#endif /* defined(__TextureManager__) */
