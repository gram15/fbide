/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005  Albert Varaksin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Contact e-mail: Albert Varaksin <vongodric@hotmail.com>
 * Program URL   : http://fbide.sourceforge.net
 */

//#include <wx/wxprec.h>

#include "inc/main.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

void MyFrame::LoadSettings() {

    wxFileName w(FB_App->argv[0]);
    w.Normalize();
    EditorPath = w.GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);

#ifdef __WXMSW__

    wxFileInputStream PrefsINIIS( EditorPath + _T("IDE/prefs_win32.ini"));
#else

    wxFileInputStream PrefsINIIS( EditorPath + _T("IDE/prefs_linux.ini"));
#endif

    wxFileConfig PrefsINI(PrefsINIIS);

    wxString Temp = PRODUCT_NAME;
    SetTitle( Temp );

    bool b = false;
    PrefsINI.SetPath(_T("/general"));
    Prefs.AutoIndent        = PrefsINI.Read(_T("autoindent"),       b);
    Prefs.SyntaxHighlight   = PrefsINI.Read(_T("syntaxhighlight"),  b);
    Prefs.LongLine          = PrefsINI.Read(_T("borderline"),       b);
    Prefs.whiteSpace        = PrefsINI.Read(_T("whitespaces"),      b);
    Prefs.LineNumber        = PrefsINI.Read(_T("linenumbers"),      b);
    Prefs.IndentGuide       = PrefsINI.Read(_T("indentguide"),      b);
    Prefs.BraceHighlight    = PrefsINI.Read(_T("bracehighlight"),   b);
    Prefs.ShowExitCode      = PrefsINI.Read(_T("showexitcode"),     b);
    Prefs.FolderMargin      = PrefsINI.Read(_T("foldermargin"),     b);
    Prefs.DisplayEOL        = PrefsINI.Read(_T("Displayeol"),       b);
    Prefs.CurrentLine       = PrefsINI.Read(_T("lightcursorline"),  b);
    Prefs.TabSize           = PrefsINI.Read(_T("tabsize"),          3l);
    Prefs.EdgeColumn        = PrefsINI.Read(_T("edgecolumn"),       80L);
    Prefs.Language          = PrefsINI.Read(_T("language"),         _T("english"));
    Prefs.ActivePath        = PrefsINI.Read(_T("ActivePath"),       true);

    PrefsINI.SetPath(_T("/paths"));
    CompilerPath            = PrefsINI.Read(_T("fbc"),      _T(""));
#ifdef __WXMSW__

    if (CompilerPath == _T("") || !wxFileExists(CompilerPath)) {
        if ( wxFileExists( EditorPath + _T("fbc.exe") ) )
            CompilerPath = EditorPath + _T("fbc.exe");
        else {
            if (wxMessageBox(_T("Compiler path is either not set or is corrupt. Set correct path now?"),
                             _T("Compiler error"), wxYES_NO | wxICON_HAND ) ==wxYES) {
                wxFileDialog dlg (this,
                                  _T("Open compiler"), //Open file
                                  _T(""),
                                  _T("fbc.exe"),
                                  _T("FreeBASIC (fbc.exe)|fbc.exe|All programs (*.exe)|*.exe"),
                                  wxFILE_MUST_EXIST );
                if (dlg.ShowModal() == wxID_OK)
                    CompilerPath=dlg.GetPath();
            }
        }
    }
#endif

#ifndef __WXMSW__
    strTerminal = PrefsINI.Read(_T("terminal"), _T(""));
