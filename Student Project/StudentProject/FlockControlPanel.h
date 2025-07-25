#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "FlockManager.h"

// Control IDs for spin controls
#define ALIGNMENT_SPIN_CTRL 30008
#define COHESION_SPIN_CTRL 30009
#define SEPARATION_SPIN_CTRL 30010
#define VISION_SPIN_CTRL 30011
#define SPEED_SPIN_CTRL 30012
#define BOID_COUNT_SPIN_CTRL 30013

class FlockControlPanel :
    public wxPanel
{
public:
    FlockControlPanel( wxWindow* parent, wxWindowID id, FlockManager* flockManager );
    virtual ~FlockControlPanel( ) {}


    double GetAlignmentValue( ) const
    {
        if ( _alignmentCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _alignmentCtrl->GetValue( );
    }
    double GetCohesionValue( ) const
    {
        if ( _cohesionCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _cohesionCtrl->GetValue( );
    }
    double GetSeparationValue( ) const
    {
        if ( _separationCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _separationCtrl->GetValue( );
    }
    double GetVisionValue( ) const
    {
        if ( _visionCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _visionCtrl->GetValue( );
    }
    double GetSpeedValue( ) const
    {
        if ( _speedCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _speedCtrl->GetValue( );
    }
    int GetBoidCount( ) const
    {
        if ( _boidCountCtrl == nullptr )
        {
            return 0.0;  // Return a default value if the control is not initialized
        }
        return _boidCountCtrl->GetValue( );
    }


    void SetAlignmentValue( double value ) { _alignmentCtrl->SetValue( value ); }
    void SetCohesionValue( double value ) { _cohesionCtrl->SetValue( value ); }
    void SetSeparationValue( double value ) { _separationCtrl->SetValue( value ); }
    void SetVisionValue( double value ) { _visionCtrl->SetValue( value ); }
    void SetSpeedValue( double value ) { _speedCtrl->SetValue( value ); }
    void SetBoidCount( int count ) { _boidCountCtrl->SetValue( count ); }
    void ResetControls( )
    {
        SetAlignmentValue( 0.01 );
        SetCohesionValue( 0.01 );
        SetSeparationValue( 0.2 );
        SetVisionValue( 25 );
        SetSpeedValue( 1.0 );
        SetBoidCount( 0 );
    }
private:
    wxSpinCtrlDouble* _alignmentCtrl;
    wxSpinCtrlDouble* _cohesionCtrl;
    wxSpinCtrlDouble* _separationCtrl;
    wxSpinCtrlDouble* _visionCtrl;
    wxSpinCtrlDouble* _speedCtrl;
    wxSpinCtrl* _boidCountCtrl;

    FlockManager* _flockManager;

    void OnSpinCtrlChange( wxSpinDoubleEvent& event );
    void OnSpinCtrlInt( wxSpinEvent& event );
};

