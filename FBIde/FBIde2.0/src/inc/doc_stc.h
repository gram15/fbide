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

#ifndef DOC_STC_H_INCLUDED
#define DOC_STC_H_INCLUDED

  #include <wx/stc/stc.h>
  #include "styleinfo.h"

  /**
   * This is a textDocument based on wxStyledTextControl
   */

  class Doc_Stc : public Document <wxStyledTextCtrl>
  {
    public:
      Doc_Stc();
      void LoadStyle (const wxString & regPath =_T("style://stc/default"));
      void SetStyle (int style, const StyleInfo & data);
  };

#endif // DOC_STC_H_INCLUDED
