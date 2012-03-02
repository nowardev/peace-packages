/*
*   Icon: daisy
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
// Init
void MyIcon::init()
{
  
  setWindowFrameMargins(0,0,0,0);
  setCursor(Qt::PointingHandCursor);
  setAcceptHoverEvents(true);
  setCacheMode( QGraphicsItem::NoCache );
  
}














//-----------------------------------------------------------------------------
// Launch program
void MyIcon::launchProg()
{
  
  KRun::runCommand( command_[0], command_[1], command_[2], NULL, NULL );
  
}




//-----------------------------------------------------------------------------
// Launch ico program
void MyIcon::launchIcoProg()
{
  
  KRun::runCommand( command_ico_[0], command_ico_[1], command_ico_[2], NULL, NULL );
  
}




























