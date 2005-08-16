/////////////////////////////////////////////////////////////////////////////
// Name:        fb_stc.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"
#include "inc/fb_doc.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"



BEGIN_EVENT_TABLE (FB_STC, wxStyledTextCtrl)
    EVT_STC_CHARADDED   (-1,                FB_STC::OnCharAdded)
END_EVENT_TABLE()


FB_STC::FB_STC ( wxWindow * parent, FB_Doc * doc ) : 
    wxStyledTextCtrl ( parent, wxID_ANY )
{
    Doc = doc;
    Parent = parent;
    return;
}

void FB_STC::LoadSettings ( ) 
{
    return;
}

void FB_STC::OnCharAdded ( wxStyledTextEvent &event ) 
{

}

//----

FB_STC_FB::FB_STC_FB ( wxWindow * parent, FB_Doc * doc ) :
    FB_STC( parent, doc )
{
    LoadSettings();
}

void FB_STC_FB::OnCharAdded ( wxStyledTextEvent &event ) 
{

}

void FB_STC_FB::LoadSettings (  ) 
{

}