#endif

    Prefs.HelpFile          = PrefsINI.Read(_T("helpfile"),         _T(""));
    wxFileName helpFile( Prefs.HelpFile );
    if( helpFile.IsRelative() )
        Prefs.UseHelp = ::wxFileExists( EditorPath + _T("IDE/") + Prefs.HelpFile );
    else
        Prefs.UseHelp = ::wxFileExists( Prefs.HelpFile );

    SyntaxFile              = PrefsINI.Read(_T("syntax"),   _T(""));
    if (SyntaxFile==_T(""))
        SyntaxFile = _T("fbfull.lng");

    ThemeFile               = PrefsINI.Read(_T("theme"),    _T(""));
    if (ThemeFile==_T(""))
        ThemeFile = _T("classic");


    PrefsINI.SetPath(_T("/compiler"));
    CMDPrototype            = PrefsINI.Read(_T("command"),  _T("<fbc> <filename>"));
    RunPrototype            = PrefsINI.Read(_T("runprototype"),    _T("<file> <param>"));

    int winx, winy, winh, winw;
    PrefsINI.SetPath(_T("/editor"));
    Prefs.FloatBars         = PrefsINI.Read(_T("floatbars"),        b);
    winx                    = PrefsINI.Read(_T("winx"),             50),
    winy                    = PrefsINI.Read(_T("winy"),             50),
    winw                    = PrefsINI.Read(_T("winw"),             350),
    winh                    = PrefsINI.Read(_T("winh"),             200);
    Prefs.SplashScreen      = PrefsINI.Read(_T("splashscreen"),     b);

    if(winw==-1||winh==-1)
        Maximize();
    else {
        Move(winx, winy);
        SetSize(winw, winh);
    }

    PrefsINI.SetPath(_T("/"));
    OpenLangFile(Prefs.Language);

    wxFileInputStream input( EditorPath + _T("IDE/history.ini") );
    wxFileConfig History(input);
    m_FileHistory = new wxFileHistory;
    m_FileHistory->Load( History );

    return;
}



void MyFrame::SaveSettings() {

#ifdef __WXMSW__
    wxString iniFile( EditorPath + _T("IDE/prefs_win32.ini") );
#else

    wxString iniFile( EditorPath + _T("IDE/prefs_linux.ini") );
#endif

    wxFileInputStream PrefsINIIS( iniFile );
    wxFileConfig PrefsINI(PrefsINIIS);
    wxFileOutputStream PrefsINIOS( iniFile );

    PrefsINI.SetPath(_T("/general"));
    PrefsINI.Write(_T("autoindent"),        (bool)Prefs.AutoIndent);
    PrefsINI.Write(_T("syntaxhighlight"),   (bool)Prefs.SyntaxHighlight);
    PrefsINI.Write(_T("linenumbers"),       (bool)Prefs.LineNumber);
    PrefsINI.Write(_T("indentguide"),       (bool)Prefs.IndentGuide);
    PrefsINI.Write(_T("bracehighlight"),    (bool)Prefs.BraceHighlight);
    PrefsINI.Write(_T("showexitcode"),      (bool)Prefs.ShowExitCode);
    PrefsINI.Write(_T("foldermargin"),      (bool)Prefs.FolderMargin);
    PrefsINI.Write(_T("Displayeol"),        (bool)Prefs.DisplayEOL);
    PrefsINI.Write(_T("borderline"),        (bool)Prefs.LongLine);
    PrefsINI.Write(_T("whitespaces"),       (bool)Prefs.whiteSpace);
    PrefsINI.Write(_T("lightcursorline"),   (bool)Prefs.CurrentLine);
    PrefsINI.Write(_T("tabsize"),           (long)Prefs.TabSize);
    PrefsINI.Write(_T("edgecolumn"),        (long)Prefs.EdgeColumn);
    PrefsINI.Write(_T("language"),          Prefs.Language);
    PrefsINI.Write(_T("ActivePath"),        (bool)Prefs.ActivePath);

    PrefsINI.SetPath(_T("/paths"));
    PrefsINI.Write(_T("fbc"),               CompilerPath);
    PrefsINI.Write(_T("syntax"),            SyntaxFile);
    PrefsINI.Write(_T("theme"),             ThemeFile);
    PrefsINI.Write(_T("helpfile"),          Prefs.HelpFile);
#ifndef __WXMSW__
    PrefsINI.Write(_T("terminal"),      strTerminal);
#endif



    PrefsINI.SetPath(_T("/compiler"));
    PrefsINI.Write(_T("command"),           CMDPrototype);
    PrefsINI.Write(_T("runprototype"),      RunPrototype);

    int winx, winy, winh, winw;

    if (IsMaximized()||IsIconized()) {
        winw=-1;
        winh=-1;
        winx=0;
        winy=0;
    }
    else {
        GetSize(&winw, &winh);
        GetPosition(&winx, &winy);
    }

    PrefsINI.SetPath(_T("/editor"));
    PrefsINI.Write(_T("winx"),             (long)winx),
    PrefsINI.Write(_T("winy"),             (long)winy),
    PrefsINI.Write(_T("winw"),             (long)winw),
    PrefsINI.Write(_T("winh"),             (long)winh);
    PrefsINI.Write(_T("splashscreen"),     (bool)Prefs.SplashScreen);

    PrefsINI.Save(PrefsINIOS);

    wxFileInputStream input( EditorPath + _T("IDE/history.ini") );
    wxFileConfig History(input);
    wxFileOutputStream output( EditorPath + _T("IDE/history.ini") );
    m_FileHistory->Save( History );
    History.Save( output );
    return;
}



