#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'arrangementConfiguration.ui'
**
** Created: Fri Mar 2 13:15:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRANGEMENTCONFIGURATION_H
#define UI_ARRANGEMENTCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_arrangementConfiguration
{
public:
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_pos;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_butPos;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_topLeft;
    QPushButton *pushButton_topCenter;
    QPushButton *pushButton_topRight;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_leftTop;
    QPushButton *pushButton_leftCenter;
    QPushButton *pushButton_leftButtom;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_rightTop;
    QPushButton *pushButton_rightCenter;
    QPushButton *pushButton_rightButtom;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_buttomLeft;
    QPushButton *pushButton_buttomCenter;
    QPushButton *pushButton_buttomRight;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox_floating;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QSlider *slider_icosize;
    QSpinBox *spinBox_icosize;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QSlider *slider_icospacing;

    void setupUi(QWidget *arrangementConfiguration)
    {
        if (arrangementConfiguration->objectName().isEmpty())
            arrangementConfiguration->setObjectName(QString::fromUtf8("arrangementConfiguration"));
        arrangementConfiguration->resize(412, 382);
        verticalLayout_5 = new QVBoxLayout(arrangementConfiguration);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_pos = new QGroupBox(arrangementConfiguration);
        groupBox_pos->setObjectName(QString::fromUtf8("groupBox_pos"));
        gridLayout = new QGridLayout(groupBox_pos);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(64, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        gridLayout_butPos = new QGridLayout();
        gridLayout_butPos->setObjectName(QString::fromUtf8("gridLayout_butPos"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_topLeft = new QPushButton(groupBox_pos);
        pushButton_topLeft->setObjectName(QString::fromUtf8("pushButton_topLeft"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_topLeft->sizePolicy().hasHeightForWidth());
        pushButton_topLeft->setSizePolicy(sizePolicy);
        pushButton_topLeft->setMinimumSize(QSize(40, 16));
        pushButton_topLeft->setMaximumSize(QSize(40, 16));
        pushButton_topLeft->setCheckable(true);

        horizontalLayout->addWidget(pushButton_topLeft);

        pushButton_topCenter = new QPushButton(groupBox_pos);
        pushButton_topCenter->setObjectName(QString::fromUtf8("pushButton_topCenter"));
        sizePolicy.setHeightForWidth(pushButton_topCenter->sizePolicy().hasHeightForWidth());
        pushButton_topCenter->setSizePolicy(sizePolicy);
        pushButton_topCenter->setMinimumSize(QSize(45, 16));
        pushButton_topCenter->setMaximumSize(QSize(45, 16));
        pushButton_topCenter->setCheckable(true);

        horizontalLayout->addWidget(pushButton_topCenter);

        pushButton_topRight = new QPushButton(groupBox_pos);
        pushButton_topRight->setObjectName(QString::fromUtf8("pushButton_topRight"));
        sizePolicy.setHeightForWidth(pushButton_topRight->sizePolicy().hasHeightForWidth());
        pushButton_topRight->setSizePolicy(sizePolicy);
        pushButton_topRight->setMinimumSize(QSize(40, 16));
        pushButton_topRight->setMaximumSize(QSize(40, 16));
        pushButton_topRight->setCheckable(true);

        horizontalLayout->addWidget(pushButton_topRight);


        gridLayout_butPos->addLayout(horizontalLayout, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_leftTop = new QPushButton(groupBox_pos);
        pushButton_leftTop->setObjectName(QString::fromUtf8("pushButton_leftTop"));
        sizePolicy.setHeightForWidth(pushButton_leftTop->sizePolicy().hasHeightForWidth());
        pushButton_leftTop->setSizePolicy(sizePolicy);
        pushButton_leftTop->setMinimumSize(QSize(16, 30));
        pushButton_leftTop->setMaximumSize(QSize(16, 30));
        pushButton_leftTop->setCheckable(true);

        verticalLayout_3->addWidget(pushButton_leftTop);

        pushButton_leftCenter = new QPushButton(groupBox_pos);
        pushButton_leftCenter->setObjectName(QString::fromUtf8("pushButton_leftCenter"));
        sizePolicy.setHeightForWidth(pushButton_leftCenter->sizePolicy().hasHeightForWidth());
        pushButton_leftCenter->setSizePolicy(sizePolicy);
        pushButton_leftCenter->setMinimumSize(QSize(16, 30));
        pushButton_leftCenter->setMaximumSize(QSize(16, 30));
        pushButton_leftCenter->setCheckable(true);

        verticalLayout_3->addWidget(pushButton_leftCenter);

        pushButton_leftButtom = new QPushButton(groupBox_pos);
        pushButton_leftButtom->setObjectName(QString::fromUtf8("pushButton_leftButtom"));
        sizePolicy.setHeightForWidth(pushButton_leftButtom->sizePolicy().hasHeightForWidth());
        pushButton_leftButtom->setSizePolicy(sizePolicy);
        pushButton_leftButtom->setMinimumSize(QSize(16, 30));
        pushButton_leftButtom->setMaximumSize(QSize(16, 30));
        pushButton_leftButtom->setCheckable(true);

        verticalLayout_3->addWidget(pushButton_leftButtom);


        gridLayout_butPos->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_rightTop = new QPushButton(groupBox_pos);
        pushButton_rightTop->setObjectName(QString::fromUtf8("pushButton_rightTop"));
        sizePolicy.setHeightForWidth(pushButton_rightTop->sizePolicy().hasHeightForWidth());
        pushButton_rightTop->setSizePolicy(sizePolicy);
        pushButton_rightTop->setMinimumSize(QSize(16, 30));
        pushButton_rightTop->setMaximumSize(QSize(16, 30));
        pushButton_rightTop->setCheckable(true);

        verticalLayout_2->addWidget(pushButton_rightTop);

        pushButton_rightCenter = new QPushButton(groupBox_pos);
        pushButton_rightCenter->setObjectName(QString::fromUtf8("pushButton_rightCenter"));
        sizePolicy.setHeightForWidth(pushButton_rightCenter->sizePolicy().hasHeightForWidth());
        pushButton_rightCenter->setSizePolicy(sizePolicy);
        pushButton_rightCenter->setMinimumSize(QSize(16, 30));
        pushButton_rightCenter->setMaximumSize(QSize(16, 30));
        pushButton_rightCenter->setCheckable(true);

        verticalLayout_2->addWidget(pushButton_rightCenter);

        pushButton_rightButtom = new QPushButton(groupBox_pos);
        pushButton_rightButtom->setObjectName(QString::fromUtf8("pushButton_rightButtom"));
        sizePolicy.setHeightForWidth(pushButton_rightButtom->sizePolicy().hasHeightForWidth());
        pushButton_rightButtom->setSizePolicy(sizePolicy);
        pushButton_rightButtom->setMinimumSize(QSize(16, 30));
        pushButton_rightButtom->setMaximumSize(QSize(16, 30));
        pushButton_rightButtom->setCheckable(true);

        verticalLayout_2->addWidget(pushButton_rightButtom);


        gridLayout_butPos->addLayout(verticalLayout_2, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_buttomLeft = new QPushButton(groupBox_pos);
        pushButton_buttomLeft->setObjectName(QString::fromUtf8("pushButton_buttomLeft"));
        sizePolicy.setHeightForWidth(pushButton_buttomLeft->sizePolicy().hasHeightForWidth());
        pushButton_buttomLeft->setSizePolicy(sizePolicy);
        pushButton_buttomLeft->setMinimumSize(QSize(40, 16));
        pushButton_buttomLeft->setMaximumSize(QSize(40, 16));
        pushButton_buttomLeft->setCheckable(true);

        horizontalLayout_2->addWidget(pushButton_buttomLeft);

        pushButton_buttomCenter = new QPushButton(groupBox_pos);
        pushButton_buttomCenter->setObjectName(QString::fromUtf8("pushButton_buttomCenter"));
        sizePolicy.setHeightForWidth(pushButton_buttomCenter->sizePolicy().hasHeightForWidth());
        pushButton_buttomCenter->setSizePolicy(sizePolicy);
        pushButton_buttomCenter->setMinimumSize(QSize(45, 16));
        pushButton_buttomCenter->setMaximumSize(QSize(45, 16));
        pushButton_buttomCenter->setCheckable(true);

        horizontalLayout_2->addWidget(pushButton_buttomCenter);

        pushButton_buttomRight = new QPushButton(groupBox_pos);
        pushButton_buttomRight->setObjectName(QString::fromUtf8("pushButton_buttomRight"));
        sizePolicy.setHeightForWidth(pushButton_buttomRight->sizePolicy().hasHeightForWidth());
        pushButton_buttomRight->setSizePolicy(sizePolicy);
        pushButton_buttomRight->setMinimumSize(QSize(40, 16));
        pushButton_buttomRight->setMaximumSize(QSize(40, 16));
        pushButton_buttomRight->setCheckable(true);

        horizontalLayout_2->addWidget(pushButton_buttomRight);


        gridLayout_butPos->addLayout(horizontalLayout_2, 2, 1, 1, 1);


        gridLayout->addLayout(gridLayout_butPos, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(65, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_pos);

        checkBox_floating = new QCheckBox(arrangementConfiguration);
        checkBox_floating->setObjectName(QString::fromUtf8("checkBox_floating"));

        verticalLayout_5->addWidget(checkBox_floating);

        groupBox_2 = new QGroupBox(arrangementConfiguration);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slider_icosize = new QSlider(groupBox_2);
        slider_icosize->setObjectName(QString::fromUtf8("slider_icosize"));
        slider_icosize->setMinimum(24);
        slider_icosize->setMaximum(256);
        slider_icosize->setPageStep(5);
        slider_icosize->setValue(24);
        slider_icosize->setSliderPosition(24);
        slider_icosize->setOrientation(Qt::Horizontal);
        slider_icosize->setTickPosition(QSlider::TicksAbove);
        slider_icosize->setTickInterval(22);

        verticalLayout->addWidget(slider_icosize);


        horizontalLayout_3->addLayout(verticalLayout);

        spinBox_icosize = new QSpinBox(groupBox_2);
        spinBox_icosize->setObjectName(QString::fromUtf8("spinBox_icosize"));
        spinBox_icosize->setMinimum(24);
        spinBox_icosize->setMaximum(256);
        spinBox_icosize->setValue(24);

        horizontalLayout_3->addWidget(spinBox_icosize);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(arrangementConfiguration);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        slider_icospacing = new QSlider(groupBox_3);
        slider_icospacing->setObjectName(QString::fromUtf8("slider_icospacing"));
        slider_icospacing->setMinimum(-10);
        slider_icospacing->setMaximum(150);
        slider_icospacing->setPageStep(5);
        slider_icospacing->setOrientation(Qt::Horizontal);
        slider_icospacing->setTickPosition(QSlider::TicksAbove);
        slider_icospacing->setTickInterval(20);

        verticalLayout_4->addWidget(slider_icospacing);


        horizontalLayout_4->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(groupBox_3);


        retranslateUi(arrangementConfiguration);

        QMetaObject::connectSlotsByName(arrangementConfiguration);
    } // setupUi

    void retranslateUi(QWidget *arrangementConfiguration)
    {
        arrangementConfiguration->setWindowTitle(tr2i18n("Appearance", 0));
        groupBox_pos->setTitle(tr2i18n("Position", 0));
#ifndef UI_QT_NO_TOOLTIP
        pushButton_topLeft->setToolTip(tr2i18n("top left", 0));
#endif // QT_NO_TOOLTIP
        pushButton_topLeft->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_topCenter->setToolTip(tr2i18n("top center", 0));
#endif // QT_NO_TOOLTIP
        pushButton_topCenter->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_topRight->setToolTip(tr2i18n("top right", 0));
#endif // QT_NO_TOOLTIP
        pushButton_topRight->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_leftTop->setToolTip(tr2i18n("left top", 0));
#endif // QT_NO_TOOLTIP
        pushButton_leftTop->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_leftCenter->setToolTip(tr2i18n("left center", 0));
#endif // QT_NO_TOOLTIP
        pushButton_leftCenter->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_leftButtom->setToolTip(tr2i18n("left bottom", 0));
#endif // QT_NO_TOOLTIP
        pushButton_leftButtom->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_rightTop->setToolTip(tr2i18n("right top", 0));
#endif // QT_NO_TOOLTIP
        pushButton_rightTop->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_rightCenter->setToolTip(tr2i18n("right center", 0));
#endif // QT_NO_TOOLTIP
        pushButton_rightCenter->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_rightButtom->setToolTip(tr2i18n("right bottom", 0));
#endif // QT_NO_TOOLTIP
        pushButton_rightButtom->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_buttomLeft->setToolTip(tr2i18n("bottom left", 0));
#endif // QT_NO_TOOLTIP
        pushButton_buttomLeft->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_buttomCenter->setToolTip(tr2i18n("bottom center", 0));
#endif // QT_NO_TOOLTIP
        pushButton_buttomCenter->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        pushButton_buttomRight->setToolTip(tr2i18n("bottom right", 0));
#endif // QT_NO_TOOLTIP
        pushButton_buttomRight->setText(QString());
        checkBox_floating->setText(tr2i18n("Floating", 0));
        groupBox_2->setTitle(tr2i18n("Size", 0));
        spinBox_icosize->setSuffix(tr2i18n("pixels", 0));
        groupBox_3->setTitle(tr2i18n("Spacing", 0));
    } // retranslateUi

};

namespace Ui {
    class arrangementConfiguration: public Ui_arrangementConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ARRANGEMENTCONFIGURATION_H

