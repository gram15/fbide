///////////////////////////////////////////////////////////////////////////////
//// Name:        fb_tab.cpp
//// Purpose:     
//// Author:      VonGodric
//// Modified by: 
//// Created:     08/03/05 14:23:04
//// RCS-ID:      
//// Copyright:   
//// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////
//
//
//#include "inc/wxall.h"
//#include "inc/wxmynotebook.h"
//
//#include "inc/fb_frame.h"
//#include "inc/fb_stc.h"
//#include "inc/fb_doc.h"
//#include "inc/fb_config.h"
//#include "inc/fb_docmngr.h"
//
//FB_DocMngr::FB_DocMngr( FB_Frame * parent, FB_Config * config )
//{
//    //this->Create( parent );
////    AddChild( new wxPanel( this, -1 ) );
//}
//
//FB_DocMngr::~FB_DocMngr(  )
//{
//    
//}
//
//void FB_DocMngr::AddPage( wxWindow * page )
//{
//    
//}
//
//void FB_DocMngr::ClosePage( int idx )
//{
//    
//}
//
//void FB_DocMngr::ClosePages( int idx[] )
//{
//    
//}
//
//void FB_DocMngr::CloseAll(  )
//{
//    
//}
//
////void FB_DocMngr::Show( bool status )
////{
////    
////}
//
//wxWindow * FB_DocMngr::GetPage()
//{
//    
//}
//
//
//
////
////FB_DocMngr::FB_DocMngr( FB_Frame * parent, FB_Config * config ) 
////{
////    Config = config;
////    Parent = parent;
////    tablimit = Config->TabLimit;
////    tab = NULL;
////    Show( false );
////    tabcount = 0;
////    tabvis = 0;
////}
////
////FB_DocMngr::~FB_DocMngr() 
////{
////    if ( tab ) delete tab;
////}
////
////void FB_DocMngr::Create( wxWindow* parent )
////{
////    tab = new wxMyNotebook( parent, wxID_ANY, 
////        wxDefaultPosition, wxDefaultSize, 
////        wxNO_FULL_REPAINT_ON_RESIZE|wxCLIP_CHILDREN|wxBC_DEFAULT );
////}
////
////FB_STC *  FB_DocMngr::GetPage (  ) 
////{ 
////    return tabcount ? ((FB_STC *)tab->GetCurrentPage()) : 0; 
////}
////
////void FB_DocMngr::AddPage()
////{
////    
////    if ( NewPageVeto() ) return;
////    
////    Show( true );
////    tabcount++;
////    wxString name;
////    name = "UnTitled ";
////    name << tab->GetPageCount();
////    page = new FB_STC_FB( tab, NULL, Config );
////    tab->AddPage( page, name, true );
////    tabvis = tab->GetSelection();
////}
////
////
////bool FB_DocMngr::NewPageVeto(  )
////{
////    if( tablimit&&tabcount >= tablimit ) 
////    {
////        wxMessageBox( _("Tab limit reached!") );
////        return true;
////    }
////    return false;
////}
////
////
////void FB_DocMngr::Show( bool status ) {
////    
////    if(!status) {
////        wxWindow * old = Parent->Code_area;
////        if ( tab ) { if ( old!=tab ) return; }
////        Parent->Code_area = new wxPanel( Parent->VSplitter, wxID_ANY,
////                    wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
////        Parent->Code_area->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ));
////        if ( old ) {
////            Parent->VSplitter->ReplaceWindow( old, Parent->Code_area );
////            delete (wxMyNotebook*)old;
////            tab = 0;
////        }
////    }
////    else
////    {
////        if ( tab ) return;
////        Create( Parent->VSplitter );
////        Parent->VSplitter->ReplaceWindow( Parent->Code_area, tab );
////        delete (wxPanel*)Parent->Code_area;
////        Parent->Code_area = tab;
////    }
////}
////
////
////void FB_DocMngr::ClosePage( int idx  )
////{
////    if ( !tab ) return;
////    if ( idx == -1 ) idx = tab->GetSelection();
////    tab->DeletePage( idx );
////    tabcount--;
////    if ( tabcount == 0 ) Show( false );
////    
////    return;
////}
////
////
////void FB_DocMngr::ClosePages( int idx[] )
////{
////    if ( !tab ) return;
////    return;
////}
////
////
////void FB_DocMngr::CloseAll()
////{
////    if ( !tab ) return;
////}
//
