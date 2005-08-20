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

#include "wx/fileconf.h"
#include "wx/wfstream.h"
#include "wx/filesys.h"
#include "wx/datetime.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/app.h"

#define mySTC_STYLE_BOLD 	1
#define mySTC_STYLE_ITALIC 	2
#define mySTC_STYLE_UNDERL 	4

extern wxApp* wxGetApp();

typedef unsigned int uint;

struct Style_STC_FB {    
    struct Style{
        uint        Face;
        uint        Back;
        int    		Case;
        int    		Size;
        int    		Style;
        wxString 	Font;
    }Style[16];
    uint        LineNumberFace;
    uint        LineNumberBack;
    uint        SelectFace;
    uint        SelectBack;
    uint        CaretFace;
    uint        CaretLine;
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
             WhiteSpace,
             AutoIndent,
             BraceHighlight,
             FolderMargin,
             ShowConsole, 
             ShowProject,
             ShowToolBar, 
             ShowStatusBar,
             ShowExitCode,
             CurrentLine,
             RightMargin,
             SplashScreen;
        int  TabLimit;
        int  TabSize;
        int  EdgeColumn;
        
        int winx, winy, winw, winh;
        
        Style_STC_FB Style_FB;
        wxString FB_Keywords[4];
        wxArrayString FB_Kw;
        int FB_KwTable[26][26];
        
        wxString CompilerPath;
        wxString EditorPath;
        wxString SyntaxFile;
        wxString ThemeFile;
        
        FB_Config(  );
        ~FB_Config();
        void LoadFBTheme ( wxString file );
        void LoadConfig  ( wxString file );
        void SaveConfig  ( wxString file );
        void LoadKWFile  ( wxString file );
        wxColour GetClr( uint c ) { 
            wxColour clr((c >> 16) & 255, (c >> 8) & 255, c & 255);
            return clr;
        }
};


#endif
