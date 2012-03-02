/*
*   Effects: daisy
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
// Clicked effect TODO
void daisy::clickEffect(int clickedlaunch_tmp)
{
  
  
  if ( m_click_effects )
  {
    
    // Default effect
    if ( m_click_effect_type == QString("default") )
    {
      m_widgets[clickedlaunch_tmp]->setTransform( QTransform().scale(0.7, 0.7).translate(m_icodimension/4,m_icodimension/4) );
      QTimer::singleShot(1000, this, SLOT(mormalizeLauncher()));
    }
    
    
    // Fade effect TODO
    else if ( m_click_effect_type == QString("fade") )
    {
      QTimer::singleShot(1000, this, SLOT(mormalizeLauncher()));
    }
    
    
    
  }
  
}












//-----------------------------------------------------------------------------
// Hover launcher TODO
void daisy::hoverLauncher(QObject *obj)
{
  
  int hoveredlaunch_tmp = -1;
  for (int i = 0; i < m_widgets.size(); ++i)
  {
    m_zoomszdiff[i] = 0;
    m_zoomposdiff[i] = 0;
    if (m_widgets[i] == obj)
    {hoveredlaunch_tmp = i;break;}
  }
  
  
  if ( hoveredlaunch_tmp != -1 )
  {
    QRectF cur_geo = m_widgets[hoveredlaunch_tmp]->geometry();
    
    
    
    // Simple Zoom
    if ( m_zoomtype == QString("simple") )
    {
      m_zoomszdiff[hoveredlaunch_tmp] = ( m_icodimension/5 );
      m_zoomposdiff[hoveredlaunch_tmp] = ( -m_icodimension/10 );
      
      m_widgets[hoveredlaunch_tmp]->setGeometry( QRect( cur_geo.left()+m_zoomposdiff[hoveredlaunch_tmp], cur_geo.top()+m_zoomposdiff[hoveredlaunch_tmp], cur_geo.width()+m_zoomszdiff[hoveredlaunch_tmp], cur_geo.height()+m_zoomszdiff[hoveredlaunch_tmp] ) );
      
      emit update();
    }
    
    
    // Fruity Zoom
    else if ( m_zoomtype == QString("fruity") )
    {
      m_hoverpz = QPointF( cur_geo.left(), cur_geo.top()+(m_icodimension/3.3) );
      m_hoversz = QSizeF(cur_geo.width(), cur_geo.height());
      
      emit update();
    }
    
    
    // Framed Zoom
    else if ( m_zoomtype == QString("framed") )
    {
      m_hoverpz = QPointF( cur_geo.left()+( -m_icodimension/10 ), cur_geo.top()+( -m_icodimension/10 ));
      m_hoversz = QSizeF(cur_geo.width()+( m_icodimension/5 ), cur_geo.height()+( m_icodimension/5 ));
      
      emit update();
    }
    
    
    
    
    
    
    
  }
  
}








//-----------------------------------------------------------------------------
// Normalize launcher TODO
void daisy::mormalizeLauncher()
{
  
  for (int i = 0; i < m_zoomszdiff.size(); ++i)
  {
    m_zoomszdiff[i] = 0;
    m_zoomposdiff[i] = 0;
  }
  
  for (int i = 0; i < m_widgets.size(); ++i)
  {
    m_widgets[i]->resetTransform();
  }
  
  m_hoverpz = QPointF( -100000, -100000 );
  
  emit update();
  
}















//-----------------------------------------------------------------------------
// Polish the launchers
void daisy::polishLaunchers()
{
  
  for (int i = 0; i < m_widgets.size(); ++i)
  {
    if ( m_zoomtype != QString("default") || m_type==QString("media_controller") || ( m_type==QString("circular_dock") && i==0 )  )
      m_widgets[i]->setDrawBackground(false);
    else
      m_widgets[i]->setDrawBackground(m_draw_icoback);
  }
  
  
  if ( m_zoomtype == QString("fruity") ) m_hoverimage.setElementPrefix("fruity");
  else if ( m_zoomtype == QString("framed") )
  {
    m_hoverimage.setElementPrefix("framed");
  }
  
  m_hoverpz = QPointF( -100000, -100000 );
  
}





































