#pragma once
#include "Boid.h"
#include <vector>
class FlockManager
{
public:
    FlockManager( )
    {
        for ( int i = 0; i < _numBoids; i++ )
        {
            AddBoid( new Boid( ) );
        }
    }

    // TODO: Fix constructor. error with boundary initialization; still persists
    FlockManager( int numBoids, int boundary_X, int boundary_Y ) : _numBoids( numBoids ), _boundary( boundary_X, boundary_Y )
    {
        int posX;
        int posY;
        int startingMagnitude;
        int startingSpeed = 1;
        srand( static_cast< unsigned int >( time( nullptr ) ) );

        for ( int i = 0; i < _numBoids; i++ )
        {
            startingMagnitude = rand( ) % 10 + 1; // random magnitude between 1 and 10

            //refact to accept boundary data member
            posX = rand( ) % int( _boundary.x );
            posY = rand( ) % int( _boundary.y );
            AddBoid( new Boid( Vec2( posX, posY ), Vec2( startingMagnitude, startingSpeed ) ) );
        }
    }

    ~FlockManager( )
    {
        for ( Boid* boid : _Flock )
        {
            if ( boid == nullptr ) { continue; }
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
    float GetVisionFactor( ) const { return _visionFactor; }
    float GetSpeedFactor( ) const { return _speedFactor; }
    Vec2 GetBoundary( ) const { return _boundary; }

    void SetNumBoids( int numBoids ) { _numBoids = numBoids; };
    void SetCohesionFactor( float factor ) { _cohesionFactor = factor; };
    void SetSeparationFactor( float factor ) { _separationFactor = factor; };
    void SetAlignmentFactor( float factor ) { _alignmentFactor = factor; };
    void SetSpeedFactor( float factor ) { _speedFactor = factor; };
    void SetVisionFactor( float factor ) { _visionFactor = factor; };
    void SetBoundary( float x, float y )
    {
        _boundary.x = x; _boundary.y = y;
    }

    void AddBoid( Boid* boid )
    {
        if ( boid != nullptr )
        {
            _Flock.push_back( boid );
        }
    };

    void AddBoids( int numBoid = 1 )
    {
        int posX;
        int posY;
        int startingMagnitude;
        int startingSpeed = 1;
        srand( static_cast< unsigned int >( time( nullptr ) ) ); // seed the random number generator
        for ( int i = 0; i < numBoid; i++ )
        {
            startingMagnitude = rand( ) % 10 + 1; // random magnitude between 1 and 10
            posX = rand( ) % int( _boundary.x );
            posY = rand( ) % int( _boundary.y );
            AddBoid( new Boid( Vec2( posX, posY ), Vec2( startingMagnitude, startingSpeed ) ) );
        }
    }

    void RemoveBoid( Boid* boid )
    {
        auto it = std::find( _Flock.begin( ), _Flock.end( ), boid );
        if ( it != _Flock.end( ) )
        {
            delete* it; // delete the Boid object
            _Flock.erase( it ); // remove from the vector
        }
    };
    void RemoveBoid( )
    {
        if ( !_Flock.empty( ) )
        {
            Boid* boid = _Flock.back( );
            RemoveBoid( boid );
        }
    }
    void RemoveBoids( int numBoids )
    {
        for ( int i = 0; i < numBoids && !_Flock.empty( ); i++ )
        {
            Boid* boid = _Flock.back( );
            RemoveBoid( boid );
        }
    }

    void UpdateFlock( float delta = 1.0 )
    {
        for ( Boid* boid : _Flock )
        {
            if ( boid != nullptr )
            {

                Vec2 alignment = CalcAlignment( *boid );
                Vec2 cohesion = CalcCohesion( *boid );
                Vec2 separation = CalcSeparation( *boid );

                // get the new velocity
                Vec2 newVelocity = boid->GetVelocity( ) + alignment + cohesion + separation;

                // normalize the velocity
                newVelocity.Normalize( );

                newVelocity *= _speedFactor;

                // Update the Boid's velocity
                boid->SetVelocity( newVelocity );

                // Update the Boid's position based on the new velocity
                Vec2 position = boid->GetPosition( );
                position += newVelocity * delta;

                // Check for boundary bounce
                boid->SetPosition( position );
                SetBoundaryBounce( *boid );
            }
        }
    }

private:
    std::vector<Boid*> _Flock;
    int     _numBoids = 50;
    Vec2    _boundary = Vec2( 0, 0 );
    float   _speedFactor = 1.0;
    float   _cohesionFactor = 0.01;
    float   _separationFactor = 0.2;
    float   _alignmentFactor = 0.01;
    float   _visionFactor = 25;

    Vec2 CalcAlignment( Boid& boid )
    {
        Vec2 avgVelocity( 0, 0 );
        int neighborCount = 0;

        if ( _Flock.size( ) < 2 ) { return avgVelocity; }

        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }
            Vec2 diff = b->GetPosition( ) - boid.GetPosition( );
            float distance = std::sqrt( diff.x * diff.x + diff.y * diff.y );

            if ( distance < _visionFactor )
            {
                avgVelocity += b->GetVelocity( );
                neighborCount++;
            }
        }

        if ( neighborCount == 0 ) { return avgVelocity; };

        avgVelocity /= static_cast< float >( neighborCount );

        Vec2 alignmentDir = avgVelocity - boid.GetVelocity( );
        alignmentDir.Normalize( );

        return alignmentDir * _alignmentFactor;
    };

