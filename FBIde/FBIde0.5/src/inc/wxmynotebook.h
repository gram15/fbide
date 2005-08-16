/////////////////////////////////////////////////////////////////////////////
// Name:        wxmynotebook.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef WXMYNOTEBOOK_H_
#define WXMYNOTEBOOK_H_

#include "wx/notebook.h"
#include "wx/menu.h"

class wxMyNotebook : public wxNotebook 
{ 
private: 
    DECLARE_EVENT_TABLE() 
    
protected: 
    // for Tab Dragging 
    int m_TabID; 
    wxCoord m_X,m_Y; 
    void OnMouseEvent(wxMouseEvent& event);
    
public: 
    wxMyNotebook(wxWindow *parent, 
             wxWindowID id, 
             const wxPoint& pos = wxDefaultPosition, 
             const wxSize& size = wxDefaultSize, 
             long style = 0, 
             const wxString& name = wxNotebookNameStr) 
             :wxNotebook(parent,id,pos,size,style,name), m_TabID(-1) 
    {  }

}; 

#endif
