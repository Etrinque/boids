#pragma once

// Helper structs for Boids implementation;
// fine precision not guaranteed;
// TODO: Add finer grain precision equality comparisons ex...
// std::abs( float == other.float ) < 1e-5 epsilon;

struct Vec2
{
    float x, y;

    Vec2( ) : x( 0 ), y( 0 ) {}
    Vec2( float _x, float _y ) { x = _x; y = _y; }
    Vec2 operator+( const Vec2& other ) const { return Vec2( x + other.x, y + other.y ); }
    Vec2 operator-( const Vec2& other ) const { return Vec2( x - other.x, y - other.y ); }
    bool operator==( const Vec2& other ) const
    {
        return x == other.x && y == other.y;
    }
};

struct Vec3
{
    float x, y, z;

    Vec3( ) :x( 0 ), y( 0 ), z( 0 ) {}
    Vec3( float _x, float _y, float _z ) { x = _x; y = _y; z = _z; }
    Vec3 operator+( const Vec3& other ) const { return Vec3( x + other.x, y + other.y, z + other.z ); }
    Vec3 operator-( const Vec3& other ) const { return Vec3( x - other.x, y - other.y, z - other.z ); }

    bool operator==( const Vec3& other ) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Vec4
{
    float w, x, y, z;

    Vec4( ) :w( 0 ), x( 0 ), y( 0 ), z( 0 ) {}
    Vec4( float _w, float _x, float _y, float _z ) { w = _w; x = _x; y = _y; z = _z; }
    Vec4 operator+( const Vec4& other ) const { return Vec4( w + other.w, x + other.x, y + other.y, z + other.z ); }
    Vec4 operator-( const Vec4& other ) const
    {
        return Vec4( w - other.w, x - other.x, y - other.y, z - other.z );
    }
    bool operator==( const Vec4& other ) const
    {
        return w == other.w && x == other.x && y == other.y && z == other.z;
    }
};
