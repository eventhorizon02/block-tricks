
#include "BrickMap.h"

BrickMap *BrickMap::t_iShared = nullptr;

void BrickMap::init()
{
    mapRenderer = Game::Instance()->getRenderer();
    TextureManager::Instance()->load("block.png", "block",mapRenderer);
    
    //intialize the tile map array
    memset(mapArray, 0, sizeof(mapArray));
    
    startTime = 0;
    endTime = 0;
    
    memset(sansArray, 0, sizeof(sansArray));// same as map array but will be blanked at the completed rows
    
    //intialize the pieces positions array
    memset(piecePosArray, 0, sizeof(piecePosArray));
    
    blockPosX = INITIAL_X;
    blockPosY = MAP_HEIGHT - 2;
    
    needsFlashing = false;
    p_block = new Block;
    p_nextBlock = new Block;
    
}


void BrickMap::draw()
{
    
    for (int row = 0; row <= 19; row++)
    {
        for (int col = 0; col <= 9; col++)
        {
            if (mapArray[col][row])
            PLOT_AT_MAP_COORD(col, row);
        }
    }
    this->drawBlock();
}

// display block on map but don't add it to the array

void BrickMap::drawBlock()
{
    for (int i = 0; i <= 3; i++)
    PLOT_AT_MAP_COORD(piecePosArray[i].x, piecePosArray[i].y);
}

void BrickMap::addBlockToMap()
{
    for (int i = 0; i <= 3; i++)
    mapArray[piecePosArray[i].x][ piecePosArray[i].y] = 1;
}

void BrickMap::update()
{
    this->retreiveBlock();
    
    endTime = SDL_GetTicks();
    if (endTime - startTime >= Game::Instance()->returnDelayTime())
    this->decreaseY();
}

// convert map coordinates to window coordinates

SDL_Point BrickMap::mapToScreen(int x, int y)
{
  return { x * TILE_WIDTH + MAP_OFFSET, (MAP_HEIGHT -1 - y) * TILE_HEIGHT };
}


// this method converts the brick image which is coded as a number in a 16 bit short into the piece positions array

void BrickMap::retreiveBlock()
{
    short blockImage = p_block->grid[p_block->rndBlock][p_block->numTurns % 4];
    short index = 0;
    int pieceNum = 0;
    for (int row = 0; row <= 3; row++)
    {
        for (int col = 0; col <= 3; col++)
        {
            int x = pow(2, index);
            if ( blockImage & x)
            {
                piecePosArray[pieceNum] = { blockPosX+col,blockPosY+row }; //save coords of lit up pieces so we can remove them when block moves or rotates
                pieceNum++;
            }
            index++;
        }
    }
}


// check if lateral movment is possible , dir should only be called with either -1 or +1

bool BrickMap::isLatMoveLegal(int dir)
{
    for (int i = 0; i <= 3; i++)
    {
        if ((piecePosArray[i].x + dir > MAP_WIDTH - 1) || (piecePosArray[i].x + dir < 0)) // out of map edge bounds
            return false;
        
        if (mapArray[piecePosArray[i].x + dir][piecePosArray[i].y]) // will bump a resting block
            return false;
    }
    return true;
}


// check if we have reached the bottom or landed on top of another brick

bool BrickMap::isClearBellow()
{
   for (int i = 0; i <= 3; i++)
    {
        if (piecePosArray[i].y -1 < 0) //bottom ahead
           return false;
        
         // now check for bumping against anothet block from bellow
        
        if (mapArray[piecePosArray[i].x][piecePosArray[i].y -1]) // will bump a resting block
            return false;
    }
    
    return true;
}

//check if block rotation does't cause going outside walls or bumping other bricks

bool BrickMap:: isClearToRotate(int dir)
{
    short index = 0;
    int pieceNum = 0;
    SDL_Point TempPiecePosArray[4];
   
    memset(TempPiecePosArray, 0, sizeof(TempPiecePosArray)); //intialize the temp array
    
    // retrieve image of after potential rotation
    
    short tempImage = p_block->grid[p_block->rndBlock][(p_block->numTurns + dir) % 4];
    
    // populate temp array with positions on map after potential rotation
    for (int row = 0; row <= 3; row++)
    {
        for (int col = 0; col <= 3; col++)
        {
            int x = pow(2, index);
            if (tempImage & x)
            {
                TempPiecePosArray[pieceNum] = {blockPosX+col,blockPosY+row};
                pieceNum++;
            }
            index++;
        }
    }
    
        // iterate through temp array and check for map bounds execedence or if we are going to bump against another block
        
        for (int i = 0; i <= 3; i++)
        {
            SDL_Point tmpPoint = TempPiecePosArray[i];
            
            if ((tmpPoint.x > MAP_WIDTH -1) || ( tmpPoint.x < 0) || (tmpPoint.y < 0) || (mapArray[tmpPoint.x][tmpPoint.y]))
            return false;
         }
    
    return true;
}


// everything to do after block lands

