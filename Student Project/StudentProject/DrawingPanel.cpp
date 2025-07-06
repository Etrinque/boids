#include "DrawingPanel.h"
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

//wxBEGIN_EVENT_TABLE( DrawingPanel, wxPanel )
//EVT_PAINT( DrawingPanel::OnPaint )
//wxEND_EVENT_TABLE( )


DrawingPanel::DrawingPanel( wxFrame* parent ) :wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
{
    this->SetBackgroundStyle( wxBG_STYLE_PAINT );
    this->Bind( wxEVT_PAINT, &DrawingPanel::OnPaint, this );
}

DrawingPanel::~DrawingPanel( ) {}

void DrawingPanel::OnPaint( wxPaintEvent& event )
{
    wxAutoBufferedPaintDC dc( this );
    dc.Clear( );


    wxGraphicsContext* context = wxGraphicsContext::Create( dc );
    if ( !context ) return;
    context->SetPen( *wxBLACK );
    context->SetBrush( *wxWHITE );

    int xOffset = 0;
    int yOffset = 0;

    // testing larger size
   /* _gridSize = 30;
    _cellSize.x = 15;
    _cellSize.y = 15;*/

    for ( int i = 0; i < _gridSize; i++ )
    {

        for ( int j = 0; j < _gridSize; j++ )
        {
            context->DrawRectangle( xOffset, yOffset, _cellSize.x, _cellSize.y );
            xOffset += _cellSize.x;
            wxMilliSleep( 200 );
        }
        xOffset = 0;
        yOffset += _cellSize.y;
    }
  /*  wxSize size = GetSize( );
    int centerX = size.x / 2;
    int centerY = size.y / 2;
    int height = 100;
    int width = 100;
    context->DrawRectangle( centerX - width / 2, centerY - height / 2, width, height );*/

}