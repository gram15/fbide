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

#ifndef REGACCESSOR_H_INCLUDED
#define REGACCESSOR_H_INCLUDED

    #include "regmanager.h"

    /**
     * This class provides the interface for
     * interacting with FBIde registry.
     */
    class RegAccessor
    {
        public:
            RegAccessor (const wxString & ns);
            ~RegAccessor();

            wxString ReadString (const wxString & key, const wxString & defValue = _T(""));
            void WriteString (const wxString & key, const wxString & value);

            long ReadLong (const wxString & key, const long defValue = 0L);
            void WriteLong (const wxString & key, const long value);

            bool ReadBool (const wxString & key, const bool defValue = false);
            void WriteBool (const wxString & key, const bool value);

            wxColour ReadColour (const wxString & key, const wxColour & defValue = _T("RGB(0, 0, 0)"));
            void WriteColour (const wxString & key, const wxColour & value);

            wxString GetPath () const { return m_path; }
            void SetPath (const wxString & path);

            wxString GetNamespace () const { return m_namespace; }
            void SetNamespace (const wxString & ns, const wxString & folder = _T("/"));

            void LoadFile (const wxFileName & file);
            void SaveFile (const wxFileName & file);


        private:
            wxString      m_path;
            wxString      m_namespace;
            RegManager  * m_base;

            RegManager::RegistryFolderMap * m_folderMap;
            RegManager::RegistryValueMap  * m_valueMap;

    };

#endif // REGACCESSOR_H_INCLUDED
