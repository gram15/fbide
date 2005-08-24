/////////////////////////////////////////////////////////////////////////////
// Name:        wxmynotebook.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "inc/wxmynotebook.h"
#include "inc/main.h"
#include "inc/fbedit.h"

BEGIN_EVENT_TABLE(wxMyNotebook,wxNotebook) 
    EVT_MOUSE_EVENTS(wxMyNotebook::OnMouseEvent) 
END_EVENT_TABLE() 

void wxMyNotebook::OnMouseEvent(wxMouseEvent& event) 
{ 
    wxEventType eventType = event.GetEventType(); 
    
        m_X=event.GetX(); 
        m_Y=event.GetY(); 
        int tabid = HitTest(wxPoint(m_X, m_Y));
        
        if (eventType==wxEVT_RIGHT_DOWN) 
        {
            /*/
             *  In the sake of integrity
             *  this should be moved out of here... but How?
             *  generate costom event and pass data along?
             *  well for now it can stay here...
            /*/
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            FB_Edit * stc = (FB_Edit*)GetCurrentPage();
            wxMenu popup("");
            popup.Append(Menu_Close,        _("Close"));
            popup.Append(Menu_CloseAll,    _("Close all"));
            popup.AppendSeparator();
            popup.Append(Menu_Undo,         _("Undo"));
            popup.Enable(Menu_Undo, stc->CanUndo());
            popup.Append(Menu_Redo,         _("Redo"));
            popup.Enable(Menu_Redo, stc->CanRedo());
            popup.AppendSeparator();
            popup.Append(Menu_Copy,         _("Copy"));
            popup.Enable(Menu_Copy, (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Cut,          _("Cut"));
            popup.Enable(Menu_Cut,   (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Paste,        _("Paste"));
            popup.Enable(Menu_Paste, stc->CanPaste());
            popup.Append(Menu_SelectAll,    _("Select All"));
            popup.Enable(Menu_SelectAll, stc->GetLength());
            wxWindow::PopupMenu(&popup, m_X, m_Y);
            return;
        }
        else if (eventType==wxEVT_MIDDLE_DOWN)
        {
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, Menu_Close );
            GetEventHandler()->ProcessEvent( event );
            return;
        }
    event.Skip();
} 
 
