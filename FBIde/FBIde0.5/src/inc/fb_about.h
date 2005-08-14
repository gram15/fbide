/////////////////////////////////////////////////////////////////////////////
// Name:        fb_about.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_ABOUT_H_
#define _FB_ABOUT_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "fb_about.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/statline.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define SYMBOL_FB_ABOUT_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_FB_ABOUT_TITLE _("About")
#define SYMBOL_FB_ABOUT_IDNAME ID_DIALOG
#define SYMBOL_FB_ABOUT_SIZE wxDefaultSize
#define SYMBOL_FB_ABOUT_POSITION wxDefaultPosition
#define ID_TEXTCTRL 10001
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * FB_About class declaration
 */

class FB_About: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( FB_About )
    DECLARE_EVENT_TABLE()

public:
    FB_About( );
    FB_About( wxWindow* parent, wxWindowID id = SYMBOL_FB_ABOUT_IDNAME, const wxString& caption = SYMBOL_FB_ABOUT_TITLE, const wxPoint& pos = SYMBOL_FB_ABOUT_POSITION, const wxSize& size = SYMBOL_FB_ABOUT_SIZE, long style = SYMBOL_FB_ABOUT_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FB_ABOUT_IDNAME, const wxString& caption = SYMBOL_FB_ABOUT_TITLE, const wxPoint& pos = SYMBOL_FB_ABOUT_POSITION, const wxSize& size = SYMBOL_FB_ABOUT_SIZE, long style = SYMBOL_FB_ABOUT_STYLE );
    void CreateControls();
    void OnCloseWindow( wxCloseEvent& event );
    void OnOkClick( wxCommandEvent& event );
    wxBitmap GetBitmapResource( const wxString& name );

};

#endif
    // _FB_ABOUT_H_
