#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "x.xpm"

#include "reload_arrow.xpm"
#include "FlockManager.h"
// TODO: Clean up file;

class MainWindow : public wxFrame
{
public:
    MainWindow( );
    ~MainWindow( );


private:
    enum SimulationState
    {
        RUNNING,
        PAUSED,
        MANUAL,
        STOPPED
    };

    // game panel
    DrawingPanel* _drawingPanel = nullptr;
    FlockManager* _flockManager = nullptr;
    wxTimer* _timer = nullptr;

    // toolbar
    wxToolBar* _toolBar = nullptr;


    //status bar
    wxStatusBar* _statusBar = nullptr;
    wxStopWatch* _stopWatch = nullptr; // for displaying running time of each round;

    int _boidCount = 0; // number of boids on screen;
    float _simSpeed = 1.0; // ratio for simulation speed; 

    SimulationState _simState = STOPPED; // Display the simulation state Stopped / Running / Manual;
    SimulationState GetSimState( ) { return _simState; }
    void SimulationLoop( SimulationState& state );

    void SetSimState( SimulationState state )
    {
        _simState = state;
    };
    void SetFlockManager( FlockManager* manager ) { _flockManager = manager; };
    void OnTimerTick( wxTimerEvent& event );
    void UpdateStatusBar( wxString& status );
    void OnSizeChange( wxSizeEvent& event );
    void OnButtonClick( wxCommandEvent& event );
    //void OnSize( wxSizeEvent& event );
    //void OnPaint( wxPaintEvent& event );
    wxDECLARE_EVENT_TABLE( );
};
