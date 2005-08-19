/////////////////////////////////////////////////////////////////////////////
// Name:        fb_stc.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_STC_H_
#define _FB_STC_H_

#include "stc/stc.h"

class FB_Doc;
class FB_Config;

// Base class - Also ordinary txt file
class FB_STC : public wxStyledTextCtrl
{
    private:
        DECLARE_EVENT_TABLE()
        
    public:
        wxWindow    * Parent;
        FB_Config   * Config;
        FB_Doc      * Doc;
        FB_STC ( wxWindow * parent, FB_Doc * doc, FB_Config * config );
        virtual void LoadSettings ( );
        virtual void OnCharAdded ( wxStyledTextEvent &event );
        void SetDoc ( FB_Doc * doc ) { Doc = doc; }
        bool HasSelection() { return ( GetSelectionEnd() - GetSelectionStart() ) > 0; }
        FB_Doc * GetDoc () const { return Doc; }
        
        void OnUndo             ( wxCommandEvent& event );
        void OnRedo             ( wxCommandEvent& event );
        void OnCopy             ( wxCommandEvent& event );
        void OnCut              ( wxCommandEvent& event );
        void OnPaste            ( wxCommandEvent& event );
        void OnSelectall        ( wxCommandEvent& event );
        void OnSelectline       ( wxCommandEvent& event );
        void OnJustifyRight     ( wxCommandEvent& event );
        void OnJustifyLeft      ( wxCommandEvent& event );
        
        void ReplaceText        (int from, int to, const wxString& text);
        
        virtual void OnCommentblock     ( wxCommandEvent& event );
        virtual void OnUncommentblock   ( wxCommandEvent& event );

};


class FB_STC_FB : public FB_STC
{
    public:
    FB_STC_FB ( wxWindow * parent, FB_Doc * doc, FB_Config * config );
    void OnCharAdded( wxStyledTextEvent &event );
    void LoadSettings ( );
    void OnCommentblock     ( wxCommandEvent& event );
    void OnUncommentblock   ( wxCommandEvent& event );
};

#endif
