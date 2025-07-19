#include "SettingsDialog.h"

// spin control for timer
#define TIMER_INTERVAL 40000
#define NUM_BOIDS 40001
#define MAX_BOIDS 40002
#define BOID_VISION 40003
// choice controls for screen size, grid size, and cell size
#define SCREEN_SIZE 40004
#define GRID_SIZE 40005
#define CELL_SIZE 40006
// button controls
#define OK_BUTTON 40007
#define CANCEL_BUTTON 40008

BEGIN_EVENT_TABLE( SettingsDialog, wxDialog )
EVT_SPINCTRL( TIMER_INTERVAL, SettingsDialog::OnSpinControlChange )
EVT_SPINCTRL( NUM_BOIDS, SettingsDialog::OnSpinControlChange )
EVT_SPINCTRL( MAX_BOIDS, SettingsDialog::OnSpinControlChange )
EVT_SPINCTRL( BOID_VISION, SettingsDialog::OnSpinControlChange )
EVT_CHOICE( SCREEN_SIZE, SettingsDialog::OnChoiceChange )
EVT_CHOICE( GRID_SIZE, SettingsDialog::OnChoiceChange )
EVT_CHOICE( CELL_SIZE, SettingsDialog::OnChoiceChange )
EVT_BUTTON( wxID_OK, SettingsDialog::OnButtonChange )
EVT_BUTTON( wxID_CANCEL, SettingsDialog::OnButtonChange )
END_EVENT_TABLE( )

