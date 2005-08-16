/////////////////////////////////////////////////////////////////////////////
// Name:        fb_config.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_CONFIG_H_
#define _FB_CONFIG_H_

typedef unsigned int uint;
struct Style_STC_FB {    
    struct Style{
        uint        Face;
        uint        Back;
        wxString 	Font;
        int    		Size;
        int    		Style;
        int    		Case;
    }Style[16];
    uint        LineNumberFace;
    uint        LineNumberBack;
    uint        SelectFace;
    uint        SelectBack;
    uint        CaretFace;
    uint        BraceFace;
    uint        BraceBack;
    int         BraceStyle;
    uint        BadBraceFace;
    uint        BadBraceBack;
    int         BadBraceStyle;
};

class FB_Config
{
    public:
        bool SyntaxHighlight,
             IndentGuide,
             DisplayEOL,
             LineNumber,
             whiteSpace,
             AutoIndent,
             BraceHighlight,
             FolderMargin,
        int  TabSize;
        int  EdgeColumn;
        Style_STC_FB STC_FB;
        wxString FB_Keywords;
        
        FB_Config::FB_Config();
};
