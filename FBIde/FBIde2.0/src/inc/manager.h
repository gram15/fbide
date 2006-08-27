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

#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include "event.h"
#include "regmanager.h"
#include "uimanager.h"
#include "docmanager.h"


  /**
   * This class is used to access manage all managers.
   * it is a singleton class and only way to obtain instance is to use
   * Get() method.
   */
  class Manager
  {
    private:
      Manager();
      ~Manager();

      bool m_isShuttingDown;

    public:
      static Manager * Get();

      /**
       * Get Ui manager instance
       */
      UiManager * GetUiManager() const { return UiManager::Get(); }
      DocManager * GetDocManager() const { return DocManager::Get(); }
      RegManager * GetRegManager() const { return RegManager::Get(); }

      /**
       * If we are shutting down
       */
      bool IsShuttingDown() const { return m_isShuttingDown; }
      void ShutDown();
  };

#endif // MANAGER_H_INCLUDED
