/*
*   C++ Implementation: daisy
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







// Includes
#include "daisy.h"
#include "daisyConfig.cpp"
#include "daisyLaunchers.cpp"
#include "daisyFx.cpp"
#include "daisyTasks.cpp"
#include "daisyDrawers.cpp"
#include "daisyPlug_trash.cpp"
#include "daisyIcon.cpp"
#include "daisyMediaControl.cpp"
#include "daisyDialogs.cpp"






//-----------------------------------------------------------------------------
/// The daisy plasma
daisy::daisy(QObject *parent, const QVariantList &args):
Plasma::Containment(parent, args), m_backframe(this), m_backframe_t(this), m_hoverimage(this)

{
  KGlobal::locale()->insertCatalog("daisy");
  
  
  m_backframe.setImagePath("widgets/circular-background");
  m_backframe.setEnabledBorders(Plasma::FrameSvg::NoBorder);
  m_backframe.setCacheAllRenderedFrames(true);
  
  m_backframe_t.setImagePath("widgets/translucentbackground");
  m_backframe_t.setEnabledBorders(Plasma::FrameSvg::AllBorders);
  m_backframe_t.setCacheAllRenderedFrames(true);
  
  m_hoverimage.setImagePath("widgets/dock-animations");
  m_hoverimage.setEnabledBorders(Plasma::FrameSvg::NoBorder);
  m_hoverimage.setElementPrefix("framed");
  m_hoverimage.setCacheAllRenderedFrames(true);
  
  
  QList< Plasma::IconWidget* > m_widgets;
  QList< Plasma::IconWidget* > m_drawericons;
  QList< Plasma::IconWidget* > m_taskicons;
  QList< Plasma::FrameSvg* > m_indicons;
  
  
  Plasma::Dialog m_drawdial;
  
  
  m_trashfull = false;
  m_drawerscleared = false;
  m_floating = false;
  m_reservespace = true;
  m_autohide = false;
  m_showondesk = false;
  m_accept_drops = true;
  m_oktodestroy = true;
  m_to_paint = int(0);
  m_dialogLauncher = 0;
  m_reserver = 0;
  drawerpopspot_x = 0;
  drawerpopspot_y = 0;
  m_activewindow = int(-1);
  m_trash_dir = QString( QDir("").homePath() + "/.local/share/Trash/files/");
  m_icodimension = int(52);
  m_icospacing = 0.250;
  m_position = QString("buttom_center");
  m_orientation = QString("horizontal");
  m_backopacity = 1.0;
  m_hidingdelay = 3000;
  m_workwid = 0;
  m_toupwid = 0;
  m_focusedWindow = 0;
  
  m_drawersize = 38;
  m_drawerrotation = 1.50;
  
  
  last_icopos << -1000 << -1000;
  total_taskpreviews = 0;
  m_max_taskpreviews = 20;//FIXME
  m_taskpreviews = true;
  m_showtaskoflauncher = true;
  
  m_showclosetask = false;
  m_middleClickAction = QString("shade");
  
  
  
  m_trash_spot = int(3);//FIXME
  m_total_launchers = int(9);
  m_total_plugs = int(1);
  m_show_trash = true;
  m_circpos = QPointF(62,268);
  m_clickpos = QPointF(0,0);
  
  m_hoverpz = QPointF( -100000, -100000 );
  m_hoversz = QSizeF(m_icodimension,m_icodimension);
  
  
  m_zoomtype = QString("framed");
  QList <double> m_zoomszdiff;
  QList <double> m_zoomposdiff;
  
  m_click_effects = false;
  m_click_effect_type = QString("default");
  m_tiptype = QString("icon");
  
  
  
  
  // timers
  m_paint_tmr = new QTimer();
  m_paint_tmr->setInterval(1000);
  connect( m_paint_tmr, SIGNAL(timeout()), this, SLOT(paintLaunchers()) );
  
  m_up_tmr = new QTimer();
  m_up_tmr->setInterval(500);
  connect( m_up_tmr, SIGNAL(timeout()), this, SLOT(delayUpdate()) );
  
  m_rz_tmr = new QTimer();
  m_rz_tmr->setInterval(700);
  connect( m_rz_tmr, SIGNAL(timeout()), this, SLOT(delayResize()) );
  
  m_tracker_tmr = new QTimer();
  m_tracker_tmr->setInterval(m_hidingdelay);
  connect( m_tracker_tmr, SIGNAL(timeout()), this, SLOT(mouseTracker()) );
  
  m_dlx_tmr = new QTimer();
  m_dlx_tmr->setInterval(50);
  connect( m_dlx_tmr, SIGNAL(timeout()), this, SLOT(delayExec()) );
  
  m_dlt_tmr = new QTimer();
  m_dlt_tmr->setInterval(50);
  connect( m_dlt_tmr, SIGNAL(timeout()), this, SLOT(delayShade()) );
  
  m_uti_tmr = new QTimer();
  m_uti_tmr->setInterval(10);
  connect( m_uti_tmr, SIGNAL(timeout()), this, SLOT(delayTaskIcoChange()) );
  
  
  
  // watchers
  m_watch_trash = new KDirWatch(this);
  m_watch_trash->addDir( m_trash_dir );
  connect( m_watch_trash, SIGNAL( dirty (const QString) ), this, SLOT(checkTrash()) );
  
  // actions
  m_act_role = new QAction(KIcon("applications-multimedia"), i18n("Media controller"), this);
  connect(m_act_role, SIGNAL(triggered(bool)), this, SLOT(swapCircular()));
  
  m_act_role_t = new QAction(KIcon("preferences-desktop-default-applications"), i18n("Linear dock"), this);
  connect(m_act_role_t, SIGNAL(triggered(bool)), this, SLOT(swapLinear()));
  
  m_act_lock = new QAction(KIcon("object-locked"), i18n("Lock Daisy"), this);
  connect(m_act_lock, SIGNAL(triggered(bool)), this, SLOT(toggleLockedState()));
  
  m_act_close = new QAction(KIcon("edit-delete"), i18n("Remove this Daisy"), this);
  connect(m_act_close, SIGNAL(triggered(bool)), this, SLOT(removeDaisy()));
  
  m_act_opentrash = new QAction(KIcon("document-open-folder"), i18n("Open"), this);
  connect(m_act_opentrash, SIGNAL(triggered()), this, SLOT(openTrash()));
  
  m_act_emptytrash = new QAction(KIcon("user-trash"), i18n("Empty Trashcan"), this);
  connect(m_act_emptytrash, SIGNAL(triggered()), this, SLOT(emptyTrash()));
  
  m_act_restoretrash = new QAction(KIcon("document-revert"), i18n("Restore items"), this);
  connect(m_act_restoretrash, SIGNAL(triggered()), this, SLOT(restoreTrash()));
  
  m_act_editlauncher = new QAction(KIcon("configure"), i18n("Edit launcher..."), this);
  connect(m_act_editlauncher, SIGNAL(triggered()), this, SLOT(configLauncher()));
  
  m_act_remlauncher = new QAction(KIcon("list-remove"), i18n("Remove launcher"), this);
  connect(m_act_remlauncher, SIGNAL(triggered()), this, SLOT(removeLauncher()));
  
  m_act_remtrash = new QAction(KIcon("list-remove"), i18n("Remove trash plugin"), this);
  connect(m_act_remtrash, SIGNAL(triggered()), this, SLOT(remTrash()));
  
  m_act_newinstance = new QAction(KIcon("application-x-executable"), i18n("New instance"), this);
  connect(m_act_newinstance, SIGNAL(triggered()), this, SLOT(launNewInstance()));
  
  m_act_closetask = new QAction(KIcon("window-close"), i18n("Close"), this);
  connect(m_act_closetask, SIGNAL(triggered()), this, SLOT(taskClosing()));
  
  
  
  QList <QAction*> m_acta;
  QList <QStringList> m_values;
  QList <QStringList> m_avalues;
  
  QList<WId> taskDrawers;
  QList<QUrl> m_url_drag;
  
  
  
  
//   setContainmentType(Containment::CustomPanelContainment);
  setImmutability(Plasma::Mutable);
  setAcceptsHoverEvents(true);
  setAcceptDrops(true);
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setHasConfigurationInterface(true);
  setBackgroundHints(NoBackground);
  setAspectRatioMode(Plasma::KeepAspectRatio);
  setContentsMargins(0, 0, 0, 0);
  setWindowFrameMargins(0,0,0,0);
  setFocusPolicy( Qt::NoFocus );
  resize(330,330);
  setPos(m_circpos);
  setCacheMode( QGraphicsItem::NoCache );
  
}






//-----------------------------------------------------------------------------
// Initialize
void daisy::init()
{
  
  if( location() == 3 ){m_inpanel = true;setMinimumSize(8,8);}
  else{m_inpanel = false;setMinimumSize(100,100);}
  
  // tasks
  m_groupManager = new TaskManager::GroupManager(this);
  connect( TaskManager::TaskManager::self(), SIGNAL( startupAdded(StartupPtr) ), this, SLOT( startupAdded(StartupPtr)) );
  connect( TaskManager::TaskManager::self(), SIGNAL( startupRemoved(StartupPtr) ), this, SLOT(startupRemoved(StartupPtr)) );
  connect( KWindowSystem::self(), SIGNAL( windowAdded(WId) ), this, SLOT( windowAdded(WId) ) );
  connect( KWindowSystem::self(), SIGNAL( windowRemoved(WId) ), this, SLOT( windowRemoved(WId) ) );
  connect( KWindowSystem::self(), SIGNAL( activeWindowChanged(WId) ), this, SLOT( activeWindowChanged(WId) ) );
  connect( KWindowSystem::self(), SIGNAL( currentDesktopChanged(int) ), this, SLOT( currentDesktopChanged(int) ) );
  connect( KWindowSystem::self(), SIGNAL( workAreaChanged() ), this, SLOT( workAreaChanged() ) );
  connect( KWindowSystem::self(), SIGNAL( windowChanged(WId, const unsigned long* ) ), this, SLOT( windowChanged(WId, const unsigned long* ) ) );
  
  
  readConfiguration();
  getLauncherValues();
  emit spaceReserver(true);
  setTheme();
  resizeRepos( false );
  createLaunchers( m_type );
  createMenus();
  getAllTasks();
  m_paint_tmr->start();
  raise();
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
  
}






//-----------------------------------------------------------------------------
// Painter
void daisy::paintInterface(QPainter *p, const QStyleOptionGraphicsItem *option, const QRect &contentsRect)
{
  Q_UNUSED (option);
  if (!m_inpanel) {paintDesktop(p, contentsRect);}
  else {paintPanel(p, contentsRect);}
}




//-----------------------------------------------------------------------------
// Paint the Widgets (on DESKTOP)
void daisy::paintDesktop(QPainter *p, const QRect &contentsRect)
{
  QList< QList<double> > get_val = calcWidgetPositions( contentsRect );
  QList<double> m_ico_posX = get_val[0];QList<double> m_ico_posY = get_val[1];
  QList<double> m_ico_szX = get_val[2];QList<double> m_ico_szY = get_val[3];
  QList<double> m_back_sz = get_val[4];
  QList<double> m_indico_posX = get_val[5];QList<double> m_indico_posY = get_val[6];
  p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
  
  
  
  // Background
  p->setOpacity(m_backopacity);
  if ( m_type == QString("circular_dock") ||  m_type == QString("media_controller") )
  {
    m_backframe.resizeFrame( QSizeF( m_back_sz[0], m_back_sz[1] ) );
    m_backframe.paintFrame( p, QPointF(0, 0) );
  }
  else if ( m_type == QString("standard_dock") )
  {
    m_backframe_t.resizeFrame( QSizeF( m_back_sz[0], m_back_sz[1] ) );
    m_backframe_t.paintFrame( p, QPointF(0, 0) );
  }
  p->setOpacity(1.0);
  
  
  
  if ( m_type == QString("circular_dock") ||  m_type == QString("standard_dock") )
  {
    
    
    //Thumbnails
    if ( m_taskpreviews && m_type == QString("standard_dock") )
    {
      for (int i = 0; i < total_taskpreviews; ++i)
      {
	
	if ( m_orientation== QString("horizontal") )
	{
	  m_taskicons[i]->setGeometry( QRect( last_icopos[0] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ), last_icopos[1], m_icodimension, m_icodimension) );
	}
	else
	{
	  m_taskicons[i]->setGeometry( QRect( last_icopos[0] , last_icopos[1] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ), m_icodimension, m_icodimension) );
	}
	
	
	if ( m_showmirror )
	{
	  p->setOpacity(0.55);
	  QRect mirrect;QImage image_tmp;
	  QPixmap pixmap_tmp = m_taskicons[i]->icon().pixmap(m_icodimension,m_icodimension);
	  
	  if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
	  {
	    pixmap_tmp = pixmap_tmp.copy(0, (pixmap_tmp.height() * 0.66), pixmap_tmp.width(), (pixmap_tmp.height() * 0.33));
	    image_tmp = pixmap_tmp.toImage();
	    image_tmp = image_tmp.mirrored(true, true);image_tmp = image_tmp.mirrored(true, false);
	    mirrect = QRect( last_icopos[0] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ),
			      last_icopos[1]+(m_icodimension-(m_icodimension/15)),
			      m_icodimension,
			      (m_icodimension)/3 );
	  }
	  else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
	  {
	    pixmap_tmp = pixmap_tmp.copy(0, 0, pixmap_tmp.width(), (pixmap_tmp.height() * 0.33));
	    image_tmp = pixmap_tmp.toImage();
	    image_tmp = image_tmp.mirrored(true, true);image_tmp = image_tmp.mirrored(true, false);
	    mirrect = QRect( last_icopos[0] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ),
			     last_icopos[1]-((m_icodimension-(m_icodimension/15))/3),
			     m_icodimension, (m_icodimension)/3 );
	  }
	  else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
	  {
	    pixmap_tmp = pixmap_tmp.copy( 0, 0, (pixmap_tmp.width() * 0.33), pixmap_tmp.height() );
	    image_tmp = pixmap_tmp.toImage();
	    image_tmp = image_tmp.mirrored(true, false);
	    mirrect = QRect( last_icopos[0]-(m_icodimension-(m_icodimension/15))/3,
			     last_icopos[1] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ),
			     (m_icodimension)/3, m_icodimension );
	  }
	  else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
	  {
	    pixmap_tmp = pixmap_tmp.copy( (pixmap_tmp.width() * 0.66), 0, (pixmap_tmp.width() * 0.33), pixmap_tmp.height() );
	    image_tmp = pixmap_tmp.toImage();
	    image_tmp = image_tmp.mirrored(true, false);
	    mirrect = QRect( last_icopos[0]+(m_icodimension-(m_icodimension/15)),
			     last_icopos[1] + ( ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) ),
			     (m_icodimension)/3, m_icodimension );
	  }
	  
	  p->drawImage ( mirrect, image_tmp );
	  p->setOpacity(1.0);
	}
      }
    }
    
    
    
    //Launchers
    for (int i = 0; i < m_widgets.size(); ++i)
    {
      m_widgets[m_domino[i]]->setGeometry( QRect( m_ico_posX[i], m_ico_posY[i], m_ico_szX[i]+m_zoomszdiff[m_domino[i]], m_ico_szY[i]+m_zoomszdiff[m_domino[i]]) );
      
      if ( m_showmirror && m_type == QString("standard_dock") )
      {
	p->setOpacity(0.55);
	QRect mirrect;QImage image_tmp;
	QPixmap pixmap_tmp = KIcon(m_values[m_domino[i]][2]).pixmap(m_ico_szX[i]+m_zoomszdiff[m_domino[i]],m_ico_szY[i]+m_zoomszdiff[m_domino[i]]);
	
	
	if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
	{
	  pixmap_tmp = pixmap_tmp.copy(0, (pixmap_tmp.height() * 0.66), pixmap_tmp.width(), (pixmap_tmp.height() * 0.33));
	  image_tmp = pixmap_tmp.toImage();
	  image_tmp = image_tmp.mirrored(true, true);image_tmp = image_tmp.mirrored(true, false);
	  mirrect = QRect( m_ico_posX[i], m_ico_posY[i]+(m_ico_szY[i]-(m_ico_szY[i]/15)), 
			   m_ico_szX[i]+m_zoomszdiff[m_domino[i]], (m_ico_szY[i]+m_zoomszdiff[m_domino[i]])/3 );
	}
	
	else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
	{
	  pixmap_tmp = pixmap_tmp.copy(0, 0, pixmap_tmp.width(), (pixmap_tmp.height() * 0.33));
	  image_tmp = pixmap_tmp.toImage();
	  image_tmp = image_tmp.mirrored(true, true);image_tmp = image_tmp.mirrored(true, false);
	  mirrect = QRect( m_ico_posX[i], m_ico_posY[i]-((m_ico_szY[i]-(m_ico_szY[i]/15))/3), 
			   m_ico_szX[i]+m_zoomszdiff[m_domino[i]], (m_ico_szY[i]+m_zoomszdiff[m_domino[i]])/3 );
	}
	
	else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
	{
	  pixmap_tmp = pixmap_tmp.copy( 0, 0, (pixmap_tmp.width() * 0.33), pixmap_tmp.height() );
	  image_tmp = pixmap_tmp.toImage();
	  image_tmp = image_tmp.mirrored(true, false);
	  mirrect = QRect( m_ico_posX[i]-(m_ico_szX[i]-(m_ico_szX[i]/15))/3, m_ico_posY[i], 
			   (m_ico_szX[i]+m_zoomszdiff[m_domino[i]])/3, m_ico_szY[i]+m_zoomszdiff[m_domino[i]] );
	}
	
	else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
	{
	  pixmap_tmp = pixmap_tmp.copy( (pixmap_tmp.width() * 0.66), 0, (pixmap_tmp.width() * 0.33), pixmap_tmp.height() );
	  image_tmp = pixmap_tmp.toImage();
	  image_tmp = image_tmp.mirrored(true, false);
	  mirrect = QRect( m_ico_posX[i]+(m_ico_szX[i]-(m_ico_szX[i]/15)), m_ico_posY[i], 
			   (m_ico_szX[i]+m_zoomszdiff[m_domino[i]])/3, m_ico_szY[i]+m_zoomszdiff[m_domino[i]] );
	}
	
	
	p->drawImage ( mirrect, image_tmp );
	p->setOpacity(1.0);
      }
      
      //Indicons
      if (m_showindicons)
      {
	QString indiconpath_tmp = QString("inactive");
	if ( m_domino[i] == m_startingwindow )indiconpath_tmp = QString("starting");
	else if ( m_domino[i] == m_closingwindow )indiconpath_tmp = QString("closing");
	else if ( m_domino[i] == m_activewindow )indiconpath_tmp = QString("focused");
	else if ( m_attentionwindow.contains(m_domino[i]) )indiconpath_tmp = QString("attention");
	else if ( m_activetasks.contains(m_domino[i]) )indiconpath_tmp = QString("active");
	m_indicons[m_domino[i]]->setElementPrefix(indiconpath_tmp);
	m_indicons[m_domino[i]]->resizeFrame( QSizeF( m_ico_szX[i]+m_zoomszdiff[m_domino[i]], m_ico_szY[i]+m_zoomszdiff[m_domino[i]] ) );
	m_indicons[m_domino[i]]->paintFrame( p, QPointF(m_indico_posX[i], m_indico_posY[i]) );
	
	//FIXME
	if ( m_showmirror && m_type == QString("standard_dock") && (m_position == QString("buttom_center") || m_position == QString("buttom_right") || m_position == QString("buttom_left") ) )
	{
	  p->setOpacity(0.55);
	  QPixmap pixmap_tmp = m_indicons[m_domino[i]]->framePixmap();
	  QImage image_tmp = pixmap_tmp.toImage();
	  image_tmp = image_tmp.mirrored(true, true);image_tmp = image_tmp.mirrored(true, false);
	  p->drawImage ( QRect( m_indico_posX[i], m_indico_posY[i]+((m_ico_szY[i]+m_zoomszdiff[m_domino[i]])-(m_ico_szY[i]/13)), m_ico_szX[i]+m_zoomszdiff[m_domino[i]], m_ico_szY[i]+m_zoomszdiff[m_domino[i]] ), image_tmp );
	  p->setOpacity(1.0);
	}
      }
    }
    
    
    //Drawers
    for (int i = 0; i < m_drawericons.size(); ++i)
    {
      QRect drawerrect_tmp;
      
      if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
	drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension/1.5)+(5*i))-(m_drawersize*8.33), drawerpopspot_y - (i*(m_drawersize*1.27)+(m_drawersize*1.27)), 
				(m_drawersize*8.33), m_drawersize);
      
      else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
	drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension/1.5)+(5*i))-(m_drawersize*8.33), drawerpopspot_y + (i*(m_drawersize*1.27)+(m_icodimension*1.27)), 
				(m_drawersize*8.33), m_drawersize);
      
      else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
	drawerrect_tmp = QRect( (drawerpopspot_x+(m_icodimension*1.3)+(5*i)), drawerpopspot_y+(i*(m_drawersize*1.27)), 
				(m_drawersize*8.33), m_drawersize);
      
      else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
	drawerrect_tmp = QRect( (drawerpopspot_x-((m_drawersize*8.33)+m_icodimension/3)-(5*i)), drawerpopspot_y+(i*(m_drawersize*1.27)), 
				(m_drawersize*8.33), m_drawersize);
      
      
      m_drawericons[i]->setGeometry(drawerrect_tmp);
    }
    
  }
  
  
  
  
  
  else if ( m_type == QString("media_controller") )
  {
    for (int i = 0; i < m_widgets.size(); ++i)
    {m_widgets[i]->setGeometry(QRect( m_ico_posX[i], m_ico_posY[i], m_ico_szX[i], m_ico_szY[i]));}
  }
  
  
  // Hover image
  m_hoverimage.resizeFrame( m_hoversz );
  m_hoverimage.paintFrame( p, m_hoverpz );
  
  p->save();
  p->restore();

}





//-----------------------------------------------------------------------------
// Paint the Widgets (on PANEL)
void daisy::paintPanel(QPainter *p, const QRect &contentsRect)
{
  Q_UNUSED (p);
  
  double t_width=contentsRect.width(), t_height=contentsRect.height();
  double t_wdico=t_width, t_hgico=t_height;
  
  for (int i = 0; i < m_widgets.size(); ++i)
  {m_widgets[i]->setGeometry(QRect( -100000, -100000, t_wdico, t_hgico));}
  
  if ( m_widgets.size()>0 && (m_type == QString("circular_dock") || m_type == QString("standard_dock")) )
  {m_widgets[1]->setGeometry(QRect( 0, 0, t_wdico, t_hgico));}
  else if ( m_type == QString("media_controller") )
  {m_widgets[8]->setGeometry(QRect( 0, 0, t_wdico, t_hgico));}
  
}





//-----------------------------------------------------------------------------
// Constraints event
void daisy::constraintsEvent(Plasma::Constraints constraints)
{
  
  if( location() == 3 ){m_inpanel = true;setMinimumSize(8,8);}
  else
  {
    m_inpanel = false;
    if ( m_type!=QString("standard_dock") )setMinimumSize(100,100);
  }
  
  if (constraints & Plasma::FormFactorConstraint)
  {
    setBackgroundHints(NoBackground);
  }
  
  if (constraints & Plasma::SizeConstraint)
  {}
  
  
  
}







//-----------------------------------------------------------------------------
// Mouse wheel event
void daisy::wheelEvent(QGraphicsSceneWheelEvent *event)
//FIXME add move animation here.
{
  int delta = event->delta();
  
  if ( m_type == QString("circular_dock") )
  {circleAround(delta);emit update();}
  
  else if ( m_type == QString("media_controller") )
  {
    if (delta < 0)
    {
      KRun::runCommand( getPlayerComs()[10], 0, 0, NULL, NULL );
    }
    else
    {
      KRun::runCommand( getPlayerComs()[9], 0, 0, NULL, NULL );
    }
  }
  
  else if ( m_type == QString("standard_dock") )
  {scrollTasks(delta);}
  
  
  event->accept();
}



//-----------------------------------------------------------------------------
// Hover enter event
void daisy::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  if ( m_autohide && m_type == QString("standard_dock") && !m_inpanel && !m_floating )
    m_tracker_tmr->stop();
  event->accept();
  
}



//-----------------------------------------------------------------------------
// Hover move event
void daisy::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
  
  event->accept();
  
}


//-----------------------------------------------------------------------------
// Hover leave event
void daisy::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  if ( m_autohide && m_type == QString("standard_dock") && !m_inpanel && !m_floating )
    m_tracker_tmr->start();
  event->accept();
}




//-----------------------------------------------------------------------------
// Mouse press event FIXME
void daisy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  startPos = event->scenePos();
  m_clickpos = event->pos();
  setFlag(QGraphicsItem::ItemIsMovable, true);
  m_dexval = -1;
  m_dlx_tmr->stop();m_dlt_tmr->stop();
  
  if ( contentsRect().contains(m_clickpos) )
  {
    if (event->buttons () == Qt::LeftButton )
    {}
    
    else if (event->buttons () == Qt::MidButton )
    {
      if ( m_type == QString("media_controller") )
      {QProcess *myProcess = new QProcess(this);myProcess->start(getPlayerComs()[7]);}
      
      else
      {
	m_dexval = getContextLauncher(m_clickpos);
	if ( m_dexval != m_trash_spot )
	{
	  if ( m_dexval !=-1 )
	  {
	    if (m_middleClickAction == QString("shade"))
	    {
	      m_workwid = matchTask( m_alias[m_dexval] );
	      if ( m_activetasks.contains(m_dexval) && m_workwid != 0 )
	      {m_dlt_tmr->start();}
	    }
	    else if (m_middleClickAction == QString("run"))
	    {m_dlx_tmr->start();}
	  }
	  else if ( m_taskpreviews && m_type == QString("standard_dock") )
	  {
	    m_dexval = getContextTask(m_clickpos);
	    if ( m_dexval !=-1 )
	    {
	      m_workwid = showedTasks[m_dexval];
	      m_dlt_tmr->start();
	    }
	  }
	}
      }
    }
  }
  Containment::mousePressEvent(event);
}




//-----------------------------------------------------------------------------
// Drag enter event
void daisy::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  m_oktodestroy = false;
  event->setDropAction(Qt::MoveAction);
  event->accept();
}


//-----------------------------------------------------------------------------
// Drag move event
void daisy::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
  event->setDropAction(Qt::MoveAction);
  event->accept();
}


//-----------------------------------------------------------------------------
// Drag leave event
void daisy::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
  m_oktodestroy = true;
  event->accept();
}





//-----------------------------------------------------------------------------
// Mouse move event
void daisy::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  m_clickpos = event->pos();
  
  if(event->buttons() & Qt::LeftButton)
  {
    if ( m_dexval != -1 )
    {
      int distance = (event->scenePos() - startPos).toPoint().manhattanLength();
      if( distance >= (12) && m_type != QString("media_controller") && !m_inpanel && m_accept_drops )
      {startDrag(event);}
    }
  }
  event->accept();
}





//-----------------------------------------------------------------------------
// Initialize drag
void daisy::startDrag(QGraphicsSceneMouseEvent *event)
{
  QMimeData *mimeData = new QMimeData;
  m_url_drag.clear();
  
  QStringList list_tmp;
  list_tmp = m_values[m_dexval][0].split(QRegExp("\\s+"));
  KService::Ptr service = KService::serviceByStorageId( list_tmp[0] );
  
  
  if (service && service->isValid())
  {
    QString path = service->entryPath();
    if (!path.isEmpty() && QDir::isAbsolutePath(path))
    {
      m_url_drag << QUrl(path);
      mimeData->setUrls(m_url_drag);
    }
  }
  
  else
  {
    service = KService::serviceByStorageId( m_alias[m_dexval] );
    if (service && service->isValid())
    {
      QString path = service->entryPath();
      if (!path.isEmpty() && QDir::isAbsolutePath(path))
      {
	m_url_drag << QUrl(path);
	mimeData->setUrls(m_url_drag);
      }
    }
  }
  
  m_oktodestroy = true;
  QDrag *drag = new QDrag(event->widget());
  connect(drag, SIGNAL(destroyed()), this, SLOT ( destroyLauncher() ));
  drag->setMimeData(mimeData);
  QPixmap pixmap_tmp = KIcon(m_values[m_dexval][2]).pixmap(32,32);
  drag->setPixmap( pixmap_tmp );
  drag->setHotSpot( QPoint(16,16) );
  drag->exec(Qt::MoveAction);
  
}





//-----------------------------------------------------------------------------
// Drop event
void daisy::dropEvent(QGraphicsSceneDragDropEvent* event)
{
  m_clickpos = event->pos();
  
  if (!KUrl::List::canDecode(event->mimeData()))
  {event->ignore();return;}
  
  if ( m_type != QString("media_controller") && !m_inpanel && m_accept_drops )
  {
    QList<QUrl> payload;payload = event->mimeData()->urls();
    
    if ( payload != m_url_drag )
    {
      m_dexval = getContextLauncher(m_clickpos);
      if ( m_dexval != -1 )
      {if (m_dexval==m_trash_spot && m_show_trash)moveToTrash(payload);}
      else{emit addLauncher(m_clickpos, payload);}
      event->accept();
    }
    
    else
    {
      if ( m_type == QString("standard_dock") )
      {emit moveLauncher( m_clickpos );}
    }
  }
  
}



//-----------------------------------------------------------------------------
// Screen Changed
void daisy::screenChanged(int wasScreen, int isScreen, Plasma::Containment *containment)
{
  Q_UNUSED (containment);
  
  #ifdef INFORMATION_DEBUG
  kDebug() << wasScreen << isScreen;
  #endif
  
}





//-----------------------------------------------------------------------------
// Context menu event
void daisy::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
  m_clickpos = event->pos();
  
  if (m_dialogLauncher == 0)
  {
    if ( m_type == QString("media_controller") || m_inpanel )
    {Applet::contextMenuEvent(event);}
    else
    {
      m_dexval = getContextLauncher(m_clickpos);
      if ( m_dexval == -1 )
      {
	if ( m_taskpreviews && m_type == QString("standard_dock") )
	  m_dexval = getContextTask(m_clickpos);
	if ( m_dexval == -1 )
	  Applet::contextMenuEvent(event);
	else
	{
	  if (!m_drawerscleared) clearDrawers();
	  m_task = TaskManager::TaskManager::self()->findTask( showedTasks[m_dexval] );
	  if (m_task)
	  {
	    TaskManager::BasicMenu *taskMenu;TaskManager::TaskItem *taskitem;
	    taskitem = new TaskManager::TaskItem(this, m_task);
	    taskMenu = new TaskManager::BasicMenu( qobject_cast<QWidget*>(this), taskitem, m_groupManager );
	    taskMenu->popup( event->screenPos() );
	  }
	}
      }
      
      else
      {
	if (!m_drawerscleared) clearDrawers();
	if (m_dexval == m_trash_spot)
	{
	  m_act_emptytrash->setEnabled(m_trashfull);
	  m_act_restoretrash->setEnabled(m_trashfull);
	  if ( m_type == QString("circular_dock") )
	    m_trash_menu->exec( event->screenPos() );
	  else if ( m_type == QString("standard_dock") )
	    m_trash_menu_t->exec( event->screenPos() );
	}
	
	else
	{
	  if ( getTaskPtr(m_alias[m_dexval]) )
	  {
	    QList<QAction*> actionList;actionList << m_act_newinstance << m_act_editlauncher;
	    TaskManager::BasicMenu *taskMenu;TaskManager::TaskItem *taskitem;
	    taskitem = new TaskManager::TaskItem(this, m_task);
	    taskMenu = new TaskManager::BasicMenu( qobject_cast<QWidget*>(this), taskitem, m_groupManager, actionList );
	    taskMenu->popup( event->screenPos() );
	  }
	  
	  else
	  {
	    if ( m_type == QString("circular_dock") )m_launcher_menu->exec( event->screenPos() );
	    else if ( m_type == QString("standard_dock") )m_launcher_menu_t->exec( event->screenPos() );
	  }
	}
	
      }
      
    }
    
  }
}






//-----------------------------------------------------------------------------
// Add context actions
QList<QAction*> daisy::contextualActions()
{
  QList<QAction*> tempActions;
  
  if (!m_inpanel)
  {
    
    if ( m_type == QString("circular_dock") || m_type == QString("media_controller") )
    {
      if ( m_type == QString("circular_dock") )
      {m_act_role->setIcon(KIcon("applications-multimedia"));m_act_role->setText(i18n("Media controller"));}
      else if ( m_type == QString("media_controller") )
      {m_act_role->setIcon(KIcon("start-here-kde"));m_act_role->setText( i18n("Circular dock") );}
      tempActions << m_act_role << m_act_role_t;
      
      if (immutability() != 1)
      {
	m_act_lock->setIcon(KIcon("object-unlocked"));m_act_lock->setText(i18n("Unlock Daisy"));
	tempActions << m_act_lock;
	tempActions << m_act_close;
      }
      else
      {
	m_act_lock->setIcon(KIcon("object-locked"));m_act_lock->setText(i18n("Lock Daisy"));
	tempActions << m_act_lock;
      }
    }
    
    
    else if ( m_type == QString("standard_dock") )
    {
      m_act_role->setIcon(KIcon("start-here-kde"));m_act_role->setText(i18n("Circular dock"));
      tempActions << m_act_role;
      
      if (m_floating)
      {
	if (immutability() != 1)
	{
	  m_act_lock->setIcon(KIcon("object-unlocked"));m_act_lock->setText(i18n("Unlock Daisy"));
	  tempActions << m_act_lock;
	}
	else
	{
	  m_act_lock->setIcon(KIcon("object-locked"));m_act_lock->setText(i18n("Lock Daisy"));
	  tempActions << m_act_lock;
	}
      }
      else if (immutability() != 1 && !m_floating)tempActions << m_act_close;
    }
    
    
  }
  return tempActions;
}






//-----------------------------------------------------------------------------
// Destructor
daisy::~daisy()
{
  if (hasFailedToLaunch())
  {
    #ifdef INFORMATION_DEBUG
    kDebug() <<"FAILED TO LAUNCH";
    #endif
  }
  
  else
  {
    if (m_dialogLauncher != 0)m_dialogLauncher->deleteLater();
    if (m_reserver != 0)m_reserver->deleteLater();
    
    emit configNeedsSaving();
    if (m_paint_tmr){m_paint_tmr->stop();}
    if (m_up_tmr){m_up_tmr->stop();}
    if (m_tracker_tmr){m_tracker_tmr->stop();}
    
    int all = m_widgets.size();
    for (int i = 0; i < all; ++i)
    {delete m_widgets[i];delete m_indicons[i];}
    
    int alll = m_drawericons.size();
    for (int i = 0; i < alll; ++i)
    {delete m_drawericons[i];}
    
  }
}



//-----------------------------------------------------------------------------
// Shape
QPainterPath daisy::shape() const
{
  
  QPainterPath path;
  if (m_type==QString("circular_dock")  || m_type==QString("media_controller"))
  {path.addEllipse(boundingRect());}
  else{path.addRect(boundingRect());}
  return path;
  
}








/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////




//-----------------------------------------------------------------------------
// Get the right-clicked launcher
int daisy::getContextLauncher( QPointF &p_click )
{
  m_dexval = -1;
  for (int i = 0; i < m_widgets.size(); ++i)
  {
    if ( m_widgets[i]->geometry().contains(p_click) )
      m_dexval = i;
  }
  return m_dexval;
}


//-----------------------------------------------------------------------------
// Get the right-clicked task
int daisy::getContextTask( QPointF &p_click )
{
  for (int i = 0; i < total_taskpreviews; ++i)
  {if (m_taskicons[i]->geometry().contains(p_click))return i;}
  return -1;
}







//-----------------------------------------------------------------------------
// Create the Menus
void daisy::createMenus()
{
  //edit launcher menu
  m_launcher_menu = new KMenu();
  m_launcher_menu->addAction ( m_act_editlauncher );
  
  
  //edit launcher menu 2
  m_launcher_menu_t = new KMenu();
  m_launcher_menu_t->addAction ( m_act_editlauncher );
  m_launcher_menu_t->addSeparator();
  m_launcher_menu_t->addAction ( m_act_remlauncher );
  
  
  //trash menu
  m_trash_menu = new KMenu();
  m_trash_menu->addAction ( m_act_opentrash );
  m_trash_menu->addAction ( m_act_emptytrash );
  m_trash_menu->addAction ( m_act_restoretrash );
  
  
  //trash menu 2
  m_trash_menu_t = new KMenu();
  m_trash_menu_t->addAction ( m_act_opentrash );
  m_trash_menu_t->addAction ( m_act_emptytrash );
  m_trash_menu_t->addAction ( m_act_restoretrash );
  m_trash_menu_t->addSeparator();
  m_trash_menu_t->addAction ( m_act_remtrash );
  
  
  //task menu
  m_task_menu = new KMenu();
}





//-----------------------------------------------------------------------------
// Circle icons around
void daisy::circleAround(int &delta)
{
  
  int memb_tmp = m_domino[0];
  if (delta < 0)
  {
    switch (memb_tmp)
    {
      case 1:{m_domino.clear();m_domino << 5 << 7 << 2 << 4 << 8 << 6 << 1 << 3 << 0;break;}
      case 5:{m_domino.clear();m_domino << 8 << 3 << 6 << 1 << 2 << 7 << 5 << 4 << 0;break;}
      case 8:{m_domino.clear();m_domino << 2 << 4 << 7 << 5 << 6 << 3 << 8 << 1 << 0;break;}
      case 2:{m_domino.clear();m_domino << 6 << 1 << 3 << 8 << 7 << 4 << 2 << 5 << 0;break;}
      case 6:{m_domino.clear();m_domino << 7 << 5 << 4 << 2 << 3 << 1 << 6 << 8 << 0;break;}
      case 7:{m_domino.clear();m_domino << 3 << 8 << 1 << 6 << 4 << 5 << 7 << 2 << 0;break;}
      case 3:{m_domino.clear();m_domino << 4 << 2 << 5 << 7 << 1 << 8 << 3 << 6 << 0;break;}
      default:{m_domino.clear();m_domino << 1 << 6 << 8 << 3 << 5 << 2 << 4 << 7 << 0;break;}
    }
  }
  
  else
  {
    switch (memb_tmp)
    {
      case 8:{m_domino.clear();m_domino << 5 << 7 << 2 << 4 << 8 << 6 << 1 << 3 << 0;break;}
      case 2:{m_domino.clear();m_domino << 8 << 3 << 6 << 1 << 2 << 7 << 5 << 4 << 0;break;}
      case 6:{m_domino.clear();m_domino << 2 << 4 << 7 << 5 << 6 << 3 << 8 << 1 << 0;break;}
      case 7:{m_domino.clear();m_domino << 6 << 1 << 3 << 8 << 7 << 4 << 2 << 5 << 0;break;}
      case 3:{m_domino.clear();m_domino << 7 << 5 << 4 << 2 << 3 << 1 << 6 << 8 << 0;break;}
      case 4:{m_domino.clear();m_domino << 3 << 8 << 1 << 6 << 4 << 5 << 7 << 2 << 0;break;}
      case 1:{m_domino.clear();m_domino << 4 << 2 << 5 << 7 << 1 << 8 << 3 << 6 << 0;break;}
      default:{m_domino.clear();m_domino << 1 << 6 << 8 << 3 << 5 << 2 << 4 << 7 << 0;break;}
    }
  }
  

  
  /* 1-HOME  5-AMAROK  7-SETTINGS  8-TRASH  4-KMAIL  2-KONSOLE  3-BROWSER  6-MARBLE  0-KDE
  Diamond configuration
		1    
		
	    4         3           
  
	7       0	8
  
	    2        6
	    
		5
  */
  
}









