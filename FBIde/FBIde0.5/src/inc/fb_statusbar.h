/////////////////////////////////////////////////////////////////////////////
// Name:        fb_statusbar.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_STATUSBAR_H_
#define _FB_STATUSBAR_H_

class FB_Frame;

class FB_StatusBar {
    private:
        FB_Frame    * m_Parent;
        wxStatusBar * m_StatusBar;
        void CreateStatusBar();
        void DestroyStatusBar();
        
    public:
        FB_StatusBar( FB_Frame * parent );
        ~FB_StatusBar();
        void Show( bool status = true );
        void SetStatusText( const wxString& text, int i = 0 );
};

#endif
