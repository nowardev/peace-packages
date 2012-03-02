/*
*   Trash plugin: daisy
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
// Check TRASH
void daisy::checkTrash(void)
{
  
  if ( m_domino.contains(m_trash_spot) && (m_type==QString("circular_dock") || m_type==QString("standard_dock")) && m_show_trash )
  {
    QDir trashed_items = QDir( m_trash_dir );
    //trashed_items.setFilter(QDir::NoDotAndDotDot);
    int trashed_count = trashed_items.count()-2;
    QString str;
    str.setNum(trashed_count);
    
    if (trashed_count > 0)
    {
      m_widgets[m_trash_spot]->setIcon( KIcon("user-trash-full") );
      m_trashfull = true;
      
      if (m_showtooltips)
      {
	Plasma::ToolTipContent toolTipData;
	toolTipData.setAutohide(false);
	if ( m_tiptype == "thumbnail" || m_tiptype == "icon" )
	  toolTipData.setImage(KIcon("user-trash-full").pixmap(IconSize(KIconLoader::Panel)));
	toolTipData.setMainText( i18n("Trash") );
	if (trashed_count > 1) {toolTipData.setSubText( str + " " + i18n("items") );}
	else {toolTipData.setSubText( i18n("One item") );}
	Plasma::ToolTipManager::self()->setContent(m_widgets[m_trash_spot], toolTipData);
      }
      else {Plasma::ToolTipManager::self()->clearContent(m_widgets[m_trash_spot]);}
    }
    
    else
    {
      m_widgets[m_trash_spot]->setIcon( KIcon("user-trash") );
      m_trashfull = false;
      
      if (m_showtooltips)
      {
	Plasma::ToolTipContent toolTipData;
	toolTipData.setAutohide(false);
	if ( m_tiptype == "thumbnail" || m_tiptype == "icon" )
	  toolTipData.setImage(KIcon("user-trash").pixmap(IconSize(KIconLoader::Panel)));
	toolTipData.setMainText( i18n("Trash") );
	toolTipData.setSubText( i18n("Empty") );
	Plasma::ToolTipManager::self()->setContent(m_widgets[m_trash_spot], toolTipData);
      }
      else {Plasma::ToolTipManager::self()->clearContent(m_widgets[m_trash_spot]);}
    }
    
  }
}






//-----------------------------------------------------------------------------
// Move to TRASH
void daisy::moveToTrash(QList<QUrl> &payload)
{
  foreach (QUrl url, payload)
  {
    KUrl url_tmp = KUrl(url);
    
    if ( url_tmp.isLocalFile() )
    {
      QString program = QString("kioclient");
      QStringList arguments;
      arguments <<QString("move");
      arguments <<QString(url_tmp.path());
      arguments <<QString("trash:/");
      QProcess *myProcess = new QProcess(this);
      myProcess->start(program, arguments);
    }
  }
  
}



//-----------------------------------------------------------------------------
// Open TRASH
void daisy::openTrash(void)
{
  KRun::runCommand( QString("kfmclient exec trash:/"), i18n("trash"), QString("user-trash"), NULL, NULL );
}



//-----------------------------------------------------------------------------
// Empty TRASH
void daisy::emptyTrash(void)
{
  int oktotrash_tmp = 0;
  QDir trashed_items = QDir( m_trash_dir );
  //trashed_items.setFilter(QDir::NoDotAndDotDot);
  int trashed_count = trashed_items.count()-2;
  
  if (trashed_count > 0)
    oktotrash_tmp = KMessageBox::warningYesNo (  NULL, 
    i18n("Do you really want to empty the trash? All items will be deleted."), 
    QString::null, 
    KGuiItem (i18n("&Empty Trash"),QString("user-trash"), QString::null, QString::null), 
    KGuiItem (i18n("&Cancel"),QString("dialog-cancel"), QString::null, QString::null)
    );
  
  if (oktotrash_tmp == 3)
  {
    // ... Some systems use ktrash4 ...
    QProcess *myProcess = new QProcess(this);
    myProcess->start( QString("ktrash --empty && ktrash4 --empty") );
  }
}





//-----------------------------------------------------------------------------
// Restore TRASH
void daisy::restoreTrash(void)
{
  QDir trashed_items = QDir( m_trash_dir );
  int trashed_count = trashed_items.count()-2;
  
  if (trashed_count > 0)
  {
    QString trashcom_tmp = QString("");
    for (uint i = 0; i < trashed_items.count(); ++i)
    {
      if ( trashed_items[i] != QString(".") && trashed_items[i] != QString("..") )
      {
	// ... Some systems use ktrash4 ...
	trashcom_tmp.clear();trashcom_tmp.append("ktrash --restore trash:/0-");
	trashcom_tmp.append(trashed_items[i]);
	KRun::runCommand( trashcom_tmp, i18n("trash"), QString("user-trash"), NULL, NULL );
	
      }
    }
    emit checkTrash();
  }
}























