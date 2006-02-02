/////////////////////////////////////////////////////////////////////////////
// Name:        class.pluginlist.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     01/02/2006 01:42:59
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CLASSPLUGINLIST_H_
#define _CLASSPLUGINLIST_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "class.pluginlist.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/listctrl.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxListCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define PLUGINLIST 10000
#define SYMBOL_CLASSPLUGINLIST_STYLE wxRESIZE_BORDER|wxCLIP_CHILDREN 
#define SYMBOL_CLASSPLUGINLIST_TITLE _("Plugin tester")
#define SYMBOL_CLASSPLUGINLIST_IDNAME PLUGINLIST
#define SYMBOL_CLASSPLUGINLIST_SIZE wxSize(400, 300)
#define SYMBOL_CLASSPLUGINLIST_POSITION wxDefaultPosition
#define ID_BUTTON 10004
#define ID_TextBox_Input 10001
#define ID_Button_Input 10002
#define ID_PluginList 10003
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * classPluginList class declaration
 */

class classPluginList: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( classPluginList )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    classPluginList( );
    classPluginList( wxWindow* parent, wxWindowID id = SYMBOL_CLASSPLUGINLIST_IDNAME, const wxPoint& pos = SYMBOL_CLASSPLUGINLIST_POSITION, const wxSize& size = SYMBOL_CLASSPLUGINLIST_SIZE, long style = SYMBOL_CLASSPLUGINLIST_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CLASSPLUGINLIST_IDNAME, const wxPoint& pos = SYMBOL_CLASSPLUGINLIST_POSITION, const wxSize& size = SYMBOL_CLASSPLUGINLIST_SIZE, long style = SYMBOL_CLASSPLUGINLIST_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin classPluginList event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnButtonClick( wxCommandEvent& event );

////@end classPluginList event handler declarations

////@begin classPluginList member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end classPluginList member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin classPluginList member variables
    wxTextCtrl* m_objInputBox;
    wxListCtrl* m_objPluginListCtrl;
////@end classPluginList member variables
    wxTextCtrl* GetTextCtrl() const { return m_objInputBox; }
    wxListCtrl* GetListCtrl() const { return m_objPluginListCtrl; }
};

#endif
    // _CLASSPLUGINLIST_H_
