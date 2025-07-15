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
private:
    void OnPaint( wxPaintEvent& event );
    float _gridSize = 15.0;
    Vec2 _cellSize = Vec2( 10.0, 10.0 );
    FlockManager* _flockManager = nullptr;

};

