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
#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/wxmynotebook.h"

BEGIN_EVENT_TABLE(wxMyNotebook,wxNotebook) 
    EVT_MOUSE_EVENTS(wxMyNotebook::OnMouseEvent) 
END_EVENT_TABLE() 

wxMyNotebook::wxMyNotebook(MyFrame* mf, wxWindow *parent, wxWindowID id, 
              const wxPoint& pos, const wxSize& size, 
              long style, const wxString& name)
              : wxNotebook(parent,id,pos,size,style,name) 
{ 
    p = mf;
}


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
            popup.Append(Menu_Close,        _(p->Lang[21]));
            popup.Append(Menu_CloseAll,    _(p->Lang[173]));
            popup.AppendSeparator();
            popup.Append(Menu_Undo,         _(p->Lang[27]));
            popup.Enable(Menu_Undo, stc->CanUndo());
            popup.Append(Menu_Redo,         _(p->Lang[29]));
            popup.Enable(Menu_Redo, stc->CanRedo());
            popup.AppendSeparator();
            popup.Append(Menu_Copy,         _(p->Lang[33]));
            popup.Enable(Menu_Copy, (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Cut,          _(p->Lang[31]));
            popup.Enable(Menu_Cut,   (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Paste,        _(p->Lang[35]));
            popup.Enable(Menu_Paste, stc->CanPaste());
            popup.Append(Menu_SelectAll,    _(p->Lang[37]));
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
 
