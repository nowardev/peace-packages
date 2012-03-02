/*
*   Launchers: daisy
*   Description: a daisy for plasma
*   Copyright (C) 2009,2010 by Lechio <Alessandros1pt@yahoo.com.br>
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
// Create the Launchers
void daisy::createLaunchers( QString &m_type  )
{
  
  #ifdef INFORMATION_DEBUG
  kDebug() <<m_type;
  #endif
  
  m_widgets.clear();m_acta.clear();m_indicons.clear();
  for (int i = 0; i < m_values.size(); ++i)
  {
    m_acta << new QAction(KIcon(m_avalues[i][2]), "", this);
    m_widgets << new MyIcon( m_values[i], m_avalues[i], m_acta[i], this );
    if ( i == m_trash_spot && m_type != QString("media_controller") )
    {m_widgets[i]->addIconAction(m_act_emptytrash);}
    connect(m_widgets[i], SIGNAL(pressed(bool)), this, SLOT(launClick()));
    m_widgets[i]->installEventFilter(this);
    m_zoomszdiff.append(0);
    m_zoomposdiff.append(0);
    
    
    //HACK Plasma:Svg stopped working right.
    m_indicons << new Plasma::FrameSvg( this );
    m_indicons[i]->setImagePath("widgets/tasks-indicators");
    m_indicons[i]->setElementPrefix( QString("inactive") );
    m_indicons[i]->setEnabledBorders(Plasma::FrameSvg::NoBorder);
    m_indicons[i]->setCacheAllRenderedFrames(true);
    
    if (i > 8) m_domino << i;
  }
  polishLaunchers();
  createTaskIcons();
  
  
}




//-----------------------------------------------------------------------------
// Create the Task Icons
void daisy::createTaskIcons()
{
  int all = m_taskicons.size();
  for (int i = 0; i < all; ++i)
  {delete m_taskicons[i];}
  m_taskicons.clear();
  
  
  for (int i = 0; i < m_max_taskpreviews; ++i)
  {
    m_taskicons << new Plasma::IconWidget(QIcon(""), QString(""), this);
    m_taskicons[i]->setGeometry( QRect(-10000, -10000, 0, 0)  );
    
    m_taskicons[i]->setCursor(Qt::PointingHandCursor);
    
    connect(m_taskicons[i], SIGNAL(pressed(bool)), this, SLOT(taskClick()));
    m_taskicons[i]->installEventFilter(this);
    
    if (m_showclosetask)
      m_taskicons[i]->addIconAction(m_act_closetask);
    
  }
  
  
}








//-----------------------------------------------------------------------------
// Paint the launchers
void daisy::paintLaunchers(void)
{
  
  QList<int> m_paint_order;
  
  if ( m_type==QString("media_controller") || m_type==QString("circular_dock") )
  {
    m_paint_order.clear();
    if ( m_type==QString("circular_dock") )m_paint_order << 4 << 3 << 7 << 6 << 2 << 8 << 5 << 1 << 0;
    else if ( m_type==QString("media_controller") )m_paint_order << 6 << 3 << 7 << 1 << 5 << 2 << 4 << 0 << 8;
    if (m_paint_order[m_to_paint]== m_paint_order[0])
    {setBusy(true);m_paint_tmr->setInterval(75);}
    else if (m_paint_order[m_to_paint]== m_paint_order[7])m_paint_tmr->setInterval(150);
    m_act_1 = new QAction(KIcon( m_values[m_paint_order[m_to_paint]][2]), "", this);
    m_widgets[m_paint_order[m_to_paint]]->setAction(m_act_1);
    if (m_paint_order[m_to_paint]== m_paint_order[8])
    {
      m_to_paint=int(0);m_paint_tmr->stop();
      m_trashfull = false;m_watch_trash->setDirty( m_trash_dir );
      setBusy(false);return;
    }
    m_to_paint++;
  }
  
  
  else if ( m_type==QString("standard_dock") )
  {
    for (int i = 0; i < m_widgets.size(); ++i)
    {
      m_act_1 = new QAction(KIcon( m_values[i][2] ), "", this);
      m_widgets[i]->setAction(m_act_1);
    }
    m_to_paint=int(0);m_paint_tmr->stop();
    m_trashfull = false;m_watch_trash->setDirty( m_trash_dir );
    m_tracker_tmr->setInterval(m_hidingdelay);m_tracker_tmr->start();
  }
  
  
}




//-----------------------------------------------------------------------------
// Refurbish the launchers
void daisy::refurbishLaunchers()
{
  getLauncherValues();
  m_domino.clear();
  if ( m_type == QString("circular_dock") || m_type == QString("media_controller") )
    m_domino << 1 << 6 << 8 << 3 << 5 << 2 << 4 << 7 << 0;
  
  else if ( m_type == QString("standard_dock") )
  {
    QList<float> m_domino_tmp;//FIXME
    m_domino << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    for (int i = 0; i < m_domino_tmp.size(); ++i)
    {
      if ( m_domino_tmp[i] < m_values.size() )
	m_domino << m_domino_tmp[i];
    }
  }
  
  int all = m_widgets.size();
  for (int i = 0; i < all; ++i)
  {delete m_widgets[i];delete m_indicons[i];}
  
  createLaunchers( m_type );
  emit update();
  m_paint_tmr->start();
  
}







//-----------------------------------------------------------------------------
// Elaborate Tasks Menu
void daisy::elabTaskMenu( QList<WId> taskDict, int clickedlaunch_tmp )
{
  
  delete m_task_menu;
  m_task_menu = new KMenu();
  
  taskDrawers.clear();
  
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName | NET::WMWindowType | NET::WMVisibleIconName , NET::WM2StartupId | NET::WM2WindowClass | NET::WM2WindowRole );
    
    QString visiconame_tmp = taskInfo.visibleIconName();
    QString visname_tmp = taskInfo.visibleName();
    QString iconame_tmp = m_values[clickedlaunch_tmp][2];
    
    m_act_1 = new QAction(KIcon(iconame_tmp), visiconame_tmp, this);
    connect(m_act_1, SIGNAL(triggered(bool)), this, SLOT(taskMenuClicked()));
    
    m_task_menu->addAction ( m_act_1 );
    taskDrawers << *it;
    
  }
  
  m_task_menu->exec( QCursor::pos() );
  
}




//-----------------------------------------------------------------------------
// Task Clicked
//FIXME
void daisy::taskMenuClicked()
{
  
  QList<QAction*> task_actions_tmp = m_task_menu->actions();
  
  int clickedlaunch_tmp = -1;
  for (int i = 0; i < task_actions_tmp.size(); ++i)
  {if (task_actions_tmp[i] == sender())clickedlaunch_tmp = i;}
  
  if ( clickedlaunch_tmp != -1 )
  {toggTask( taskDrawers[clickedlaunch_tmp] );}
  
}


//-----------------------------------------------------------------------------
// New launcher instance
void daisy::launNewInstance(void)
{
  KRun::runCommand( m_values[m_dexval][0], m_values[m_dexval][1], m_values[m_dexval][2], NULL, NULL );
}







//-----------------------------------------------------------------------------
// Task click
void daisy::taskClick(void)
{
  int clickedlaunch_tmp = -1;
  for (int i = 0; i < m_taskicons.size(); ++i)
  {if (m_taskicons[i] == m_objclick)clickedlaunch_tmp = i;}
  
  if ( clickedlaunch_tmp != -1 )
  {
    toggTask(showedTasks[clickedlaunch_tmp]);
  }
  
  
}






//-----------------------------------------------------------------------------
// Launcher click
void daisy::launClick(void)
{
  
  int clickedlaunch_tmp = -1;
  for (int i = 0; i < m_widgets.size(); ++i)
  {if (m_widgets[i] == m_objclick)clickedlaunch_tmp = i;}
  
  if ( clickedlaunch_tmp != -1 )
  {
    clickEffect(clickedlaunch_tmp);
    
    if ( m_activetasks.contains(clickedlaunch_tmp) )
    {
      
      QList<WId> widtasks_tmp = matchAllTasks( m_alias[clickedlaunch_tmp], -1 );
      
      
      // Single app instance
      if ( widtasks_tmp.size() == 1 )
      {
	clearDrawers();
	toggTask(widtasks_tmp[0]);
      }
      
      
      // Multiple app instances
      else if ( widtasks_tmp.size() > 1 )
      {
	if ( !m_drawerscleared && m_objclick==m_reobjclick )
	{
	  clearDrawers();
	}
	else
	{
	  if ( m_type == QString("standard_dock") && !m_inpanel && !m_reservespace )
	  {
	    clearDrawers();
	    drawerpopspot_x = qobject_cast<Plasma::IconWidget*>(m_objclick)->geometry().x();
	    drawerpopspot_y = qobject_cast<Plasma::IconWidget*>(m_objclick)->geometry().y();
	    elabDrawers( widtasks_tmp, clickedlaunch_tmp );
	  }
	  else
	  {
	    elabTaskMenu( widtasks_tmp, clickedlaunch_tmp );
	  }
	  
	}
      }
      
      
    }
    
    else
    {
      KRun::runCommand( m_values[clickedlaunch_tmp][0], m_values[clickedlaunch_tmp][1], m_values[clickedlaunch_tmp][2], NULL, NULL );
      //KToolInvocation::startServiceByDesktopName (m_values[clickedlaunch_tmp][0], QStringList(), 0, 0, 0, QByteArray(), false );
      
      
    }
  }
  
}










//-----------------------------------------------------------------------------
// Event filter
// TODO
bool daisy::eventFilter(QObject *obj, QEvent *event)
{
  switch (event->type()) 
  {
    case QEvent::GraphicsSceneMousePress:
    {
      m_reactwin_save = m_actwin_save;m_actwin_save = KWindowSystem::activeWindow();
      m_reobjclick = m_objclick;m_objclick = obj;
      mousePressEvent(static_cast<QGraphicsSceneMouseEvent*>(event));
      break;
    }
    
    
    case QEvent::GraphicsSceneMouseMove:
    {
      m_dexval= -1;
      for (int i = 0; i < m_widgets.size(); ++i)
      {
	if (m_widgets[i] == obj)
	{
	  m_dexval = i;
	  break;
	}
      }
      mouseMoveEvent(static_cast<QGraphicsSceneMouseEvent*>(event));
      break;
    }
    
    
    
    case QEvent::GraphicsSceneHoverEnter:
    {
      if ( !m_draw_icoback || m_zoomtype == QString("default") || m_type==QString("media_controller") ) return QObject::eventFilter(obj, event);
      emit hoverLauncher(obj);
      break;
    }
    
    
//     case QEvent::GraphicsSceneHoverMove:
//     {
//       if ( !m_draw_icoback || m_zoomtype != QString("parabolic") || m_type==QString("circular_dock") || m_type==QString("media_controller") ) return QObject::eventFilter(obj, event);
//       emit hoverLauncher(obj);
//       break;
//     }
    
    
    case QEvent::GraphicsSceneHoverLeave:
    {
      if ( !m_draw_icoback || m_zoomtype == QString("default") || m_type==QString("media_controller") ) return QObject::eventFilter(obj, event);
      emit mormalizeLauncher();
      break;
    }
    
    
    
    
    default:break;
  }
  
  // standard event processing
  return QObject::eventFilter(obj, event);
}








