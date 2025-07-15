#pragma once
#include "Window.h"

// using macros
#define BUTTON_EVT_ID_1 30001 // macro for btn_1
#define BUTTON_EVT_ID_2 30002 // macro for btn_2

// could also use enum...

enum BUTTON_EVT
{
    BTN_1 = 30001, // convolution set to 30001
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5
};

// could also use event binding Bind() method to inline functionality for
// dynamic elements

// define a macro Event Lookup Table
wxBEGIN_EVENT_TABLE( Window, wxFrame )
EVT_BUTTON( BUTTON_EVT::BTN_1, Window::OnButtonClick ) // register macro for btn 1
EVT_BUTTON( BUTTON_EVT_ID_2, Window::OnButtonClick ) EVT_PAINT( OnPaint )
EVT_SIZE( OnSizeChanged )
//EVT_SIZE( OnSize ) 
wxEND_EVENT_TABLE( )

Window::Window( )
    : wxFrame( nullptr, wxID_ANY, "Window", wxPoint( 0, 0 ), wxSize( 500, 500 ) )
{
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    this->SetSizer( sizer );

    _drawingPanel = new DrawingPanel( this );
    //_drawingPanel->SetSize( 100, 100 );


   /* _button = new wxButton( this, BUTTON_EVT_ID_1, "Click-me", wxDefaultPosition,
                            wxDefaultSize );
    _button2 = new wxButton( this, BUTTON_EVT_ID_2, "Click-me_instead",
                             wxPoint( 100, 0 ), wxDefaultSize );
    */
}

Window::~Window( ) {}

void Window::_drawRect( wxPaintEvent& event )
{
    wxPaintDC dc( this ); // create the device context for drawing

    wxPen Pen( wxColour( 100, 100, 100, 0.5 ), 2, wxPENSTYLE_DOT_DASH );
    dc.SetPen( Pen );

    wxBrush brush( "black", wxBRUSHSTYLE_FDIAGONAL_HATCH );
    dc.SetBrush( brush );

    // centered rect
    //  define rect size to paint

    int width = 150;
    int height = 150;

    wxSize size = GetSize( );
    int centerX = size.x / 2;
    int centerY = size.y / 2;

    int startX = centerX / 2;
    int startY = centerY / 2;
    dc.DrawRectangle( startX, startY, width, height );

    int topLeftX = 0;
    int topLeftY = 0;
    // int botRightX = 500;
    // int botRightY = 500;
    dc.DrawRectangle( topLeftX, topLeftY, width, height );
}

void Window::OnSizeChanged( wxSizeEvent& event )
{
    _drawingPanel->SetSize( event.GetSize( ) );
    Refresh( );
}

void Window::OnSize( wxSizeEvent& event )
{

    Refresh( );
    event.Skip( );
}

void Window::OnPaint( wxPaintEvent& event ) { _drawRect( event ); }

void Window::OnButtonClick( wxCommandEvent& event )
{
    if ( event.GetId( ) == BUTTON_EVT::BTN_1 )
    {
        _count += 1;
        std::string msg = "Clicked " + std::to_string( _count );
        _button->SetLabel( msg );
    }
    else if ( event.GetId( ) == BUTTON_EVT_ID_2 )
    {
        _button2->SetSize( _button2->GetSize( ).x + 5, _button2->GetSize( ).y + 5 );
    }
};