#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'launcherConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHERCONFIGURATION_H
#define UI_LAUNCHERCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kicondialog.h"

QT_BEGIN_NAMESPACE

class Ui_launcherConfiguration
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_6;
    KIconButton *pushButton_ico;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_alias;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_command;
    QLineEdit *lineEdit_command;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    KIconButton *pushButton_action_ico;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QCheckBox *checkBox_action_launcher;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *lineEdit_action_name;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *lineEdit_action_command;
    QFrame *line_2;

    void setupUi(QWidget *launcherConfiguration)
    {
        if (launcherConfiguration->objectName().isEmpty())
            launcherConfiguration->setObjectName(QString::fromUtf8("launcherConfiguration"));
        launcherConfiguration->resize(415, 401);
        gridLayout_2 = new QGridLayout(launcherConfiguration);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_ico = new KIconButton(launcherConfiguration);
        pushButton_ico->setObjectName(QString::fromUtf8("pushButton_ico"));
        pushButton_ico->setMinimumSize(QSize(70, 70));
        pushButton_ico->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_ico->setFlat(true);

        horizontalLayout_6->addWidget(pushButton_ico);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_name = new QLabel(launcherConfiguration);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        horizontalLayout->addWidget(label_name);

        lineEdit_name = new QLineEdit(launcherConfiguration);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        horizontalLayout->addWidget(lineEdit_name);


        horizontalLayout_6->addLayout(horizontalLayout);


        gridLayout_2->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(launcherConfiguration);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_alias = new QLineEdit(launcherConfiguration);
        lineEdit_alias->setObjectName(QString::fromUtf8("lineEdit_alias"));

        horizontalLayout_3->addWidget(lineEdit_alias);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_command = new QLabel(launcherConfiguration);
        label_command->setObjectName(QString::fromUtf8("label_command"));

        horizontalLayout_2->addWidget(label_command);

        lineEdit_command = new QLineEdit(launcherConfiguration);
        lineEdit_command->setObjectName(QString::fromUtf8("lineEdit_command"));

        horizontalLayout_2->addWidget(lineEdit_command);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_action_ico = new KIconButton(launcherConfiguration);
        pushButton_action_ico->setObjectName(QString::fromUtf8("pushButton_action_ico"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_action_ico->sizePolicy().hasHeightForWidth());
        pushButton_action_ico->setSizePolicy(sizePolicy);
        pushButton_action_ico->setMinimumSize(QSize(70, 70));

        gridLayout->addWidget(pushButton_action_ico, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        line = new QFrame(launcherConfiguration);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        checkBox_action_launcher = new QCheckBox(launcherConfiguration);
        checkBox_action_launcher->setObjectName(QString::fromUtf8("checkBox_action_launcher"));

        verticalLayout->addWidget(checkBox_action_launcher);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(launcherConfiguration);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        lineEdit_action_name = new QLineEdit(launcherConfiguration);
        lineEdit_action_name->setObjectName(QString::fromUtf8("lineEdit_action_name"));

        horizontalLayout_5->addWidget(lineEdit_action_name);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(launcherConfiguration);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        lineEdit_action_command = new QLineEdit(launcherConfiguration);
        lineEdit_action_command->setObjectName(QString::fromUtf8("lineEdit_action_command"));

        horizontalLayout_4->addWidget(lineEdit_action_command);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        line_2 = new QFrame(launcherConfiguration);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);


        gridLayout_2->addLayout(verticalLayout_2, 2, 0, 1, 1);

        QWidget::setTabOrder(lineEdit_name, pushButton_ico);

        retranslateUi(launcherConfiguration);

        QMetaObject::connectSlotsByName(launcherConfiguration);
    } // setupUi

    void retranslateUi(QWidget *launcherConfiguration)
    {
        launcherConfiguration->setWindowTitle(tr2i18n("Edit launcher", 0));
#ifndef UI_QT_NO_TOOLTIP
        pushButton_ico->setToolTip(tr2i18n("Click to set icon", 0));
#endif // QT_NO_TOOLTIP
        label_name->setText(tr2i18n("Name:", 0));
        label_3->setText(tr2i18n("Alias:", 0));
#ifndef UI_QT_NO_TOOLTIP
        lineEdit_alias->setToolTip(tr2i18n("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Example:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Command</span>: <span style=\" font-style:italic;\">kfmclient openURL</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Alias</span>: <span style=\" font-style:italic;\">konqueror</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_command->setText(tr2i18n("Command:", 0));
#ifndef UI_QT_NO_TOOLTIP
        pushButton_action_ico->setToolTip(tr2i18n("Click to set action icon", 0));
#endif // QT_NO_TOOLTIP
        checkBox_action_launcher->setText(tr2i18n("Enable action launcher", 0));
        label_2->setText(tr2i18n("Name:", 0));
        label->setText(tr2i18n("Command:", 0));
    } // retranslateUi

};

namespace Ui {
    class launcherConfiguration: public Ui_launcherConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LAUNCHERCONFIGURATION_H