//-----------------------------------------------------------------------------
// Resize and repos
//TODO
void daisy::resizeRepos( bool m_resetpos )
{
  if (!m_drawerscleared) clearDrawers();
  m_tracker_tmr->setInterval(m_hidingdelay);m_tracker_tmr->stop();
  
  
  if ( m_type == QString("circular_dock") || m_type == QString("media_controller")  )
  {
    m_domino.clear();m_domino << 1 << 6 << 8 << 3 << 5 << 2 << 4 << 7 << 0;
    setImmutability(Plasma::Mutable);
    setAspectRatioMode(Plasma::KeepAspectRatio);
    setContentsMargins(0, 0, 0, 0);
    if (m_resetpos)
    {
      // Plasma Resizing Bug (KDE 4.3).
      setMinimumSize(330,330);
      setMaximumSize(330,330);
      resize(330,330);
      if (!m_inpanel)setPos(QPointF(62,268));
      QTimer::singleShot(150, this, SLOT(resetResize()));
    }
    if (!m_inpanel)setMinimumSize(100,100);
  }
  
  
  
  else if ( m_type == QString("standard_dock") )
  {
    
    if (!m_resetpos)
    {
      m_domino.clear();
      QList<float> m_domino_tmp;
      m_domino_tmp << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
      for (int i = 0; i < m_domino_tmp.size(); ++i)
      {
	if ( m_domino_tmp[i] < m_values.size() )
	  m_domino << m_domino_tmp[i];
      }
    }
    
    QDesktopWidget m_boundry_tmp;
    QRect rect = m_boundry_tmp.screenGeometry( screen() );
    int pos_x=0;int pos_y=0;
    int sz_x=0;int sz_y=0;
    
    setImmutability(Plasma::Mutable);
    setAspectRatioMode(Plasma::IgnoreAspectRatio);
    setContentsMargins(0, 0, 0, 0);
    
    
    //Horz
    if ( m_position == QString("buttom_center") )
    {
      pos_x = ( rect.width()/2)-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))/2  ); pos_y = rect.height()- (m_icodimension+((m_icodimension/5)*2) );
      m_orientation = QString("horizontal");
    }
    else if ( m_position == QString("buttom_left") )
    {
      pos_x = 0; pos_y = rect.height()- (m_icodimension+((m_icodimension/5)*2) );
      m_orientation = QString("horizontal");
    }
    else if ( m_position == QString("buttom_right") )
    {
      pos_x = ( rect.width())-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )) + ((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)) ); pos_y = rect.height()- (m_icodimension+((m_icodimension/5)*2) );
      m_orientation = QString("horizontal");
    }
    
    else if ( m_position == QString("top_center") )
    {
      pos_x = ( rect.width()/2)-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))/2  ); pos_y = 0;
      m_orientation = QString("horizontal");
    }
    else if ( m_position == QString("top_left") )
    {pos_x = 0; pos_y = 0;m_orientation = QString("horizontal");}
    else if ( m_position == QString("top_right") )
    {
      pos_x = ( rect.width())-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  ))+ ((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing))  ); pos_y = 0;m_orientation = QString("horizontal");
    }
    
    
    
    //Vert
    else if ( m_position == QString("left_center") )
    {
      pos_x = 0; pos_y = ( rect.height()/2)-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))/2  );
      m_orientation = QString("vertical");
    }
    else if ( m_position == QString("left_top") )
    {pos_x = 0; pos_y = 0;m_orientation = QString("vertical");}
    else if ( m_position == QString("left_buttom") )
    {
      pos_x = 0; pos_y = ( rect.height() )-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+ ((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))  );
      m_orientation = QString("vertical");
    }
    
    else if ( m_position == QString("right_center") )
    {
      pos_x = ( rect.width())-( (  (m_icodimension/5)  + ( (m_icodimension+(m_icodimension/5))  ))  ); pos_y = ( rect.height()/2)-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))/2  );
      m_orientation = QString("vertical");
    }
    else if ( m_position == QString("right_top") )
    {
      pos_x = ( rect.width())-( (  (m_icodimension/5)  + ( (m_icodimension+(m_icodimension/5))  ))  ); pos_y = 0;
      m_orientation = QString("vertical");
    }
    else if ( m_position == QString("right_buttom") )
    {
      pos_x = ( rect.width())-( (  (m_icodimension/5)  + ( (m_icodimension+(m_icodimension/5))  ))  ); pos_y = ( rect.height() )-( (  (((m_icodimension/1.7)*2)-(m_icodimension*m_icospacing))  + (m_total_launchers*  (m_icodimension+(m_icodimension*m_icospacing))  )+ ((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing)))  );
      m_orientation = QString("vertical");
    }
    
    
    
    
    setElements();
    
    
    
    
    // Resize
    if ( m_orientation == QString("horizontal") )
    {
      sz_x = (((m_icodimension/1.7)*2) - (m_icodimension*m_icospacing)) + (m_total_launchers*(m_icodimension+(m_icodimension*m_icospacing))) +((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing));
      sz_y = m_icodimension + ((m_icodimension/5)*2);
    }
    else
    {
      sz_x = m_icodimension + ((m_icodimension/5)*2);
      sz_y = (((m_icodimension/1.7)*2) - (m_icodimension*m_icospacing)) + (m_total_launchers*(m_icodimension+(m_icodimension*m_icospacing)))+((total_taskpreviews*(m_icodimension+(m_icodimension*m_icospacing))) + (m_icospacing));
    }
    
    resize( sz_x, sz_y );
    setMinimumSize(sz_x,sz_y);
    setMaximumSize(sz_x,sz_y);
    
    
    
    
    
    // Lazzy math FIXME
    if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
    {
      if ( pos_y+sz_y < rect.height() ){pos_y++;}
    }
    else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
    {
      if ( pos_x+sz_x < rect.width() ){pos_x++;}
    }
    
    
    if (!m_inpanel)
    {
      if (!m_floating)
      {
	setPos(pos_x,pos_y);
	setAspectRatioMode(Plasma::FixedSize);
	setImmutability(Plasma::UserImmutable);
	if ( m_autohide )m_tracker_tmr->start();
      }
      else
      {
	//if (m_resetpos)setPos(pos_x,pos_y);
	setAspectRatioMode(Plasma::FixedSize);
      }
    }
    
    
    
  }
  
  
  
  
  
  
  
