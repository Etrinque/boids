#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include "wx/spinctrl.h"

class SettingsDialog :
    public wxDialog
{
public:
    SettingsDialog( wxWindow* parent, wxStandardID = wxID_ANY, const wxString& title, Settings* settings );;

    int GetTimeInterval( ) const { return _settings->TimeInterval; };
    Vec2 GetScreenSize( ) const { return _settings->ScreenSize; };
    int GetGridSize( ) const { return _settings->GridSize; };
    Vec2 GetCellSize( ) const { return _settings->CellSize; };
    int GetNumBoids( ) const { return _settings->NumBoids; };
    int GetMaxBoids( ) const { return _settings->MaxBoids; };
    int GetBoidVision( ) const { return _settings->BoidVision; };

private:
    Settings* _settings;

    void OnSpinControlChange( wxSpinEvent& event );
    void OnChoiceChange( wxCommandEvent& event );
    void OnButtonChange( wxCommandEvent& event );
    DECLARE_EVENT_TABLE( )
};

