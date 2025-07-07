#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
// TODO: Clean up file;
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


    void OnSizeChange( wxSizeEvent& event );
    void OnButtonClick( wxCommandEvent& event );
    //void _drawRect( wxPaintEvent& event );
    //void OnSize( wxSizeEvent& event );
    //void OnPaint( wxPaintEvent& event );
    //wxDECLARE_EVENT_TABLE( );
};
