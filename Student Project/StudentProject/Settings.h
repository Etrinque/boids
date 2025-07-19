#pragma once
#include"Vec.h"

struct Settings
{
    int TimeInterval = 16; // framerate in milliseconds default to 16ms (60 FPS+-)
    Vec2 ScreenSize = Vec2( 900, 600 );     // overall initial screen size default to 900x600
    int GridSize = 50;       // size of the grid for boids; default to 50x50
    Vec2 CellSize = Vec2( 10, 10 );       // size of the grid cells for boids; superflous but useful for future features; default to 10x10
    int NumBoids = 0;       // initial number of boids; default to 0
    int MaxBoids = 1000;      // maximum number of boids allowed in the simulation; default to 1000
    int BoidVision = 25;    // initial vision radius of each boid; default to 25
};