//
//  defs.h
//  Block Tricks
//
//  Created by Benny Abramovici on 2/4/15.
//  Copyright (c) 2015 Benny Abramovici. All rights reserved.
//

#ifndef Block_Tricks_defs_h
#define Block_Tricks_defs_h


#define TILE_WIDTH 25
#define TILE_HEIGHT 25
#define MAP_WIDTH 10
#define MAP_HEIGHT 20
#define MAP_SIZE_WIDTH 250
#define MAP_SIZE_HEIGHT 500
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define MAP_OFFSET 50
#define INITIAL_X 3

#define PLOT_AT_COORD(x,y) TextureManager::Instance()->draw("block", (x),(y), TILE_WIDTH, TILE_HEIGHT, mapRenderer);
#define PLOT_AT_MAP_COORD(j,k) PLOT_AT_COORD(mapToScreen(j, k).x,mapToScreen(j, k).y)


#define theMap BrickMap::SharedMap()

enum {LEFT = -1, RIGHT = 1};
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

#endif