StyleInfo  MyFrame::LoadThemeFile( wxString ThemeFile ) {

    StyleInfo Style;

    wxFileInputStream ThemeIS( EditorPath + _T("IDE/") + ThemeFile + _T(".fbt") );
    wxFileConfig Theme( ThemeIS );

    wxString StyleTypes[]={ _T("default"),      _T("comment"),     _T("number"),
                            _T("keyword"),      _T("string"),      _T("preprocessor"),
                            _T("operator"),  _T("identifier"),  _T("date"),
                            _T("stringeol"),    _T("keyword2"),    _T("keyword3"),
                            _T("keyword4"),     _T("constant"),    _T("asm") };

    //Default:

    Theme.SetPath(_T("/default"));
    Style.DefaultBgColour       = Theme.Read(_T("background"),      0xffffff);
    Style.DefaultFgColour       = Theme.Read(_T("foreground"),      0L);
    Style.CaretColour           = Theme.Read(_T("caret"),           0L);
    Style.DefaultFontSize       = Theme.Read(_T("fontsize"),        12L);
    Style.CaretLine             = Theme.Read(_T("caretline"),       0xdddddd);
    Style.DefaultFontStyle      = Theme.Read(_T("fontstyle"),       0L);
    Style.DefaultFont           = Theme.Read(_T("font"),            _T(""));

    //Line number
    Theme.SetPath(_T("/linenumber"));
    Style.LineNumberBgColour    = Theme.Read(_T("background"),      0xc0c0c0);
    Style.LineNumberFgColour    = Theme.Read(_T("foreground"),      0xffffff);

    Theme.SetPath(_T("/select"));
    Style.SelectBgColour        = Theme.Read(_T("background"),      0xc0c0c0);
    Style.SelectFgColour        = Theme.Read(_T("foreground"),      0xffffff);

    Theme.SetPath(_T("/brace"));
    Style.BraceBgColour         = Theme.Read(_T("background"),      (long)Style.DefaultFgColour);
    Style.BraceFgColour         = Theme.Read(_T("foreground"),      (long)Style.DefaultBgColour);
    Style.BraceFontStyle        = Theme.Read(_T("fontstyle"),       0L);

    Theme.SetPath(_T("/badbrace"));
    Style.BadBraceBgColour      = Theme.Read(_T("background"),      (long)Style.DefaultFgColour);
    Style.BadBraceFgColour      = Theme.Read(_T("foreground"),      0L);
    Style.BadBraceFontStyle     = Theme.Read(_T("fonstyle"),        0L);


    for (int i=1; i<15;i++) {
        Theme.SetPath(_T("/") + StyleTypes[i]);
        Style.Info[i].background    = Theme.Read(_T("background"),      (long)Style.DefaultBgColour);
        Style.Info[i].foreground    = Theme.Read(_T("foreground"),      (long)Style.DefaultFgColour);
        Style.Info[i].fontsize      = Theme.Read(_T("fontsize"),        (long)Style.DefaultFontSize);
        Style.Info[i].lettercase    = Theme.Read(_T("capital"),         0L);
        Style.Info[i].fontstyle     = Theme.Read(_T("fontstyle"),       (long)Style.DefaultFontStyle);
        Style.Info[i].fontname      = Theme.Read(_T("font"),            Style.DefaultFont);
    }

    return Style;
}



