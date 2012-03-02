#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'appearanceConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPEARANCECONFIGURATION_H
#define UI_APPEARANCECONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_appearanceConfiguration
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxIcoEffects;
    QComboBox *comboBoxIcoEffects;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxClickEffects;
    QComboBox *comboBoxClickEffects;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxTips_launchers;
    QComboBox *comboBoxTips_launchers;
    QCheckBox *checkBoxTips_inactive_launchers;
    QCheckBox *checkBoxTips;
    QCheckBox *checkBox_indicons;
    QCheckBox *checkBoxIcoMirror;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBoxBackground;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSlider *slider_Opacity;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *appearanceConfiguration)
    {
        if (appearanceConfiguration->objectName().isEmpty())
            appearanceConfiguration->setObjectName(QString::fromUtf8("appearanceConfiguration"));
        appearanceConfiguration->resize(519, 340);
        verticalLayout_2 = new QVBoxLayout(appearanceConfiguration);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxIcoEffects = new QCheckBox(appearanceConfiguration);
        checkBoxIcoEffects->setObjectName(QString::fromUtf8("checkBoxIcoEffects"));

        horizontalLayout->addWidget(checkBoxIcoEffects);

        comboBoxIcoEffects = new QComboBox(appearanceConfiguration);
        comboBoxIcoEffects->setObjectName(QString::fromUtf8("comboBoxIcoEffects"));
        comboBoxIcoEffects->setMinimumSize(QSize(170, 0));

        horizontalLayout->addWidget(comboBoxIcoEffects);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBoxClickEffects = new QCheckBox(appearanceConfiguration);
        checkBoxClickEffects->setObjectName(QString::fromUtf8("checkBoxClickEffects"));

        horizontalLayout_2->addWidget(checkBoxClickEffects);

        comboBoxClickEffects = new QComboBox(appearanceConfiguration);
        comboBoxClickEffects->setObjectName(QString::fromUtf8("comboBoxClickEffects"));
        comboBoxClickEffects->setMinimumSize(QSize(170, 0));

        horizontalLayout_2->addWidget(comboBoxClickEffects);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxTips_launchers = new QCheckBox(appearanceConfiguration);
        checkBoxTips_launchers->setObjectName(QString::fromUtf8("checkBoxTips_launchers"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBoxTips_launchers->sizePolicy().hasHeightForWidth());
        checkBoxTips_launchers->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(checkBoxTips_launchers);

        comboBoxTips_launchers = new QComboBox(appearanceConfiguration);
        comboBoxTips_launchers->setObjectName(QString::fromUtf8("comboBoxTips_launchers"));

        horizontalLayout_3->addWidget(comboBoxTips_launchers);


        verticalLayout_2->addLayout(horizontalLayout_3);

        checkBoxTips_inactive_launchers = new QCheckBox(appearanceConfiguration);
        checkBoxTips_inactive_launchers->setObjectName(QString::fromUtf8("checkBoxTips_inactive_launchers"));

        verticalLayout_2->addWidget(checkBoxTips_inactive_launchers);

        checkBoxTips = new QCheckBox(appearanceConfiguration);
        checkBoxTips->setObjectName(QString::fromUtf8("checkBoxTips"));

        verticalLayout_2->addWidget(checkBoxTips);

        checkBox_indicons = new QCheckBox(appearanceConfiguration);
        checkBox_indicons->setObjectName(QString::fromUtf8("checkBox_indicons"));

        verticalLayout_2->addWidget(checkBox_indicons);

        checkBoxIcoMirror = new QCheckBox(appearanceConfiguration);
        checkBoxIcoMirror->setObjectName(QString::fromUtf8("checkBoxIcoMirror"));

        verticalLayout_2->addWidget(checkBoxIcoMirror);

        verticalSpacer = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(appearanceConfiguration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxBackground = new QComboBox(appearanceConfiguration);
        comboBoxBackground->setObjectName(QString::fromUtf8("comboBoxBackground"));

        gridLayout->addWidget(comboBoxBackground, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(appearanceConfiguration);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        slider_Opacity = new QSlider(appearanceConfiguration);
        slider_Opacity->setObjectName(QString::fromUtf8("slider_Opacity"));
        slider_Opacity->setMinimum(1);
        slider_Opacity->setMaximum(100);
        slider_Opacity->setSingleStep(10);
        slider_Opacity->setPageStep(10);
        slider_Opacity->setOrientation(Qt::Horizontal);
        slider_Opacity->setTickPosition(QSlider::TicksBelow);

        verticalLayout->addWidget(slider_Opacity);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(appearanceConfiguration);

        QMetaObject::connectSlotsByName(appearanceConfiguration);
    } // setupUi

    void retranslateUi(QWidget *appearanceConfiguration)
    {
        appearanceConfiguration->setWindowTitle(tr2i18n("Appearance", 0));
        checkBoxIcoEffects->setText(tr2i18n("Enable mouseover effects", 0));
        checkBoxClickEffects->setText(tr2i18n("Enable on-click effects", 0));
        checkBoxTips_launchers->setText(tr2i18n("Show tooltips on launchers", 0));
        checkBoxTips_inactive_launchers->setText(tr2i18n("Show tooltips on inactive launchers", 0));
        checkBoxTips->setText(tr2i18n("Show tooltips on plugins", 0));
        checkBox_indicons->setText(tr2i18n("Show application activity indicators", 0));
        checkBoxIcoMirror->setText(tr2i18n("Enable mirror effects", 0));
        label->setText(tr2i18n("Background:", 0));
        label_2->setText(tr2i18n("Background opacity:", 0));
    } // retranslateUi

};

namespace Ui {
    class appearanceConfiguration: public Ui_appearanceConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // APPEARANCECONFIGURATION_H

