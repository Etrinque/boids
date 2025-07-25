#pragma once
#include <cmath>
#include <string>
// Helper classes for Boids implementation;
// fine precision not guaranteed;

class Vec2
{
public:
    float x, y;

    Vec2( ) : x( 0 ), y( 0 ) {}
    Vec2( float _x, float _y ) { x = _x; y = _y; }
    Vec2 operator+( const Vec2& other ) const { return Vec2( x + other.x, y + other.y ); }
    Vec2 operator-( const Vec2& other ) const { return Vec2( x - other.x, y - other.y ); }
    Vec2& operator+=( const Vec2& vec ) { x = x + vec.x; y = y + vec.y; return *this; }
    Vec2 operator/=( float div )
    {
        if ( div != 0 )
        {
            x /= div;
            y /= div;
            return *this;
        }
        else
        {
            x = 0;
            y = 0;
            return *this;
        }
    }
    Vec2 operator/( float div ) const
    {
        if ( div != 0 )
        {
            return Vec2( x / div, y / div );
        }
        else
        {
            return Vec2( 0, 0 );
        }
    }
    Vec2 operator*( float mult ) const { return Vec2( x * mult, y * mult ); }
    Vec2 operator*=( float mult )
    {
        x *= mult;
        y *= mult;
        return *this;
    }
    bool operator==( const Vec2& other ) const
    {
        return x == other.x && y == other.y;
    }
    void Normalize( )
    {
        float magnitude = std::sqrt( this->x * this->x + this->y * this->y );
        if ( magnitude > 0 )
        {
            this->x /= magnitude;
            this->y /= magnitude;
        }
        else
        {
            this->x = 0;
            this->y = 0;
        }
    }
    std::string ToString( ) const
    {
        return std::to_string( x ) + "," + std::to_string( y ); // truncate to int
    };
};

//class Vec3
//{
//    float x, y, z;
//
//    Vec3( ) :x( 0 ), y( 0 ), z( 0 ) {}
//    Vec3( float _x, float _y, float _z ) { x = _x; y = _y; z = _z; }
//    Vec3 operator+( const Vec3& other ) const { return Vec3( x + other.x, y + other.y, z + other.z ); }
//    Vec3 operator-( const Vec3& other ) const { return Vec3( x - other.x, y - other.y, z - other.z ); }
//
//    bool operator==( const Vec3& other ) const
//    {
//        return x == other.x && y == other.y && z == other.z;
//    }
//};
//
//class Vec4
//{
//    float w, x, y, z;
//
//    Vec4( ) :w( 0 ), x( 0 ), y( 0 ), z( 0 ) {}
//    Vec4( float _w, float _x, float _y, float _z ) { w = _w; x = _x; y = _y; z = _z; }
//    Vec4 operator+( const Vec4& other ) const { return Vec4( w + other.w, x + other.x, y + other.y, z + other.z ); }
//    Vec4 operator-( const Vec4& other ) const
//    {
//        return Vec4( w - other.w, x - other.x, y - other.y, z - other.z );
//    }
//    bool operator==( const Vec4& other ) const
//    {
//        return w == other.w && x == other.x && y == other.y && z == other.z;
//    }
//};
