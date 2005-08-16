/////////////////////////////////////////////////////////////////////////////
// Name:        fb_config.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"

#include "inc/fb_config.h"

FB_Config::FB_Config(  )
{
    wxApp * App = wxGetApp();
    EditorPath = wxPathOnly(App->argv[0]);
    LoadConfig( EditorPath + "/ide/prefs.ini" );
}

FB_Config::~FB_Config()
{
    SaveConfig( EditorPath + "/ide/prefs.ini" );
}

void FB_Config::LoadFBTheme ( wxString file ) {
    return;
}

void FB_Config::LoadConfig  ( wxString file ) {
    wxFileInputStream input( file );
    wxFileConfig PrefsINI(input);
    
    bool b = false;
    PrefsINI.SetPath("/general");
    AutoIndent          = PrefsINI.Read("autoindent",       b);
    SyntaxHighlight     = PrefsINI.Read("syntaxhighlight",  b);
    WhiteSpace          = PrefsINI.Read("whitespaces",      b);
    LineNumber          = PrefsINI.Read("linenumbers",      b);
    IndentGuide         = PrefsINI.Read("indentguide",      b);
    BraceHighlight      = PrefsINI.Read("bracehighlight",   b);
    ShowExitCode        = PrefsINI.Read("showexitcode",     b);
    RightMargin         = PrefsINI.Read("rightmargin",      b);
    FolderMargin        = PrefsINI.Read("foldermargin",     b);
    DisplayEOL          = PrefsINI.Read("Displayeol",       b);
    CurrentLine         = PrefsINI.Read("lightcursorline",  b);
    TabSize             = PrefsINI.Read("tabsize",          3L);
    EdgeColumn          = PrefsINI.Read("edgecolumn",       80L);
    SplashScreen        = PrefsINI.Read("splashscreen",     b);
    ShowConsole         = PrefsINI.Read("showconsole",      b);
    ShowProject         = PrefsINI.Read("showproject",      b);
    ShowToolBar         = PrefsINI.Read("showtoolbar",      b);
    ShowStatusBar       = PrefsINI.Read("showstatusbar",    b);
    TabLimit            = PrefsINI.Read("tablimit",         100L);
    
    PrefsINI.SetPath("/paths");
    CompilerPath        = PrefsINI.Read("fbc",              "");
    SyntaxFile          = PrefsINI.Read("syntax",           "");
    ThemeFile           = PrefsINI.Read("theme",            "");

    PrefsINI.SetPath("/window");
    winx                = PrefsINI.Read("winx",             50),
    winy                = PrefsINI.Read("winy",             50),
    winw                = PrefsINI.Read("winw",             350),
    winh                = PrefsINI.Read("winh",             200);
}

void FB_Config::SaveConfig  ( wxString file )
{
    wxFileInputStream input( file );
    wxFileConfig PrefsINI(input);
    wxFileOutputStream output( file );

    PrefsINI.SetPath("/general");
    PrefsINI.Write( "autoindent",       (bool)AutoIndent );
    PrefsINI.Write( "syntaxhighlight",  (bool)SyntaxHighlight );
    PrefsINI.Write( "whitespaces",      (bool)WhiteSpace );
    PrefsINI.Write( "linenumbers",      (bool)LineNumber );
    PrefsINI.Write( "indentguide",      (bool)IndentGuide );
    PrefsINI.Write( "bracehighlight",   (bool)BraceHighlight );
    PrefsINI.Write( "showexitcode",     (bool)ShowExitCode );
    PrefsINI.Write( "rightmargin",      (bool)RightMargin );
    PrefsINI.Write( "foldermargin",     (bool)FolderMargin );
    PrefsINI.Write( "Displayeol",       (bool)DisplayEOL );
    PrefsINI.Write( "lightcursorline",  (bool)CurrentLine );
    PrefsINI.Write( "tabsize",          (long)TabSize );
    PrefsINI.Write( "edgecolumn",       (long)EdgeColumn );
    PrefsINI.Write( "splashscreen",     (bool)SplashScreen );
    PrefsINI.Write( "showconsole",      (bool)ShowConsole );
    PrefsINI.Write( "showproject",      (bool)ShowProject );
    PrefsINI.Write( "showtoolbar",      (bool)ShowToolBar );
    PrefsINI.Write( "showstatusbar",    (bool)ShowStatusBar );
    PrefsINI.Write( "tablimit",         (long)TabLimit );
    
    PrefsINI.SetPath("/paths");
    PrefsINI.Write( "fbc",              CompilerPath );
    PrefsINI.Write( "syntax",           SyntaxFile );
    PrefsINI.Write( "theme",            ThemeFile );

    PrefsINI.SetPath("/window");
    PrefsINI.Write( "winx",             (long) winx),
    PrefsINI.Write( "winy",             (long) winy),
    PrefsINI.Write( "winw",             (long) winw),
    PrefsINI.Write( "winh",             (long) winh);
    
    PrefsINI.Save(output);

}
