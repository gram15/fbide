/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005 - 2006 Albert Varaksin
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

#include "inc/fbide.h"
#include "inc/manager.h"

#include "inc/main.h"

#include "inc/doc_stc.h"

/**
 * This is main entry function into our FBIde
 *
 * If returns false then application will not be started.
 * @return bool
 */
bool FBIde::OnInit()
{

  // Force creation of managers
  (void)Manager::Get();
  (void)Manager::Get()->GetRegManager();
  (void)Manager::Get()->GetUiManager();
  (void)Manager::Get()->GetDocManager();


  // Set top window
  SetTopWindow (Manager::Get()->GetUiManager()->GetFrame());

  Doc_Stc * tt1 = new Doc_Stc;
  tt1->ShowDocument();

  Doc_Stc * tt2 = new Doc_Stc;
  tt2->ShowDocument();


  // Show
  Manager::Get()->GetUiManager()->GetFrame()->Show();
  return true;
}



/**
 * This is function that gets called apon exit from FBIde
 *
 * Returns an exit code.
 * @return int
 */
int FBIde::OnExit()
{
  wxTheClipboard->Flush();
  return wxApp::OnExit();
}



/**
 * Implement and declare FBIde application
 */
IMPLEMENT_APP(FBIde)
DECLARE_APP(FBIde)