//   setContainmentType(Containment::CustomPanelContainment);
  emit spaceReserver(false);
}






//-----------------------------------------------------------------------------
// Calculate the launchers' positions
QList< QList <double> > daisy::calcWidgetPositions( const QRect &contentsRect )
{
  
  double t_width=contentsRect.width(), t_height=contentsRect.height();
  double t_wdico=t_width/5, t_hgico=t_height/5;
  QList<double> m_ico_posX;QList<double> m_ico_posY;
  QList<double> m_indico_posX;QList<double> m_indico_posY;
  QList<double> m_ico_szX;QList<double> m_ico_szY;
  QList<double> m_back_sz;
  QList< QList<double> > ret_val;
  
  
  m_back_sz << t_width << t_height;
  
  // ROUNDED
  if (m_type==QString("circular_dock")  || m_type==QString("media_controller"))
  {
    m_ico_posX << (int)t_width/2.5 << (int)t_width/2.5 << (int)t_width/20 << (int)t_width/1.33333;
    m_ico_posY << (int)t_height/20 << (int)t_height/1.33333 << (int)t_height/2.5 << (int)t_height/2.5;
    m_ico_szX << t_wdico << t_wdico << t_wdico << t_wdico;
    m_ico_szY << t_hgico << t_hgico << t_hgico << t_hgico;
    
    if ( m_type==QString("circular_dock") )
    {
      m_ico_posX << (int)t_width/6.66667 << (int)t_width/6.66667 << (int)t_width/1.53846 <<
      (int)t_width/1.53846 << (int)t_width/2.58620689655;
      m_ico_posY << (int)t_height/6.66667 << (int)t_height/1.53846 << (int)t_height/6.66667 <<
      (int)t_height/1.53846 << (int)t_height/2.58620689655;
      m_ico_szX << t_wdico << t_wdico << t_wdico << t_wdico << (int)t_width/4.41176470588;
      m_ico_szY << t_hgico << t_hgico << t_hgico << t_hgico << (int)t_height/4.41176470588;
    }
    else if ( m_type==QString("media_controller") )
    {
      m_ico_posX << (int)t_width/6.66667 + t_wdico/3 << (int)t_width/6.66667 + t_wdico/3 << (int)t_width/1.53846 <<
      (int)t_width/1.53846 << (int)t_width/2.58620689655;
      m_ico_posY << (int)t_height/6.66667 + t_hgico/3 << (int)t_height/1.53846 << (int)t_height/6.66667 + t_hgico/3 <<
      (int)t_height/1.53846 << (int)t_height/2.58620689655;
      m_ico_szX << t_wdico/1.5 << t_wdico/1.5 << t_wdico/1.5 << t_wdico/1.5 << (int)t_width/4.41176470588;
      m_ico_szY << t_hgico/1.5 << t_hgico/1.5 << t_hgico/1.5 << t_hgico/1.5 << (int)t_height/4.41176470588;
    }
    
    m_indico_posX << (int)t_width/2.5 << 
    (int)t_width/2.5 << 
    (int)t_width/20 << 
    (int)t_width/1.33333 << 
    (int)t_width/6.66667 << 
    (int)t_width/6.66667 << 
    (int)t_width/1.53846 <<
    (int)t_width/1.53846 << 
    (int)t_width/2.58620689655;
    
    m_indico_posY << (int)m_ico_posY[0]+(m_ico_szY[0]/5) << 
    (int)m_ico_posY[1]+(m_ico_szY[1]/5) << 
    (int)m_ico_posY[2]+(m_ico_szY[2]/5) << 
    (int)m_ico_posY[3]+(m_ico_szY[3]/5) << 
    (int)m_ico_posY[4]+(m_ico_szY[4]/5) << 
    (int)m_ico_posY[5]+(m_ico_szY[5]/5) << 
    (int)m_ico_posY[6]+(m_ico_szY[6]/5) <<
    (int)m_ico_posY[7]+(m_ico_szY[7]/5) << 
    (int)m_ico_posY[8]+(m_ico_szY[8]/5);
      
  }
  
  
  else if ( m_type==QString("standard_dock") )
  {
    for (int i = 0; i < m_widgets.size(); ++i)
    {
      m_ico_szX << m_icodimension;m_ico_szY << m_icodimension;
      
      if ( m_orientation== QString("horizontal") )
      {
	m_ico_posX << ( (m_icodimension/1.7) + ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) )+m_zoomposdiff[i];
	m_ico_posY << (m_icodimension/5.5)+m_zoomposdiff[i];
	
	m_indico_posX << ( (m_icodimension/1.7) + ( i* (m_icodimension+(m_icodimension*m_icospacing)) ) )+m_zoomposdiff[i];
	m_indico_posY << (m_icodimension/5) + (m_ico_szY[i]/5)+m_zoomposdiff[i];
	
	
	last_icopos.clear();
	last_icopos << ( (m_icodimension/1.7) + ( (i+1)* (m_icodimension+(m_icodimension*m_icospacing)) ) );
	last_icopos << (m_icodimension/5.5);
      }
      
      else
      {
	m_ico_posY << ( (m_icodimension/1.7) + (i* ((m_icodimension*m_icospacing)+m_icodimension)  ) )+m_zoomposdiff[i];
	m_ico_posX << (m_icodimension/5)+m_zoomposdiff[i];
	
	m_indico_posY << ( (m_icodimension/1.7) + (i* ((m_icodimension*m_icospacing)+m_icodimension)) )+ (m_ico_szY[i]/5)+m_zoomposdiff[i];
	m_indico_posX << (m_icodimension/5)+m_zoomposdiff[i];
	
	
	last_icopos.clear();
	last_icopos << (m_icodimension/5.5);
	last_icopos << ( (m_icodimension/1.7) + ( (i+1)* (m_icodimension+(m_icodimension*m_icospacing)) ) );
      }
      
    }
    
  }
  
  
  ret_val << m_ico_posX << m_ico_posY << m_ico_szX << m_ico_szY << m_back_sz << m_indico_posX << m_indico_posY;
  return ret_val;
}












