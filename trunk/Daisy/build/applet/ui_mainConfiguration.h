#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'mainConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCONFIGURATION_H
#define UI_MAINCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainConfiguration
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_role;
    QComboBox *comboBox_role;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_media;
    QComboBox *comboBox_player;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_drop;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *mainConfiguration)
    {
        if (mainConfiguration->objectName().isEmpty())
            mainConfiguration->setObjectName(QString::fromUtf8("mainConfiguration"));
        mainConfiguration->resize(556, 300);
        verticalLayout_2 = new QVBoxLayout(mainConfiguration);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_role = new QLabel(mainConfiguration);
        label_role->setObjectName(QString::fromUtf8("label_role"));
        label_role->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_4->addWidget(label_role);

        comboBox_role = new QComboBox(mainConfiguration);
        comboBox_role->setObjectName(QString::fromUtf8("comboBox_role"));

        horizontalLayout_4->addWidget(comboBox_role);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_media = new QLabel(mainConfiguration);
        label_media->setObjectName(QString::fromUtf8("label_media"));

        horizontalLayout->addWidget(label_media);

        comboBox_player = new QComboBox(mainConfiguration);
        comboBox_player->setObjectName(QString::fromUtf8("comboBox_player"));
        comboBox_player->setMinimumSize(QSize(120, 0));
        comboBox_player->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(comboBox_player);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox_drop = new QCheckBox(mainConfiguration);
        checkBox_drop->setObjectName(QString::fromUtf8("checkBox_drop"));

        verticalLayout->addWidget(checkBox_drop);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 46, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(mainConfiguration);

        QMetaObject::connectSlotsByName(mainConfiguration);
    } // setupUi

    void retranslateUi(QWidget *mainConfiguration)
    {
        mainConfiguration->setWindowTitle(tr2i18n("Main", 0));
        label_role->setText(tr2i18n("Role:", 0));
        comboBox_role->clear();
        comboBox_role->insertItems(0, QStringList()
         << tr2i18n("Circular dock", 0)
         << tr2i18n("Media controller", 0)
         << tr2i18n("Linear dock", 0)
        );
        label_media->setText(tr2i18n("Media source:", 0));
        comboBox_player->clear();
        comboBox_player->insertItems(0, QStringList()
         << tr2i18n("Amarok 1.x", 0)
         << tr2i18n("Amarok 2.x", 0)
         << tr2i18n("juK", 0)
         << tr2i18n("VLC", 0)
         << tr2i18n("XMMS", 0)
        );
        checkBox_drop->setText(tr2i18n("Allow drag and drop of objects", 0));
    } // retranslateUi

};

namespace Ui {
    class mainConfiguration: public Ui_mainConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINCONFIGURATION_H