void BrickMap::blockLanded()
{
    SoundManager::Instance()->playSound("land", 0);
    
    this->addBlockToMap();
    
    this->setAllCompletes();
    
    delete p_block;
    
    blockPosX = INITIAL_X;
    blockPosY = MAP_HEIGHT - 1;
    
    p_block = p_nextBlock;
    this->destroyCompletes();
    
    
    p_nextBlock = new Block;
}


void BrickMap::clearRow(int rowNum)
{
    for (int i = 0 ; i <= 9; i++)
        mapArray[i][rowNum] = 0;
}


void BrickMap::setRow(int rowNum)  // sets a row to full (to be used with game over animation sequence)
{
    for (int i = 0 ; i <= 9; i++)
        mapArray[i][rowNum] = 1;
}


// after a row clears this function will drop all rows above the empty line down to it.

void BrickMap::applyGravity(int rowNum)
{
    
    for (rowNum = rowNum; rowNum <= 18; rowNum ++)
{
      for (int i = 0; i <= 9; i ++) // this portion swaps two rows
    {
        mapArray[i][rowNum + 1] = mapArray[i][rowNum + 1] ^ mapArray[i][rowNum];
        mapArray[i][rowNum] = mapArray[i][rowNum] ^ mapArray[i][rowNum + 1];
        mapArray[i][rowNum + 1] = mapArray[i][rowNum + 1] ^ mapArray[i][rowNum];
    }
    
  }
}

// remove completed lines

void BrickMap::destroyCompletes()
{
    if (this->isGameOver()) return; // don't count and destroy lines during game over animation
    
    int numChecked = 0;
    
    for (int row = 0; row <= MAP_HEIGHT - 1; row++)
    {
        for (int col = 0; col <= MAP_WIDTH -1; col++)
        {
            if (!mapArray[col][row]) // empty spot, no need to keep checking, it's not a full row
            {
                numChecked = 0;
                break;
            }else
            numChecked++;
            
            if (numChecked == 10) // we have a full row
            {
                Game::Instance()->rowsCleared++;
                this->clearRow(row);
                this->applyGravity(row);
                numChecked = 0;
                row--;
            }
        }
    }
}

 // this function moves block down one row at a time

void BrickMap::decreaseY()
{
    startTime = SDL_GetTicks();
    if (InputManager::SharedManager()->isKeyDown(SDL_SCANCODE_DOWN)) // avoid double down speed which causes bricks going through issues
        return;
    else{
        if (!this->isClearBellow())
        {
            this->blockLanded();
            return;
        }
        blockPosY--;
        }
}


// create an array with all the completed lines

void BrickMap:: setAllCompletes()
{
    
    // copy map array to copy array
    
    memcpy(cpyArray, mapArray, sizeof(cpyArray));
    
    // copy map array to sans array
    
    memcpy(sansArray, mapArray, sizeof(sansArray));
    int numChecked = 0;
    
    for (int row = 0; row <= MAP_HEIGHT - 1; row++)
    {
        for (int col = 0; col <= MAP_WIDTH -1; col++)
        {
            if (!mapArray[col][row]) // empty spot, no need to keep checking, it's not a full row
            {
                numChecked = 0;
                break;
            }else
                numChecked++;
            
            if (numChecked == 10) // we have a full row
            {
                for (int i = 0 ; i <= 9; i++)  sansArray[i][row] = 0;
                   
                needsFlashing = true;
                
                numChecked = 0;
            }
        }
    }
    
}


// draw screen without completed lines for purpose of flashing

void BrickMap:: drawWithout ()
{
    for (int row = 0; row <= 19; row++)
    {
        for (int col = 0; col <= 9; col++)
        {
            if (sansArray[col][row])
        
                PLOT_AT_MAP_COORD(col, row);
        }
    }
}

// draw a copy of map (for flashing purposes)

void BrickMap:: drawWith()
{
    for (int row = 0; row <= 19; row++)
    {
        for (int col = 0; col <= 9; col++)
        {
            if (cpyArray[col][row])
                
                PLOT_AT_MAP_COORD(col, row);
        }
    }
}

// handle movments

void BrickMap:: moveLeft()
{
    blockPosX--;
    SoundManager::Instance()->playSound("move", 0);
}

void BrickMap:: moveRight()
{
    blockPosX++;
    SoundManager::Instance()->playSound("move", 0);
}

void BrickMap:: moveDown()
{
   blockPosY--;
    SoundManager::Instance()->playSound("move", 0);
}

void BrickMap::rotateLeft()
{
     p_block->numTurns--;
    SoundManager::Instance()->playSound("rl", 0);
}

void BrickMap::rotateRight()
{
   p_block->numTurns++;
   SoundManager::Instance()->playSound("rr", 0);
}


// return an image of the next block in line, so we can display it on the hud

short BrickMap:: returnNextblockImage()
{
    return p_nextBlock->grid[p_nextBlock->rndBlock][0];
}

// check if we've reached the top row

bool BrickMap::isGameOver()
{
    for (int col = 0; col <= 9; col++)
    if (mapArray[col][MAP_HEIGHT]) return true;
    return false;
}










