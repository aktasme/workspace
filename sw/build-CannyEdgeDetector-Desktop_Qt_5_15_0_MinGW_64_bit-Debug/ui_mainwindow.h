/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCanny;
    QPushButton *pushButtonSave;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lableSigma;
    QSpinBox *spinBoxSigma;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lableKernelSize;
    QSpinBox *spinBoxKernelSize;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelThresholdLow;
    QSpinBox *spinBoxThresholdLow;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelThresholdHigh;
    QSpinBox *spinBoxThresholdHigh;
    QSpacerItem *horizontalSpacer_2;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonSelect = new QPushButton(centralwidget);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));

        horizontalLayout->addWidget(pushButtonSelect);

        pushButtonCanny = new QPushButton(centralwidget);
        pushButtonCanny->setObjectName(QString::fromUtf8("pushButtonCanny"));
        pushButtonCanny->setEnabled(false);

        horizontalLayout->addWidget(pushButtonCanny);

        pushButtonSave = new QPushButton(centralwidget);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setEnabled(false);

        horizontalLayout->addWidget(pushButtonSave);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lableSigma = new QLabel(groupBox);
        lableSigma->setObjectName(QString::fromUtf8("lableSigma"));

        horizontalLayout_2->addWidget(lableSigma);

        spinBoxSigma = new QSpinBox(groupBox);
        spinBoxSigma->setObjectName(QString::fromUtf8("spinBoxSigma"));
        spinBoxSigma->setEnabled(false);
        spinBoxSigma->setMaximum(10);
        spinBoxSigma->setSingleStep(1);
        spinBoxSigma->setValue(1);

        horizontalLayout_2->addWidget(spinBoxSigma);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lableKernelSize = new QLabel(groupBox);
        lableKernelSize->setObjectName(QString::fromUtf8("lableKernelSize"));

        horizontalLayout_3->addWidget(lableKernelSize);

        spinBoxKernelSize = new QSpinBox(groupBox);
        spinBoxKernelSize->setObjectName(QString::fromUtf8("spinBoxKernelSize"));
        spinBoxKernelSize->setEnabled(false);
        spinBoxKernelSize->setMinimum(3);
        spinBoxKernelSize->setMaximum(21);
        spinBoxKernelSize->setSingleStep(2);
        spinBoxKernelSize->setValue(5);

        horizontalLayout_3->addWidget(spinBoxKernelSize);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_10->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelThresholdLow = new QLabel(groupBox_2);
        labelThresholdLow->setObjectName(QString::fromUtf8("labelThresholdLow"));

        horizontalLayout_6->addWidget(labelThresholdLow);

        spinBoxThresholdLow = new QSpinBox(groupBox_2);
        spinBoxThresholdLow->setObjectName(QString::fromUtf8("spinBoxThresholdLow"));
        spinBoxThresholdLow->setEnabled(false);
        spinBoxThresholdLow->setMaximum(255);
        spinBoxThresholdLow->setValue(40);

        horizontalLayout_6->addWidget(spinBoxThresholdLow);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelThresholdHigh = new QLabel(groupBox_2);
        labelThresholdHigh->setObjectName(QString::fromUtf8("labelThresholdHigh"));

        horizontalLayout_7->addWidget(labelThresholdHigh);

        spinBoxThresholdHigh = new QSpinBox(groupBox_2);
        spinBoxThresholdHigh->setObjectName(QString::fromUtf8("spinBoxThresholdHigh"));
        spinBoxThresholdHigh->setEnabled(false);
        spinBoxThresholdHigh->setMaximum(255);
        spinBoxThresholdHigh->setValue(120);

        horizontalLayout_7->addWidget(spinBoxThresholdHigh);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(horizontalLayout_8);

        labelThresholdLow->raise();

        horizontalLayout_10->addWidget(groupBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_10);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
        pushButtonCanny->setText(QCoreApplication::translate("MainWindow", "Canny", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Gaussian", nullptr));
        lableSigma->setText(QCoreApplication::translate("MainWindow", "Sigma:", nullptr));
        lableKernelSize->setText(QCoreApplication::translate("MainWindow", "Kernel Size:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Thresholds", nullptr));
        labelThresholdLow->setText(QCoreApplication::translate("MainWindow", "Lower Limit:", nullptr));
        labelThresholdHigh->setText(QCoreApplication::translate("MainWindow", "Upper Limit:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
