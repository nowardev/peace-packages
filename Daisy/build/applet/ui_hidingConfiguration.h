#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'hidingConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIDINGCONFIGURATION_H
#define UI_HIDINGCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hidingConfiguration
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *button_allwaysShow;
    QRadioButton *button_autoHide;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSpinBox *spinBox_secHide;
    QLabel *label_secHide;
    QRadioButton *button_allowCover;
    QSpacerItem *verticalSpacer;
    QCheckBox *button_showOnDesk;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *hidingConfiguration)
    {
        if (hidingConfiguration->objectName().isEmpty())
            hidingConfiguration->setObjectName(QString::fromUtf8("hidingConfiguration"));
        hidingConfiguration->resize(510, 292);
        gridLayout_2 = new QGridLayout(hidingConfiguration);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(hidingConfiguration);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        button_allwaysShow = new QRadioButton(groupBox);
        button_allwaysShow->setObjectName(QString::fromUtf8("button_allwaysShow"));

        verticalLayout->addWidget(button_allwaysShow);

        button_autoHide = new QRadioButton(groupBox);
        button_autoHide->setObjectName(QString::fromUtf8("button_autoHide"));

        verticalLayout->addWidget(button_autoHide);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        spinBox_secHide = new QSpinBox(groupBox);
        spinBox_secHide->setObjectName(QString::fromUtf8("spinBox_secHide"));

        horizontalLayout->addWidget(spinBox_secHide);

        label_secHide = new QLabel(groupBox);
        label_secHide->setObjectName(QString::fromUtf8("label_secHide"));

        horizontalLayout->addWidget(label_secHide);


        verticalLayout->addLayout(horizontalLayout);

        button_allowCover = new QRadioButton(groupBox);
        button_allowCover->setObjectName(QString::fromUtf8("button_allowCover"));

        verticalLayout->addWidget(button_allowCover);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        button_showOnDesk = new QCheckBox(groupBox);
        button_showOnDesk->setObjectName(QString::fromUtf8("button_showOnDesk"));

        gridLayout->addWidget(button_showOnDesk, 2, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);


        retranslateUi(hidingConfiguration);

        QMetaObject::connectSlotsByName(hidingConfiguration);
    } // setupUi

    void retranslateUi(QWidget *hidingConfiguration)
    {
        hidingConfiguration->setWindowTitle(tr2i18n("Hiding", 0));
        groupBox->setTitle(tr2i18n("Hide Mode", 0));
        button_allwaysShow->setText(tr2i18n("Hide only when a dock-hiding button is clicked", 0));
        button_autoHide->setText(tr2i18n("Hide automatically", 0));
        spinBox_secHide->setSuffix(tr2i18n("secs", 0));
        label_secHide->setText(tr2i18n("after the cursor leaves the dock", 0));
        button_allowCover->setText(tr2i18n("Allow other windows to cover the dock", 0));
        button_showOnDesk->setText(tr2i18n("Show dock when switching desktops", 0));
    } // retranslateUi

};

namespace Ui {
    class hidingConfiguration: public Ui_hidingConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HIDINGCONFIGURATION_H

