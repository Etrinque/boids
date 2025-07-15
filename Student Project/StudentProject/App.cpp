#include "App.h"
#include "Window.h"
wxIMPLEMENT_APP( App );

App::App( ) :_main_window( nullptr )
{

}

App::~App( )
{

}

bool App::OnInit( )
{
    _main_window = new MainWindow( );
    _main_window->CenterOnScreen( );
    _main_window->Show( );
    return true;

}