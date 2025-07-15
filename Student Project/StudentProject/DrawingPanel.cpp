#include "DrawingPanel.h"
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"




DrawingPanel::DrawingPanel( wxFrame* parent ) : wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
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

    float xOffset = 0.0;
    float yOffset = 0.0;

    wxSize size = this->GetClientSize( );
    float cellSizeX = size.GetWidth( ) / _gridSize;
    float cellSizeY = size.GetHeight( ) / _gridSize;

    for ( int i = 0; i < _gridSize; i++ )
    {

        for ( int j = 0; j < _gridSize; j++ )
        {
            context->DrawRectangle( xOffset, yOffset, cellSizeX, cellSizeY );
            xOffset += cellSizeX;

        }
        xOffset = 0.0;
        yOffset += cellSizeY;
    }

    for ( Boid* boid : _flockManager->GetBoidsList( ) )
    {
        if ( boid != nullptr )
        {
            Vec2 position = boid->GetPosition( );
            context->SetPen( *wxBLACK );
            context->SetBrush( *wxGREEN );
            dc.DrawBitmap( boid->GetIcon( ), position.x, position.y, true );
        }
    }
}