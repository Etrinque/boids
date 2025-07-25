#pragma once
#include "Window.h"
#include "wx/wx.h"
#include "wx/display.h"
#include "wx/spinctrl.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>
#include "Helper.h"
// TODO: Clean up file;

// using macros
#define TIMER 30000
#define PLAY_BUTTON 30001
#define PAUSE_BUTTON 30002
#define NEXT_BUTTON 30003
#define DELETE_BUTTON 30004
#define QUIT_BUTTON 30005
#define RESET_BUTTON 30006
#define ADD_BOIDS_SCROLL 30007
#define SETTINGS_MENU 30008
#define FILE_MENU 30009
#define ID_IMPORT 30010
#define SETTINGS_MENU_RESET 30011
#define VIEW_HUD 30012

wxBEGIN_EVENT_TABLE( MainWindow, wxFrame )
EVT_TIMER( TIMER, MainWindow::OnTimerTick )
EVT_TOOL( PLAY_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( PAUSE_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( NEXT_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( RESET_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( DELETE_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( QUIT_BUTTON, MainWindow::OnButtonClick )
EVT_TOOL( ADD_BOIDS_SCROLL, MainWindow::OnButtonClick )
EVT_MENU( SETTINGS_MENU, MainWindow::OnSettingsButtonClick )
EVT_MENU( SETTINGS_MENU_RESET, MainWindow::OnSettingsButtonClick )
EVT_MENU( wxID_NEW, MainWindow::OnFileButtonClick )
EVT_MENU( wxID_OPEN, MainWindow::OnFileButtonClick )
EVT_MENU( ID_IMPORT, MainWindow::OnFileButtonClick )
EVT_MENU( wxID_SAVEAS, MainWindow::OnFileButtonClick )
EVT_MENU( wxID_SAVE, MainWindow::OnFileButtonClick )
EVT_MENU( wxID_EXIT, MainWindow::OnFileButtonClick )
EVT_MENU( VIEW_HUD, MainWindow::OnViewButtonClick )
wxEND_EVENT_TABLE( )

MainWindow::MainWindow( )
    : wxFrame( nullptr, wxID_ANY, "Boids", wxDefaultPosition, wxSize( 1024, 768 ) )
{
    wxMenuBar* menuBar = new wxMenuBar( );

    wxMenu* fileMenu = new wxMenu( );
    fileMenu->Append( wxID_NEW, "New", "Create a new simulation" );
    fileMenu->Append( wxID_OPEN, "Open", "Open an existing simulation" );
    fileMenu->Append( ID_IMPORT, "Import", "Save the current simulation" );
    fileMenu->Append( wxID_SAVEAS, "Save As", "Save the current simulation with a new name" );
    fileMenu->Append( wxID_SAVE, "Save", "Save the current simulation" );
    fileMenu->Append( wxID_EXIT, "Exit", "Exit the application" );
    menuBar->Append( fileMenu, "File" );


    wxMenu* settingsMenu = new wxMenu( );
    settingsMenu->Append( SETTINGS_MENU, "Settings" );
    settingsMenu->Append( SETTINGS_MENU_RESET, "Reset Settings", "Reset settings to default values" );
    menuBar->Append( settingsMenu, "Settings" );

    wxMenu* viewMenu = new wxMenu( );
    viewMenu->AppendCheckItem( VIEW_HUD, "Show Hud", "Overlay the HUD display" );
    viewMenu->Check( VIEW_HUD, _settings.HudShown );
    menuBar->Append( viewMenu, "View" );

    this->SetMenuBar( menuBar );

    _settings.LoadSettings( );

    this->SetSize( _settings.ScreenSize.x, _settings.ScreenSize.y );

    // sizer for dynamic sizing
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    _toolBar = CreateToolBar( wxTB_HORIZONTAL | wxTB_TEXT, wxID_ANY, "Tools" );

    _toolBar->AddTool( PLAY_BUTTON, "Play", wxBitmap( play_xpm ) );
    _toolBar->SetToolShortHelp( PLAY_BUTTON, "Start the simulation" );

    _toolBar->AddTool( PAUSE_BUTTON, "Pause", wxBitmap( pause_xpm ) );
    _toolBar->SetToolShortHelp( PAUSE_BUTTON, "Pause the simulation" );

    _toolBar->AddTool( NEXT_BUTTON, "Next", wxBitmap( next_xpm ) );
    _toolBar->SetToolShortHelp( NEXT_BUTTON, "Advance the simulation by one frame" );

    _toolBar->AddTool( RESET_BUTTON, "Reset", wxBitmap( reload_arrow_xpm ) );
    _toolBar->SetToolShortHelp( RESET_BUTTON, "Reset the simulation" );

    _toolBar->AddTool( DELETE_BUTTON, "Delete", wxBitmap( trash_xpm ) );

    _toolBar->AddTool( QUIT_BUTTON, "Quit", wxBitmap( x_xpm ) );
    _toolBar->SetToolShortHelp( QUIT_BUTTON, "Quit the application" );

    _toolBar->Realize( );

    // status bar for displaying simulation metrics;
    _statusBar = CreateStatusBar( );
    _statusBar->SetStatusText( "Boids Simulation" );

    wxSize statusBarSize = _statusBar->GetSize( );

    _drawingPanel = new DrawingPanel( this );
    wxSize clientSize = this->GetClientSize( );
    int maxWidth = clientSize.x;
    int maxHeight = clientSize.y - statusBarSize.y;
    _drawingPanel->SetGridSize( _settings.GridSize );
    _drawingPanel->SetCellSize( _settings.CellSize );
    _drawingPanel->IsHudShown( _settings.HudShown );

    _flockManager = new FlockManager( _settings.NumBoids, maxWidth, maxHeight );
    _drawingPanel->SetFlockManager( _flockManager );

    // flock controls panel
    _controlPanel = new FlockControlPanel( this, wxID_ANY, _flockManager );

    sizer->Add( _controlPanel, 0, wxEXPAND | wxALL, 5 );
    sizer->Add( _drawingPanel, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    // stopwatch for displaying running time; TODO: make it functional
    _stopWatch = new wxStopWatch( );
    _stopWatch->Pause( );

    // timer for simulation loop
    _timer = new wxTimer( this, TIMER );


    this->Bind( wxEVT_SIZE, &MainWindow::OnSizeChange, this );
    this->SetSizer( sizer );
    this->Layout( );
}

MainWindow::~MainWindow( )
{
    delete _flockManager;
    _settings.SaveSettings( );
}

void MainWindow::SimulationLoop( SimulationState& state )
{
    switch ( state )
    {
        case RUNNING:
            _flockManager->UpdateFlock( _simSpeed );
            _drawingPanel->Refresh( );
            break;
        case PAUSED:
            _timer->Stop( );
            _drawingPanel->Refresh( );
            break;
        case MANUAL:
            // logic for manual step is in button click handler
            //TODO: refactor and move logic to here;
            break;
        case STOPPED:
            SetSimSpeed( 0 );
            _timer->Stop( );
            _stopWatch->Pause( ); // pause the stopwatch
            _flockManager->UpdateFlock( _simSpeed );
            _drawingPanel->Refresh( );
            break;
        default:
            break;
    }
}

void MainWindow::OnTimerTick( wxTimerEvent& event )
{
    SimulationLoop( _simState );
    UpdateStatusBar( );
    event.Skip( );
}

void MainWindow::UpdateStatusBar( )
{
    wxSize size = this->GetClientSize( );
    wxString status = wxString::Format( "Boids: %d | State: %s | Speed: %.2f | Elapsed: %ld/s | Grid Size: X = %d, Y = %d", _flockManager->GetNumBoids( ), GetSimStateString( ), _simSpeed, _stopWatch->Time( ) / 1000, size.x, size.y );
    _statusBar->SetStatusText( status );

}

void MainWindow::OnSizeChange( wxSizeEvent& event )
{
    int statusBarSize = _statusBar->GetSize( ).GetHeight( );

    wxSize size = this->GetClientSize( );

    _flockManager->SetBoundary( size.x, size.y - statusBarSize );
    this->Layout( );
    _drawingPanel->Refresh( );

    event.Skip( );
}

void MainWindow::OnButtonClick( wxCommandEvent& event )
{
    switch ( event.GetId( ) )
    {
        case PLAY_BUTTON:
            if ( _simState != RUNNING )
            {
                _stopWatch->Start( );
            }
            SetSimState( RUNNING );
            if ( !_timer->IsRunning( ) )
            {
                _timer->Start( 16 );
            }
            break;

        case PAUSE_BUTTON:
            SetSimState( PAUSED );
            _stopWatch->Pause( );
            break;

        case NEXT_BUTTON:
            SetSimState( MANUAL );
            if ( !_timer->IsRunning( ) )
            {
                _stopWatch->Start( ); // start the stopwatch
                _timer->Start( 16 / _simSpeed );
                _flockManager->UpdateFlock( 1.0f );
                _drawingPanel->Refresh( );
                _timer->Stop( ); // stop the timer to prevent continuous updates
            }
            break;

        case RESET_BUTTON:
            SetSimState( STOPPED );
            _stopWatch->Pause( );
            _timer->Stop( );
            _flockManager->RemoveBoids( _flockManager->GetNumBoids( ) );
            _flockManager->SetNumBoids( 0 );
            _controlPanel->ResetControls( );
            _drawingPanel->Refresh( );

            break;

        case DELETE_BUTTON:
            _flockManager->RemoveBoid( ); // pop off last Boid 
            break;

        case QUIT_BUTTON:
            Close( true );
            break;

        default:
            event.Skip( );
            break;
    }
};

void MainWindow::OnSettingsButtonClick( wxCommandEvent& event )
{
    switch ( event.GetId( ) )
    {
        case SETTINGS_MENU:
        {
            SettingsDialog dialog( this, &_settings );
            dialog.ShowModal( );
            event.Skip( );
            break;
        }

        case SETTINGS_MENU_RESET:
        {
            _settings.ResetSettings( );
            _drawingPanel->SetGridSize( _settings.GridSize );
            _drawingPanel->SetCellSize( _settings.CellSize );
            _drawingPanel->Refresh( );
            _settings.SaveSettings( );
            event.Skip( );
            break;
        }
    };
}

void MainWindow::OnFileButtonClick( wxCommandEvent& event )
{
    switch ( event.GetId( ) )
    {
        case wxID_NEW:
        {

            _flockManager->RemoveBoids( _flockManager->GetNumBoids( ) );
            _flockManager->SetNumBoids( 0 );
            _stopWatch->Pause( ); // stop the stopwatch. still busted...
            SetSimState( STOPPED );
            _timer->Stop( ); // stop time
            _drawingPanel->Refresh( );
            _controlPanel->ResetControls( ); // reset controls to default values
            break;
        }
        case wxID_OPEN:
        {
            wxFileDialog FileDialog( this, "Open Simulation", "", "", "Simulation File (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST );

            if ( FileDialog.ShowModal( ) == wxID_CANCEL )
            {
                return; // User cancelled the dialog
            }

            wxString filePath = FileDialog.GetPath( );
            SetSaveFileName( filePath.AfterLast( '\\' ) ); //only works on windows??

            if ( filePath.IsEmpty( ) )
            {
                wxLogError( "No file selected." );
                return;
            }
            std::ifstream file( filePath.ToStdString( ) );
            if ( !file.is_open( ) )
            {
                wxLogError( "Could not open file: %s", filePath );
                return;
            }

            _flockManager->RemoveBoids( _flockManager->GetNumBoids( ) );
            _drawingPanel->Refresh( );

            std::string line;
            do
            {
                if ( line.empty( ) ) continue;

                std::istringstream inputStream( line );
                float posX, posY, velX, velY;

                char commaDelim = ',';


                if ( inputStream >> posX >> commaDelim >> posY >> velX >> commaDelim >> velY )
                {
                    Boid* boid = new Boid( Vec2( posX, posY ), Vec2( velX, velY ) );
                    _flockManager->AddBoid( boid );

                }
                else
                {
                    wxLogError( "Error reading line: %s", line );
                    continue; //skip
                }

            } while ( !std::getline( file, line ).eof( ) );
            _drawingPanel->Refresh( );
            break;
        }
        case ID_IMPORT:
        {

            wxFileDialog FileDialog( this, "Import Simulation", "", "", "Simulation File (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST );

            if ( FileDialog.ShowModal( ) == wxID_CANCEL )
            {
                return; // User cancelled the dialog
            }
            wxString filePath = FileDialog.GetPath( );

            if ( filePath.IsEmpty( ) )
            {
                wxLogError( "No file seelcted." );
                return;
            }

            std::ifstream file( filePath.ToStdString( ) );
            if ( !file.is_open( ) )
            {
                wxLogError( "Could not open file: %s", filePath );
                return;
            }
            _flockManager->RemoveBoids( _flockManager->GetNumBoids( ) );
            _drawingPanel->Refresh( );
            std::string line;
            do
            {
                if ( line.empty( ) ) continue;
                std::istringstream inputStream( line );
                float posX, posY, velX, velY;
                char commaDelim = ',';

                if ( inputStream >> posX >> commaDelim >> posY >> velX >> commaDelim >> velY )
                {

                    if ( posX > _flockManager->GetBoundary( ).x || posX < 0 )
                    {
                        Helper::ClampFloat( &posX, 0.0f, _flockManager->GetBoundary( ).x );
                    }
                    if ( posY > _flockManager->GetBoundary( ).y or posY < 0 )
                    {
                        Helper::ClampFloat( &posY, 0.0f, _flockManager->GetBoundary( ).y );
                    }

                    Boid* boid = new Boid( Vec2( posX, posY ), Vec2( velX, velY ) );
                    _flockManager->AddBoid( boid );

                    // ignore velocity I only care about positional adjustments.

                }
                else
                {
                    wxLogError( "Error reading line: %s", line );
                    continue; //skip
                }
            } while ( !std::getline( file, line ).eof( ) );

            break;
        }
        case wxID_SAVEAS:
        {
            wxFileDialog FileDialog( this, "Save Simulation", "", "", "Simulation File (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

            FileDialog.ShowModal( );
            wxString filePath = FileDialog.GetPath( );

            SetSaveFileName( filePath.AfterLast( '\\' ) );

            if ( !filePath.IsEmpty( ) )
            {
                std::ofstream file( filePath.ToStdString( ) );
                if ( !file.is_open( ) )
                {
                    wxLogError( "Could not open file for saving: %s", filePath );
                    return;
                }

                std::vector<Boid*> boids = _flockManager->GetBoidsList( );

                for ( Boid* boid : boids )
                {
                    if ( boid != nullptr )
                    {
                        file << boid->GetPosition( ).x << "," << boid->GetPosition( ).y << " "
                            << boid->GetVelocity( ).x << "," << boid->GetVelocity( ).y << "\n";
                    }
                }
                file.close( );
            }
            break;
        }

        case wxID_SAVE:
            if ( !_saveFileName.empty( ) )
            {
                std::ofstream file( _saveFileName );
                if ( !file.is_open( ) )
                {
                    wxLogError( "Could not open file for saving: %s", _saveFileName );
                    return;
                }
                std::vector<Boid*> boids = _flockManager->GetBoidsList( );
                for ( Boid* boid : boids )
                {
                    if ( boid != nullptr )
                    {
                        file << boid->GetPosition( ).x << "," << boid->GetPosition( ).y << " "
                            << boid->GetVelocity( ).x << "," << boid->GetVelocity( ).y << "\n";
                    }
                }
                file.close( );
            }
            break;

        case wxID_EXIT:
            Close( true );
            break;
        default:
            event.Skip( );
            break;
    }
}

void MainWindow::OnViewButtonClick( wxCommandEvent& event )
{
    switch ( event.GetId( ) )
    {
        case VIEW_HUD:
        {

            _settings.HudShown = !_settings.HudShown;

            wxMenuItem* hudCheck = GetMenuBar( )->FindItem( VIEW_HUD );
            if ( hudCheck )
            {
                hudCheck->Check( _settings.HudShown );
            }
            _drawingPanel->SetHudShown( _settings.HudShown );
            _settings.SaveSettings( );
            break;
        }
        default:
            event.Skip( );
            break;
    }
}