//-----------------------------------------------------------------------------
// Set Theme
void daisy::setTheme()
{
  m_backframe_t.clearCache();
  
  if ( m_theme_t == QString("default") )
  {m_backframe_t.setImagePath("widgets/dock-background");}
  
  else if ( m_theme_t == QString("opaque") )
  {m_backframe_t.setImagePath("widgets/background");}
  
  else if ( m_theme_t == QString("alternative") )
  {m_backframe_t.setImagePath("widgets/panel-background");}
  
  
  
  else if ( m_theme_t == QString("mach") )
  {m_backframe_t.setImagePath("widgets/dock-background-mach");}
  
  else if ( m_theme_t == QString("mach-2") )
  {m_backframe_t.setImagePath("widgets/dock-background-mach-2");}
  
  else if ( m_theme_t == QString("shiny-black") )
  {m_backframe_t.setImagePath("widgets/dock-background-shiny-black");}
  
  else if ( m_theme_t == QString("vidro") )
  {m_backframe_t.setImagePath("widgets/dock-background-vidro");}
  
  
  else
  {m_backframe_t.setImagePath("widgets/translucentbackground");}
  
  
  setElements();
  
}



//-----------------------------------------------------------------------------
// Set Theme Elements
void daisy::setElements()
{
  QString cardinal_tmp;
  
  if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
  {cardinal_tmp = QString("south");}
  else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
  {cardinal_tmp = QString("north");}
  else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
  {cardinal_tmp = QString("west");}
  else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
  {cardinal_tmp = QString("east");}
  
  if ( m_backframe_t.hasElementPrefix(cardinal_tmp) )
    m_backframe_t.setElementPrefix(cardinal_tmp);
  else
    m_backframe_t.setElementPrefix("");
  
}