    Vec2 CalcCohesion( Boid& boid )
    {
        Vec2 centerOfMass( 0, 0 );
        int neighborCount = 0;

        if ( _Flock.size( ) < 2 ) { return centerOfMass; }
        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }
            Vec2 diff = b->GetPosition( ) - boid.GetPosition( );
            float distance = std::sqrt( diff.x * diff.x + diff.y * diff.y );
            if ( distance < _visionFactor )
            {
                centerOfMass += b->GetPosition( );
                neighborCount++;
            }
        }

        if ( neighborCount == 0 ) { return centerOfMass; }

        centerOfMass /= static_cast< float >( neighborCount );

        Vec2 cohesionDir = centerOfMass - boid.GetPosition( );
        float distance = std::sqrt( cohesionDir.x * cohesionDir.x + cohesionDir.y * cohesionDir.y );

        // If distance is very small, reduce or eliminate cohesion
        float boidSize = boid.GetBoidSize( );
        if ( distance < boidSize * 2 )
        {
            // Gradually reduce cohesion as boids get closer than 2x boid size
            float reductionFactor = distance / ( boidSize * 2 );
            return cohesionDir * _cohesionFactor * reductionFactor;
        }

        // For normal distances, normalize and apply cohesion factor
        if ( distance > 0 )
        {
            cohesionDir.Normalize( );
            return cohesionDir * _cohesionFactor;
        }
        return Vec2( 0, 0 );
    };

    Vec2 CalcSeparation( Boid& boid )
    {
        Vec2 separation( 0, 0 );
        int neighborCount = 0;

        if ( _Flock.size( ) < 2 ) { return separation; }

        for ( Boid* b : _Flock )
        {
            if ( boid == *b ) { continue; }


            Vec2 diff = boid.GetPosition( ) - b->GetPosition( );
            float distance = std::sqrt( diff.x * diff.x + diff.y * diff.y );

            // check if boid has vision of other boids;
            if ( distance > 0 && distance < _visionFactor )
            {
                float factor = 1.0f - ( distance / _visionFactor );

                separation += ( diff / distance ) * factor * factor;
                neighborCount++;
            }
        }

        if ( neighborCount == 0 ) { return separation; }
        if ( separation.x != 0 || separation.y != 0 )
        {
            separation.Normalize( );
        }

        return separation * _separationFactor;
    };

   //TODO: Fix boundary bouncing 

    void SetBoundaryBounce( Boid& boid ) const
    {
        Vec2 position = boid.GetPosition( );
        float boidSize = boid.GetBoidSize( );

        if ( position.x < 0 )
        {
            position.x = 0; // bounce off left wall
            boid.SetPosition( position );
            boid.SetVelocity( Vec2( -boid.GetVelocity( ).x, boid.GetVelocity( ).y ) ); // reverse x velocity
        }
        else if ( position.x > _boundary.x - boidSize )
        {
            position.x = _boundary.x - boidSize; // bounce off right wall
            boid.SetPosition( position );
            boid.SetVelocity( Vec2( -boid.GetVelocity( ).x, boid.GetVelocity( ).y ) ); // reverse x velocity
        }


        if ( position.y < 0 )
        {
            position.y = 0; // bounce off top wall
            boid.SetPosition( position );
            boid.SetVelocity( Vec2( boid.GetVelocity( ).x, -boid.GetVelocity( ).y ) ); // reverse y velocity
        }
        else if ( position.y > _boundary.y - boidSize )
        {
            position.y = _boundary.y - boidSize; // bounce off bottom wall
            boid.SetPosition( position );
            boid.SetVelocity( Vec2( boid.GetVelocity( ).x, -boid.GetVelocity( ).y ) ); // reverse y velocity
        }

    }

};

