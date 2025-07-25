#include "FlockControlPanel.h"


FlockControlPanel::FlockControlPanel( wxWindow* parent, wxWindowID id, FlockManager* flockManager )
    : wxPanel( parent, id ), _flockManager( flockManager )
{
    wxBoxSizer* panelSizer = new wxBoxSizer( wxHORIZONTAL );
    wxStaticText* alignmentLabel = new wxStaticText( this, wxID_ANY, "Alignment:" );
    _alignmentCtrl = new wxSpinCtrlDouble( this, ALIGNMENT_SPIN_CTRL,
                                           wxEmptyString,
                                           wxDefaultPosition,
                                           wxSize( 75, -1 ),
                                           wxSP_ARROW_KEYS,
                                           0.0, 1, _flockManager->GetAlignmentFactor( ), 0.01 );
    wxStaticText* cohesionLabel = new wxStaticText( this, wxID_ANY, "Cohesion:" );
    _cohesionCtrl = new wxSpinCtrlDouble( this, COHESION_SPIN_CTRL,
                                          wxEmptyString,
                                          wxDefaultPosition,
                                          wxSize( 75, -1 ),
                                          wxSP_ARROW_KEYS,
                                          0.0, 1, _flockManager->GetCohesionFactor( ), 0.01 );
    wxStaticText* separationLabel = new wxStaticText( this, wxID_ANY, "Separation:" );
    _separationCtrl = new wxSpinCtrlDouble( this, SEPARATION_SPIN_CTRL,
                                            wxEmptyString,
                                            wxDefaultPosition,
                                            wxSize( 75, -1 ),
                                            wxSP_ARROW_KEYS,
                                            0.0, 1, _flockManager->GetSeparationFactor( ), 0.01 );
    wxStaticText* visionLabel = new wxStaticText( this, wxID_ANY, "Vision Range:" );
    _visionCtrl = new wxSpinCtrlDouble( this, VISION_SPIN_CTRL,
                                        wxEmptyString,
                                        wxDefaultPosition,
                                        wxSize( 50, -1 ),
                                        wxSP_ARROW_KEYS,
                                        0, 200.0, _flockManager->GetVisionFactor( ), 10 );
    wxStaticText* speedLabel = new wxStaticText( this, wxID_ANY, "Speed:" );
    _speedCtrl = new wxSpinCtrlDouble( this, SPEED_SPIN_CTRL,
                                       wxEmptyString,
                                       wxDefaultPosition,
                                       wxSize( 50, -1 ),
                                       wxSP_ARROW_KEYS,
                                       0.2, 10, _flockManager->GetSpeedFactor( ), .2 );
    wxStaticText* countLabel = new wxStaticText( this, wxID_ANY, "Boid Count:" );
    _boidCountCtrl = new wxSpinCtrl( this, BOID_COUNT_SPIN_CTRL,
                                     wxEmptyString,
                                     wxDefaultPosition,
                                     wxSize( 50, -1 ),
                                     wxSP_ARROW_KEYS,
                                     0, 1000, _flockManager->GetNumBoids( ) );


    panelSizer->Add( alignmentLabel, 0, wxALL, 5 );
    panelSizer->Add( _alignmentCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    panelSizer->Add( cohesionLabel, 0, wxALL, 5 );
    panelSizer->Add( _cohesionCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    panelSizer->Add( separationLabel, 0, wxALL, 5 );
    panelSizer->Add( _separationCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    panelSizer->Add( visionLabel, 0, wxALL, 5 );
    panelSizer->Add( _visionCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    panelSizer->Add( speedLabel, 0, wxALL, 5 );
    panelSizer->Add( _speedCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    panelSizer->Add( countLabel, 0, wxALL, 5 );
    panelSizer->Add( _boidCountCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5 );

    SetSizer( panelSizer );

    // bind methods is easier than using event table but I like event tables for increased readability;
    _alignmentCtrl->Bind( wxEVT_SPINCTRLDOUBLE, &FlockControlPanel::OnSpinCtrlChange, this );
    _cohesionCtrl->Bind( wxEVT_SPINCTRLDOUBLE, &FlockControlPanel::OnSpinCtrlChange, this );
    _separationCtrl->Bind( wxEVT_SPINCTRLDOUBLE, &FlockControlPanel::OnSpinCtrlChange, this );
    _visionCtrl->Bind( wxEVT_SPINCTRLDOUBLE, &FlockControlPanel::OnSpinCtrlChange, this );
    _speedCtrl->Bind( wxEVT_SPINCTRLDOUBLE, &FlockControlPanel::OnSpinCtrlChange, this );
    _boidCountCtrl->Bind( wxEVT_SPINCTRL, &FlockControlPanel::OnSpinCtrlInt, this );
}

void FlockControlPanel::OnSpinCtrlChange( wxSpinDoubleEvent& event )
{
    int id = event.GetId( );
    double value = event.GetValue( );

    switch ( id )
    {
        case ALIGNMENT_SPIN_CTRL:
            _flockManager->SetAlignmentFactor( value );
            break;
        case COHESION_SPIN_CTRL:
            _flockManager->SetCohesionFactor( value );
            break;
        case SEPARATION_SPIN_CTRL:
            _flockManager->SetSeparationFactor( value );
            break;
        case VISION_SPIN_CTRL:
            _flockManager->SetVisionFactor( value );
            break;
        case SPEED_SPIN_CTRL:
            _flockManager->SetSpeedFactor( value );
            break;
        default:
            break;
    }
}

void FlockControlPanel::OnSpinCtrlInt( wxSpinEvent& event )
{
    if ( event.GetId( ) == BOID_COUNT_SPIN_CTRL )
    {
        int newCount = event.GetValue( );
        int currentCount = _flockManager->GetNumBoids( );

        if ( newCount > currentCount )
        {
            _flockManager->AddBoids( newCount - currentCount );
        }
        else if ( newCount < currentCount )
        {
            _flockManager->RemoveBoids( currentCount - newCount );
        }
    }
}