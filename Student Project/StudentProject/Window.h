#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
class MainWindow : public wxFrame
{
public:
    MainWindow( );
    ~MainWindow( );


private:
    int _count = 0;
    wxButton* _button;
    wxButton* _button2;
    DrawingPanel* _drawingPanel;


    void _drawRect( wxPaintEvent& event );
    void OnSizeChanged( wxSizeEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnPaint( wxPaintEvent& event );
    void OnButtonClick( wxCommandEvent& event );
    wxDECLARE_EVENT_TABLE( );
};
