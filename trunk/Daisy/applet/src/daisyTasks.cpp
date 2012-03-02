/*
*   Tasks: daisy
*   Description: a daisy for plasma
*   Copyright (C) 2009,2010 by Lechio <Alessandros1pt@yahoo.com.br>
*	Patch ligne 268: pierre.parent@insa-rouen.fr
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as
*   published by the Free Software Foundation; either version 3, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details
*
*   You should have received a copy of the GNU General Public
*   License along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/







//-----------------------------------------------------------------------------
// Window added
void daisy::windowAdded(WId id)
{
  if (!m_drawerscleared)clearDrawers();
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMName | NET::WMVisibleName , NET::WM2WindowClass );
  
  if ( m_alias.indexOf( taskInfo.windowClassName() ) != -1 )
  {
    m_activetasks << m_alias.indexOf( taskInfo.windowClassName() );
    if ( m_showindicons )emit update();
  }
  else if ( m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) ) != -1 )
  {
    m_activetasks << m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) );
    if ( m_showindicons )emit update();
  }
  else if ( m_alias.indexOf( taskInfo.name() ) != -1 )
  {
    m_activetasks << m_alias.indexOf( taskInfo.name() );
    if ( m_showindicons )emit update();
  }
  
}




//-----------------------------------------------------------------------------
// Window removed
//FIXME
void daisy::windowRemoved(WId id)
{
  if (!m_drawerscleared)clearDrawers();
  m_closingwindow = -1;
    
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMName | NET::WMVisibleName , NET::WM2WindowClass );
  if ( m_alias.indexOf( taskInfo.windowClassName() ) != -1 )
  {
    m_closingwindow = m_alias.indexOf( taskInfo.windowClassName() );
    if ( m_showindicons )m_up_tmr->setInterval(1500);m_up_tmr->start();
  }
  else if ( m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) ) != -1 )
  {
    m_closingwindow = m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) );
    if ( m_showindicons )m_up_tmr->setInterval(1500);m_up_tmr->start();
  }
  else if ( m_alias.indexOf( taskInfo.name() ) != -1 )
  {
    m_closingwindow = m_alias.indexOf( taskInfo.name() );
    if ( m_showindicons )m_up_tmr->setInterval(1500);m_up_tmr->start();
  }
  else if ( m_alias.indexOf( taskInfo.visibleName() ) != -1 )
  {
    m_closingwindow = m_alias.indexOf( taskInfo.visibleName() );
    if ( m_showindicons )m_up_tmr->setInterval(1500);m_up_tmr->start();
  }
  
  else
  {
    getAllTasks();
  }
  
  
  if ( m_showindicons )emit update();
  
}





//-----------------------------------------------------------------------------
// Active Window changed
//FIXME
void daisy::activeWindowChanged(WId id)
{
  Q_UNUSED(id);
  
  getAllTasks();
  if (!m_drawerscleared)clearDrawers();
  if (m_showindicons)emit update();
  
}










//-----------------------------------------------------------------------------
// Desktop changed
void daisy::currentDesktopChanged(int desktop)
{
  Q_UNUSED(desktop);
  
  if (!m_drawerscleared)clearDrawers();
  
  if ( m_autohide && m_type == QString("standard_dock") && !m_inpanel && !m_floating && m_showondesk )
  {
    m_tracker_tmr->stop();
    if ( !isVisible() ){setVisible(true);}
    m_tracker_tmr->setInterval(m_hidingdelay);m_tracker_tmr->start();
  }
  
}









////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////








//-----------------------------------------------------------------------------
// Startup added
//FIXME
void daisy::startupAdded(Startup* startupItem)
{
  
  m_startingwindow = -1;
  if ( startupItem )
  {
    
    if ( m_alias.indexOf( startupItem->text() ) != -1 )
    {
      m_startingwindow = m_alias.indexOf( startupItem->text() );
    }
    
    else if ( m_alias.indexOf( startupItem->bin() ) != -1 )
    {
      m_startingwindow = m_alias.indexOf( startupItem->bin() );
    }
    
    else
    {
      KStartupInfoId taskid = startupItem->id();
    }
    
    
    if ( m_showindicons )emit update();
    
  }

}





//-----------------------------------------------------------------------------
// Startup removed
//FIXME
void daisy::startupRemoved(Startup* startupItem)
{
  
  Q_UNUSED(startupItem);
  
}







//-----------------------------------------------------------------------------
// Window changed
//FIXME Signal is emited 4 times?
void daisy::windowChanged(WId id, const unsigned long* properties )
{
  QString widclass_tmp;
  Plasma::ToolTipContent toolTipData;toolTipData.setAutohide(false);
  
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMState | NET::XAWMState | NET::WMDesktop, NET::WM2WindowClass );
  
  Task* task_tmp = TaskManager::TaskManager::self()->findTask( id );
  
  
  if (  m_alias.indexOf( taskInfo.windowClassName() ) != -1 || m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) ) != -1 )
  {
    
    if ( m_alias.indexOf( taskInfo.windowClassName() ) != -1  )
    {widclass_tmp = QString( taskInfo.windowClassName() );}
    else
    {widclass_tmp = QString(taskInfo.windowClassClass().toLower());}
    
    
    //ATTENTION
    checkAttention( taskInfo, widclass_tmp );
    
    if (m_showtooltips_l)
    {
      
      int win_count = m_activetasks.count( m_alias.indexOf( widclass_tmp ) );
      QString str;QString desk_name = KWindowSystem::desktopName( taskInfo.desktop() );
      
      if ( win_count == 1 )
      {
	if (taskInfo.desktop() != -1)
	{str.append( desk_name );str.insert( 0, i18n("On ") );}
	else str.insert( 0, i18n("On all desktops") );
	toolTipData.setMainText( taskInfo.visibleIconNameWithState()   );
	toolTipData.setSubText( str ); 
      }
      else
      {
	str.setNum( win_count );str.append( i18n(" instances") );
	toolTipData.setMainText( widclass_tmp );
	toolTipData.setSubText( str );
      }
      
      if ( m_tiptype == "thumbnail" )
      {
	#if (KDE_VERSION_MINOR < 3)
	toolTipData.setWindowToPreview(id);
	#else
	toolTipData.setWindowsToPreview( matchAllTasks( widclass_tmp, 4 ) );
	toolTipData.setClickable(true);
	#endif
      }
      
      //We need to check task_tmp actually exists before accessing its icon...
      if ( (m_tiptype == "thumbnail" || m_tiptype == "icon") && task_tmp)
	toolTipData.setImage( task_tmp->icon(32, 32, true) );
      Plasma::ToolTipManager::self()->setContent(m_widgets[m_alias.indexOf( widclass_tmp )], toolTipData);
    }
    
    
    if ( m_taskpreviews && m_type == QString("standard_dock") && showedTasks.indexOf( id )!=-1 )
    {
      if (m_showtooltips_l && task_tmp)
      {Plasma::ToolTipManager::self()->setContent(m_taskicons[showedTasks.indexOf( id )], toolTipData);}
      
      if(properties[ NETWinInfo::PROTOCOLS ] & NET::WMIcon)
      {
	m_uti_tmr->stop();
	m_toupwid = id;
	m_uti_tmr->start();
      }
    }
  
    
    
  }

  
}





//-----------------------------------------------------------------------------
// Work area changed
//FIXME
void daisy::workAreaChanged()
{
  
  
}





////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////






//-----------------------------------------------------------------------------
// ATTENTION
void daisy::checkAttention( KWindowInfo taskInfo, QString widclass_tmp )
{
  
  if ( taskInfo.hasState( NET::DemandsAttention ) && !m_attentionwindow.contains( m_alias.indexOf( widclass_tmp )) )
  {
    m_attentionwindow << m_alias.indexOf( widclass_tmp );
  }
  
  else if ( m_attentionwindow.contains( m_alias.indexOf( widclass_tmp )) )
  {
    m_attentionwindow.removeAt(m_attentionwindow.indexOf( m_alias.indexOf( widclass_tmp )) );
  }
  
  
}









//-----------------------------------------------------------------------------
// Get all the tasks
//FIXME
QList<WId> daisy::getAllTasks()
{
  m_activetasks.clear();m_attentionwindow.clear();showedTasks.clear();
  QList<WId> taskDict = KWindowSystem::windows();
  m_activewindow = -1;m_startingwindow = -1;m_closingwindow = -1;
  Plasma::ToolTipContent toolTipData;toolTipData.setAutohide(false);
  QString str;QString widclass_tmp;total_taskpreviews=0;
  
  
  //THUMBNAILS
  if ( m_taskpreviews && m_type == QString("standard_dock") )
  {
    for (int i = 0; i < m_max_taskpreviews; ++i)
    {m_taskicons[i]->setGeometry( QRect(-10000, -10000, 0, 0)  );}
  }
  
  
  if (m_showtooltips_l)clearToolTipContent();
  
  
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMState | NET::XAWMState | NET::WMDesktop | NET::WMWindowType, NET::WM2WindowClass );
    
    
    Task* task_tmp = TaskManager::TaskManager::self()->findTask( *it );
    if ( task_tmp && *it == KWindowSystem::activeWindow() )
    {m_focusedWindow = *it;}
    
    
    //THUMBNAILS
    if ( m_taskpreviews && m_type == QString("standard_dock") && task_tmp )
    {
      if ( !m_showtaskoflauncher && ( m_alias.indexOf( taskInfo.windowClassName() ) != -1 || m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) ) != -1 ) )
      {}
      
      else if ( total_taskpreviews<m_max_taskpreviews )
      {
	createTaskThumbnail(task_tmp, total_taskpreviews);
	total_taskpreviews++;
	showedTasks << *it;
      }
    }
    
    
    
    if ( m_alias.indexOf( taskInfo.windowClassName() ) != -1 || m_alias.indexOf( QString(taskInfo.windowClassClass().toLower()) ) != -1 )
    {
      
      if ( m_alias.indexOf( taskInfo.windowClassName() ) != -1  )
	widclass_tmp = QString( taskInfo.windowClassName() );
      else
	widclass_tmp = QString(taskInfo.windowClassClass().toLower());
      
      
      //ATTENTION
      checkAttention( taskInfo, widclass_tmp );
      
      
      
      m_activetasks << m_alias.indexOf( widclass_tmp );
      if ( *it ==  KWindowSystem::activeWindow() )
	m_activewindow = m_alias.indexOf( widclass_tmp );
      
      
      //TOLLTIPS
      if (m_showtooltips_l)
      {
	str.clear();QString desk_name = KWindowSystem::desktopName( taskInfo.desktop() );
	int win_count = m_activetasks.count( m_alias.indexOf( widclass_tmp ) );
	
	if ( win_count == 1 )
	{
	  if (taskInfo.desktop() != -1)
	  {str.append( desk_name );str.insert( 0, i18n("On ") );}
	  else str.insert( 0, i18n("On all desktops") );
	  toolTipData.setMainText( taskInfo.visibleIconNameWithState()   );
	  toolTipData.setSubText( str );
	}
	else
	{
	  str.setNum( win_count );str.append( i18n(" instances") );
	  toolTipData.setMainText( widclass_tmp );
	  toolTipData.setSubText( str );
	}
	
	if ( m_tiptype == "thumbnail" )
	{
	  #if (KDE_VERSION_MINOR < 3)
	  toolTipData.setWindowToPreview(*it);
	  #else
	  toolTipData.setWindowsToPreview( matchAllTasks( widclass_tmp, 4 ) );
	  toolTipData.setClickable(true);
	  #endif
	}
	
	if ( m_tiptype == "thumbnail" || m_tiptype == "icon" )
	  toolTipData.setImage( KIcon( m_values[m_alias.indexOf( widclass_tmp )][2]).pixmap(IconSize(KIconLoader::Panel)) );
	Plasma::ToolTipManager::self()->setContent(m_widgets[m_alias.indexOf( widclass_tmp )], toolTipData);
	
      }
      
      
    }
    
  }
  
  
  //THUMBNAILS
  if ( m_taskpreviews && m_type == QString("standard_dock") )
  {
    resizeRepos( true );
  }
  
  
  return taskDict;
}











//-----------------------------------------------------------------------------
// Create task thumbnail
//FIXME
void daisy::createTaskThumbnail( Task* task_tmp, int j )
{
  QIcon thumbnail;
  //thumbnail = QIcon( QPixmap::grabWindow ( task_tmp->win(), 0, 0, -1, -1 ) );//This would suck
  thumbnail = KIcon( task_tmp->icon( m_icodimension, m_icodimension, true ) );
  
  m_taskicons[j]->setIcon(thumbnail);
  
  if ( m_orientation== QString("horizontal") )
  {
    m_taskicons[j]->setGeometry( QRect( last_icopos[0]+( ( j* (m_icodimension+(m_icodimension*m_icospacing)) ) ), last_icopos[1], m_icodimension, m_icodimension) );
  }
  else
  {
    m_taskicons[j]->setGeometry( QRect( last_icopos[0], last_icopos[1]+( ( j* (m_icodimension+(m_icodimension*m_icospacing)) ) ), m_icodimension, m_icodimension) );
  }
  
  
  
  
  
  if (m_showtooltips_l)
  {
    Plasma::ToolTipContent toolTipData;toolTipData.setAutohide(false);
    QString str;QString desk_name = KWindowSystem::desktopName( task_tmp->desktop() );
    
    if (task_tmp->desktop() != -1)
    {str.append( desk_name );str.insert( 0, i18n("On ") );}
    else str.insert( 0, i18n("On all desktops") );
    toolTipData.setMainText( task_tmp->visibleNameWithState() );
    toolTipData.setSubText( str );
    
    if ( m_tiptype == "thumbnail" )
    {
      toolTipData.setWindowToPreview( task_tmp->window() );
      toolTipData.setClickable(true);
    }
    
    if ( m_tiptype == "thumbnail" || m_tiptype == "icon" )
      toolTipData.setImage( task_tmp->icon(32, 32, true) );
    
    Plasma::ToolTipManager::self()->setContent(m_taskicons[j], toolTipData);
  }

  
}














//-----------------------------------------------------------------------------
// Match a task by its name
//FIXME
WId daisy::matchTask(QString name)
{
  
  QList<WId> taskDict = KWindowSystem::windows();
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName , NET::WM2WindowClass );
    if ( name == QString(taskInfo.windowClassName()) || name == QString(taskInfo.windowClassClass().toLower()) )
    {
      return *it;
    }
  }
  
  return 0;
}






//-----------------------------------------------------------------------------
// Get all tasks by name
//FIXME
QList<WId> daisy::matchAllTasks(QString name, int maxtasks)
{
  QList<WId> ret_taskDict;
  QList<WId> taskDict = KWindowSystem::windows();
  
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName , NET::WM2WindowClass );
    
    if ( name == QString(taskInfo.windowClassName()) || name == QString(taskInfo.windowClassClass().toLower()) )
    {
      if ( maxtasks > ret_taskDict.size() || maxtasks == -1 )
	ret_taskDict << *it;
      else
	break;
    }
    
  }
  
  return ret_taskDict;
  
}







//-----------------------------------------------------------------------------
// Get task
bool daisy::getTaskPtr( QString name  )
{
  
  QList<WId> taskDict = KWindowSystem::windows();
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName, NET::WM2WindowClass );
    
    if ( taskInfo.windowClassName() == name || taskInfo.visibleName() == name || taskInfo.name() == name || QString(taskInfo.windowClassClass().toLower()) == name  )
    {
      m_task = TaskManager::TaskManager::self()->findTask( *it );
      return true;
    }
  }
  return false;
  
}















//-----------------------------------------------------------------------------
// Toggle task
//FIXME
void daisy::toggTask(WId id)
{
  
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMState, NET::WM2WindowClass );
  
  if ( taskInfo.valid() )
  {
    //HACK widget gains focus on click FIXME
    if ( !taskInfo.isMinimized() && ( m_actwin_save == id ) )
    {KWindowSystem::minimizeWindow( id, true  );}
    else
    {
      KWindowSystem::unminimizeWindow( id, true  );
      KWindowSystem::activateWindow( id  );
    }
    m_up_tmr->stop();m_up_tmr->setInterval(10);m_up_tmr->start();
    
  }
  
}







//-----------------------------------------------------------------------------
// Toggle Shade task
//FIXME
void daisy::toggShadeTask(WId id)
{
  
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMState, NET::WM2WindowClass );
  
  if ( taskInfo.valid() )
  {
    if ( taskInfo.hasState( NET::Shaded )  )
    {
      KWindowSystem::clearState( id, NET::Shaded );
      KWindowSystem::unminimizeWindow( id, true  );
//       KWindowSystem::activateWindow( id  );
    }
    else
    {
      KWindowSystem::setState( id, NET::Shaded );
//       KWindowSystem::setState( id, NET::DemandsAttention );//FOR TESTING, COMMENT AFTER
    }
  }
}




//-----------------------------------------------------------------------------
// Close task
//FIXME
void daisy::closeTask(WId id)
{
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMState );
  if ( taskInfo.valid() )
  {
    NETRootInfo ri( QX11Info::display(), NET::CloseWindow );
    ri.closeWindowRequest( id );
  }
}






// Scroll tasks
void daisy::scrollTasks(int delta)
{
  WId widstore_tmp = 0;WId wid_tmp = 0;
  QList<WId> real_taskDict;QList<WId> taskDict = KWindowSystem::windows();QList<WId>::ConstIterator it;
  KWindowInfo taskInfo = KWindowSystem::windowInfo( m_focusedWindow, NET::WMState, NET::WM2WindowClass );
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    Task* task_tmp = TaskManager::TaskManager::self()->findTask( *it );
    if ( task_tmp ){real_taskDict << *it;}
  }
  if (real_taskDict.size() > 0)
  {
    if ( real_taskDict.indexOf( KWindowSystem::activeWindow() ) != -1 ){widstore_tmp = KWindowSystem::activeWindow();}
    else{widstore_tmp = m_focusedWindow;}
    {
      if (delta >0)
      {
	if (real_taskDict.indexOf( widstore_tmp ) < real_taskDict.size()-1 ){wid_tmp = real_taskDict[real_taskDict.indexOf( widstore_tmp )+1];}
	else{wid_tmp = real_taskDict[0];}
      }
      else
      {
	if (real_taskDict.indexOf( widstore_tmp ) > 0 ){wid_tmp = real_taskDict[real_taskDict.indexOf( widstore_tmp )-1];}
	else{wid_tmp = real_taskDict[real_taskDict.size()-1];}
      }
      if (real_taskDict.size() == 1)
      {
	taskInfo = KWindowSystem::windowInfo( wid_tmp, NET::WMState, NET::WM2WindowClass );
	if ( !taskInfo.isMinimized() )KWindowSystem::minimizeWindow( wid_tmp, true  );
	else focusTask(wid_tmp);
      }
      else focusTask(wid_tmp);
    }
  }
}





//-----------------------------------------------------------------------------
// Focus task
//FIXME
void daisy::focusTask(WId id)
{
  KWindowInfo taskInfo = KWindowSystem::windowInfo( id, NET::WMState, NET::WM2WindowClass );
  if ( taskInfo.valid() )
  {
    KWindowSystem::unminimizeWindow( id, true  );
    KWindowSystem::activateWindow( id  );
  }
}




//-----------------------------------------------------------------------------
// HACK Delay updating task icon
void daisy::delayTaskIcoChange(void)
{
  m_uti_tmr->stop();
  Task* task_tmp = TaskManager::TaskManager::self()->findTask( m_toupwid );
  if ( task_tmp )
  {
//     QIcon thumbnail;
//     thumbnail = KIcon( task_tmp->icon( m_icodimension, m_icodimension, true ) );
//     m_taskicons[showedTasks.indexOf( m_toupwid )]->setIcon(thumbnail);
    getAllTasks();
    emit update();
  }
}