void MyFrame::SaveThemeFile      ( StyleInfo Style, wxString ThemeFile ) {

    wxFileInputStream ThemeIS( EditorPath + _T("IDE/") + ThemeFile + _T(".fbt") );
    wxFileOutputStream ThemeISOS( EditorPath + _T("IDE/") + ThemeFile + _T(".fbt") );
    wxFileConfig Theme( ThemeIS );

    wxString StyleTypes[]={ _T("default"),      _T("comment"),     _T("number"),
                            _T("keyword"),      _T("string"),      _T("preprocessor"),
                            _T("operator"),  _T("identifier"),  _T("date"),
                            _T("stringeol"),    _T("keyword2"),    _T("keyword3"),
                            _T("keyword4"),     _T("constant"),    _T("asm") };

    //Default:

    Theme.SetPath(_T("/default"));
    Theme.Write(_T("background"),                   (long)Style.DefaultBgColour);
    Theme.Write(_T("foreground"),                   (long)Style.DefaultFgColour);
    Theme.Write(_T("caret"),                        (long)Style.CaretColour);
    Theme.Write(_T("fontsize"),                     (long)Style.DefaultFontSize);
    Theme.Write(_T("caretline"),                    (long)Style.CaretLine);
    Theme.Write(_T("fontstyle"),                    (long)Style.DefaultFontStyle);
    Theme.Write(_T("font"),                         Style.DefaultFont);

    //Line number
    Theme.SetPath(_T("/linenumber"));
    Theme.Write(_T("background"),                   (long)Style.LineNumberBgColour);
    Theme.Write(_T("foreground"),                   (long)Style.LineNumberFgColour);

    Theme.SetPath(_T("/select"));
    Theme.Write(_T("background"),                   (long)Style.SelectBgColour);
    Theme.Write(_T("foreground"),                   (long)Style.SelectFgColour);

    Theme.SetPath(_T("/brace"));
    Theme.Write(_T("background"),                   (long)Style.BraceBgColour);
    Theme.Write(_T("foreground"),                   (long)Style.BraceFgColour);
    Theme.Write(_T("fontstyle"),                    (long)Style.BraceFontStyle);

    Theme.SetPath(_T("/badbrace"));
    Theme.Write(_T("background"),                   (long)Style.BadBraceBgColour);
    Theme.Write(_T("foreground"),                   (long)Style.BadBraceFgColour);
    Theme.Write(_T("fonstyle"),                     (long)Style.BadBraceFontStyle);


    for (int i=1; i<15;i++) {
        Theme.SetPath(_T("/") + StyleTypes[i]);
        Theme.Write(_T("background"),               (long)Style.Info[i].background);
        Theme.Write(_T("foreground"),               (long)Style.Info[i].foreground);
        Theme.Write(_T("font"),                     Style.Info[i].fontname);
        Theme.Write(_T("fontsize"),                 (long)Style.Info[i].fontsize);
        Theme.Write(_T("capital"),                  (long)Style.Info[i].lettercase);
        Theme.Write(_T("fontstyle"),                (long)Style.Info[i].fontstyle);
    }

    Theme.Save(ThemeISOS);
    return;
}



void MyFrame::LoadkwFile( wxString SyntaxFile ) {

    wxFileInputStream SyntaxIS( EditorPath + _T("IDE/") + SyntaxFile );
    wxFileConfig Syntax(SyntaxIS);

    Syntax.SetPath(_T("/keywords"));
    Keyword[1]            = Syntax.Read(_T("kw1"), _T(""));
    Keyword[2]            = Syntax.Read(_T("kw2"), _T(""));
    Keyword[3]            = Syntax.Read(_T("kw3"), _T(""));
    Keyword[4]            = Syntax.Read(_T("kw4"), _T(""));

    kwList.Clear();
    char c;
    wxString curword;
    for(int i=0;i<4;i++) {
        for(int j=0;j<(int)Keyword[i+1].Len();j++) {
            c = Keyword[i+1].GetChar(j);
            curword += c;
            if(c == ' ' || c == '\n' || c == '\r' ||
                    j + 1 == (int)Keyword[i+1].Len() ) {
                if(curword.Trim(false).Trim(true).Len()>0) {
                    kwList.Add( curword );
                }
                curword = _T("");
            }
        }
    }

    kwList.Sort();

    return;
}


void MyFrame::SavekwFile( wxString SyntaxFile ) {

    wxFileInputStream SyntaxIS( EditorPath + _T("IDE/") + SyntaxFile );
    wxFileOutputStream SyntaxOS( EditorPath + _T("IDE/") + SyntaxFile );
    wxFileConfig Syntax(SyntaxIS);

    Syntax.SetPath(_T("/keywords"));
    Syntax.Write(_T("kw1"),     Keyword[1]);
    Syntax.Write(_T("kw2"),     Keyword[2]);
    Syntax.Write(_T("kw3"),     Keyword[3]);
    Syntax.Write(_T("kw4"),     Keyword[4]);

    Syntax.Save(SyntaxOS);
    return;
}
