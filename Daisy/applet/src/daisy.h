/*
*   C++ Header: daisy
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






#ifndef daisy_HEADER
#define daisy_HEADER


// QT libs
#include <Qt>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QPointF>
#include <QStringList>
#include <QString>
#include <QProcess>
#include <QRect>
#include <QDir>
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QDesktopWidget>
#include <QHash>
#include <QPixmap>
#include <QImage>
#include <QMimeData>
#include <QDrag>
#include <QRegExp>
#include <QByteArray>
#include <QTextOption>
#include <QListWidget>
#include <QListWidgetItem>
#include <QX11Info>

/* NOT USED YET
#include <QPaintEngine>
#include <QGraphicsLinearLayout>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QFontMetrics>
#include <QFont>
#include <QGraphicsSceneResizeEvent>
#include <QtOpenGL/QtOpenGL>
*/


// KDE libs
#include <KDebug>
#include <KIcon>
#include <KIconLoader>
#include <KLocale>
#include <KConfigGroup>
#include <KConfigDialog>
#include <KRun>
#include <KUrl>
#include <KMenu>
#include <KDirWatch>
#include <KGlobal>
#include <KDialog>
#include <KMessageBox>
#include <KGuiItem>
#include <KDE/KWindowSystem>
#include <KWindowInfo>
#include <NET>
#include <KStartupInfoId>
#include <KService>
#include <KDesktopFile>
#include <KIconEffect>
#include <kdeversion.h>
#include <KToolInvocation>
#include <KDE/NETWinInfo>
#include <NETRootInfo>


#include <taskmanager/taskmanager.h>
#include <taskmanager/task.h>
#include <taskmanager/taskactions.h>
#include <taskmanager/taskitem.h>
#include <taskmanager/groupmanager.h>
#include <taskmanager/startup.h>
using TaskManager::Task;
using TaskManager::Startup;
using TaskManager::GroupManager;


/* NOT USED YET
#include <KDE/KSharedPtr>
#include <KStartupInfo>
#include <KStartupInfoData>
*/



// Plasma libs
#include <Plasma/Applet>
#include <Plasma/IconWidget>
#include <Plasma/ToolTipManager>
#include <Plasma/ToolTipContent>
#include <Plasma/Containment>
#include <Plasma/FrameSvg>
#include <Plasma/Dialog>
/* NOT USED YET
#include <Plasma/Corona>
#include <Plasma/View>
#include <Plasma/Theme>
#include <Plasma/Svg>
#include <Plasma/SvgWidget>
#include <Plasma/GLApplet>
#include <Plasma/BusyWidget>
#include <Plasma/Meter>
#include <Plasma/PaintUtils>
#include <Plasma/Animator>
#include <Plasma/FlashingLabel>
*/


// Other libs




// Config dialog
#include "ui_mainConfiguration.h"
#include "ui_arrangementConfiguration.h"
#include "ui_appearanceConfiguration.h"
#include "ui_advancedConfiguration.h"
#include "ui_launcherConfiguration.h"
#include "ui_hidingConfiguration.h"




/// Debug
#define INFORMATION_DEBUG










// Define our Plasma Containment
class daisy : public Plasma::Containment
{
  
  Q_OBJECT
//-----------------------------------------------------------------------------
// Publics
  public:
    
    // Basic Create/Destroy
    daisy(QObject *parent, const QVariantList &args);
    
    void init();
    void paintInterface(QPainter *painter,const QStyleOptionGraphicsItem *option, const QRect& contentsRect);
    QPainterPath shape() const;
    
    void createConfigurationInterface(KConfigDialog *parent);
    virtual QList<QAction*> contextualActions();
    
    void constraintsEvent(Plasma::Constraints constraints);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void screenChanged(int wasScreen, int isScreen, Plasma::Containment *containment);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    
    ~daisy();





//-----------------------------------------------------------------------------
// Public slots
  public slots:
    
    void paintLaunchers(void);
    void configLauncher(void);
    void spaceReserver(bool startup);
    void removeLauncher(void);
    void addLauncher( QPointF droppos, QList<QUrl> &payload );
    void moveLauncher( QPointF droppos );
    int findLauncherPos( QPointF droppos );
    void toggTrash(void);
    void remTrash(void);
    void delayUpdate(void);
    void delayTaskIcoChange(void);
    void delayResize(void);
    void checkTrash(void);
    void openTrash(void);
    void emptyTrash(void);
    void restoreTrash(void);
    void metamorphosis( QString m_type_temp );
    void swapCircular(void);
    void swapLinear(void);
    void toggleLockedState(void);
    void removeDaisy(void);
    QList< QList <double> > calcWidgetPositions( const QRect &contentsRect );
    void launClick(void);
    void taskClick(void);
    void launNewInstance(void);
    void toggTask(WId id);
    void focusTask(WId id);
    void toggShadeTask(WId id);
    void closeTask(WId id);
    void drawerClicked();
    void taskMenuClicked();
    void mouseTracker(void);
    void addDelay(void);
    void hoverLauncher(QObject *obj);
    void mormalizeLauncher();
    void clickEffect(int clickedlaunch_tmp);
    void resetResize();
    void delayExec();
    void delayShade();
    void taskClosing();





 
//-----------------------------------------------------------------------------
// Protected
  protected:
    
