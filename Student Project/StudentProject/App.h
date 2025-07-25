#pragma once

#include "wx/wx.h"
#include <ctime>
#include "Window.h"

class App : public wxApp
{
private:
    MainWindow* _main_window;
public:
    App( );
    ~App( );
    virtual bool OnInit( );
};

