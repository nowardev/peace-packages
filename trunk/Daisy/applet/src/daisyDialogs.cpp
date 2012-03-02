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
// Show configuration dialog
void daisy::createConfigurationInterface(KConfigDialog *parent)
{
  if (m_dialogLauncher == 0)
  {
    m_dialogLauncher = parent;
    parent->setButtons (KDialog::Ok | KDialog::Cancel);
    
    QWidget *mainConfiguration = new QWidget();
    m_mainConfigurationUi.setupUi(mainConfiguration);
    parent->addPage(mainConfiguration, i18n("Main"), "configure");
    
    QWidget *arrangementConfiguration = new QWidget();
    m_arrangementConfigurationUi.setupUi(arrangementConfiguration);
    parent->addPage(arrangementConfiguration, i18n("Arrangement"), "preferences-desktop-display");
    
    QWidget *hidingConfiguration = new QWidget();
    m_hidingConfigurationUi.setupUi(hidingConfiguration);
    parent->addPage(hidingConfiguration, i18n("Hiding"), "configure-toolbars");
    
    QWidget *advancedConfiguration = new QWidget();
    m_advancedConfigurationUi.setupUi(advancedConfiguration);
    parent->addPage(advancedConfiguration, i18n("Launchers"), "preferences-desktop-icons");
    
    QWidget *appearanceConfiguration = new QWidget();
    m_appearanceConfigurationUi.setupUi(appearanceConfiguration);
    parent->addPage(appearanceConfiguration, i18n("Appearance"), "preferences-desktop-theme");
    
    
    m_arrangementConfigurationUi.slider_icosize->setValue(m_icodimension);
    m_arrangementConfigurationUi.spinBox_icosize->setValue(m_icodimension);
    m_arrangementConfigurationUi.slider_icospacing->setValue( (m_icospacing+0.001)*100.000 );
    
    
    if ( m_position == QString("buttom_center") )
      m_arrangementConfigurationUi.pushButton_buttomCenter->setChecked(true);
    else if ( m_position == QString("buttom_left") )
      m_arrangementConfigurationUi.pushButton_buttomLeft->setChecked(true);
    else if ( m_position == QString("buttom_right") )
      m_arrangementConfigurationUi.pushButton_buttomRight->setChecked(true);
    else if ( m_position == QString("top_center") )
      m_arrangementConfigurationUi.pushButton_topCenter->setChecked(true);
    else if ( m_position == QString("top_left") )
      m_arrangementConfigurationUi.pushButton_topLeft->setChecked(true);
    else if ( m_position == QString("top_right") )
      m_arrangementConfigurationUi.pushButton_topRight->setChecked(true); 
    else if ( m_position == QString("left_center") )
      m_arrangementConfigurationUi.pushButton_leftCenter->setChecked(true);
    else if ( m_position == QString("left_top") )
      m_arrangementConfigurationUi.pushButton_leftTop->setChecked(true);
    else if ( m_position == QString("left_buttom") )
      m_arrangementConfigurationUi.pushButton_leftButtom->setChecked(true); 
    else if ( m_position == QString("right_center") )
      m_arrangementConfigurationUi.pushButton_rightCenter->setChecked(true);
    else if ( m_position == QString("right_top") )
      m_arrangementConfigurationUi.pushButton_rightTop->setChecked(true);
    else if ( m_position == QString("right_buttom") )
      m_arrangementConfigurationUi.pushButton_rightButtom->setChecked(true);
    m_arrangementConfigurationUi.checkBox_floating->setChecked(m_floating);
    
    
    m_appearanceConfigurationUi.slider_Opacity->setValue(m_backopacity*100.00);
    m_appearanceConfigurationUi.checkBoxIcoMirror->setChecked(m_showmirror);
    
    m_appearanceConfigurationUi.checkBoxIcoEffects->setChecked(m_draw_icoback);
    m_appearanceConfigurationUi.comboBoxIcoEffects->setEnabled(m_draw_icoback);
    
    m_appearanceConfigurationUi.checkBoxClickEffects->setChecked(m_click_effects);
    m_appearanceConfigurationUi.comboBoxClickEffects->setEnabled(m_click_effects);
    
    m_appearanceConfigurationUi.checkBoxTips->setChecked(m_showtooltips);
    m_appearanceConfigurationUi.checkBoxTips_launchers->setChecked(m_showtooltips_l);
    m_appearanceConfigurationUi.comboBoxTips_launchers->setEnabled(m_showtooltips_l);
    
    m_appearanceConfigurationUi.checkBoxTips_inactive_launchers->setChecked(m_showtooltips_i);
    m_appearanceConfigurationUi.checkBoxTips_inactive_launchers->setEnabled(m_showtooltips_l);
    
    insertFx();
    
    m_mainConfigurationUi.checkBox_drop->setChecked(m_accept_drops);
    
    
    
    
    if ( m_type != QString("media_controller") )
    {
      if ( m_type == QString("circular_dock") )
      {
	m_advancedConfigurationUi.kintspinbox_launchers->setEnabled(false);
	m_advancedConfigurationUi.checkBox_rep->setEnabled(false);
	m_mainConfigurationUi.comboBox_role->setCurrentIndex(0);
	m_arrangementConfigurationUi.slider_icosize->setEnabled(false);
	m_arrangementConfigurationUi.spinBox_icosize->setEnabled(false);
	m_arrangementConfigurationUi.slider_icospacing->setEnabled(false);
	m_arrangementConfigurationUi.groupBox_pos->setEnabled(false);
	m_arrangementConfigurationUi.checkBox_floating->setEnabled(false);
      }
      else if ( m_type == QString("standard_dock") )
      {
	insertBacks();
	m_mainConfigurationUi.comboBox_role->setCurrentIndex(2);
	m_arrangementConfigurationUi.slider_icosize->setEnabled(true);
	m_arrangementConfigurationUi.spinBox_icosize->setEnabled(true);
	m_arrangementConfigurationUi.slider_icospacing->setEnabled(true);
	if (m_floating)m_arrangementConfigurationUi.groupBox_pos->setEnabled(false);
      }
      m_mainConfigurationUi.comboBox_player->setEnabled(false);
      m_mainConfigurationUi.label_media->setEnabled(false);
    }
    else
    {
      m_advancedConfigurationUi.kintspinbox_launchers->setEnabled(false);
      m_advancedConfigurationUi.checkBox_rep->setEnabled(false);
      m_mainConfigurationUi.comboBox_role->setCurrentIndex(1);
      m_appearanceConfigurationUi.checkBox_indicons->setEnabled(false);
      m_arrangementConfigurationUi.slider_icosize->setEnabled(false);
      m_arrangementConfigurationUi.spinBox_icosize->setEnabled(false);
      m_arrangementConfigurationUi.slider_icospacing->setEnabled(false);
      m_arrangementConfigurationUi.groupBox_pos->setEnabled(false);
      m_arrangementConfigurationUi.checkBox_floating->setEnabled(false);
    }
    
    if (m_reservespace)
    {
      m_hidingConfigurationUi.button_allwaysShow->setChecked(true);
      m_hidingConfigurationUi.spinBox_secHide->setEnabled(false);
      m_hidingConfigurationUi.label_secHide->setEnabled(false);
      m_hidingConfigurationUi.button_showOnDesk->setEnabled(false);
    }
    
    else
    {
      if (m_autohide)
	m_hidingConfigurationUi.button_autoHide->setChecked(true);
      else
      {
	m_hidingConfigurationUi.button_allowCover->setChecked(true);
	m_hidingConfigurationUi.spinBox_secHide->setEnabled(false);
	m_hidingConfigurationUi.label_secHide->setEnabled(false);
	m_hidingConfigurationUi.button_showOnDesk->setEnabled(false);
      }
    }
    m_hidingConfigurationUi.spinBox_secHide->setValue(m_hidingdelay/1000);
    m_hidingConfigurationUi.button_showOnDesk->setChecked(m_showondesk);
    
    
    
    if ( m_player == QString("Amarok 1.x") )m_mainConfigurationUi.comboBox_player->setCurrentIndex(0);
    else if ( m_player == QString("Amarok 2.x") )m_mainConfigurationUi.comboBox_player->setCurrentIndex(1);
    else if ( m_player == QString("juK") )m_mainConfigurationUi.comboBox_player->setCurrentIndex(2);
    else if ( m_player == QString("VLC") )m_mainConfigurationUi.comboBox_player->setCurrentIndex(3);
    else if ( m_player == QString("XMMS") )m_mainConfigurationUi.comboBox_player->setCurrentIndex(4);
    m_appearanceConfigurationUi.checkBox_indicons->setChecked(m_showindicons);
    
    
    m_advancedConfigurationUi.kintspinbox_launchers->setValue(m_total_launchers);
    m_advancedConfigurationUi.checkBox_rep->setChecked(!m_showtaskoflauncher);
    m_advancedConfigurationUi.slider_drawerSize->setValue( m_drawersize );
    m_advancedConfigurationUi.slider_drawerRotation->setValue( m_drawerrotation*10.00 );
    m_advancedConfigurationUi.checkBoxCloseTasks->setChecked(m_showclosetask);
    
    if (m_middleClickAction == QString("shade") )
    {m_advancedConfigurationUi.comboBox_middleClick->setCurrentIndex(0);}
    else if (m_middleClickAction == QString("run") )
    {m_advancedConfigurationUi.comboBox_middleClick->setCurrentIndex(1);}
    
    
    insertPlugs();
    
    
    
    
    
    connect(parent, SIGNAL(okClicked ()), this, SLOT (configAccepted ()));
    connect(parent, SIGNAL(cancelClicked ()), this, SLOT (configRejected ()));
    connect(parent, SIGNAL(destroyed()), this, SLOT (configRejected ()));
    connect(m_mainConfigurationUi.comboBox_role, SIGNAL(currentIndexChanged ( int )), this, SLOT ( toggleMediaCombo() ) );
    
    
    connect (m_hidingConfigurationUi.button_allwaysShow, SIGNAL (clicked ()), this, SLOT (toggleHide()));
    connect (m_hidingConfigurationUi.button_autoHide, SIGNAL (clicked ()), this, SLOT (toggleHide()));
    connect (m_hidingConfigurationUi.button_allowCover, SIGNAL (clicked ()), this, SLOT (toggleHide()));
    
    
    connect(m_appearanceConfigurationUi.slider_Opacity, SIGNAL(valueChanged ( int )), this, SLOT ( opacityValueChange( int ) ) );
    connect(m_appearanceConfigurationUi.comboBoxBackground, SIGNAL(currentIndexChanged ( int )), this, SLOT ( backgroundChanged( int ) ) );
    connect(m_appearanceConfigurationUi.checkBoxIcoEffects, SIGNAL(clicked ()), this, SLOT ( toggleEffectsCombo() ) );
    connect(m_appearanceConfigurationUi.checkBoxClickEffects, SIGNAL(clicked ()), this, SLOT ( toggleEffectsCombo() ) );
    connect(m_appearanceConfigurationUi.checkBoxTips_launchers, SIGNAL(clicked ()), this, SLOT ( toggleEffectsCombo() ) );
    
    
    connect(m_arrangementConfigurationUi.slider_icosize, SIGNAL(valueChanged ( int )), this, SLOT ( szValueChange() ) );
    connect(m_arrangementConfigurationUi.spinBox_icosize, SIGNAL(valueChanged ( int )), this, SLOT ( spinBoxSize_Clicked(int) ) );
    connect(m_arrangementConfigurationUi.slider_icospacing, SIGNAL(valueChanged ( int )), this, SLOT ( szValueChange() ) );
    
    
    connect (m_arrangementConfigurationUi.pushButton_buttomCenter, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_buttomLeft, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_buttomRight, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    
    connect (m_arrangementConfigurationUi.pushButton_topCenter, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_topLeft, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_topRight, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    
    connect (m_arrangementConfigurationUi.pushButton_leftCenter, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_leftTop, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_leftButtom, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    
    connect (m_arrangementConfigurationUi.pushButton_rightCenter, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_rightTop, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    connect (m_arrangementConfigurationUi.pushButton_rightButtom, SIGNAL (clicked ()), this, SLOT (posButton_Clicked ()));
    
    connect (m_arrangementConfigurationUi.checkBox_floating, SIGNAL (clicked ()), this, SLOT (floating_Clicked ()));
    
    connect(m_advancedConfigurationUi.slider_drawerSize, SIGNAL(valueChanged ( int )), this, SLOT ( drawerSizeChange( int ) ) );
    connect(m_advancedConfigurationUi.slider_drawerRotation, SIGNAL(valueChanged ( int )), this, SLOT ( drawerRotationChange( int ) ) );
    
    
    
    
    parent->adjustSize();
    //parent->show();
    
  }
}






//-----------------------------------------------------------------------------
// Insert plugins
void daisy::insertPlugs()
{
  QListWidget *avail_list = m_advancedConfigurationUi.kactionselector_plugs->availableListWidget();
  QListWidget *select_list = m_advancedConfigurationUi.kactionselector_plugs->selectedListWidget();
  avail_list->clear();select_list->clear();
  
  
  QListWidgetItem *m_list_trash = new QListWidgetItem(KIcon("user-trash"), i18n("Trash"), NULL);
  QListWidgetItem *m_list_tasks = new QListWidgetItem(KIcon("application-x-plasma"), i18n("Task manager"), NULL);
//   QListWidgetItem *m_list_spacer = new QListWidgetItem(i18n("--- separator ---"), NULL);
  
  
  if (m_show_trash)select_list->addItem( m_list_trash );
  else avail_list->addItem( m_list_trash );
  
  if (m_taskpreviews) select_list->addItem( m_list_tasks );
  else avail_list->addItem( m_list_tasks );
  
  
  
  
  
}






//-----------------------------------------------------------------------------
// Insert backgrounds
void daisy::insertBacks()
{
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("default") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("translucent") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("opaque") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("alternative") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("mach") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("mach-2") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("shiny-black") );
  m_appearanceConfigurationUi.comboBoxBackground->addItem( i18n("vidro") );
  
  
  if ( m_theme_t == QString("translucent") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(1);
  else if ( m_theme_t == QString("opaque") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(2);
  else if ( m_theme_t == QString("alternative") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(3);
  
  else if ( m_theme_t == QString("mach") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(4);
  else if ( m_theme_t == QString("mach-2") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(5);
  else if ( m_theme_t == QString("shiny-black") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(6);
  else if ( m_theme_t == QString("vidro") ) m_appearanceConfigurationUi.comboBoxBackground->setCurrentIndex(7);
  
}



//-----------------------------------------------------------------------------
// Insert FX
void daisy::insertFx()
{
  
  m_appearanceConfigurationUi.comboBoxIcoEffects->addItem( i18n("default") );
  m_appearanceConfigurationUi.comboBoxIcoEffects->addItem( i18n("simple") );
  m_appearanceConfigurationUi.comboBoxIcoEffects->addItem( i18n("fruity") );
  m_appearanceConfigurationUi.comboBoxIcoEffects->addItem( i18n("framed") );
  
  m_appearanceConfigurationUi.comboBoxClickEffects->addItem( i18n("default") );
  //m_appearanceConfigurationUi.comboBoxClickEffects->addItem( i18n("fade") );
  
  m_appearanceConfigurationUi.comboBoxTips_launchers->addItem( i18n("Application icon") );
  m_appearanceConfigurationUi.comboBoxTips_launchers->addItem( i18n("Text only") );
  m_appearanceConfigurationUi.comboBoxTips_launchers->addItem( i18n("Window thumbnail") );
  
  
  if (m_zoomtype == QString("default")) m_appearanceConfigurationUi.comboBoxIcoEffects->setCurrentIndex(0);
  else if (m_zoomtype == QString("simple")) m_appearanceConfigurationUi.comboBoxIcoEffects->setCurrentIndex(1);
  else if (m_zoomtype == QString("fruity")) m_appearanceConfigurationUi.comboBoxIcoEffects->setCurrentIndex(2);
  else if (m_zoomtype == QString("framed")) m_appearanceConfigurationUi.comboBoxIcoEffects->setCurrentIndex(3);
  
  if (m_click_effect_type == QString("default")) m_appearanceConfigurationUi.comboBoxClickEffects->setCurrentIndex(0);
  else if (m_click_effect_type == QString("fade")) m_appearanceConfigurationUi.comboBoxClickEffects->setCurrentIndex(1);
  
  if (m_tiptype == QString("icon")) m_appearanceConfigurationUi.comboBoxTips_launchers->setCurrentIndex(0);
  else if (m_tiptype == QString("text")) m_appearanceConfigurationUi.comboBoxTips_launchers->setCurrentIndex(1);
  else if (m_tiptype == QString("thumbnail")) m_appearanceConfigurationUi.comboBoxTips_launchers->setCurrentIndex(2);
  

}







//-----------------------------------------------------------------------------
// Accept configuration
void daisy::configAccepted()
{
  
  bool m_show_trash_tmp = m_show_trash;
  bool m_taskpreviews_tmp = m_taskpreviews;
  bool m_draw_icoback_tmp = m_draw_icoback;
  bool m_showtooltips_tmp = m_showtooltips;
  bool m_showtooltips_l_tmp = m_showtooltips_l;
  bool m_showtooltips_i_tmp = m_showtooltips_i;
  bool m_reservespace_tmp = m_reservespace;
  bool m_showclosetask_tmp = m_showclosetask;
  int m_total_launchers_tmp = m_total_launchers;
  QString m_type_tmp = m_type;QString m_player_tmp = m_player;QString m_theme_t_tmp=m_theme_t;QString m_zoomtype_tmp=m_zoomtype;QString m_tiptype_tmp = m_tiptype;
  int m_box_index;
  
  
  // Draw icons background
  m_draw_icoback = m_appearanceConfigurationUi.checkBoxIcoEffects->isChecked();
  // Show tooltips
  m_showtooltips = m_appearanceConfigurationUi.checkBoxTips->isChecked();
  m_showtooltips_l = m_appearanceConfigurationUi.checkBoxTips_launchers->isChecked();
  m_showtooltips_i = m_appearanceConfigurationUi.checkBoxTips_inactive_launchers->isChecked();
  // Theme
  m_box_index = m_appearanceConfigurationUi.comboBoxBackground->currentIndex();
  if ( m_type == QString("standard_dock") )
  {
    if (m_box_index == 0)m_theme_t = QString("default");
    else if (m_box_index == 1)m_theme_t = QString("translucent");
    else if (m_box_index == 2)m_theme_t = QString("opaque");
    else if (m_box_index == 3)m_theme_t = QString("alternative");
    else if (m_box_index == 4)m_theme_t = QString("mach");
    else if (m_box_index == 5)m_theme_t = QString("mach-2");
    else if (m_box_index == 6)m_theme_t = QString("shiny-black");
    else if (m_box_index == 7)m_theme_t = QString("vidro");
  }
  // Role
  m_box_index = m_mainConfigurationUi.comboBox_role->currentIndex();
  if (m_box_index == 0)m_type = QString("circular_dock");
  else if (m_box_index == 1)m_type = QString("media_controller");
  else if (m_box_index == 2)m_type = QString("standard_dock");
  // Player
  m_box_index = m_mainConfigurationUi.comboBox_player->currentIndex();
  if (m_box_index == 0) m_player = QString("Amarok 1.x");
  else if (m_box_index == 1) m_player = QString("Amarok 2.x");
  else if (m_box_index == 2) m_player = QString("juK");
  else if (m_box_index == 3) m_player = QString("VLC");
  else if (m_box_index == 4) m_player = QString("XMMS");
  // Mouse over effects
  m_box_index = m_appearanceConfigurationUi.comboBoxIcoEffects->currentIndex();
  if (m_box_index == 0) m_zoomtype = QString("default");
  else if (m_box_index == 1) m_zoomtype = QString("simple");
  else if (m_box_index == 2) m_zoomtype = QString("fruity");
  else if (m_box_index == 3) m_zoomtype = QString("framed");
  
  m_box_index = m_appearanceConfigurationUi.comboBoxClickEffects->currentIndex();
  if (m_box_index == 0) m_click_effect_type = QString("default");
  else if (m_box_index == 1) m_click_effect_type = QString("fade");
  
  m_box_index = m_appearanceConfigurationUi.comboBoxTips_launchers->currentIndex();
  if (m_box_index == 0) m_tiptype = QString("icon");
  else if (m_box_index == 1) m_tiptype = QString("text");
  else if (m_box_index == 2) m_tiptype = QString("thumbnail");
  
  
  m_showindicons = m_appearanceConfigurationUi.checkBox_indicons->isChecked();
  m_showmirror = m_appearanceConfigurationUi.checkBoxIcoMirror->isChecked();
  m_reservespace = m_hidingConfigurationUi.button_allwaysShow->isChecked();
  m_autohide = m_hidingConfigurationUi.button_autoHide->isChecked();
  m_hidingdelay = m_hidingConfigurationUi.spinBox_secHide->value()*1000;
  m_showondesk = m_hidingConfigurationUi.button_showOnDesk->isChecked();
  m_accept_drops = m_mainConfigurationUi.checkBox_drop->isChecked();
  m_showclosetask =  m_advancedConfigurationUi.checkBoxCloseTasks->isChecked();
  
  
  m_click_effects = m_appearanceConfigurationUi.checkBoxClickEffects->isChecked();
  
  
  
  
  m_total_launchers = m_advancedConfigurationUi.kintspinbox_launchers->value();
  m_showtaskoflauncher = !m_advancedConfigurationUi.checkBox_rep->isChecked();
  m_drawersize = m_advancedConfigurationUi.slider_drawerSize->value();
  m_drawerrotation = m_advancedConfigurationUi.slider_drawerRotation->value()/10.00;
  
  
  QListWidget *avail_list = m_advancedConfigurationUi.kactionselector_plugs->availableListWidget();
  QListWidget *select_list = m_advancedConfigurationUi.kactionselector_plugs->selectedListWidget();
  
  m_box_index = m_advancedConfigurationUi.comboBox_middleClick->currentIndex();
  if (m_box_index == 0) m_middleClickAction = QString("shade");
  else if (m_box_index == 1) m_middleClickAction = QString("run");
  
  
  
  
  for (int i = 0; i < avail_list->count(); ++i)
  {
    
   if ( avail_list->item(i)->text() == i18n("Trash") )
     m_show_trash = false;
   
   else if ( avail_list->item(i)->text() == i18n("Task manager") )
     m_taskpreviews = false;
   
  }
  
  
  
  for (int i = 0; i < select_list->count(); ++i)
  {
    
   if ( select_list->item(i)->text() == i18n("Trash") )
     m_show_trash = true;
   
   else if ( select_list->item(i)->text() == i18n("Task manager") )
     m_taskpreviews = true;
   
  }
  
  
  
  if (m_show_trash_tmp != m_show_trash)
  {
    m_show_trash = !m_show_trash;
    emit toggTrash();
    kDebug() << m_total_launchers;
    if (m_total_launchers == 0)
    {
      m_total_launchers ++;
      refurbishLaunchers();
      resizeRepos( true );
    }
  }
  
  
  
  
  
  
  KConfigGroup cg = config();
  cg.writeEntry("theme", m_theme);
  cg.writeEntry("theme_t", m_theme_t);
  cg.writeEntry("type", m_type);
  cg.writeEntry("player", m_player);
  cg.writeEntry("draw_icoback", m_draw_icoback);
  cg.writeEntry("showtooltips", m_showtooltips);
  cg.writeEntry("showtooltips_launchers", m_showtooltips_l);
  cg.writeEntry("showtooltips_inactive", m_showtooltips_i);
  cg.writeEntry("showindicons", m_showindicons);
  cg.writeEntry("total_launchers", m_total_launchers);
  cg.writeEntry("position", m_position);
  cg.writeEntry("background_opacity", m_backopacity);
  cg.writeEntry("floating", m_floating);
  cg.writeEntry("reservespace", m_reservespace);
  cg.writeEntry("autohide", m_autohide);
  cg.writeEntry("hidingdelay", m_hidingdelay);
  cg.writeEntry("showmirror", m_showmirror);
  cg.writeEntry("icospacing", m_icospacing);
  cg.writeEntry("icodimension", m_icodimension);
  cg.writeEntry("showondesk", m_showondesk);
  cg.writeEntry("acceptdrops", m_accept_drops);
  cg.writeEntry("showtaskoflauncher", m_showtaskoflauncher);
  cg.writeEntry("zoomtype", m_zoomtype);
  cg.writeEntry("click_effects", m_click_effects);
  cg.writeEntry("click_effect_type", m_click_effect_type);
  cg.writeEntry("tip_type", m_tiptype);
  cg.writeEntry("drawersize", m_drawersize);
  cg.writeEntry("drawerrotation", m_drawerrotation);
  cg.writeEntry("taskpreviews", m_taskpreviews);
  cg.writeEntry("showclosetask", m_showclosetask);
  cg.writeEntry("middleclickaction", m_middleClickAction);
  
  
  
  setAcceptDrops(m_accept_drops);
  
  
  
  if (m_draw_icoback_tmp != m_draw_icoback || m_zoomtype_tmp != m_zoomtype) polishLaunchers();
  if (m_showtooltips_tmp != m_showtooltips){m_trashfull = false;m_watch_trash->setDirty( m_trash_dir );}
  if (m_showtooltips_l_tmp != m_showtooltips_l || m_tiptype_tmp != m_tiptype || m_showtooltips_i_tmp != m_showtooltips_i)
  {m_trashfull = false;m_watch_trash->setDirty( m_trash_dir );updateToolTipContent();}
  
  
  if ( m_taskpreviews_tmp != m_taskpreviews || m_showclosetask != m_showclosetask_tmp )
  {
    total_taskpreviews = 0;
    refurbishLaunchers();
    resizeRepos( true );
    getAllTasks();
  }
  
  
  
  if ( m_type_tmp != m_type || (m_player_tmp != m_player && m_type == QString("media_controller")) || m_total_launchers != m_total_launchers_tmp )
  {
    refurbishLaunchers();
    if ( (m_type_tmp != m_type && ( m_type_tmp == QString("standard_dock") || m_type == QString("standard_dock") ))  )
    {
      if ( m_type_tmp != QString("standard_dock") )m_circpos = scenePos();
      resizeRepos( true );
      m_up_tmr->stop();m_rz_tmr->stop();m_rz_tmr->setInterval(550);m_rz_tmr->start();
    }
    else if ( m_type == QString("standard_dock") &&  (m_total_launchers != m_total_launchers_tmp ) )
    {resizeRepos( true );}
  }
  
  
  
  m_dialogLauncher = 0;
  if (m_reservespace != m_reservespace_tmp && m_type == QString("standard_dock") )
  {
    emit spaceReserver(false);
    m_up_tmr->stop();m_rz_tmr->stop();m_rz_tmr->setInterval(550);m_rz_tmr->start();
  }
  if ( m_autohide )m_tracker_tmr->setInterval(m_hidingdelay);m_tracker_tmr->start();
  if ( !isVisible() ){setVisible(true);}
  emit configNeedsSaving();
  emit update();
}








//-----------------------------------------------------------------------------
// Toggle hide
void daisy::toggleHide(void)
{
  m_hidingConfigurationUi.spinBox_secHide->setEnabled(m_hidingConfigurationUi.button_autoHide->isChecked());
  m_hidingConfigurationUi.label_secHide->setEnabled(m_hidingConfigurationUi.button_autoHide->isChecked());
  m_hidingConfigurationUi.button_showOnDesk->setEnabled(m_hidingConfigurationUi.button_autoHide->isChecked());
}







//-----------------------------------------------------------------------------
// Toggle effects combo
void daisy::toggleEffectsCombo(void)
{
  m_appearanceConfigurationUi.comboBoxIcoEffects->setEnabled(m_appearanceConfigurationUi.checkBoxIcoEffects->isChecked());
  m_appearanceConfigurationUi.comboBoxClickEffects->setEnabled(m_appearanceConfigurationUi.checkBoxClickEffects->isChecked());
  m_appearanceConfigurationUi.comboBoxTips_launchers->setEnabled(m_appearanceConfigurationUi.checkBoxTips_launchers->isChecked());
  m_appearanceConfigurationUi.checkBoxTips_inactive_launchers->setEnabled(m_appearanceConfigurationUi.checkBoxTips_launchers->isChecked());
}





//-----------------------------------------------------------------------------
// Toggle media combo
void daisy::toggleMediaCombo(void)
{
  int m_type_index;
  m_type_index = m_mainConfigurationUi.comboBox_role->currentIndex();
  if (m_type_index == 1)
  {
    m_mainConfigurationUi.label_media->setEnabled(true);
    m_mainConfigurationUi.comboBox_player->setEnabled(true);
    m_appearanceConfigurationUi.checkBox_indicons->setEnabled(false);
    m_advancedConfigurationUi.kintspinbox_launchers->setEnabled(false);
    m_advancedConfigurationUi.checkBox_rep->setEnabled(false);
    m_arrangementConfigurationUi.slider_icosize->setEnabled(false);
    m_arrangementConfigurationUi.spinBox_icosize->setEnabled(false);
    m_arrangementConfigurationUi.slider_icospacing->setEnabled(false);
    m_arrangementConfigurationUi.groupBox_pos->setEnabled(false);
    m_arrangementConfigurationUi.checkBox_floating->setEnabled(false);
  }
  
  else
  {
    m_mainConfigurationUi.label_media->setEnabled(false);
    m_mainConfigurationUi.comboBox_player->setEnabled(false);
    m_appearanceConfigurationUi.checkBox_indicons->setEnabled(true);
    if (m_type_index == 0)
    {
      m_advancedConfigurationUi.kintspinbox_launchers->setEnabled(false);
      m_advancedConfigurationUi.checkBox_rep->setEnabled(false);
      m_advancedConfigurationUi.label_launchers->setEnabled(false);
      m_arrangementConfigurationUi.slider_icosize->setEnabled(false);
      m_arrangementConfigurationUi.spinBox_icosize->setEnabled(false);
      m_arrangementConfigurationUi.slider_icospacing->setEnabled(false);
      m_arrangementConfigurationUi.groupBox_pos->setEnabled(false);
      m_arrangementConfigurationUi.checkBox_floating->setEnabled(false);
    }
    else if (m_type_index == 2)
    {
      m_advancedConfigurationUi.kintspinbox_launchers->setEnabled(true);
      m_advancedConfigurationUi.checkBox_rep->setEnabled(true);
      m_advancedConfigurationUi.label_launchers->setEnabled(true);
      m_arrangementConfigurationUi.slider_icosize->setEnabled(true);
      m_arrangementConfigurationUi.spinBox_icosize->setEnabled(true);
      m_arrangementConfigurationUi.slider_icospacing->setEnabled(true);
      m_arrangementConfigurationUi.groupBox_pos->setEnabled(true);
      m_arrangementConfigurationUi.checkBox_floating->setEnabled(true);
    }
  }
  
}






//-----------------------------------------------------------------------------
// Spinbox size clicked
void daisy::spinBoxSize_Clicked(int value)
{
  m_arrangementConfigurationUi.slider_icosize->setValue(value);
  emit szValueChange();
}




//-----------------------------------------------------------------------------
// Size value change
void daisy::szValueChange()
{
  if ( m_type == QString("standard_dock") )
  {
    m_arrangementConfigurationUi.spinBox_icosize->setValue( m_arrangementConfigurationUi.slider_icosize->value() );
    m_icodimension = m_arrangementConfigurationUi.slider_icosize->value();
    m_icospacing = (m_arrangementConfigurationUi.slider_icospacing->value())/100.000;
    
    m_up_tmr->stop();m_rz_tmr->stop();m_rz_tmr->setInterval(750);m_rz_tmr->start();
    
  }
}



//-----------------------------------------------------------------------------
// Opacity change
void daisy::opacityValueChange( int value )
{
  
  m_up_tmr->stop();
  m_backopacity = value/100.0;
  m_up_tmr->setInterval(700);m_up_tmr->start();
  
}


//-----------------------------------------------------------------------------
// Drawer size change
void daisy::drawerSizeChange( int value )
{
  
  m_drawersize = value;
  
}


//-----------------------------------------------------------------------------
// Drawer rotation change
void daisy::drawerRotationChange( int value )
{
  
  m_drawerrotation = value/10.00;
  
}





//-----------------------------------------------------------------------------
// Background change
void daisy::backgroundChanged( int value )
{
  
  if ( m_type == QString("standard_dock") )
  {
    if (value == 0)m_theme_t = QString("default");
    else if (value == 1)m_theme_t = QString("translucent");
    else if (value == 2)m_theme_t = QString("opaque");
    else if (value == 3)m_theme_t = QString("alternative");
    
    else if (value == 4)m_theme_t = QString("mach");
    else if (value == 5)m_theme_t = QString("mach-2");
    else if (value == 6)m_theme_t = QString("shiny-black");
    else if (value == 7)m_theme_t = QString("vidro");
    
    setTheme();
    emit update();
  }
  
}




//-----------------------------------------------------------------------------
// Buttom Pos clicked
void daisy::posButton_Clicked()
{
  
  uncheckPosButtons();
  qobject_cast<QPushButton*>( sender() )->setChecked(true);
  
  if ( sender() == m_arrangementConfigurationUi.pushButton_buttomCenter)
    m_position = QString("buttom_center");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_buttomLeft)
    m_position = QString("buttom_left");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_buttomRight)
    m_position = QString("buttom_right");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_topCenter)
    m_position = QString("top_center");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_topLeft)
    m_position = QString("top_left");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_topRight)
    m_position = QString("top_right");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_leftCenter)
    m_position = QString("left_center");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_leftTop)
    m_position = QString("left_top");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_leftButtom)
    m_position = QString("left_buttom");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_rightCenter)
    m_position = QString("right_center");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_rightTop)
    m_position = QString("right_top");
  else if ( sender() == m_arrangementConfigurationUi.pushButton_rightButtom)
    m_position = QString("right_buttom");
  
  if ( m_type == QString("standard_dock") && !checkLock() )
  {resizeRepos( true );m_up_tmr->stop();m_up_tmr->setInterval(100);m_up_tmr->start();}
  QTimer::singleShot(300, this, SLOT(delayResize()));
  
}



