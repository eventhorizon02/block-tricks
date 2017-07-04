
#ifndef __BrickMap__
#define __BrickMap__

#include <SDL2_image/SDL_image.h>
#include "TextureManager.h"
#include "inputManager.h"
#include "Game.h"
#include "defs.h"
#include "Block.h"

class BrickMap
{
public:
    static BrickMap *SharedMap()
    {
        if (t_iShared == nullptr)
            t_iShared = new BrickMap;
        
        return t_iShared;
    }
    
    bool needsFlashing; // we need to flash completed rows
    bool isGameOver(); // check if we've reached the top row
    void init();
    void draw();
    void update();
    void hadleRotationKeys();
    void decreaseY();
    void drawWithout (); // draw the map with completed lines missing for the purpose of flashing
    void drawWith();
    bool isLatMoveLegal(int dir);
    bool isClearBellow();
    bool isClearToRotate(int dir);
    void blockLanded();
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateLeft();
    void rotateRight();
    short returnNextblockImage(); // returns an image of the next block when hud requests it.
    void clearRow(int rowNum);
    void setRow(int rowNum); // sets a row to full (to be used with game over animation sequence)
        
private:
    
    BrickMap(){};
    ~BrickMap(){};
    inline SDL_Point mapToScreen(int x, int y); //convert map to screen coordinates
    void retreiveBlock();
    
    void destroyCompletes(); // search map for complete lines and delete them
    void applyGravity(int rowNum); // drop lines above an empty row
    void drawBlock();
    void addBlockToMap();
    void setAllCompletes(); // create an array with all the completed lines
    
    static BrickMap *t_iShared;
    SDL_Renderer *mapRenderer;
    char mapArray[MAP_WIDTH][25];
    char cpyArray[MAP_WIDTH][25]; // copy of map array, to be used for flashing
    char sansArray[MAP_WIDTH][25];
    SDL_Point piecePosArray[4];  // hold positions of lit up squares of block
    Block *p_block;
    Block *p_nextBlock;
    
    int blockPosX;
    int blockPosY;
    Uint32 startTime, endTime; // time the blocks drop rate
    
};

#endif /* defined(__BrickMap__) */









