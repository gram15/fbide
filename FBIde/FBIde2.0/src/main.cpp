#include "inc/manager.h"
#include "inc/main.h"


BEGIN_EVENT_TABLE(Main, wxFrame)
    EVT_CLOSE(Main::OnClose)
END_EVENT_TABLE()



Main::Main()
    : wxFrame(NULL, wxID_ANY, _T("FBIde"))
{

}


Main::~Main()
{
}

/**
 * This means that we want to exit FBIde
 * @todo - first generate FBIde notification
 *         event about exiting!
 */
void Main::OnClose (wxCloseEvent & event)
{
    Manager::Get()->ShutDown();
    event.Skip();
}