//-----------------------------------------------------------------------------
// Uncheck buttons
void daisy::uncheckPosButtons()
{
  m_arrangementConfigurationUi.pushButton_buttomCenter->setChecked(false);
  m_arrangementConfigurationUi.pushButton_buttomLeft->setChecked(false);
  m_arrangementConfigurationUi.pushButton_buttomRight->setChecked(false);
  
  m_arrangementConfigurationUi.pushButton_topCenter->setChecked(false);
  m_arrangementConfigurationUi.pushButton_topLeft->setChecked(false);
  m_arrangementConfigurationUi.pushButton_topRight->setChecked(false);
  
  m_arrangementConfigurationUi.pushButton_leftCenter->setChecked(false);
  m_arrangementConfigurationUi.pushButton_leftTop->setChecked(false);
  m_arrangementConfigurationUi.pushButton_leftButtom->setChecked(false);
  
  m_arrangementConfigurationUi.pushButton_rightCenter->setChecked(false);
  m_arrangementConfigurationUi.pushButton_rightTop->setChecked(false);
  m_arrangementConfigurationUi.pushButton_rightButtom->setChecked(false);
  
}



//-----------------------------------------------------------------------------
// Floating clicked
void daisy::floating_Clicked()
{
  m_floating = m_arrangementConfigurationUi.checkBox_floating->isChecked();
  m_arrangementConfigurationUi.groupBox_pos->setEnabled(!m_floating);
  if ( m_type == QString("standard_dock") )
  {
    m_tracker_tmr->stop();
    if ( !isVisible() ){setVisible(true);}
    
    if ( m_floating )
    {
      setImmutability(Plasma::Mutable);
      if (m_reservespace) resizeRepos( true );
    }
    else
    {
      if ( !checkLock() )
	resizeRepos( true );
    }
    
  }
}