//-----------------------------------------------------------------------------
// Toggle state
//FIXME does not work when all the widgets in the plasma workspace are locked. 
void daisy::toggleLockedState(void)
{
  if (immutability() == 1) {setImmutability(Plasma::UserImmutable);emit update();}
  else {setImmutability(Plasma::Mutable);}
}



//-----------------------------------------------------------------------------
// Remove Daisy
//FIXME does not work when all the widgets in the plasma workspace are locked. 
void daisy::removeDaisy(void)
{
  
  int oktorem_tmp = 0;
  oktorem_tmp = KMessageBox::warningYesNo ( NULL, 
  i18n("Do you really want to remove this Daisy?"), 
  QString::null, 
  KGuiItem (i18n("&Remove this Daisy"),QString("dialog-ok"), QString::null, QString::null), 
  KGuiItem (i18n("&Cancel"),QString("dialog-cancel"), QString::null, QString::null)
  );
  if (oktorem_tmp == 3)
  {
    if (immutability() != 1){setImmutability(Plasma::Mutable);}
    if (immutability() != 1) 
    {
      KMessageBox::sorry(NULL, i18n("Unlock Plasma Workspace Widgets first"), i18n("Widgets locked") );
      if (!m_floating)setImmutability(Plasma::UserImmutable);
    }
    else {emit destroy();}
  }
  
}





