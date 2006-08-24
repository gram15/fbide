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

#include "inc/styleinfo.h"

#define SECURITY_STRING _T("fbi@STYLEv1:")
#define SECURITY_SIZE 12

wxString StyleInfo::GetAsString() const
{
  wxString data;
  data << SECURITY_STRING;
  data << GetStyle() << _T("|");
  data << GetFont() << _T("|");
  data << GetSize() << _T("|");
  data << GetFG().GetAsString(wxC2S_CSS_SYNTAX) << _T("|");
  data << GetBG().GetAsString(wxC2S_CSS_SYNTAX);
  return data;
}


void StyleInfo::Set (wxString data)
{
  wxString tmp;
  int pos;
  long buffer;

  // security check
  if (data.Left(SECURITY_SIZE) != SECURITY_STRING) return;
  data = data.Mid(SECURITY_SIZE);

  // Style
  pos = data.Find('|');
  tmp = data.Left(pos);
  tmp.ToLong(&buffer, 10);
  SetStyle(buffer);
  data = data.Mid(pos + 1);

  // font
  pos = data.Find('|');
  SetFont(data.Left(pos));
  data = data.Mid(pos + 1);

  // Size
  pos = data.Find('|');
  tmp = data.Left(pos);
  tmp.ToLong(&buffer, 10);
  SetSize(buffer);
  data = data.Mid(pos + 1);

  // font FG
  pos = data.Find('|');
  SetFG(data.Left(pos));
  data = data.Mid(pos + 1);

  // font BG
  SetBG(data);
}