//-----------------------------------------------------------------------------
// Reject configuration
void daisy::configRejected()
{
  
  m_dialogLauncher = 0;
  
}





/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////




//-----------------------------------------------------------------------------
// Edit launcher
void daisy::configLauncher(void)
{
  m_launtoedit = m_dexval;
  if (m_dialogLauncher == 0)
  {
    
    m_dialogLauncher = new KDialog;
    m_dialogLauncher->setCaption (i18n ("Edit launcher"));
    
    
    QWidget *widget = new QWidget;
    m_launcherConfiguration.setupUi(widget);
    
    m_launcherConfiguration.lineEdit_command->setText( m_values[m_launtoedit][0] );
    m_launcherConfiguration.lineEdit_name->setText( m_values[m_launtoedit][1] );
    m_launcherConfiguration.lineEdit_alias->setText( m_alias[m_launtoedit] );
    m_launcherConfiguration.pushButton_ico->setIcon(KIcon( m_values[m_launtoedit][2] ));
    
    m_launcherConfiguration.lineEdit_action_command->setText( m_avalues[m_launtoedit][0] );
    m_launcherConfiguration.lineEdit_action_name->setText(m_avalues[m_launtoedit][1]);
    m_launcherConfiguration.pushButton_action_ico->setIcon(KIcon(m_avalues[m_launtoedit][2]));
    m_launcherConfiguration.checkBox_action_launcher->setChecked(true);
    
    if (m_avalues[m_launtoedit][3] == QString("0"))
    {
      m_launcherConfiguration.lineEdit_action_command->setEnabled(false);
      m_launcherConfiguration.lineEdit_action_name->setEnabled(false);
      m_launcherConfiguration.pushButton_action_ico->setEnabled(false);
      m_launcherConfiguration.checkBox_action_launcher->setChecked(false);
    }
    
    m_dialogLauncher->setMainWidget(widget);
    m_dialogLauncher->setButtons (KDialog::Ok | KDialog::Cancel);
    m_dialogLauncher->resize(QSize(400, 300));
    
    connect (m_dialogLauncher, SIGNAL (okClicked ()), this, SLOT (configLauncherAccepted ()));
    connect (m_dialogLauncher, SIGNAL (cancelClicked ()), this, SLOT (configLauncherRejected ()));
    connect (m_launcherConfiguration.checkBox_action_launcher, SIGNAL (clicked ()), this, SLOT (toggleActionLauncher ()));
    
    m_dialogLauncher->show();
  }
  
}








