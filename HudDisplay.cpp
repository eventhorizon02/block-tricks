

#include "HudDisplay.h"

HudDisplay *HudDisplay::s_pInstance = nullptr;

HudDisplay::HudDisplay()
{
    mapRenderer = Game::Instance()->getRenderer();
    
    // create 16 positions inside an array to hold the spots to draw the next block
    
    SDL_Point initialPoint = {MAP_SIZE_WIDTH + (WINDOW_WIDTH - MAP_SIZE_WIDTH)/3 , WINDOW_HEIGHT/2};
    
    int index = 0;
    
    for (int row = 0; row <= 3; row++)
    {
        for (int col = 0; col <= 3; col++)
        {
            blockDisplays[index] = { initialPoint.x + col * TILE_WIDTH , initialPoint.y - row * TILE_HEIGHT };
            index++;
        }
    }
}


void HudDisplay::drawHud()
{
    TextureManager::Instance()->draw("backround", MAP_OFFSET, 0, TILE_WIDTH * MAP_WIDTH, WINDOW_HEIGHT, mapRenderer);
    
    int lines = Game::Instance()->rowsCleared;
    std::string s = std::to_string(lines);
    
    short blockImage = BrickMap::SharedMap()->returnNextblockImage(); // get an image of the next block coded inside a short
    
    // retreive the image and plot at predetermined coordinates
    for ( int index = 0; index <= 15; index++)
    {
        int x = pow(2, index);
        if (blockImage & x)
            PLOT_AT_COORD(blockDisplays[index].x, blockDisplays[index].y);
    }
    
    // draw text labels
    
     TextureManager::Instance()->renderLabel("NEXT", MAP_SIZE_WIDTH + (WINDOW_WIDTH - MAP_SIZE_WIDTH)/2.7, WINDOW_HEIGHT/3.5);
     TextureManager::Instance()->renderLabel("LINES", MAP_SIZE_WIDTH + (WINDOW_WIDTH - MAP_SIZE_WIDTH)/2.7, WINDOW_HEIGHT/1.5);
     TextureManager::Instance()->renderLabel(s, MAP_SIZE_WIDTH + (WINDOW_WIDTH - MAP_SIZE_WIDTH)/1.9, WINDOW_HEIGHT/1.4);
    
}