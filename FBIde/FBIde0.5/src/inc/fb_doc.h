/////////////////////////////////////////////////////////////////////////////
// Name:        fb_doc.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_DOC_H_
#define _FB_DOC_H_

#include "wx/filename.h"
#include "stc/stc.h"

enum fbDoc_Enums {
    fbDoc_Single,
    fbDoc_Project,
    fbDoc_Html,
    fbDoc_Other // txt...
};

class FB_Doc {
    public:
        wxStyledTextCtrl * stc;
        wxString FileName;
        int DocStyle;
        bool modified;
};

#endif
