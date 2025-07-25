#pragma once
#include "Vec.h"
#include "wx/wx.h"
#include "up_arrow.xpm"

class Boid
{
public:
    Boid( ) : _position( 0, 0 ), _velocity( 0, 0 ) {};
    Boid( Vec2 position, Vec2 velocity ) : _position( position ), _velocity( velocity ) {};

    ~Boid( ) {};

    wxBitmap GetIcon( ) { return _icon; };

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
        return false;
    }

    float GetBoidSize( ) const { return _BOID_SIZE; };
    Vec2 GetVelocity( ) const { return _velocity; };
    Vec2 GetPosition( ) const { return _position; };

    // Get rotation angle in radians based on velocity heading
    double GetRotationAngle( ) const
    {
        // If velocity is zero, return 0 (no rotation)
        if ( _velocity.x == 0 && _velocity.y == 0 )
            return 0.0;

        // Calculate angle in radians: atan2 returns the angle between positive x-axis and point (y,x)
        // Subtract PI/2 (90 degrees) because our bitmap faces up (north) by default
        return atan2( _velocity.y, _velocity.x ) - M_PI / 2.0;
    }

    // Get a rotated version of the icon based on current velocity
    wxBitmap GetRotatedIcon( ) const
    {
        // If no velocity, return the original icon
        if ( _velocity.x == 0 && _velocity.y == 0 )
            return _icon;

        double angle = GetRotationAngle( );

        wxImage image = _icon.ConvertToImage( );

        // Set the rotation center to the middle of the bitmap
        int width = image.GetWidth( );
        int height = image.GetHeight( );
        //image.SetMaskColour( 255, 255, 255 );

        // Rotate the image
        return wxBitmap( image.Rotate( angle, wxPoint( width / 2, height / 2 ) ) );
    }

    void SetVelocity( Vec2 vec2 ) { _velocity = vec2; };
    void SetPosition( Vec2 vec2 ) { _position = vec2; };
private:
    Vec2 _position;
    Vec2 _velocity;
    wxBitmap _icon = wxBitmap( up_arrow );

    static constexpr float _BOID_SIZE = 16.0f;

};

