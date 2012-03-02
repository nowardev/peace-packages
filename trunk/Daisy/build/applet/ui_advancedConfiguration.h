#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'advancedConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEDCONFIGURATION_H
#define UI_ADVANCEDCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kactionselector.h"
#include "knuminput.h"

QT_BEGIN_NAMESPACE

class Ui_advancedConfiguration
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *Main;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    KActionSelector *kactionselector_plugs;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_launchers;
    KIntSpinBox *kintspinbox_launchers;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_rep;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSlider *slider_drawerSize;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSlider *slider_drawerRotation;
    QWidget *Advanced;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox_middleClick;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBoxCloseTasks;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *advancedConfiguration)
    {
        if (advancedConfiguration->objectName().isEmpty())
            advancedConfiguration->setObjectName(QString::fromUtf8("advancedConfiguration"));
        advancedConfiguration->resize(465, 369);
        gridLayout_3 = new QGridLayout(advancedConfiguration);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(advancedConfiguration);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        Main = new QWidget();
        Main->setObjectName(QString::fromUtf8("Main"));
        verticalLayout_4 = new QVBoxLayout(Main);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        kactionselector_plugs = new KActionSelector(Main);
        kactionselector_plugs->setObjectName(QString::fromUtf8("kactionselector_plugs"));

        verticalLayout_2->addWidget(kactionselector_plugs);


        verticalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(20, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_launchers = new QLabel(Main);
        label_launchers->setObjectName(QString::fromUtf8("label_launchers"));

        horizontalLayout_3->addWidget(label_launchers);

        kintspinbox_launchers = new KIntSpinBox(Main);
        kintspinbox_launchers->setObjectName(QString::fromUtf8("kintspinbox_launchers"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kintspinbox_launchers->sizePolicy().hasHeightForWidth());
        kintspinbox_launchers->setSizePolicy(sizePolicy);
        kintspinbox_launchers->setMinimum(1);
        kintspinbox_launchers->setMaximum(30);

        horizontalLayout_3->addWidget(kintspinbox_launchers);


        horizontalLayout->addLayout(horizontalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        checkBox_rep = new QCheckBox(Main);
        checkBox_rep->setObjectName(QString::fromUtf8("checkBox_rep"));

        verticalLayout->addWidget(checkBox_rep);

        groupBox_2 = new QGroupBox(Main);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        slider_drawerSize = new QSlider(groupBox_2);
        slider_drawerSize->setObjectName(QString::fromUtf8("slider_drawerSize"));
        slider_drawerSize->setMinimum(20);
        slider_drawerSize->setMaximum(100);
        slider_drawerSize->setSingleStep(5);
        slider_drawerSize->setPageStep(10);
        slider_drawerSize->setSliderPosition(20);
        slider_drawerSize->setOrientation(Qt::Horizontal);
        slider_drawerSize->setTickPosition(QSlider::TicksBelow);

        gridLayout_2->addWidget(slider_drawerSize, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(Main);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        slider_drawerRotation = new QSlider(groupBox);
        slider_drawerRotation->setObjectName(QString::fromUtf8("slider_drawerRotation"));
        slider_drawerRotation->setMaximum(30);
        slider_drawerRotation->setSingleStep(3);
        slider_drawerRotation->setPageStep(5);
        slider_drawerRotation->setOrientation(Qt::Horizontal);
        slider_drawerRotation->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(slider_drawerRotation, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        verticalLayout_4->addLayout(verticalLayout);

        tabWidget->addTab(Main, QString());
        Advanced = new QWidget();
        Advanced->setObjectName(QString::fromUtf8("Advanced"));
        verticalLayout_3 = new QVBoxLayout(Advanced);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Advanced);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox_middleClick = new QComboBox(Advanced);
        comboBox_middleClick->setObjectName(QString::fromUtf8("comboBox_middleClick"));
        comboBox_middleClick->setMaximumSize(QSize(500, 28));

        horizontalLayout_2->addWidget(comboBox_middleClick);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(horizontalSpacer_4);

        checkBoxCloseTasks = new QCheckBox(Advanced);
        checkBoxCloseTasks->setObjectName(QString::fromUtf8("checkBoxCloseTasks"));

        verticalLayout_3->addWidget(checkBoxCloseTasks);

        horizontalSpacer_3 = new QSpacerItem(20, 388, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(horizontalSpacer_3);

        tabWidget->addTab(Advanced, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(advancedConfiguration);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(advancedConfiguration);
    } // setupUi

    void retranslateUi(QWidget *advancedConfiguration)
    {
        advancedConfiguration->setWindowTitle(tr2i18n("Advanced", 0));
        kactionselector_plugs->setAvailableLabel(tr2i18n("&Available plugins:", 0));
        kactionselector_plugs->setSelectedLabel(tr2i18n("&Selected plugins:", 0));
        label_launchers->setText(tr2i18n("Total launchers:", 0));
        checkBox_rep->setText(tr2i18n("Show taskbar representations only for applications\n"
"that are not represented by a launcher", 0));
        groupBox_2->setTitle(tr2i18n("Drawers size:", 0));
        groupBox->setTitle(tr2i18n("Drawers rotation factor:", 0));
        tabWidget->setTabText(tabWidget->indexOf(Main), tr2i18n("Main", 0));
        label->setText(tr2i18n("Middle mouse button\n"
"click on launcher:", 0));
        comboBox_middleClick->clear();
        comboBox_middleClick->insertItems(0, QStringList()
         << tr2i18n("Shades task", 0)
         << tr2i18n("Starts new application instance", 0)
        );
        checkBoxCloseTasks->setText(tr2i18n("Show close button on mouse over for \n"
" taskbar representations", 0));
        tabWidget->setTabText(tabWidget->indexOf(Advanced), tr2i18n("Advanced", 0));
    } // retranslateUi

};

namespace Ui {
    class advancedConfiguration: public Ui_advancedConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ADVANCEDCONFIGURATION_H

