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

#ifndef REGMANAGER_H_INCLUDED
#define REGMANAGER_H_INCLUDED

#include "singleton.h"

/**
 * The content of the namespace is for private use of Registry only
 */


  /**
   * This class holds and manages the registry content
   * Registry is structured in 3 parts
   *   1 - namespaces. Registry content is splitted into namespaces to allow
   *       more flexibility. (like protocol in url aka: http://)
   *       Namespaces are linear!
   *   2 - Folders. are second level and reside in the namespace
   *       Folders can be nested in eachother: /some, /som/nested
   *       and seperated with / character
   *   3 - keys. Reside in the folders and hold actual value
   */
  class RegManager : public Singleton<RegManager>
  {
      public:
          /**
           * Hash map holding key value pairs
           */
          WX_DECLARE_STRING_HASH_MAP(wxVariant, RegistryValueMap);


          /**
           * Hash map holding folders and RegistryValueMap
           */
          WX_DECLARE_STRING_HASH_MAP(RegistryValueMap *, RegistryFolderMap);


          /**
           * Hash map that holds namespaces and RegistryFolderMap
           */
          WX_DECLARE_STRING_HASH_MAP(RegistryFolderMap *, RegistryNamespaceMap);

      private:
          friend class Singleton<RegManager>;
          RegManager();
          ~RegManager();

          RegistryNamespaceMap m_namespace;
          wxMutex m_LockerMutex;

      public:

          /**
           * Return foldermap. Takes namespace name as argument
           */
          RegistryFolderMap * GetFolderMap (const wxString & ns);

          /**
           * Return values. Takes foldermap and name of the folder
           */
          RegistryValueMap  * GetValueMap (RegistryFolderMap * folderMap, const wxString & folder);

          /**
           * Values are handled and stored using wxWidget's wxVariant class
           */
          wxVariant Read (RegistryValueMap * valueMap, const wxString & key, const wxVariant & defValue);
          void Write (RegistryValueMap * valueMap, const wxString & key, const wxVariant & value);

          /**
           * Save / Load namespace data from file
           */
          void SaveNamespace (const wxString & ns, wxConfigBase * config);
          void LoadToNamespace (const wxString & ns, wxConfigBase * config);

      private:
          void LoadToNamespace (RegistryFolderMap * folderMap, wxString entryGroup, wxConfigBase * config);
  };

#endif // REGMANAGER_H_INCLUDED