//-----------------------------------------------------------------------------
// Check if workspace is locked
bool daisy::checkLock()
{
  if (immutability() != 1)
  {setImmutability(Plasma::Mutable);}
  
  if (immutability() != 1)
  {
    if (!m_floating)
    {
      setImmutability(Plasma::UserImmutable);
    }
    return true;
  }
  
  else
  {
    if (!m_floating)
    {
      setImmutability(Plasma::UserImmutable);
    }
  }
  
  return false;
  
}







//-----------------------------------------------------------------------------
// Tooltip Update
void daisy::updateToolTipContent()
{
  
  if (!m_showtooltips_l)
  {clearToolTipContent();}
  
  else
  {getAllTasks();}
  
}



//-----------------------------------------------------------------------------
// Clear tooltips
void daisy::clearToolTipContent()
{
  Plasma::ToolTipContent toolTipData;toolTipData.setAutohide(false);
  int all = m_widgets.size();
  
  
  for (int i = 0; i < all; ++i)
  {
    if (m_show_trash && m_widgets[i] == m_widgets[m_trash_spot])
    {}
    
    else
    {
      if (m_showtooltips_l && m_showtooltips_i && m_type != QString("media_controller") )
      {
	toolTipData.setMainText( m_values[i][1] );
	if ( m_tiptype == "thumbnail" || m_tiptype == "icon" )
	  toolTipData.setImage( KIcon( m_values[i][2]).pixmap(IconSize(KIconLoader::Panel)) );
	Plasma::ToolTipManager::self()->setContent(m_widgets[i], toolTipData);
      }
      
      else
	Plasma::ToolTipManager::self()->clearContent(m_widgets[i]);
    }
  }
  
  
  
  if ( m_taskpreviews && m_type == QString("standard_dock") )
  {
    all = m_taskicons.size();
    for (int i = 0; i < all; ++i)
    {Plasma::ToolTipManager::self()->clearContent(m_taskicons[i]);}
  }
  
  
}








