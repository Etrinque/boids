#pragma once
#include "wx/wx.h"
#include "Vec.h"
#include "FlockManager.h"

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel( wxFrame* parent );
    ~DrawingPanel( );
    void SetFlockManager( FlockManager* manager ) { _flockManager = manager; }
    void SetGridSize( float gridSize ) { _gridSize = gridSize; }
    void SetCellSize( const Vec2& cellSize ) { _cellSize = cellSize; }
    float GetGridSize( ) const { return _gridSize; }
    Vec2 GetCellSize( ) const { return _cellSize; }
    void IsHudShown( bool showHud ) { _isHudShown = showHud; };
    void SetHudShown( bool showHud )
    {
        _isHudShown = showHud;
        Refresh( );
    }
private:
    void OnPaint( wxPaintEvent& event );
    float _gridSize = 50.0;
    Vec2 _cellSize = Vec2( 10.0, 10.0 );
    FlockManager* _flockManager = nullptr;
    bool _isHudShown;

};

