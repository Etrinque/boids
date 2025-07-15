#pragma once
#include "wx/wx.h"



class DrawingPanel : public wxPanel
{
public:
    DrawingPanel( wxFrame* parent );
    ~DrawingPanel( );
private:
    void OnPaint( wxPaintEvent& event );

    wxDECLARE_EVENT_TABLE( );
};