//-----------------------------------------------------------------------------
// Track Mouse
void daisy::mouseTracker(void)
{
  
  if ( m_autohide && m_type == QString("standard_dock") && !m_inpanel && !m_floating )
  {
    if ( isUnderMouse() )
    {
      m_tracker_tmr->setInterval(m_hidingdelay);m_tracker_tmr->start();
      if ( !isVisible() ){setVisible(true);}
    }
    else
    {
      m_tracker_tmr->setInterval(500);m_tracker_tmr->start();
      if ( isVisible() )setVisible(false);
    }
  }
  
  else
  {
    m_tracker_tmr->stop();
    if ( !isVisible() ){setVisible(true);}
  }
  
}








//-----------------------------------------------------------------------------
// Swap to linear role
void daisy::swapLinear()
{
  m_circpos = scenePos();
  m_paint_tmr->stop();m_to_paint=int(0);
  setBusy(false);
  
  m_type=QString("standard_dock");
  QTimer::singleShot(550, this, SLOT(delayResize()));
  emit metamorphosis( m_type );
  
}



//-----------------------------------------------------------------------------
// Swap circular role
void daisy::swapCircular()
{
  
  m_paint_tmr->stop();m_to_paint=int(0);
  QString m_type_temp = m_type;
  setBusy(false);
  
  if ( m_type == QString("circular_dock") ) m_type=QString("media_controller");
  else if ( m_type == QString("media_controller") ) m_type=QString("circular_dock");
  else if ( m_type == QString("standard_dock") )
  {
    QTimer::singleShot(550, this, SLOT(delayResize()));
    m_type=QString("circular_dock");
  }
  
  emit metamorphosis( m_type_temp );
  
}




