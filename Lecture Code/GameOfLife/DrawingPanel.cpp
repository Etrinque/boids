#include "DrawingPanel.h"
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE( DrawingPanel, wxPanel )
EVT_PAINT( DrawingPanel::OnPaint )
wxEND_EVENT_TABLE( )


DrawingPanel::DrawingPanel( wxFrame* parent ) :wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
{
    this->SetBackgroundStyle( wxBG_STYLE_PAINT );
}

DrawingPanel::~DrawingPanel( ) {}

void DrawingPanel::OnPaint( wxPaintEvent& event )
{
    wxAutoBufferedPaintDC dc( this );
    dc.Clear( );


    wxGraphicsContext* context = wxGraphicsContext::Create( dc );
    if ( !context ) return;
    context->SetPen( *wxBLACK );
    context->SetBrush( *wxGREEN );

    wxSize size = GetSize( );
    int centerX = size.x / 2;
    int centerY = size.y / 2;
    int height = 100;
    int width = 100;
    context->DrawRectangle( centerX - width / 2, centerY - height / 2, width, height );

}