    void uncheckPosButtons();
    void insertBacks();
    void insertPlugs();
    void insertFx();
    bool eventFilter(QObject *obj, QEvent *event);






//-----------------------------------------------------------------------------
// Protected slots
  protected slots:
    
    void configAccepted();
    void configRejected();
    void configLauncherAccepted();
    void configLauncherRejected();
    void toggleActionLauncher();
    void toggleMediaCombo();
    void toggleHide();
    void backgroundChanged(int);
    void szValueChange();
    void opacityValueChange(int value);
    void spinBoxSize_Clicked(int value);
    void destroyLauncher(void);
    void toggleEffectsCombo();
    
    void posButton_Clicked();
    void floating_Clicked();
    
    void drawerSizeChange(int value);
    void drawerRotationChange(int value);
    
    





//-----------------------------------------------------------------------------
// Privates
  private:
    
    void paintDesktop(QPainter *p, const QRect &contentsRect);
    void paintPanel(QPainter *p, const QRect &contentsRect);
    void createLaunchers(QString &m_type);
    void createTaskIcons();
    void readConfiguration();
    void writeConfiguration();
    void polishLaunchers();
    void refurbishLaunchers();
    void getLauncherValues();
    void plugItUp();
    void updateToolTipContent();
    void clearToolTipContent();
    void createMenus();
    void moveToTrash( QList<QUrl> &payload );
    int getContextLauncher( QPointF &p_click );
    int getContextTask( QPointF &p_click );
    
    QStringList getPlayerComs();
    void circleAround(int &delta);
    void resizeRepos( bool m_resetpos );
    QList<WId> getAllTasks();
    WId matchTask(QString name);
    QList<WId> matchAllTasks(QString name, int maxtasks);
    bool getTaskPtr( QString name );
    void elabDrawers( QList<WId> taskDict, int clickedlaunch_tmp  );
    void elabTaskMenu( QList<WId> taskDict, int clickedlaunch_tmp );
    void clearDrawers();
    void setTheme();
    void setElements();
    void startDrag(QGraphicsSceneMouseEvent *event);
    bool checkLock();
    
    void checkAttention( KWindowInfo taskInfo, QString widclass_tmp );
    void createTaskThumbnail( Task* task_tmp, int j );
    void scrollTasks(int delta);
    
    
    
    
    bool m_showtooltips;
    bool m_showtooltips_l;
    bool m_showtooltips_i;
    bool m_showindicons;
    bool m_showmirror;
    bool m_floating;
    bool m_reservespace;
    bool m_autohide;
    bool m_showondesk;
    bool m_draw_icoback;
    bool m_click_effects;
    bool m_taskpreviews;
    bool m_showtaskoflauncher;
    bool m_showclosetask;
    float m_icodimension;
    int m_total_launchers;
    int m_total_plugs;
    QString m_player;
    QString m_theme;
    QString m_theme_t;
    QString m_type;
    QString m_tiptype;
    QString m_position;
    QString m_orientation;
    QString m_zoomtype;
    QString m_click_effect_type;
    QString m_middleClickAction;
    qreal m_backopacity;
    qreal m_icospacing;
    qreal m_hidingdelay;
    qreal m_drawersize;
    qreal m_drawerrotation;
    
    bool m_show_trash;
    bool m_accept_drops;
    
    
    QList<double> m_zoomszdiff;
    QList<double> m_zoomposdiff;
    
    QList<double> last_icopos;
    int total_taskpreviews;
    int m_max_taskpreviews;
    
    
    
    
    int m_to_paint;
    int m_dexval;
    int m_launtoedit;
    int m_trash_spot;
    bool m_trashfull;
    bool m_inpanel;
    bool m_drawerscleared;
    bool m_oktodestroy;
    QString m_trash_dir;
    QList <float> m_domino;
    QList <int> m_activetasks;
    int m_activewindow;
    int m_startingwindow;
    int m_closingwindow;
    QList <int>  m_attentionwindow;
    
