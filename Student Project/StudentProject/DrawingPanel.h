#pragma once
#include "wx/wx.h"
#include "Vec.h"


class DrawingPanel : public wxPanel
{
public:
    DrawingPanel( wxFrame* parent );
    ~DrawingPanel( );
private:
    void OnPaint( wxPaintEvent& event );
    float _gridSize = 15.0;
    Vec2 _cellSize = Vec2( 10.0, 10.0 );

    //wxDECLARE_EVENT_TABLE( );
};

