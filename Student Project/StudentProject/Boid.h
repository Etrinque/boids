#pragma once
#include "Vec.h"
#include "wx/wx.h"
#include "up_arrow.xpm"

class Boid
{
private:
    Vec2 _position;
    Vec2 _velocity;
    wxImage _icon = wxBitmap( up_arrow ).ConvertToImage( );

public:

    Boid( ) : _position( 0, 0 ), _velocity( 0, 0 ) {};
    Boid( Vec2 position, Vec2 velocity ) : _position( position ), _velocity( velocity ) {};
    Boid( float x, float y, float vx, float vy, wxImage icon ) : _position( x, y ), _velocity( vx, vy ), _icon( icon ) {};
    ~Boid( ) {};

    wxImage* GetIcon( ) { return &_icon; };

    Boid( const Boid& other ) : _position( other._position ), _velocity( other._velocity ) {};

    // may not be needed;
    Boid& operator=( const Boid& other )
    {
        if ( this != &other && this != nullptr )
        {
            _position = other._position;
            _velocity = other._velocity;
        }
        return *this;
    }
    // for loop skipping
    bool operator==( const Boid& other )
    {
        if ( this != nullptr )
        {
            return _position == other._position && _velocity == other._velocity;
        }
    }


    Vec2 GetVelocity( ) const { return _velocity; };
    Vec2 GetPosition( ) const { return _position; };

    Vec2 SetVelocity( Vec2& vec2 ) { _velocity = vec2; };
    Vec2 SetPosition( Vec2& vec2 ) { _position = vec2; };

};

