
#ifndef __Block__
#define __Block__

class Block
{
public:
    Block();
    ~Block();
    
    short grid[7][4] = // all possible variations of blocks and their poses are saved here as Hex numbers which represent their image in binary.
    {
        { 0x1700, 0x6220, 0x740, 0x2230 }, // J shape with all poses
        { 0x4700, 0x2260, 0x710, 0x3220 }, // L shape with all poses
        { 0x2700, 0x2620, 0x720, 0x2320 }, // T shape with all poses
        { 0x6300, 0x2640, 0x630, 0x1320 }, // S shape with all poses
        { 0x3600, 0x4620, 0x360, 0x2310 }, // Z shape with all poses
        { 0x6600, 0x6600, 0x6600,0x6600 }, // O shape with all poses
        { 0xF00,  0x4444, 0xF0,  0x2222 }  // I shape with all poses
    
    };
    
    int numTurns;  // the number of times the block has been turned either cw or ccw.
    int rndBlock;
    
private:
    
    
    
};

#endif /* defined(__Block__) */
