/*
*   Drawers: daisy
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
// Create Drawers
void daisy::elabDrawers( QList<WId> taskDict, int clickedlaunch_tmp )
{
  m_drawerscleared = false;int i = 0;
  QRect drawerrect_tmp;bool invert_tmp = true;qreal rotval_tmp = 1.00;
  QList<WId>::ConstIterator it;
  for (it = taskDict.begin(); it != taskDict.end(); ++it )
  {
    
    KWindowInfo taskInfo = KWindowSystem::windowInfo( *it, NET::WMName | NET::WMVisibleName | NET::WMWindowType | NET::WMVisibleIconName , NET::WM2StartupId | NET::WM2WindowClass | NET::WM2WindowRole );
    
    QString visiconame_tmp = taskInfo.visibleIconName();
    QString visname_tmp = taskInfo.visibleName();
    QString iconame_tmp = m_values[clickedlaunch_tmp][2];
    
    m_drawericons << new Plasma::IconWidget( KIcon( iconame_tmp ), visiconame_tmp, this );
    m_drawericons[i]->setOrientation(Qt::Horizontal);
    m_drawericons[i]->setCursor(Qt::PointingHandCursor);
    m_drawericons[i]->setAcceptHoverEvents(true);
    m_drawericons[i]->setWindowFrameMargins(0,0,0,0);
    m_drawericons[i]->setNumDisplayLines(1);
    m_drawericons[i]->setDrawBackground(m_draw_icoback);
    //m_drawericons[i]->setToolTip ( visname_tmp );
    
    connect( m_drawericons[i], SIGNAL(pressed(bool)), this, SLOT( drawerClicked() ) );
    m_drawericons[i]->installEventFilter(this);
    
    
    taskDrawers << *it;
    
    
    
    if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
    {
      rotval_tmp = m_drawerrotation*i;invert_tmp = true;
      drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension/1.5)+(5*i))-(m_drawersize*8.33), drawerpopspot_y - (m_drawersize*1.27), 
			      (m_drawersize*8.33), m_drawersize);
    }
    
    else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
    {
      rotval_tmp = -m_drawerrotation*i;invert_tmp = true;
      drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension/1.5)+(5*i))-(m_drawersize*8.33), drawerpopspot_y + (m_icodimension*1.27), 
			      (m_drawersize*8.33), m_drawersize);
    }
    
    else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
    {
      rotval_tmp = -m_drawerrotation*i;invert_tmp = false;
      drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension*1.3)+(5*i)), drawerpopspot_y, 
			      (m_drawersize*8.33), m_drawersize);
    }
    
    else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
    {
      rotval_tmp = m_drawerrotation*i;invert_tmp = true;
      drawerrect_tmp = QRect( (drawerpopspot_x-((m_drawersize*8.33)+m_icodimension/3)-(5*i)), drawerpopspot_y, 
			      (m_drawersize*8.33), m_drawersize);
    }
    
    
    
    
    m_drawericons[i]->invertLayout( invert_tmp );
    m_drawericons[i]->setGeometry( drawerrect_tmp );
    m_drawericons[i]->setTransform(QTransform().rotate(rotval_tmp));
    
    
    i++;
    
  }
  
  raise();
  emit update();
  
  
}
















//-----------------------------------------------------------------------------
// Drawer Clicked
//FIXME
void daisy::drawerClicked()
{
  int clickedlaunch_tmp = -1;
  for (int i = 0; i < m_drawericons.size(); ++i)
  {if (m_drawericons[i] == m_objclick)clickedlaunch_tmp = i;}
  
  
  if ( clickedlaunch_tmp != -1 )
  {
    m_actwin_save = m_reactwin_save;
    toggTask( taskDrawers[clickedlaunch_tmp] );
  }
  
}













//-----------------------------------------------------------------------------
// Clear Drawers
void daisy::clearDrawers( )
{
  
  int all = m_drawericons.size();
  for (int i = 0; i < all; ++i)
  {delete m_drawericons[i];}
  
  m_drawericons.clear();taskDrawers.clear();
  m_drawerscleared = true;
  
  
}













