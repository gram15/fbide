/////////////////////////////////////////////////////////////////////////////
// Name:        fb_tab.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_DOCMNGR_H_
#define _FB_DOCMNGR_H_

#include "wx/notebook.h"
#include "wx/textctrl.h"

class wxMyNotebook;
class FB_Frame;
class FB_STC;
class FB_Config;

class FB_DocMngr
{
    private:
        wxMyNotebook * tab;
        int tabcount;
        int tablimit;
        int tabvis;
        FB_Frame * Parent;
        FB_STC * page;
        FB_Config * Config;
        
    public:
        FB_DocMngr      ( FB_Frame * parent, FB_Config * config );
        ~FB_DocMngr     (  );
        void Create     ( wxWindow * parent );
        void AddPage    (  );
        void ClosePage  ( int idx = -1 );
        void ClosePages ( int idx[] );
        void CloseAll   (  );
        void Show       ( bool status );
        int PageCount   (  ) { return tabcount; }
        FB_STC *  GetPage (  );
        
        bool NewPageVeto(  );
        
};

#endif
