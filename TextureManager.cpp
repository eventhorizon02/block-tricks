#include "TextureManager.h"



TextureManager *TextureManager::s_pInstance = NULL;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    TTF_Init(); // SDL2_TTF needs to be initialized
    
    font = TTF_OpenFont( "Commodore Pixelized v1.2.ttf", 25 ); // Load our fonts and font size
    
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    
    if(pTempSurface == NULL)
    {
		std::cout << IMG_GetError();
        return false;
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    SDL_FreeSurface(pTempSurface);
    
    if(pTexture)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::renderLabel( std::string textureText, float x, float y)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    SDL_Renderer *t_renderer = Game::Instance()->getRenderer();
    
    SDL_Texture *t_texture;
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(),{76,76,76,255});
    
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
    t_texture = SDL_CreateTextureFromSurface(t_renderer,textSurface );
        
        
        if( t_texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get text image dimensions
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = destRect.w = textSurface->w;
            srcRect.h = destRect.h = textSurface->h;
            destRect.x = x;
            destRect.y = y;
        }
        
        //destroy old surface
        SDL_FreeSurface( textSurface );
        
    }
    
    SDL_RenderCopy(t_renderer, t_texture, &srcRect, &destRect);
    
    // destroy old texture
    SDL_DestroyTexture (t_texture);
    
}






















