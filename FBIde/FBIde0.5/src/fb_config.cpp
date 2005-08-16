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
    LoadFBTheme( EditorPath + "/ide/" + ThemeFile + ".fbt" );
    LoadKWFile( EditorPath + "/ide/" + SyntaxFile );
}

FB_Config::~FB_Config()
{
    SaveConfig( EditorPath + "/ide/prefs.ini" );
}



void FB_Config::LoadKWFile ( wxString file )
{
    wxFileInputStream input( file );
    wxFileConfig Syntax(input);
    
    Syntax.SetPath("/keywords");
    FB_Keywords[0] = Syntax.Read("kw1", "");
    FB_Keywords[1] = Syntax.Read("kw2", "");
    FB_Keywords[2] = Syntax.Read("kw3", "");
    FB_Keywords[3] = Syntax.Read("kw4", "");
}



void FB_Config::LoadFBTheme ( wxString file ) 
{
    
    wxFileInputStream input( file );
    wxFileConfig Theme( input );
    
	wxString StyleTypes[]={	"default", 	    "comment", 	   "number",
                            "keyword",      "string",      "preprocessor",
							"operator", 	"identifier",  "date",
                            "stringeol",    "keyword2",    "keyword3",
                            "keyword4",     "constant",    "asm" };

	//Default:
	
    #define _STYLE(nr) Style_FB.Style[nr]
        Theme.SetPath("/default");
        _STYLE(0).Face          = Theme.Read("foreground",  0L);
        _STYLE(0).Back          = Theme.Read("background",  0xffffff);
        _STYLE(0).Case          = Theme.Read("capital",     0L);
        _STYLE(0).Size          = Theme.Read("fontsize",    10L);
        _STYLE(0).Style         = Theme.Read("fontstyle",   0L);
        _STYLE(0).Font          = Theme.Read("font",        "" );
    
        Theme.SetPath("/caret");
        Style_FB.CaretFace      = Theme.Read("caret",       _STYLE(0).Face);
        Style_FB.CaretLine      = Theme.Read("caretline",   _STYLE(0).Back);
       
    	//Line number
        Theme.SetPath("/linenumber");
        Style_FB.LineNumberFace = Theme.Read("foreground",  0xffffff);
        Style_FB.LineNumberBack = Theme.Read("background",  0xc0c0c0);
    	
        Theme.SetPath("/select");
        Style_FB.SelectFace     = Theme.Read("foreground",  0xffffff);
        Style_FB.SelectBack     = Theme.Read("background",  0xc0c0c0);
        
        Theme.SetPath("/brace");
        Style_FB.BraceFace      = Theme.Read("foreground",  _STYLE(0).Back);
        Style_FB.BraceBack      = Theme.Read("background",  _STYLE(0).Face);
        Style_FB.BraceStyle     = Theme.Read("fontstyle",   0L);
        
        Theme.SetPath("/badbrace");
        Style_FB.BadBraceFace   = Theme.Read("foreground",  _STYLE(0).Back);
        Style_FB.BadBraceBack   = Theme.Read("background",  _STYLE(0).Face);
        Style_FB.BadBraceStyle  = Theme.Read("fonstyle",    0L);
        
        for (int i=1; i<15;i++) {
            Theme.SetPath("/" + StyleTypes[i]);
            _STYLE(i).Face          = Theme.Read("foreground",  _STYLE(0).Face);
            _STYLE(i).Back          = Theme.Read("background",  _STYLE(0).Back);
            _STYLE(i).Case          = Theme.Read("capital",     _STYLE(0).Case);
            _STYLE(i).Size          = Theme.Read("fontsize",    _STYLE(0).Size);
            _STYLE(i).Style         = Theme.Read("fontstyle",   _STYLE(0).Style);
            _STYLE(i).Font          = Theme.Read("font",        _STYLE(0).Font);
        }
    #undef _STYLE
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
