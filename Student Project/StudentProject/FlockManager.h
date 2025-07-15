#pragma once
#include "Boid.h"
#include <vector>
class FlockManager
{
private:
    std::vector<Boid*> _Flock;
    int     _numBoids = 50;  // max should be < 1000? performance dependent;

    //TODO: defaults set to 1.0 for simplicity - likely will need to be adjusted before finalizing program;
    //float   _speedFactor = 1.0;     // TODO: refactor to Main-Loop; Default to 1.0 speed, max of 2 or 3?
    float   _cohesionFactor = 1.0;
    float   _separationFactor = 1.0;
    float   _alignmentFactor = 1.0;

     // TODO: Ruleset for Flocking Physics
    Vec2 CalcAlignment( Boid& boid, float speedFactor = 1.0 )
    {
        Vec2 avgVelocity( 0, 0 );
        if ( _Flock.size( ) < 2 ) { return avgVelocity; }

        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }
            avgVelocity += b->GetVelocity( );
        }

        avgVelocity /= static_cast< float >( _Flock.size( ) - 1 );

        Vec2 alignmentDir = avgVelocity - boid.GetVelocity( );
        alignmentDir.Normalize( alignmentDir );

        return alignmentDir * speedFactor;
    };

    Vec2 CalcCohesion( Boid& boid, float speedFactor = 1.0 )
    {
        Vec2 centerOfMass( 0, 0 );
        if ( _Flock.size( ) < 2 ) { return centerOfMass; }
        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }
            centerOfMass += b->GetPosition( );
        }

        centerOfMass /= static_cast< float >( _Flock.size( ) - 1 );
        Vec2 cohesionDir = centerOfMass - boid.GetPosition( );
        return cohesionDir * speedFactor;
    };

    Vec2 CalcSeparation( Boid& boid, float speedFactor = 1.0 )
    {
        Vec2 separation( 0, 0 );
        if ( _Flock.size( ) < 2 ) { return separation; }
        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }
        }
        separation /= static_cast< float >( _Flock.size( ) - 1 );

        Vec2 direction = boid.GetPosition( ) - separation;

        direction.Normalize( direction );
        return direction * speedFactor;
    };

   //TODO Add speedFactor method for adjusting boid speed based on user input;

public:
    FlockManager( )
    {
        for ( int i = 0; i < _numBoids; i++ )
        {
            AddBoid( new Boid( ) );
        }
    }

    FlockManager( int numBoids, int gameBoardMaxX, int gameBoardMaxY ) : _numBoids( numBoids )
    {
        int posX;
        int posY;
        int startingMagnitude = 1;
        int startingSpeed = 1;
        for ( int i = 0; i < _numBoids; i++ )
        {
            posX = rand( ) % gameBoardMaxX;
            posY = rand( ) % gameBoardMaxY;
            AddBoid( new Boid( Vec2( posX, posY ), Vec2( startingMagnitude, startingSpeed ) ) );
        }
    }

    ~FlockManager( )
    {
        for ( Boid* boid : _Flock )
        {
            delete boid;
        }
        _Flock.clear( );
    }
    const std::vector<Boid*>& GetBoidsList( ) const
    {
        return _Flock;
    };

    float GetAlignmentFactor( ) const { return _alignmentFactor; }
    float GetCohesionFactor( ) const { return _cohesionFactor; }
    float GetSeparationFactor( ) const { return _separationFactor; }
    int   GetNumBoids( ) const { return _Flock.size( ); };

    //float GetSpeedFactor( ) const { return _speedFactor; } // TODO: Refactor to Main-Loop
    //void SetSpeedFactor( float factor ) { _speedFactor = factor; }; // TODO: Refactor to Main-Loop

    void SetNumBoids( int numBoids ) { _numBoids = numBoids; };
    void SetCohesionFactor( float factor ) { _cohesionFactor = factor; };
    void SetSeparationFactor( float factor ) { _separationFactor = factor; };
    void SetAlignmentFactor( float factor ) { _alignmentFactor = factor; };

    void AddBoid( Boid* boid )
    {
        if ( boid != nullptr )
        {
            _Flock.push_back( boid );
        }
    };

    // overloaded method for use with ScrollButton/Input Field
    void AddBoid( int numBoid = 1 )
    {
        for ( int i = 0; i < numBoid; i++ )
        {
            _Flock.push_back( new Boid );
        }
    }

    void RemoveBoid( Boid* boid )
    {
        if ( boid != nullptr )
        {
            auto it = std::remove( _Flock.begin( ), _Flock.end( ), boid );
            if ( it != _Flock.end( ) )
            {
                _Flock.erase( it, _Flock.end( ) );
            }
            // delete boid pointer;
            delete boid;
        }
    };

    // TODO Refactor to use Ruleset
    void UpdateBoids( float deltaTime = 1.0 ) const
    {
        for ( Boid* boid : _Flock )
        {
            if ( boid != nullptr )
            {
                Vec2 velocity = boid->GetVelocity( );
                Vec2 position = boid->GetPosition( );
                position += velocity * deltaTime;
                boid->SetPosition( position );
            }
        }
    };






};

