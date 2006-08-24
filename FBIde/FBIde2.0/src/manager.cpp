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


/**
 * Holds an instance to Manager class
 * @var Manager *
 */
Manager * Manager::m_instance = NULL;



/**
 * Constructor of the Manager class
 *
 * Is private to avoid duplicate instace creation of the manager
 */
Manager::Manager()
{
  m_instance = this;
  m_isShuttingDown = false;
  m_parentEventHanlder = NULL;

  m_registryBase = new FBIdeRegistry::RegistryBase;
  m_uiMngr = new UiManager;
  m_docMngr = new DocManager;

  return;
}



/**
 * Destroy all active managers
 */
Manager::~Manager()
{
  delete m_registryBase;
  m_instance = NULL;
}



/**
 * Returns an instance to Manager
 * @return Manager *
 */
Manager * Manager::Get()
{
  if (m_instance == NULL)
    new Manager;

  return m_instance;
}



/**
 * Sets an instance of teh Manager if not yet set
 * (Is used for setting up manager in plugins)
 *
 * @var Manager *
 */
void Manager::Set (Manager * mngr)
{
  if (m_instance == NULL) m_instance = mngr;
}



/**
 * Releases an instance of the Manager
 * However only in FBIde::OnExit should this be called!
 */
void Manager::Release ()
{
  delete this;
}


/**
 * Shut down managers
 */
void Manager::ShutDown()
{
  delete m_docMngr;
  m_docMngr = NULL;
  m_isShuttingDown = true;
}



/**
 * Set an event handler of the base (wxApp usually)
 */
void Manager::SetParentEventHandler (wxEvtHandler * evt)
{
  if (m_parentEventHanlder) return;
  m_parentEventHanlder = evt;
}



/**
 * Get base event handler
 */
wxEvtHandler * Manager::GetParentEventHandler ()
{
  return m_parentEventHanlder;
}