//-----------------------------------------------------------------------------
// Metamorphosis
void daisy::metamorphosis( QString m_type_temp )
{
  
  KConfigGroup cg = config();
  cg.writeEntry("type", m_type);
  emit configNeedsSaving();
  refurbishLaunchers();
  
  if ( m_type_temp == QString("standard_dock") )
  {
    resizeRepos(true);
  }
  m_up_tmr->setInterval(100);m_up_tmr->start();
  
}




//-----------------------------------------------------------------------------
// HACK delay resize
void daisy::delayResize(void)
{
  
  m_up_tmr->stop();m_rz_tmr->stop();
  KConfigGroup cg = config();
  cg.writeEntry("icodimension", m_icodimension);
  resizeRepos(true);
  emit update();
  m_up_tmr->setInterval(500);m_up_tmr->start();
  
}


//-----------------------------------------------------------------------------
// HACK ghost showing on repaint
void daisy::delayUpdate(void)
{
  m_up_tmr->stop();
  if (!m_drawerscleared)clearDrawers();
  getAllTasks();
  setVisible(true);
  emit update();
}



//-----------------------------------------------------------------------------
// HACK Delayed Resize circular
void daisy::resetResize(void)
{
  resize(330,330);
  if (!m_inpanel)setPos(QPointF(62,268));
  setMaximumSize(2330,2330);
}



//-----------------------------------------------------------------------------
// HACK Avoid repeating execution
void daisy::delayExec(void)
{
  m_dlx_tmr->stop();
  KRun::runCommand( m_values[m_dexval][0], m_values[m_dexval][1], m_values[m_dexval][2], NULL, NULL );
}



//-----------------------------------------------------------------------------
// HACK Avoid repeating shade
void daisy::delayShade(void)
{
  m_dlt_tmr->stop();
  toggShadeTask( m_workwid );
}




//-----------------------------------------------------------------------------
// Close a task
void daisy::taskClosing(void)
{
  m_workwid = 0;
  for (int i = 0; i < total_taskpreviews; ++i)
  {
    if (m_taskicons[i]->isUnderMouse())
    {
      m_workwid = showedTasks[i];
      break;
    }
  }
  closeTask(m_workwid);
}











#include "daisy.moc"