inline SettingsDialog::SettingsDialog( wxWindow* parent, wxStandardID, const wxString& title, Settings* settings ) : _settings( settings )
{

    wxBoxSizer* mainSizer = new wxBoxSizer( wxVERTICAL );
    this->SetSizer( mainSizer );

    wxBoxSizer* spinSizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* timeIntervalLabel = new wxStaticText( this, wxID_ANY, "Time Interval (ms)" );
    wxSpinCtrl* timeIntervalCtrl = new wxSpinCtrl( this, TIMER_INTERVAL, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, _settings->TimeInterval ); //up to 1 second frame rate

    wxStaticText* startingBoidsLabel = new wxStaticText( this, wxID_ANY, "Starting Boid #" );
    wxSpinCtrl* numBoids = new wxSpinCtrl( this, NUM_BOIDS, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, settings->NumBoids );

    wxStaticText* maxBoidsLabel = new wxStaticText( this, wxID_ANY, "Max Boids #" );
    wxSpinCtrl* maxBoids = new wxSpinCtrl( this, MAX_BOIDS, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, settings->MaxBoids );

    wxStaticText* boidVisionLabel = new wxStaticText( this, wxID_ANY, "Boid Vision Radius" );
    wxSpinCtrl* boidVision = new wxSpinCtrl( this, BOID_VISION, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 500, settings->BoidVision );

    spinSizer->Add( timeIntervalLabel, 0, wxALL, 5 );
    spinSizer->Add( timeIntervalCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    spinSizer->Add( startingBoidsLabel, 0, wxALL, 5 );
    spinSizer->Add( numBoids, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    spinSizer->Add( maxBoidsLabel, 0, wxALL, 5 );
    spinSizer->Add( maxBoids, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    spinSizer->Add( boidVisionLabel, 0, wxALL, 5 );
    spinSizer->Add( boidVision, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    mainSizer->Add( spinSizer, 0, wxEXPAND | wxALL, 5 );
    //=======================END SPINNERS==========================

    wxBoxSizer* choicesSizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* screenSizeLabel = new wxStaticText( this, wxID_ANY, "Screen Size" );
    wxArrayString screenSizeChoices;
    screenSizeChoices.Add( "640x480" );
    screenSizeChoices.Add( "800x600" );
    screenSizeChoices.Add( "1024x768" );
    screenSizeChoices.Add( "1280x720" );
    screenSizeChoices.Add( "1920x1080" );
    wxChoice* screenSizeChoice = new wxChoice( this, SCREEN_SIZE, wxDefaultPosition, wxDefaultSize, screenSizeChoices );
    screenSizeChoice->SetSelection( 2 );

    wxStaticText* gridSizeLabel = new wxStaticText( this, wxID_ANY, "Grid Size" );
    wxArrayString gridSizeChoices;
    gridSizeChoices.Add( "0" );
    gridSizeChoices.Add( "15" );
    gridSizeChoices.Add( "25" );
    gridSizeChoices.Add( "35" );
    gridSizeChoices.Add( "45" );
    gridSizeChoices.Add( "55" );
    gridSizeChoices.Add( "65" );
    gridSizeChoices.Add( "75" );
    gridSizeChoices.Add( "85" );
    gridSizeChoices.Add( "95" );
    wxChoice* gridSizeChoice = new wxChoice( this, GRID_SIZE, wxDefaultPosition, wxDefaultSize, gridSizeChoices );
    gridSizeChoice->SetSelection( 5 );

    wxStaticText* cellSizeLabel = new wxStaticText( this, wxID_ANY, "Cell Size" );
    wxArrayString cellSizeChoices;
    cellSizeChoices.Add( "5x5" );
    cellSizeChoices.Add( "10x10" );
    cellSizeChoices.Add( "15x15" );
    cellSizeChoices.Add( "20x20" );
    cellSizeChoices.Add( "25x25" );
    wxChoice* cellSizeChoice = new wxChoice( this, CELL_SIZE, wxDefaultPosition, wxDefaultSize, cellSizeChoices );
    cellSizeChoice->SetSelection( 1 );

    choicesSizer->Add( screenSizeLabel, 0, wxALL, 5 );
    choicesSizer->Add( screenSizeChoice, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    choicesSizer->Add( gridSizeLabel, 0, wxALL, 5 );
    choicesSizer->Add( gridSizeChoice, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    choicesSizer->Add( cellSizeLabel, 0, wxALL, 5 );
    choicesSizer->Add( cellSizeChoice, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );
    mainSizer->Add( choicesSizer, 0, wxEXPAND | wxALL, 5 );

    //=======================END CHOICES==========================

    wxBoxSizer* buttonSizer = new wxBoxSizer( wxHORIZONTAL );
    wxButton* okButton = new wxButton( this, wxID_OK, "OK" );
    wxButton* cancelButton = new wxButton( this, wxID_CANCEL, "Cancel" );
    buttonSizer->Add( okButton, 0, wxRIGHT, 5 );
    buttonSizer->Add( cancelButton, 0, wxLEFT, 5 );
    mainSizer->Add( buttonSizer, 0, wxALIGN_RIGHT | wxALL, 5 );
}

inline void SettingsDialog::OnSpinControlChange( wxSpinEvent& event )
{
    int id = event.GetId( );
    int value = event.GetValue( );
    switch ( id )
    {
        // TODO: refactor to use setters
        case TIMER_INTERVAL:
            _settings->TimeInterval = value;
            break;
        case NUM_BOIDS:
            _settings->NumBoids = value;
            break;
        case MAX_BOIDS:
            _settings->MaxBoids = value;
            break;
        case BOID_VISION:
            _settings->BoidVision = value;
            break;

        default:
            break;
    }
}

void SettingsDialog::OnChoiceChange( wxCommandEvent& event )
{
    // Handle choice change if needed
    int id = event.GetId( );
    wxString value = event.GetString( );
    switch ( id )
    {
        case SCREEN_SIZE:
            // Handle screen size change
            break;
        case GRID_SIZE:
            // Handle grid size change
            break;
        case CELL_SIZE:
            // Handle cell size change
            break;
        default:
            break;
    }
}
void SettingsDialog::OnButtonChange( wxCommandEvent& event )
{
    if ( event.GetId( ) == wxID_OK )
    {
        // Save settings and close dialog
        EndModal( wxID_OK );
    }
    else if ( event.GetId( ) == wxID_CANCEL )
    {
        // Close dialog without saving
        EndModal( wxID_CANCEL );
    }
}
