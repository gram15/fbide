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

#include "inc/regmanager.h"

#include <wx/fileconf.h>
#include <wx/wfstream.h>
#include <wx/confbase.h>

using namespace FBIdeRegistry;

/**
 * Constructs a new Registry base
 */
RegistryBase::RegistryBase()
{
  return;
}



/**
 * Destroy
 */
RegistryBase::~RegistryBase ()
{
  wxMutexLocker lock(m_LockerMutex);

  RegistryFolderMap * folderMap;
  RegistryValueMap * valueMap;
  RegistryFolderMap::iterator folderIter;
  RegistryNamespaceMap::iterator nsIter;

  for (nsIter = m_namespace.begin(); nsIter != m_namespace.end(); nsIter++)
  {
    folderMap = (*nsIter).second;
    for (folderIter = folderMap->begin(); folderIter != folderMap->end(); folderIter++)
    {
      valueMap = (*folderIter).second;
      valueMap->clear();
      delete valueMap;
    }
    folderMap->clear();
    delete folderMap;
  }
  m_namespace.clear();
}



/**
 * Returns a folder map for the given namespace.
 * If doesn't exist then it is creates.
 */
RegistryFolderMap * RegistryBase::GetFolderMap (const wxString & ns)
{
  wxMutexLocker lock(m_LockerMutex);

  #if __WXDEBUG__
    wxASSERT_MSG (!ns.IsEmpty(), _T("Registry: an emptry namespace name!"));
    wxRegEx regex(_T("^[[:alnum:]_]+$"));
    wxASSERT_MSG (regex.Matches(ns), _T("Registry: Invalid namespace: " + ns));
  #endif

  if (m_namespace.find(ns) == m_namespace.end()) {
    // if no namespace yet
    RegistryFolderMap * map = new RegistryFolderMap;
    m_namespace[ns] = map;
    return map;
  }
  return m_namespace[ns];
}



/**
 * Get value map for the folder
 */
RegistryValueMap * RegistryBase::GetValueMap (RegistryFolderMap * folderMap, const wxString & folder)
{
  wxMutexLocker lock(m_LockerMutex);

  #if __WXDEBUG__
    wxASSERT (folderMap);
    wxASSERT_MSG (!folder.IsEmpty(), _T("Registry: an emptry folder name!"));
    wxRegEx regex;
    if (folder.Len() > 1)
      regex.Compile(_T("^(/([[:alnum:]_]+))+$"));
    else
      regex.Compile(_T("^/$"));
    wxASSERT_MSG (regex.Matches(folder), _T("Registry: invalid folder: ") + folder);
  #endif

  if (folderMap->find(folder) == folderMap->end())
  {
    // folder does not yet exist
    RegistryValueMap * newFolder = new RegistryValueMap;
    (*folderMap)[folder] = newFolder;
    return newFolder;
  }
  return (*folderMap)[folder];
}



/**
 * Write value onto registry. If key doesn't exist them create
 */
void RegistryBase::Write (RegistryValueMap * valueMap, const wxString & key, const wxVariant & value)
{
  wxMutexLocker lock(m_LockerMutex);

  #if __WXDEBUG__
    wxASSERT (valueMap);
    wxASSERT_MSG (!key.IsEmpty(), _T("Registry: an emptry key name!"));
    wxRegEx regex(_T("^[[:alnum:]_]+$"));
    wxASSERT_MSG (regex.Matches(key), _T("Registry: Invalid key: ") + key);
  #endif
  (*valueMap)[key] = value;
  return;
}



/**
 * Read value from registry. If doesn't exist -default will be used.
 */
wxVariant RegistryBase::Read (RegistryValueMap * valueMap, const wxString & key, const wxVariant & defValue)
{
  wxMutexLocker lock(m_LockerMutex);

  #if __WXDEBUG__
    wxASSERT (valueMap);
    wxASSERT_MSG (!key.IsEmpty(), _T("Registry: an emptry key name!"));
    wxRegEx regex(_T("([[:alnum:].-_])+"));
    wxASSERT_MSG (regex.Matches(key), _T("Registry: Key does not match to: ([[:alnum:].-_])+"));
  #endif

  if (valueMap->find(key) == valueMap->end())
  {
    (*valueMap)[key] = defValue;
    return defValue;
  }
  return (*valueMap)[key];
}



/**
 * Save namespace content into config. Can be anything as long as derived from
 * wxConfigBase
 */
