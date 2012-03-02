/*
*   Configuration: daisy
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
// Space reserver
// HACK
void daisy::spaceReserver(bool startup)
{
  
  if (startup)
  {
    m_reserver = new QWidget;
    m_reserver->setFixedSize( 1,1 );
    m_reserver->move(-100000,-100000);
    KWindowSystem::setType(m_reserver->winId(), NET::Dock);
    KWindowSystem::setState(m_reserver->winId(), NET::KeepBelow);
    KWindowSystem::setOnAllDesktops(m_reserver->winId(), true);
    m_reserver->show();
  }
  
  else
  {
    if ( m_type == QString("circular_dock") || m_type == QString("media_controller")  )
      KWindowSystem::setStrut(m_reserver->winId(), 0,0,0,0);
    
    else if ( m_type == QString("standard_dock") )
    {
      if (m_inpanel || m_floating || !m_reservespace)
	KWindowSystem::setStrut(m_reserver->winId(), 0,0,0,0);
      
      else
      {
	if ( m_position == QString("buttom_center") || m_position == QString("buttom_left") || m_position == QString("buttom_right") )
	  KWindowSystem::setStrut(m_reserver->winId(), 0,0,0, m_icodimension+((m_icodimension/5)*2) );
	
	else if ( m_position == QString("top_center") || m_position == QString("top_left") || m_position == QString("top_right") )
	  KWindowSystem::setStrut(m_reserver->winId(), 0,0,m_icodimension+((m_icodimension/5)*2), 0);
	
	else if ( m_position == QString("right_center") || m_position == QString("right_top") || m_position == QString("right_buttom") )
	  KWindowSystem::setStrut(m_reserver->winId(), 0,m_icodimension+((m_icodimension/5)*2),0, 0);
	
	else if ( m_position == QString("left_center") || m_position == QString("left_top") || m_position == QString("left_buttom") )
	  KWindowSystem::setStrut(m_reserver->winId(), m_icodimension+((m_icodimension/5)*2),0,0, 0);
      }
      
    }
  }
  
}






//-----------------------------------------------------------------------------
// Remove launcher later
void daisy::destroyLauncher(void)
{
  
  if ( m_oktodestroy && m_dexval != -1 && m_type == QString("standard_dock") )
  {
    if ( m_alias[m_dexval] != QString("Trash_Plugin_alias") )
      emit removeLauncher();
    else
      emit remTrash();
  }
  
  
}




//-----------------------------------------------------------------------------
// Remove launcher
void daisy::removeLauncher(void)
{
  if (m_total_launchers <= 1)emit removeDaisy();
  else
  {
    int oktorem_tmp = 0;
    oktorem_tmp = KMessageBox::warningYesNo (  NULL, 
    i18n("Do you really want to remove this launcher from dock?"), 
    QString::null, 
    KGuiItem (i18n("&Remove launcher"),QString("dialog-ok"), QString::null, QString::null), 
    KGuiItem (i18n("&Cancel"),QString("dialog-cancel"), QString::null, QString::null)
    );
    
    if (oktorem_tmp == 3)
    {
      KConfigGroup cg = config();
      QStringList m_vals_tmp = m_values[m_dexval];QStringList m_avals_tmp = m_avalues[m_dexval];QString m_alias_tmp = m_alias[m_dexval];
      
      m_total_launchers--;
      cg.writeEntry("total_launchers", m_total_launchers);
      
      int svlaun_tmp = 30;
      if (m_show_trash) svlaun_tmp=m_total_launchers-1;
      else svlaun_tmp=m_total_launchers;
      
      m_values.removeAt(m_dexval);m_avalues.removeAt(m_dexval);m_alias.removeAt(m_dexval);
      m_values.insert( svlaun_tmp, m_vals_tmp );
      m_avalues.insert( svlaun_tmp, m_avals_tmp );
      m_alias.insert( svlaun_tmp, m_alias_tmp );
      
      writeConfiguration();
      refurbishLaunchers();
      getAllTasks();
      resizeRepos( true );
    }
    m_dexval = -1;
  }
  
}







//-----------------------------------------------------------------------------
// Find launcher position
int daisy::findLauncherPos( QPointF droppos )
{
  int wid_pos;int comp_pos;
  
  if ( m_orientation == QString("horizontal") ){comp_pos = droppos.x();}
  else{comp_pos = droppos.y();}
  
  int widnewpos_tmp = -1;
  for (int i = 0; i < m_widgets.size(); ++i)
  {
    if ( m_orientation == QString("horizontal") ){wid_pos = m_widgets[i]->geometry().x();}
    else{wid_pos = m_widgets[i]->geometry().y();}
    
    if ( m_widgets[i]->geometry().contains(droppos) || comp_pos <= wid_pos + ( m_icodimension +(m_icodimension*m_icospacing) )  )
    {
      if ( i < m_dexval && i != 0 ) {widnewpos_tmp = i+1;}
      else if (i == 0)
      {
	if (wid_pos < comp_pos){widnewpos_tmp = 1;}
	else {widnewpos_tmp = 0;}
      }
      else {widnewpos_tmp = i;}
      break;
    }
  }
  
  return widnewpos_tmp;
}







//-----------------------------------------------------------------------------
// Add Launcher
void daisy::addLauncher( QPointF droppos, QList<QUrl> &payload )
{
  Q_UNUSED(droppos);
  
  foreach (QUrl url, payload)
  {
    KUrl url_tmp = KUrl(url);
    
    if ( url_tmp.isLocalFile() && KDesktopFile::isDesktopFile( QString(url_tmp.path()) ) )
    {
      KDesktopFile deskfile_tmp(QString(url_tmp.path()));
      KConfigGroup deskconfig = deskfile_tmp.desktopGroup();
      
      QString deskcom_tmp = deskconfig.readPathEntry("Exec", QString());
      if (deskcom_tmp.isEmpty())
      {
	deskcom_tmp = deskfile_tmp.readUrl();
	if ( deskcom_tmp.isEmpty() ) 
	{deskcom_tmp = deskfile_tmp.readPath();}
      }
      QStringList list_tmp;
      list_tmp = deskcom_tmp.split(QRegExp("\\s+"));
      deskcom_tmp = list_tmp[0];
      
      QString deskicon_tmp = deskfile_tmp.readIcon();
      QString deskname_tmp = ( deskfile_tmp.readName() );
      if ( deskname_tmp.isEmpty() ){deskname_tmp = deskcom_tmp;}
      if ( !deskname_tmp.isEmpty() )
      {
	QString deskalias_tmp = deskcom_tmp;
	QStringList val_tmp = QStringList( QStringList() <<  deskcom_tmp << deskname_tmp  << deskicon_tmp );
	QStringList aval_tmp = QStringList( QStringList() << QString("false") << QString("false") << QString("application-x-executable") << QString("0") );
	m_values.append( val_tmp );
	m_avalues.append( aval_tmp );
	m_alias.append( deskalias_tmp );
	m_total_launchers++;
      }
    }
  }
  
  KConfigGroup cg = config();
  if ( m_total_launchers != cg.readEntry("total_launchers", 9) && m_type == QString("standard_dock") )
  {
    QTimer::singleShot(200, this, SLOT(addDelay()));
  }
  
}





//-----------------------------------------------------------------------------
// Move Launcher
void daisy::moveLauncher( QPointF droppos )
{
  int widnewpos_tmp = findLauncherPos( droppos );
  
  if ( widnewpos_tmp != -1 && m_dexval != widnewpos_tmp && m_alias[m_dexval] != QString("Trash_Plugin_alias") )
  {
    if (widnewpos_tmp == m_trash_spot)
    {widnewpos_tmp--;}
    
    QStringList m_vals_tmp = m_values[m_dexval];QStringList m_avals_tmp = m_avalues[m_dexval];QString m_alias_tmp = m_alias[m_dexval];
    m_values.removeAt(m_dexval);m_avalues.removeAt(m_dexval);m_alias.removeAt(m_dexval);
    
    m_values.insert( widnewpos_tmp, m_vals_tmp );
    m_avalues.insert( widnewpos_tmp, m_avals_tmp );
    m_alias.insert( widnewpos_tmp, m_alias_tmp );
    
    QTimer::singleShot(200, this, SLOT(addDelay()));
    
  }
  
}




//-----------------------------------------------------------------------------
// Delay adding launcher
void daisy::addDelay(void)
{
  KConfigGroup cg = config();
  cg.writeEntry("total_launchers", m_total_launchers);
  writeConfiguration();
  refurbishLaunchers();
  getAllTasks();resizeRepos( true );
  m_dexval = -1;
}





//-----------------------------------------------------------------------------
// Remove Trash
void daisy::remTrash(void)
{
  if (m_total_launchers <= 1)emit removeDaisy();
  else
  {
    int oktorem_tmp = 0;
    oktorem_tmp = KMessageBox::warningYesNo (  NULL, 
    i18n("Do you really want to remove this trash plugin?"), 
    QString::null, 
    KGuiItem (i18n("&Remove trash plugin"),QString("dialog-ok"), QString::null, QString::null), 
    KGuiItem (i18n("&Cancel"),QString("dialog-cancel"), QString::null, QString::null)
    );
    if (oktorem_tmp == 3)
      toggTrash();
  }
  m_dexval = -1;
}



//-----------------------------------------------------------------------------
// Toggle Trash
void daisy::toggTrash(void)
{
  KConfigGroup cg = config();
  
  m_show_trash = not m_show_trash;
  cg.writeEntry( "show_trash", m_show_trash);
  if (!m_show_trash) m_total_launchers--;
  else m_total_launchers++;
  cg.writeEntry("total_launchers", m_total_launchers);
  
  writeConfiguration();
  refurbishLaunchers();
  getAllTasks();
  resizeRepos( true );
  
}







//-----------------------------------------------------------------------------
// Write configuration
void daisy::writeConfiguration()
{
  KConfigGroup cg = config();
  
  if ( m_values.size() >= m_trash_spot-1 )
    m_values.removeAt(m_trash_spot);m_avalues.removeAt(m_trash_spot);m_alias.removeAt(m_trash_spot);
  
  for (int i = 0; i < m_values.size(); ++i)
  {
    QString str;
    str.setNum(i);
    
    if ( m_alias[i] != QString("Trash_Plugin_alias") )
    {
      cg.writeEntry( "launcher" + str, m_values[i] );
      cg.writeEntry( "launcher" + str + "a", m_avalues[i] );
      cg.writeEntry( "alias" + str, m_alias[i] );
    }
  }
  
  getLauncherValues();
  
  emit configNeedsSaving();
  
}





//-----------------------------------------------------------------------------
// Read configuration
void daisy::readConfiguration()
{
  
  KConfigGroup cg = config();
  m_theme = cg.readEntry("theme", QString("default"));
  m_theme_t = cg.readEntry("theme_t", QString("default"));
  m_type = cg.readEntry("type", QString("circular_dock"));
  m_player = cg.readEntry("player", QString("Amarok 2.x"));
  m_draw_icoback = cg.readEntry("draw_icoback", true);
  m_showtooltips = cg.readEntry("showtooltips", true);
  m_showtooltips_l = cg.readEntry("showtooltips_launchers", true);
  m_showtooltips_i = cg.readEntry("showtooltips_inactive", true);
  m_showindicons = cg.readEntry("showindicons", true);
  m_showmirror = cg.readEntry("showmirror", true);
  m_total_launchers = cg.readEntry("total_launchers", 9);
  m_icodimension = cg.readEntry("icodimension", 52);
  m_icospacing = cg.readEntry("icospacing", 0.250);
  m_position = cg.readEntry("position", "buttom_center");
  m_backopacity = cg.readEntry("background_opacity", 1.0);
  m_floating = cg.readEntry("floating", false);
  m_reservespace = cg.readEntry("reservespace", true);
  m_autohide = cg.readEntry("autohide", false);
  m_show_trash = cg.readEntry("show_trash", true);
  m_hidingdelay = cg.readEntry("hidingdelay", 3000);
  m_showondesk = cg.readEntry("showondesk", false);
  m_accept_drops = cg.readEntry("acceptdrops", true);
  m_zoomtype = cg.readEntry("zoomtype", QString("framed"));
  m_click_effects = cg.readEntry("click_effects", false);
  m_click_effect_type = cg.readEntry("click_effect_type", QString("default"));
  m_tiptype = cg.readEntry("tip_type", QString("thumbnail"));
  m_drawersize = cg.readEntry("drawersize", 38);
  m_drawerrotation = cg.readEntry("drawerrotation", 1.50);
  m_showtaskoflauncher = cg.readEntry("showtaskoflauncher", true);
  m_taskpreviews = cg.readEntry("taskpreviews", true);
  m_showclosetask = cg.readEntry("showclosetask", false);
  m_middleClickAction = cg.readEntry("middleclickaction", QString("shade"));
  
}






//-----------------------------------------------------------------------------
// Get the launchers' values
void daisy::getLauncherValues()
{
  m_values.clear();m_avalues.clear();m_alias.clear();
  
  if (m_type==QString("media_controller"))
  {
    QStringList m_player_coms;QStringList m_icos_tmp;
    m_player_coms = getPlayerComs();
    m_icos_tmp << QString("media-playback-pause") << QString("media-playback-stop") << QString("media-skip-backward") <<
    QString("media-skip-forward") << QString("media-seek-backward") << QString("view-media-playlist") <<
    QString("media-seek-forward") << QString("player-volume-muted") << QString("media-playback-start");
    
    for (int i = 0; i < m_icos_tmp.count(); ++i)
    {
      m_values << QStringList( QStringList() << m_player_coms[i] << QString("") << m_icos_tmp[i] );
      m_avalues << QStringList( QStringList() << QString("") << QString("") << QString("") << QString("0") );
      m_alias << QString( "false" );
    }
  }
  
  
  else
  {
    QStringList m_coms_tmp;QStringList m_icos_tmp;QStringList m_names_tmp;QStringList m_alias_tmp;
    QStringList m_acoms_tmp;QStringList m_aicos_tmp;QStringList m_anames_tmp;QStringList m_iact_tmp;
    
    m_coms_tmp 
    << QString("dolphin $HOME") 
    << QString("konsole") 
    << QString("opera") 
    << QString("kmail") 
    << QString("amarok -m") 
    << QString("kate") 
    << QString("okular")
    << QString("systemsettings") 
    ;
    
    m_icos_tmp 
    << QString("user-home") 
    << QString("utilities-terminal") 
    << QString("applications-internet") 
    << QString("internet-mail") 
    << QString("amarok") 
    << QString("kate") 
    << QString("graphics-viewer-document")
    << QString("preferences-system") 
    ;
    
    m_names_tmp 
    << i18n("personal files") 
    << i18n("konsole") 
    << i18n("opera") 
    << i18n("kmail") 
    << i18n("amarok") 
    << i18n("kate") 
    << i18n("Document viewer")
    << i18n("systemsettings") 
    ;
    
    m_acoms_tmp 
    << QString("kfmclient exec bookmarks:/") 
    << QString("ksysguard") 
    << QString("kfmclient exec bookmarks:/") 
    << QString("kfmclient exec mailto:/") 
    << QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Pause") 
    << QString("okular") 
    << QString("gwenview")
    << QString("kfmclient exec settings:/") 
    ;
    
    m_anames_tmp 
    << i18n("bookmarks")
    << i18n("system") 
    << i18n("bookmarks") 
    << i18n("mail") 
    << i18n("pause") 
    << i18n("okular") 
    << i18n("gwenview") 
    << i18n("settings") 
    ;
    
    m_aicos_tmp 
    << QString("bookmarks")
    << QString("utilities-system-monitor") 
    << QString("bookmarks") 
    << QString("email") 
    << QString("media-playback-pause") 
    << QString("okular") 
    << QString("gwenview") 
    << QString("configure") 
    ;
    
    m_iact_tmp 
    << QString("0") 
    << QString("0") 
    << QString("0") 
    << QString("0") 
    << QString("0") 
    << QString("0") 
    << QString("0") 
    << QString("0")
    ;
    
    m_alias_tmp 
    << QString("dolphin") 
    << QString("konsole") 
    << QString("opera") 
    << QString("kmail") 
    << QString("amarok") 
    << QString("kate") 
    << QString("okular")
    << QString("systemsettings") 
    ;
    
    
    KConfigGroup cg = config();
    int iter_tmp=0;QStringList val_tmp;QStringList aval_tmp;QString alias_tmp;
    if ( m_type == QString("circular_dock") ){iter_tmp=9;}
    else if ( m_type == QString("standard_dock") ){iter_tmp=m_total_launchers;}
    
    for (int i = 0; i < iter_tmp - m_total_plugs; ++i)
    {
      if ( i > m_coms_tmp.size()-1 )
      {
	val_tmp = QStringList( QStringList() << QString("false") <<  QString("false") << QString("application-x-executable") );
	aval_tmp = QStringList( QStringList() << QString("false") << QString("false") << QString("application-x-executable") << QString("0") );
	alias_tmp = QString( "none" );
      }
      else
      {
	val_tmp = QStringList( QStringList() << m_coms_tmp[i] <<  m_names_tmp[i] << m_icos_tmp[i] );
	aval_tmp = QStringList( QStringList() << m_acoms_tmp[i] << m_anames_tmp[i] << m_aicos_tmp[i] << m_iact_tmp[i] );
	alias_tmp = QString( m_alias_tmp[i] );
      }
      
      
      QString str;str.setNum(i);
      m_values << cg.readEntry( "launcher" + str, val_tmp );
      m_avalues << cg.readEntry( "launcher"+str+"a", aval_tmp );
      m_alias << cg.readEntry( "alias" + str, alias_tmp );
    }
    
    plugItUp();
    
    
  }
  
}






//-----------------------------------------------------------------------------
// Get the plugins values
// FIXME
void daisy::plugItUp()
{
  KConfigGroup cg = config();
  m_show_trash = cg.readEntry("show_trash", true);
  
  if ( m_type == QString("circular_dock") )
  {
    m_trash_spot = int(3);
  }
  
  else if ( m_type == QString("standard_dock") )
  {
    m_trash_spot = m_total_launchers-1;
  }
  
  if ( m_values.size() >= m_trash_spot-1 )
  {
    if ( m_show_trash  || m_type == QString("circular_dock") )
    {
      m_values.insert( m_trash_spot, QStringList() << QString("kfmclient exec trash:/") <<  i18n("Trash") << QString("user-trash") );
      m_avalues.insert( m_trash_spot, QStringList() << QString("ktrash --empty") << i18n("Trash") << QString("user-trash") << QString("0")  );
      m_alias.insert( m_trash_spot,  QString("Trash_Plugin_alias") );
      m_show_trash = true;
    }
    
    else
    {
      QStringList val_tmp = QStringList( QStringList() << QString("false") <<  QString("false") << QString("application-x-executable") );
      QStringList aval_tmp = QStringList( QStringList() << QString("false") << QString("false") << QString("application-x-executable") << QString("0") );
      QString alias_tmp = QString( "none" );
      
      QString str;str.setNum(m_trash_spot);
      m_values.insert( m_trash_spot, cg.readEntry( "launcher" + str, val_tmp ) );
      m_avalues.insert( m_trash_spot, cg.readEntry( "launcher"+str+"a", aval_tmp ) );
      m_alias.insert( m_trash_spot, cg.readEntry( "alias" + str, alias_tmp ) );
      
      m_trash_spot = -1;
    }
    
  }
  
  
}








