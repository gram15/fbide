/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_TAB_H_
#define _FB_TAB_H_

#include "fb_frame.h"
#include "wxmynotebook.h"

class FB_Tab
{
    private:
        wxMyNotebook * tab;
        int tabcount;
        int tabvis;
        FB_Frame * Parent;
        wxWindow * Code;
        
    public:
        FB_Tab          ( wxWindow * parent );
        ~FB_Tab         (  );
        void Create     ( wxWindow * parent );
        void AddPage    (  );
        void ClosePage  ( int idx = -1 );
        void ClosePages ( int idx[] );
        void CloseAll   (  );
        void Show       ( bool status );
};

#endif
