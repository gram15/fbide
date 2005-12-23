/////////////////////////////////////////////////////////////////////////////
// Name:        fbide.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:21:36
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FBIDE_H_
#define _FBIDE_H_


class FBIde: public wxApp
{    
    DECLARE_CLASS( FBIde )

public:

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

};


/*!
 * Application instance declaration 
 */

DECLARE_APP(FBIde)

#endif
    // _FBIDE_H_