//-----------------------------------------------------------------------------
// Accept configuration launcher
void daisy::configLauncherAccepted(void)
{
  
  QString show_launcher_tmp = QString("0");
  if (m_launcherConfiguration.checkBox_action_launcher->isChecked())
  {show_launcher_tmp = QString("1");}
  
  QString icoret_tmp = QString( m_launcherConfiguration.pushButton_ico->icon() );
  if ( icoret_tmp == QString("") )icoret_tmp = m_values[m_launtoedit][2];
  
  QString icoret_tmpa = QString( m_launcherConfiguration.pushButton_action_ico->icon() );
  if ( icoret_tmpa == QString("") )icoret_tmpa = m_avalues[m_launtoedit][2];
  
  m_values[m_launtoedit] = QStringList( QStringList() << QString(m_launcherConfiguration.lineEdit_command->text()) << QString(m_launcherConfiguration.lineEdit_name->text()) << QString(icoret_tmp) );
  m_avalues[m_launtoedit] = QStringList( QStringList() << QString(m_launcherConfiguration.lineEdit_action_command->text()) << QString(m_launcherConfiguration.lineEdit_action_name->text()) << QString(icoret_tmpa) << QString(show_launcher_tmp) );
  m_acta[m_launtoedit] = new QAction(KIcon(m_avalues[m_launtoedit][2]), "", this);
  m_alias[m_launtoedit] = QString( m_launcherConfiguration.lineEdit_alias->text() );
  
  delete m_widgets[m_launtoedit];
  m_widgets[m_launtoedit] = new MyIcon( m_values[m_launtoedit], m_avalues[m_launtoedit], m_acta[m_launtoedit], this );
  m_act_1 = new QAction(KIcon(icoret_tmp), "", this);
  m_widgets[m_launtoedit]->setAction(m_act_1);
  connect(m_widgets[m_launtoedit], SIGNAL(pressed(bool)), this, SLOT(launClick()));
  polishLaunchers();
  m_widgets[m_launtoedit]->installEventFilter(this);
  
  
  writeConfiguration();
  m_dialogLauncher = 0;
  emit update();
  m_up_tmr->setInterval(500);m_up_tmr->start();
  
}





//-----------------------------------------------------------------------------
// Reject configuration launcher
void daisy::configLauncherRejected(void)
{
  
  m_dialogLauncher = 0;
  
}



//-----------------------------------------------------------------------------
// Toggle action launcher
void daisy::toggleActionLauncher(void)
{
  
  m_launcherConfiguration.lineEdit_action_command->setEnabled(m_launcherConfiguration.checkBox_action_launcher->isChecked());
  m_launcherConfiguration.lineEdit_action_name->setEnabled(m_launcherConfiguration.checkBox_action_launcher->isChecked());
  m_launcherConfiguration.pushButton_action_ico->setEnabled(m_launcherConfiguration.checkBox_action_launcher->isChecked());
  
}




/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



