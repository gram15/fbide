/////////////////////////////////////////////////////////////////////////////
// Name:        wxfb_notebook.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "inc/wxall.h"
#include "inc/wxfb_notebook.h"
#include "inc/fb_frame.h"

BEGIN_EVENT_TABLE(wxFB_Notebook,wxNotebook) 
    EVT_MOUSE_EVENTS(wxFB_Notebook::OnMouseEvent) 
END_EVENT_TABLE() 

void wxFB_Notebook::OnMouseEvent(wxMouseEvent& event) 
{ 
    wxEventType eventType = event.GetEventType(); 
    
    if(m_TabID>=0) 
    {
        if(eventType==wxEVT_LEFT_UP) 
        { 
            int id=HitTest(wxPoint(event.GetX(), event.GetY())); 
            if(id>=0 && id!=m_TabID) 
            { 
                GetParent()->Freeze();
                    wxNotebookPage* page=GetPage(m_TabID); 
                    wxString text=GetPageText(m_TabID); 
                    int image=GetPageImage(m_TabID); 
                
                    RemovePage(m_TabID); 
                    InsertPage(id, page, text, true, image); 
                GetParent()->Thaw();
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
        event.Skip();
    } 
    else // m_TabID==-1, no dragging 
    {
        m_X=event.GetX(); 
        m_Y=event.GetY(); 
        int tabid = HitTest(wxPoint(m_X, m_Y));
        
        if(eventType==wxEVT_LEFT_DOWN) 
        { 
            m_TabID=tabid;
            event.Skip();
        }
        else if (eventType==wxEVT_RIGHT_DOWN) 
        {
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, fbideID_TabAreaPopUp );
            GetEventHandler()->ProcessEvent( event );
        }
        else if (eventType==wxEVT_MIDDLE_DOWN)
        {
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, wxID_CLOSE );
            GetEventHandler()->ProcessEvent( event );
        } else event.Skip();
    }
} 
 
