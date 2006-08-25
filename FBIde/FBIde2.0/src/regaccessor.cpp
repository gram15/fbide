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

#include "inc/manager.h"
#include "inc/regaccessor.h"

#include <wx/fileconf.h>
#include <wx/wfstream.h>
#include <wx/confbase.h>

/**
 * Constructs us a new RegAccessor object for use.
 */
RegAccessor::RegAccessor (const wxString & ns)
{
    m_base = Manager::Get()->GetRegManager();
    SetNamespace(ns);
}



/**
 * Set new path
 */
void RegAccessor::SetPath (const wxString & path)
{
    if (path[0] == '/') {
    m_path = path;
    } else {
    int pos = path.Find(_T("://"));
    if (pos != -1) {
      SetNamespace (path.Left(pos), path.Mid(pos + 2));
      return;
    } else {
      if (m_path != _T("/"))
        m_path << _T("/") << path;
      else
        m_path << path;
    }
    }
    m_valueMap = m_base->GetValueMap (m_folderMap, m_path);
}


/**
 * Set new namespace
 */
void RegAccessor::SetNamespace (const wxString & ns, const wxString & path)
{
    m_namespace = ns;
    m_folderMap = m_base->GetFolderMap (ns);
    SetPath(path);
}



/**
 * wxString
 */
wxString RegAccessor::ReadString (const wxString & key, const wxString & defValue)
{
    return m_base->Read(m_valueMap, key, defValue).GetString();
}

void RegAccessor::WriteString (const wxString & key, const wxString & value)
{
    m_base->Write(m_valueMap, key, value);
}


/**
 * long
 */

long RegAccessor::ReadLong (const wxString & key, const long defValue)
{
    return m_base->Read(m_valueMap, key, defValue).GetLong();
}

void RegAccessor::WriteLong (const wxString & key, const long value)
{
    m_base->Write(m_valueMap, key, value);
}


/**
 * bool
 */

bool RegAccessor::ReadBool (const wxString & key, const bool defValue)
{
    return m_base->Read(m_valueMap, key, defValue).GetBool();
}

void RegAccessor::WriteBool (const wxString & key, const bool value)
{
    m_base->Write(m_valueMap, key, value);
}


/**
 * wxColour
 */
wxColour RegAccessor::ReadColour (const wxString & key, const wxColour & defValue)
{
    wxString colr = m_base->Read(m_valueMap, key, defValue.GetAsString(wxC2S_CSS_SYNTAX));
    return wxColour(colr);
}


void RegAccessor::WriteColour (const wxString & key, const wxColour & value)
{
    m_base->Write(m_valueMap, key, value.GetAsString(wxC2S_CSS_SYNTAX));
}


/**
 * Load INI fail containing the config into current namespace
 */
void RegAccessor::LoadFile (const wxFileName & file)
{
    wxFileInputStream is (file.GetFullPath());
    wxFileConfig fc(is);

    m_base->LoadToNamespace(m_namespace, &fc);
}



/**
 * Save INI current namespace into INI type file
 */
void RegAccessor::SaveFile (const wxFileName & file)
{
    wxFileInputStream is (file.GetFullPath());
    wxFileOutputStream os (file.GetFullPath());
    wxFileConfig fc(is);

    m_base->SaveNamespace(m_namespace, &fc);

    fc.Save(os);

    return;
    }



/**
 * Destroy...
 */
RegAccessor::~RegAccessor ()
{

}
