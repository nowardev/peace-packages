/*
*   Media Controller: daisy
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
// Get the player commands
// FIXME
QStringList daisy::getPlayerComs()
{
  QStringList m_player_coms;
  
  if ( m_player == QString("Amarok 1.x") )
  {
    m_player_coms<<
    QString("dcop --no-user-time amarok player playPause")<<
    QString("dcop --no-user-time amarok player stop")<<
    QString("dcop --no-user-time amarok player prev")<<
    QString("dcop --no-user-time amarok player next")<<
    QString("dcop --no-user-time amarok player seekRelative -15")<<
    QString("amarok -m")<<
    QString("dcop --no-user-time amarok player seekRelative 15")<<
    QString("dcop --no-user-time amarok player mute")<<
    QString("dcop --no-user-time amarok player play")<<
    QString("dcop --no-user-time amarok player volumeUp")<<
    QString("dcop --no-user-time amarok player volumeDown");
  }
  
  else if ( m_player == QString("Amarok 2.x") )
  {
    m_player_coms<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Pause")<< 
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Stop")<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Prev")<< 
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Next")<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.SeekRelative -15")<<
    QString("qdbus org.mpris.amarok /amarok/MainWindow org.kde.amarok.MainWindow.showHide")<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.SeekRelative 15")<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Mute")<<
    QString("qdbus org.mpris.amarok /Player org.freedesktop.MediaPlayer.Play")<<
    QString("false")<<
    QString("false");
  }
  
  else if ( m_player == QString("juK") )
  {
    m_player_coms <<
    QString("qdbus org.kde.juk /Player pause")<<
    QString("qdbus org.kde.juk /Player stop")<<
    QString("qdbus org.kde.juk /Player back")<<
    QString("qdbus org.kde.juk /Player forward")<<
    QString("qdbus org.kde.juk /Player seekBack")<<
    QString("qdbus org.kde.juk /juk/MainWindow_1 com.trolltech.Qt.QWidget.show && qdbus org.kde.juk /juk/MainWindow_1 \
    com.trolltech.Qt.QWidget.raise")<<
    QString("qdbus org.kde.juk /Player seekForward")<< 
    QString("qdbus org.kde.juk /Player mute")<<
    QString("qdbus org.kde.juk /Player play")<<
    QString("false")<<
    QString("false");
  }
  
  // FIXME Let me know of a better way to do this...
  else if ( m_player == QString("VLC") )
  {
    m_player_coms <<
    QString("dbus-send --print-reply --session --dest=org.mpris.vlc /Player org.freedesktop.MediaPlayer.Pause")<<
    QString("dbus-send --print-reply --session --dest=org.mpris.vlc /Player org.freedesktop.MediaPlayer.Stop")<<
    QString("dbus-send --print-reply --session --dest=org.mpris.vlc /Player org.freedesktop.MediaPlayer.Prev")<<
    QString("dbus-send --print-reply --session --dest=org.mpris.vlc /Player org.freedesktop.MediaPlayer.Next")<<
    QString("TOTALPOS=`qdbus org.mpris.vlc /Player GetMetadata | grep length`;\
    TOTALPOS=`echo $TOTALPOS | sed 's/[length: ]//g'`;\
    CURRENTPOS=`qdbus org.mpris.vlc /Player PositionGet`;\
    TOTALPOS=`expr $TOTALPOS / 15`;\
    TOSET=`expr $CURRENTPOS - $TOTALPOS`;\
    action=`qdbus org.mpris.vlc /Player PositionSet $TOSET`;")<<
    QString("vlc")<<
    QString("TOTALPOS=`qdbus org.mpris.vlc /Player GetMetadata | grep length`;\
    TOTALPOS=`echo $TOTALPOS | sed 's/[length: ]//g'`;\
    CURRENTPOS=`qdbus org.mpris.vlc /Player PositionGet`;\
    TOTALPOS=`expr $TOTALPOS / 15`;\
    TOSET=`expr $TOTALPOS + $CURRENTPOS`;\
    action=`qdbus org.mpris.vlc /Player PositionSet $TOSET`;")<<
    QString("if [ ! `qdbus org.mpris.vlc /Player VolumeGet` = \"0\" ];then \
    qdbus org.mpris.vlc /Player VolumeSet 0;else qdbus org.mpris.vlc /Player VolumeSet 15;fi")<<
    QString("if [ -z `dbus-send --print-reply --session --dest=org.mpris.vlc /Player \
    org.freedesktop.MediaPlayer.GetStatus | grep \"int32 2\"` ]; then \
    dbus-send --print-reply --session --dest=org.mpris.vlc /Player \
    org.freedesktop.MediaPlayer.Stop && sleep 1 && dbus-send --print-reply --session --dest=org.mpris.vlc /Player \
    org.freedesktop.MediaPlayer.Play; else dbus-send --print-reply --session --dest=org.mpris.vlc /Player \
    org.freedesktop.MediaPlayer.Play; fi")<<
    QString("TOTALVOL=`qdbus org.mpris.vlc /Player VolumeGet`;\
    TOSET=`expr $TOTALVOL + 2`;if [ ! $TOSET = 51 ];then if [ ! $TOSET = 52 ];\
    then action=`qdbus org.mpris.vlc /Player VolumeSet $TOSET`;fi;fi;")<<
    QString("TOTALVOL=`qdbus org.mpris.vlc /Player VolumeGet`;\
    TOSET=`expr $TOTALVOL - 2`;if [ ! $TOSET = -1 ];then if [ ! $TOSET = -2 ];\
    then action=`qdbus org.mpris.vlc /Player VolumeSet $TOSET`;fi;fi;");
  }
  
  else if ( m_player == QString("XMMS") )
  {
    m_player_coms<<
    QString("xmms --pause")<<
    QString("xmms --stop")<<
    QString("xmms --rew")<<
    QString("xmms --fwd")<<
    QString("false")<<
    QString("xmms -m")<<
    QString("false")<<
    QString("mute")<<
    QString("xmms --play")<<
    QString("false")<<
    QString("false");
  }
  
  return m_player_coms;
}














