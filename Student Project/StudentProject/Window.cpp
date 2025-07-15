#pragma once
#include "Window.h"
#include "wx/wx.h"
#include "wx/display.h"


// TODO: Clean up file;

// using macros
#define PLAY_BUTTON 30001
#define PAUSE_BUTTON 30002
#define NEXT_BUTTON 30003
#define DELETE_BUTTON 30004
#define QUIT_BUTTON 30005
#define RESET_BUTTON 30006


wxBEGIN_EVENT_TABLE( MainWindow, wxFrame )
EVT_TIMER( wxID_ANY, MainWindow::OnTimerTick )
EVT_BUTTON( PLAY_BUTTON, MainWindow::OnButtonClick )
EVT_BUTTON( PAUSE_BUTTON, MainWindow::OnButtonClick )
EVT_BUTTON( NEXT_BUTTON, MainWindow::OnButtonClick )
EVT_BUTTON( RESET_BUTTON, MainWindow::OnButtonClick )
EVT_BUTTON( DELETE_BUTTON, MainWindow::OnButtonClick )
EVT_BUTTON( QUIT_BUTTON, MainWindow::OnButtonClick )
wxEND_EVENT_TABLE( )

MainWindow::MainWindow( )
    : wxFrame( nullptr, wxID_ANY, "Boids", wxDefaultPosition, wxSize( 900, 600 ) )
{
    // sizer for dynamic sizing
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    this->SetSizer( sizer );

    // panel
    _drawingPanel = new DrawingPanel( this );

    sizer->Add( _drawingPanel, 1, wxEXPAND | wxALL, 10 );

    // method Binding for dynamic resize;
    this->Bind( wxEVT_SIZE, &MainWindow::OnSizeChange, this );

    _toolBar = CreateToolBar( wxTB_VERTICAL | wxTB_RIGHT | wxTB_TEXT, wxID_ANY, "Tools" );
    _toolBar->AddTool( PLAY_BUTTON, "Play", wxBitmap( play_xpm ) );
    _toolBar->AddTool( PAUSE_BUTTON, "Pause", wxBitmap( pause_xpm ) );
    _toolBar->AddTool( NEXT_BUTTON, "Next", wxBitmap( next_xpm ) );
    _toolBar->AddTool( RESET_BUTTON, "Reset", wxBitmap( reload_arrow_xpm ) );
    _toolBar->AddTool( DELETE_BUTTON, "Delete", wxBitmap( trash_xpm ) );
    _toolBar->AddTool( QUIT_BUTTON, "Quit", wxBitmap( x_xpm ) );

    _toolBar->Realize( );

    // status bar for displaying simulation metrics;
    _statusBar = CreateStatusBar( );

    // stopwatch for displaying running time;
    _stopWatch = new wxStopWatch( );

    _timer = new wxTimer( this );
    Bind( wxEVT_TIMER, &MainWindow::OnTimerTick, this );
    _timer->Start( 16 ); // 60fps

    _simState = RUNNING; //set initial state to running for testing purposes;

    _simSpeed = 1.0;

    wxSize toolBarSize = _toolBar->GetSize( );
    wxSize statusBarSize = _statusBar->GetSize( );

    wxSize size = this->GetClientSize( );
    size.x -= toolBarSize.x;
    size.y -= statusBarSize.y; // adjust size for toolbar and status bar
    _flockManager = new FlockManager( 50, size.x, size.y );
    _drawingPanel->SetFlockManager( _flockManager );
}

MainWindow::~MainWindow( )
{
   /* delete _drawingPanel;
    delete _toolBar;
    delete _statusBar;
    delete _stopWatch;
    delete _timer;*/
    delete _flockManager;
}

void MainWindow::SimulationLoop( SimulationState& state )
{
    switch ( state )
    {
        case RUNNING:
            _timer->Start( 16 ); // restart the timer
            _flockManager->UpdateFlock( 1.0f ); // update frame
            _drawingPanel->Refresh( );
            break;
        case STOPPED:
            _timer->Stop( );
            _flockManager->UpdateFlock( 0.0f );
            _drawingPanel->Refresh( );
            break;
        case PAUSED:
            _timer->Stop( );
            break;
        case MANUAL:
            // TODO: Figure out how to advance state frame to frame;
            _flockManager->UpdateFlock( 1.0f );
            _drawingPanel->Refresh( );
            break;
        default:
            break;
    }
}

void MainWindow::OnTimerTick( wxTimerEvent& event )
{

    //SimulationState state = GetSimState( );
    SimulationLoop( _simState );
}

void MainWindow::UpdateStatusBar( wxString& status )
{
    _statusBar->SetStatusText( status );
}

void MainWindow::OnSizeChange( wxSizeEvent& event )
{
    _drawingPanel->SetSize( event.GetSize( ) );
    Refresh( );
    event.Skip( );
}

void MainWindow::OnButtonClick( wxCommandEvent& event )
{
    switch ( event.GetId( ) )
    {
        case PLAY_BUTTON:

            SetSimState( RUNNING );
            _timer->Start( 16 ); // start the timer

            break;

        case PAUSE_BUTTON:

            SetSimState( PAUSED );
            break;

        case NEXT_BUTTON:
            SetSimState( MANUAL );
            break;

        case RESET_BUTTON:
            SetSimState( STOPPED );
            // Reset the flock manager
            break;

        case DELETE_BUTTON:

            break;

        case QUIT_BUTTON:
            Close( true );
            break;
        default:
            break;
    }
};