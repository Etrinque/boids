#include "App.h"
#include "Utilities.h"
#include "Window.h"
wxIMPLEMENT_APP( App );

App::App( ) :_main_window( nullptr )
{

}

App::~App( )
{
    delete _main_window;
}

bool App::OnInit( )
{

    ENABLE_LEAK_DETECTION( );
    _main_window = new MainWindow( );
    _main_window->CenterOnScreen( );
    _main_window->Show( );
    return true;
}