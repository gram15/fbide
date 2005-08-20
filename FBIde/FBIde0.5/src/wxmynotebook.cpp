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
#include "inc/fb_stc.h"

BEGIN_EVENT_TABLE(wxMyNotebook,wxNotebook) 
    EVT_MOUSE_EVENTS(wxMyNotebook::OnMouseEvent) 
END_EVENT_TABLE() 

void wxMyNotebook::OnMouseEvent(wxMouseEvent& event) 
{ 
    wxEventType eventType = event.GetEventType(); 
    
    if(m_TabID>=0) 
    {
        if(eventType==wxEVT_LEFT_UP) 
        { 
            int id=HitTest(wxPoint(event.GetX(), event.GetY())); 
            if(id>=0 && id!=m_TabID) 
            { 
                // move [m_TabID] to [id] 
                //wxGetApp().GetTopWindow()->SetTitle(wxString::Format(wxT("Drag %d->%d"), m_TabID, id)); 
                wxNotebookPage* page=GetPage(m_TabID); 
                wxString text=GetPageText(m_TabID); 
                int image=GetPageImage(m_TabID); 
                
                RemovePage(m_TabID); 
                InsertPage(id, page, text, true, image); 
            } 
            
            m_TabID=-1; 
            wxSetCursor(wxCursor(wxCURSOR_ARROW)); 
        } 
        else 
        { 
            wxCoord x=event.GetX(); 
            wxCoord y=event.GetY(); 
            int id=HitTest(wxPoint(x, y)); 
            if(id<0||id==m_TabID) 
            { 
                wxSetCursor(wxCursor(wxCURSOR_ARROW)); 
            } 
            else if(x!=m_X || y!=m_Y) 
            { 
                wxSetCursor(wxCursor(wxCURSOR_HAND)); 
                m_X=m_Y=-1024; 
            } 
        } 
    } 
    else // m_TabID==-1, no dragging 
    {
        m_X=event.GetX(); 
        m_Y=event.GetY(); 
        int tabid = HitTest(wxPoint(m_X, m_Y));
        
        if(eventType==wxEVT_LEFT_DOWN) 
        { 
            m_TabID=tabid;
        }
        else if (eventType==wxEVT_RIGHT_DOWN) 
        {
            /*/
             *  In the sake of integrity
             *  this should be moved out of here... but How?
             *  generate costom event and pass data along?
             *  well for now it can stay here...
            /*/
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            FB_STC * stc = (FB_STC*)GetCurrentPage();
            wxMenu popup("");
            popup.Append(wxID_CLOSE,        _("Close"));
            popup.Append(wxID_CLOSE_ALL,    _("Close all"));
            popup.AppendSeparator();
            popup.Append(wxID_UNDO,         _("Undo"));
            popup.Enable(wxID_UNDO, stc->CanUndo());
            popup.Append(wxID_REDO,         _("Redo"));
            popup.Enable(wxID_REDO, stc->CanRedo());
            popup.AppendSeparator();
            popup.Append(wxID_COPY,         _("Copy"));
            popup.Enable(wxID_COPY, stc->HasSelection());
            popup.Append(wxID_CUT,          _("Cut"));
            popup.Enable(wxID_CUT,  stc->HasSelection());
            popup.Append(wxID_PASTE,        _("Paste"));
            popup.Enable(wxID_PASTE, stc->CanPaste());
            popup.Append(wxID_SELECTALL,    _("Select All"));
            popup.Enable(wxID_SELECTALL, stc->GetLength());
            wxWindow::PopupMenu(&popup, m_X, m_Y);
            return;
        }
        else if (eventType==wxEVT_MIDDLE_DOWN)
        {
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, wxID_CLOSE );
            GetEventHandler()->ProcessEvent( event );
            return;
        }
    }
    event.Skip();
} 
 
