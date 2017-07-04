

#include "Block.h"
#include <iostream>
#include <random>



Block::Block()
{
    numTurns = 5000; // initialized to a high enough number instead of zero to avoid a chance of negative numnber;
    
    // generate a random block number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);
    
    rndBlock = dis(gen);
}


Block::~Block()
{
    std::cout << "block deallocated" << std::endl;;
}