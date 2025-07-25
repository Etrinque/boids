#pragma once
#include "wx/wx.h"
#include <string>
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "x.xpm"
#include "reload_arrow.xpm"
#include "FlockManager.h"
#include "FlockControlPanel.h"
#include "SettingsDialog.h"
#include "Settings.h"
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
    FlockControlPanel* _controlPanel = nullptr;
    wxTimer* _timer = nullptr;

    std::string _saveFileName; // for storing saveFile name in mem

    // toolbar
    wxToolBar* _toolBar = nullptr;

    Settings _settings; // settings for the simulation;

    //status bar
    wxStatusBar* _statusBar = nullptr;
    wxStopWatch* _stopWatch = nullptr; // for displaying running time of each round;

    //int _boidCount = 0; // number of boids on screen;
    float _simSpeed = 1.0;

    SimulationState _simState = STOPPED;
    SimulationState GetSimState( ) { return _simState; }
    std::string GetSimStateString( )
    {
        switch ( _simState )
        {
            case RUNNING: return "Running";
            case PAUSED: return "Paused";
            case MANUAL: return "Manual";
            case STOPPED: return "Stopped";
            default: return "Unknown";
        }
    }
    void SimulationLoop( SimulationState& state );
    void SetSimSpeed( float speed )
    {
        _simSpeed = speed;
    };
    void SetSimState( SimulationState state )
    {
        _simState = state;
    };
    void SetFlockManager( FlockManager* manager ) { _flockManager = manager; };
    void SetSaveFileName( const wxString& fileName )
    {
        _saveFileName = fileName;
    };
    void OnTimerTick( wxTimerEvent& event );
    void UpdateStatusBar( );
    void OnSizeChange( wxSizeEvent& event );
    void OnButtonClick( wxCommandEvent& event );
    void OnSettingsButtonClick( wxCommandEvent& event );
    void OnFileButtonClick( wxCommandEvent& event );
    void OnViewButtonClick( wxCommandEvent& event );

    wxDECLARE_EVENT_TABLE( );
};
