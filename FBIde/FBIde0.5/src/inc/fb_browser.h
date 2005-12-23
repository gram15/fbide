/////////////////////////////////////////////////////////////////////////////
// Name:        fb_browser.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_BROWSER_H_
#define _FB_BROWSER_H_

class FB_Browser : public wxNotebook {
    private:
        wxTreeCtrl * m_Project;
        wxTreeCtrl * m_SFTree;
        int size;
    
    public:
        FB_Browser( wxWindow * parent );
        void SetSize( int s )  { size = s; }
        int  GetSize(  ) const { return (size == 0) ? 150 : size; }
        
        wxTreeCtrl * GetProjectTree() const { return m_Project; }
        wxTreeCtrl * GetSFTree() const { return m_SFTree; }
};

#endif
