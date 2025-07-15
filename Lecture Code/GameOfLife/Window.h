#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
class Window : public wxFrame
{
public:
    Window( );
    ~Window( );

private:
    wxButton* _button;
    int _count = 0;
    wxButton* _button2;
    DrawingPanel* _drawingPanel;
    void _drawRect( wxPaintEvent& event );
    void OnSizeChanged( wxSizeEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnPaint( wxPaintEvent& event );
    void OnButtonClick( wxCommandEvent& event );
    wxDECLARE_EVENT_TABLE( );
};
