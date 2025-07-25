#pragma once
#include"Vec.h"
#include "Boid.h"
#include <fstream>
#include <string>

struct Settings
{
    int TimeInterval = 16; // framerate in milliseconds default to 16ms (60 FPS+-)
    Vec2 ScreenSize = Vec2( 900, 600 );     // overall initial screen size default to 900x600
    int GridSize = 50;       // size of the grid for boids; default to 50x50
    Vec2 CellSize = Vec2( 10, 10 );       // size of the grid cells for boids; superflous but useful for future features; default to 10x10
    int NumBoids = 25;       // initial number of boids; default to 0
    int MaxBoids = 1000;      // maximum number of boids allowed in the simulation; default to 1000
    int BoidVision = 25;    // initial vision radius of each boid; default to 25
    bool HudShown = false; // default to false

    void SaveSettings( )
    {
        std::ofstream output( "settings.bin", std::ios::binary | std::ios::out );
        if ( !output.is_open( ) )
        {
            return;
        }

        output.write( reinterpret_cast< char* >( this ), sizeof( Settings ) );
        output.close( );
    };
    void LoadSettings( )
    {
        std::ifstream input( "settings.bin", std::ios::binary | std::ios::in );
        if ( !input.is_open( ) )
        {
            return;
        }
        input.read( reinterpret_cast< char* >( this ), sizeof( Settings ) );
        return;


    };
    void ResetSettings( )
    {
        TimeInterval = 16;
        ScreenSize = Vec2( 900, 600 );
        GridSize = 50;
        CellSize = Vec2( 10, 10 );
        NumBoids = 25;
        MaxBoids = 1000;
        BoidVision = 25;
        HudShown = false;
    };
};