void RegistryBase::SaveNamespace (const wxString & ns, wxConfigBase * config)
{
  wxMutexLocker lock(m_LockerMutex);

  if (m_namespace.find(ns) == m_namespace.end()) return;

  RegistryFolderMap * folderMap = m_namespace[ns];
  RegistryFolderMap::iterator folderIter;
  RegistryValueMap::iterator valueIter;

  for (folderIter = folderMap->begin(); folderIter != folderMap->end(); folderIter++)
  {
    config->SetPath ((*folderIter).first);
    for (valueIter = (*folderIter).second->begin(); valueIter != (*folderIter).second->end(); valueIter++)
    {
      config->Write ((*valueIter).first, (*valueIter).second.GetString());
    }
  }

  return;
}



/**
 * Lad data from config into a namespace
 */
void RegistryBase::LoadToNamespace (const wxString & ns, wxConfigBase * config)
{
  wxMutexLocker lock(m_LockerMutex);

  LoadToNamespace (GetFolderMap(ns), _T("/"), config);
}

void RegistryBase::LoadToNamespace (RegistryFolderMap * folderMap, wxString entryGroup, wxConfigBase * config)
{
  long groupIndex = 0;
  long entryIndex = 0;
  wxString group;
  wxString entry;
  wxString path = entryGroup;
  if (path != _T("/")) path << _T("/");

  config->SetPath(entryGroup);

  RegistryValueMap * valueMap = new RegistryValueMap;
  (*folderMap)[entryGroup] = valueMap;

  if (config->GetFirstEntry(entry, entryIndex))
  do {
    (*valueMap)[entry] = config->Read(entry, _T(""));
  } while (config->GetNextEntry(entry, entryIndex));


  if (config->GetFirstGroup(group, groupIndex))
  do {
    LoadToNamespace (folderMap, path + group, config);
    config->SetPath(entryGroup);
  } while (config->GetNextGroup(group, groupIndex));
}




/**
 * Constructs us a new Registry object for use.
 */
Registry::Registry (FBIdeRegistry::RegistryBase * base, const wxString & ns)
{
  m_base = base;//RegistryBase::Get();
  SetNamespace(ns);
}



/**
 * Get current path
 * @return wxString
 */
wxString Registry::GetPath ()
{
  return m_path;
}



/**
 * Set new path
 */
void Registry::SetPath (const wxString & path)
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
 * Return current namespace
 */
wxString Registry::GetNamespace ()
{
  return m_namespace;
}



/**
 * Set new namespace
 */
void Registry::SetNamespace (const wxString & ns, const wxString & path)
{
  m_namespace = ns;
  m_folderMap = m_base->GetFolderMap (ns);
  SetPath(path);
}



/**
 * wxString
 */
wxString Registry::ReadString (const wxString & key, const wxString & defValue)
{
  return m_base->Read(m_valueMap, key, defValue).GetString();
}

void Registry::WriteString (const wxString & key, const wxString & value)
{
   m_base->Write(m_valueMap, key, value);
}


/**
 * long
 */

long Registry::ReadLong (const wxString & key, const long defValue)
{
  return m_base->Read(m_valueMap, key, defValue).GetLong();
}

void Registry::WriteLong (const wxString & key, const long value)
{
  m_base->Write(m_valueMap, key, value);
}


/**
 * bool
 */

bool Registry::ReadBool (const wxString & key, const bool defValue)
{
  return m_base->Read(m_valueMap, key, defValue).GetBool();
}

void Registry::WriteBool (const wxString & key, const bool value)
{
  m_base->Write(m_valueMap, key, value);
}


/**
 * wxColour
 */
wxColour Registry::ReadColour (const wxString & key, const wxColour & defValue)
{
  wxString colr = m_base->Read(m_valueMap, key, defValue.GetAsString(wxC2S_CSS_SYNTAX));
  return wxColour(colr);
}


void Registry::WriteColour (const wxString & key, const wxColour & value)
{
  m_base->Write(m_valueMap, key, value.GetAsString(wxC2S_CSS_SYNTAX));
}


/**
 * Load INI fail containing the config into current namespace
 */
void Registry::LoadFile (const wxFileName & file)
{
  wxFileInputStream is (file.GetFullPath());
  wxFileConfig fc(is);

  m_base->LoadToNamespace(m_namespace, &fc);
}



/**
 * Save INI current namespace into INI type file
 */
void Registry::SaveFile (const wxFileName & file)
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
Registry::~Registry ()
{

}