    int drawerpopspot_x;
    int drawerpopspot_y;
    
    QPointF m_circpos;
    QPointF startPos;
    
    QPointF m_clickpos;
    
    QPointF m_hoverpz;
    QSizeF m_hoversz;
    
    
    Task* m_task;
    GroupManager *m_groupManager;
    
    
    Plasma::FrameSvg m_backframe;
    Plasma::FrameSvg m_backframe_t;
    Plasma::FrameSvg m_hoverimage;
    
    
    QList <Plasma::FrameSvg*> m_indicons;
    QList <Plasma::IconWidget*> m_widgets;
    QList <Plasma::IconWidget*> m_drawericons;
    
    QList <Plasma::IconWidget*> m_taskicons;
    
    
    Plasma::Dialog m_drawdial;
    
    
    
    QAction *m_act_1;
    QAction *m_act_editlauncher;
    QAction *m_act_remlauncher;
    QAction *m_act_remtrash;
    QAction *m_act_newinstance;
    QAction *m_act_emptytrash;
    QAction *m_act_restoretrash;
    QAction *m_act_opentrash;
    QAction *m_act_role;
    QAction *m_act_role_t;
    QAction *m_act_lock;
    QAction *m_act_close;
    QAction *m_act_closetask;
    
    QList <QAction*> m_acta;
    QList <QStringList> m_values;
    QList <QStringList> m_avalues;
    QStringList m_alias;
    
    QList<WId> taskDrawers;
    QList<WId> showedTasks;
    
    
    WId m_actwin_save;
    WId m_reactwin_save;
    WId m_workwid;
    WId m_toupwid;
    WId m_focusedWindow;
    
    QObject *m_objclick;
    QObject *m_reobjclick;
    
    KMenu *m_launcher_menu;
    KMenu *m_launcher_menu_t;
    KMenu *m_task_menu;
    KMenu *m_trash_menu;
    KMenu *m_trash_menu_t;
    
    KDirWatch *m_watch_trash;
    
    
    QTimer *m_paint_tmr;
    QTimer *m_up_tmr;
    QTimer *m_rz_tmr;
    QTimer *m_tracker_tmr;
    QTimer *m_dlx_tmr;
    QTimer *m_dlt_tmr;
    QTimer *m_uti_tmr;
    
    QList<QUrl> m_url_drag;
    
    QWidget *m_reserver;
    
    // Config dialog
    KDialog *m_dialogLauncher;
    
    
    Ui::mainConfiguration m_mainConfigurationUi;
    Ui::arrangementConfiguration m_arrangementConfigurationUi;
    Ui::hidingConfiguration m_hidingConfigurationUi;
    Ui::appearanceConfiguration m_appearanceConfigurationUi;
    Ui::advancedConfiguration m_advancedConfigurationUi;
    Ui::launcherConfiguration m_launcherConfiguration;
    
    




//-----------------------------------------------------------------------------
// Private slots
  private slots:
    
    
    void startupAdded(Startup* startupItem);
    void startupRemoved(Startup* startupItem);
    
    
    void windowAdded(WId id);
    void windowRemoved(WId id);
    void activeWindowChanged(WId id);
    void currentDesktopChanged(int desktop);
    void windowChanged(WId id, const unsigned long* properties );
    void workAreaChanged();
    



};

















/**
* Extends Plasma::IconWidget with execution of program/url
*/
class MyIcon : public Plasma::IconWidget
{
  
  Q_OBJECT
  
  
  public:
    void init();
    /**
    * Constructor
    * @param command Command to associate to the icon
    * @param command_ico Command to associate to the action icon
    * @param action Icon action
    * @param parent Parent item
    */
    MyIcon( QStringList command, QStringList command_ico, QAction *action, QGraphicsItem *parent = 0 ):
    Plasma::IconWidget(parent), command_(command), command_ico_(command_ico), action_(action)
    {
      init();
      //connect(this, SIGNAL(clicked()), this, SLOT(launchProg()));
      if (command_ico_[3] == QString("1") )
      {
	connect(action, SIGNAL(triggered()), this, SLOT(launchIcoProg()));
	addIconAction(action);
      }
    }
    
    



  private slots:
    /**
    * Slot to open the program when the icon is clicked
    */
    void launchProg();

    /**
    * Slot to open the program when the action icon is clicked
    */
    void launchIcoProg();



  private:
    /** Command */
    QStringList command_;
    /** Action icon command */
    QStringList command_ico_;
    /** Action icon action */
    QAction action_;



};






















K_EXPORT_PLASMA_APPLET(daisy, daisy) // This is the command that links your applet to the .desktop file
#endif // multiple inclusion guard

