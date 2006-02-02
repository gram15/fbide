/////////////////////////////////////////////////////////////////////////////
// Name:        plugindialog.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     01/02/2006 15:20:10
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PLUGINDIALOG_H_
#define _PLUGINDIALOG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "plugindialog.h"
#endif

/*!
 * Includes
 */

////@begin includes
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
#define SYMBOL_PLUGINDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxCLIP_CHILDREN 
#define SYMBOL_PLUGINDIALOG_TITLE _("Plugin dialog")
#define SYMBOL_PLUGINDIALOG_IDNAME ID_DIALOG
#define SYMBOL_PLUGINDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_PLUGINDIALOG_POSITION wxDefaultPosition
#define ID_TEXTCTRL 10001
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * Plugindialog class declaration
 */

class Plugindialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( Plugindialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    Plugindialog( );
    Plugindialog( wxWindow* parent, wxWindowID id = SYMBOL_PLUGINDIALOG_IDNAME, const wxString& caption = SYMBOL_PLUGINDIALOG_TITLE, const wxPoint& pos = SYMBOL_PLUGINDIALOG_POSITION, const wxSize& size = SYMBOL_PLUGINDIALOG_SIZE, long style = SYMBOL_PLUGINDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PLUGINDIALOG_IDNAME, const wxString& caption = SYMBOL_PLUGINDIALOG_TITLE, const wxPoint& pos = SYMBOL_PLUGINDIALOG_POSITION, const wxSize& size = SYMBOL_PLUGINDIALOG_SIZE, long style = SYMBOL_PLUGINDIALOG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin Plugindialog event handler declarations

////@end Plugindialog event handler declarations

////@begin Plugindialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Plugindialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin Plugindialog member variables
////@end Plugindialog member variables
};

#endif
    // _PLUGINDIALOG_H_
