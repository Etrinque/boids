#include "DrawingPanel.h"
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "wx/font.h"

DrawingPanel::DrawingPanel( wxFrame* parent ) : wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
{
    this->SetBackgroundStyle( wxBG_STYLE_PAINT );
    this->Bind( wxEVT_PAINT, &DrawingPanel::OnPaint, this );
}

DrawingPanel::~DrawingPanel( ) {};

void DrawingPanel::OnPaint( wxPaintEvent& event )
{
    wxAutoBufferedPaintDC dc( this );
    dc.Clear( );

    wxGraphicsContext* context = wxGraphicsContext::Create( dc );

    if ( !context ) return;
    context->SetPen( *wxLIGHT_GREY );

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

            position.x = std::min( position.x, GetClientSize( ).x - boid->GetBoidSize( ) ); // temp fix for overdraw
            position.y = std::min( position.y, GetClientSize( ).y - boid->GetBoidSize( ) ); // temp fix for overdraw

            wxBitmap rotatedIcon = boid->GetRotatedIcon( );

            dc.DrawBitmap( rotatedIcon, position.x, position.y, true );
        }
    }

    if ( _isHudShown )
    {
        dc.SetFont( wxFontInfo( 12 ).Bold( ) );

        wxSize size = this->GetClientSize( );

        wxString hudText = wxString::Format(
            "World Size: %d x %d\n"
            "Boids: %d\n",
            size.GetWidth( ), size.GetHeight( ),
            _flockManager->GetNumBoids( )
        );

        wxSize textSize = dc.GetTextExtent( hudText );

        //// Draw black background for better readability
        //dc.SetBrush( wxBrush( wxColour( 0, 0, 0, 128 ) ) ); // Semi-transparent black
        //dc.SetPen( *wxTRANSPARENT_PEN );
        //dc.DrawRectangle( 10, size.GetHeight( ) - textSize.GetHeight( ) - 20,
        //                  textSize.GetWidth( ) + 20, textSize.GetHeight( ) + 10 );

         // Draw text at the bottom left corner with padding
        dc.DrawText( hudText, 20, size.GetHeight( ) - textSize.GetHeight( ) - 15 );
    }


}