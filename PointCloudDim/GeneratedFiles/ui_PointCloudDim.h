/********************************************************************************
** Form generated from reading UI file 'PointCloudDim.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTCLOUDDIM_H
#define UI_POINTCLOUDDIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_PointCloudDimClass
{
public:
    QAction *actionImportSource;
    QAction *actionImportTarget;
    QAction *actionDimInfo;
    QAction *actionClose;
    QAction *actiond_5;
    QAction *actionHelp;
    QAction *actionFPFHCalculate;
    QAction *actionRegister;
    QAction *actionDim;
    QAction *actionOutput;
    QAction *actionMaximized;
    QAction *actionMinimized;
    QAction *actionImportCAD;
    QAction *actionNormal;
    QAction *actionSampling;
    QAction *action_change_dir;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVTKWidget *qvtkWidgetSource;
    QVTKWidget *qvtkWidgetTarget;
    QVTKWidget *qvtkWidgetUnRegistered;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QVTKWidget *qvtkWidgetDimInfo;
    QVTKWidget *qvtkWidgetRegistered;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxVoxelGrid;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxNormalRadius;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxFPFHRadius;
    QPushButton *pushButtonFPFHCalculate;
    QPushButton *pushButtonRegister;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *doubleSpinBoxCylinder;
    QSpinBox *spinBoxkSearch;
    QDoubleSpinBox *doubleSpinBoxPlane;
    QPushButton *pushButtonDim;
    QDoubleSpinBox *doubleSpinBoxNormalWeight;
    QPushButton *pushButtonOutput;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QSpinBox *spinBoxMaxIterations;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PointCloudDimClass)
    {
        if (PointCloudDimClass->objectName().isEmpty())
            PointCloudDimClass->setObjectName(QStringLiteral("PointCloudDimClass"));
        PointCloudDimClass->resize(1264, 755);
        actionImportSource = new QAction(PointCloudDimClass);
        actionImportSource->setObjectName(QStringLiteral("actionImportSource"));
        actionImportTarget = new QAction(PointCloudDimClass);
        actionImportTarget->setObjectName(QStringLiteral("actionImportTarget"));
        actionDimInfo = new QAction(PointCloudDimClass);
        actionDimInfo->setObjectName(QStringLiteral("actionDimInfo"));
        actionClose = new QAction(PointCloudDimClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actiond_5 = new QAction(PointCloudDimClass);
        actiond_5->setObjectName(QStringLiteral("actiond_5"));
        actionHelp = new QAction(PointCloudDimClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionFPFHCalculate = new QAction(PointCloudDimClass);
        actionFPFHCalculate->setObjectName(QStringLiteral("actionFPFHCalculate"));
        actionRegister = new QAction(PointCloudDimClass);
        actionRegister->setObjectName(QStringLiteral("actionRegister"));
        actionDim = new QAction(PointCloudDimClass);
        actionDim->setObjectName(QStringLiteral("actionDim"));
        actionOutput = new QAction(PointCloudDimClass);
        actionOutput->setObjectName(QStringLiteral("actionOutput"));
        actionMaximized = new QAction(PointCloudDimClass);
        actionMaximized->setObjectName(QStringLiteral("actionMaximized"));
        actionMinimized = new QAction(PointCloudDimClass);
        actionMinimized->setObjectName(QStringLiteral("actionMinimized"));
        actionImportCAD = new QAction(PointCloudDimClass);
        actionImportCAD->setObjectName(QStringLiteral("actionImportCAD"));
        actionNormal = new QAction(PointCloudDimClass);
        actionNormal->setObjectName(QStringLiteral("actionNormal"));
        actionSampling = new QAction(PointCloudDimClass);
        actionSampling->setObjectName(QStringLiteral("actionSampling"));
        action_change_dir = new QAction(PointCloudDimClass);
        action_change_dir->setObjectName(QStringLiteral("action_change_dir"));
        centralWidget = new QWidget(PointCloudDimClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        qvtkWidgetSource = new QVTKWidget(widget);
        qvtkWidgetSource->setObjectName(QStringLiteral("qvtkWidgetSource"));

        gridLayout->addWidget(qvtkWidgetSource, 0, 0, 1, 1);

        qvtkWidgetTarget = new QVTKWidget(widget);
        qvtkWidgetTarget->setObjectName(QStringLiteral("qvtkWidgetTarget"));

        gridLayout->addWidget(qvtkWidgetTarget, 0, 1, 1, 1);

        qvtkWidgetUnRegistered = new QVTKWidget(widget);
        qvtkWidgetUnRegistered->setObjectName(QStringLiteral("qvtkWidgetUnRegistered"));

        gridLayout->addWidget(qvtkWidgetUnRegistered, 0, 2, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        qvtkWidgetDimInfo = new QVTKWidget(widget_2);
        qvtkWidgetDimInfo->setObjectName(QStringLiteral("qvtkWidgetDimInfo"));

        gridLayout_2->addWidget(qvtkWidgetDimInfo, 0, 1, 1, 1);

        qvtkWidgetRegistered = new QVTKWidget(widget_2);
        qvtkWidgetRegistered->setObjectName(QStringLiteral("qvtkWidgetRegistered"));

        gridLayout_2->addWidget(qvtkWidgetRegistered, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget_2, 1, 0, 1, 1);


        horizontalLayout->addWidget(widget_3);

        widget_4 = new QWidget(centralWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_2 = new QGroupBox(widget_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 2, 4, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 0, 1, 1, 1);

        doubleSpinBoxVoxelGrid = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxVoxelGrid->setObjectName(QStringLiteral("doubleSpinBoxVoxelGrid"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBoxVoxelGrid->sizePolicy().hasHeightForWidth());
        doubleSpinBoxVoxelGrid->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(doubleSpinBoxVoxelGrid, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 1, 1, 1, 1);

        doubleSpinBoxNormalRadius = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxNormalRadius->setObjectName(QStringLiteral("doubleSpinBoxNormalRadius"));
        doubleSpinBoxNormalRadius->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(doubleSpinBoxNormalRadius->sizePolicy().hasHeightForWidth());
        doubleSpinBoxNormalRadius->setSizePolicy(sizePolicy2);

        gridLayout_6->addWidget(doubleSpinBoxNormalRadius, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_6->addWidget(label_3, 2, 1, 1, 1);

        doubleSpinBoxFPFHRadius = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxFPFHRadius->setObjectName(QStringLiteral("doubleSpinBoxFPFHRadius"));

        gridLayout_6->addWidget(doubleSpinBoxFPFHRadius, 2, 3, 1, 1);

        pushButtonFPFHCalculate = new QPushButton(groupBox_2);
        pushButtonFPFHCalculate->setObjectName(QStringLiteral("pushButtonFPFHCalculate"));

        gridLayout_6->addWidget(pushButtonFPFHCalculate, 3, 1, 1, 1);

        pushButtonRegister = new QPushButton(groupBox_2);
        pushButtonRegister->setObjectName(QStringLiteral("pushButtonRegister"));

        gridLayout_6->addWidget(pushButtonRegister, 3, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 4, 0, 1, 1);

        doubleSpinBoxCylinder = new QDoubleSpinBox(groupBox);
        doubleSpinBoxCylinder->setObjectName(QStringLiteral("doubleSpinBoxCylinder"));
        doubleSpinBoxCylinder->setSingleStep(0.05);

        gridLayout_7->addWidget(doubleSpinBoxCylinder, 1, 3, 2, 1);

        spinBoxkSearch = new QSpinBox(groupBox);
        spinBoxkSearch->setObjectName(QStringLiteral("spinBoxkSearch"));

        gridLayout_7->addWidget(spinBoxkSearch, 3, 3, 2, 1);

        doubleSpinBoxPlane = new QDoubleSpinBox(groupBox);
        doubleSpinBoxPlane->setObjectName(QStringLiteral("doubleSpinBoxPlane"));
        sizePolicy2.setHeightForWidth(doubleSpinBoxPlane->sizePolicy().hasHeightForWidth());
        doubleSpinBoxPlane->setSizePolicy(sizePolicy2);
        doubleSpinBoxPlane->setSingleStep(0.05);

        gridLayout_7->addWidget(doubleSpinBoxPlane, 0, 3, 1, 1);

        pushButtonDim = new QPushButton(groupBox);
        pushButtonDim->setObjectName(QStringLiteral("pushButtonDim"));

        gridLayout_7->addWidget(pushButtonDim, 8, 1, 1, 1);

        doubleSpinBoxNormalWeight = new QDoubleSpinBox(groupBox);
        doubleSpinBoxNormalWeight->setObjectName(QStringLiteral("doubleSpinBoxNormalWeight"));
        doubleSpinBoxNormalWeight->setSingleStep(0.05);

        gridLayout_7->addWidget(doubleSpinBoxNormalWeight, 5, 3, 2, 1);

        pushButtonOutput = new QPushButton(groupBox);
        pushButtonOutput->setObjectName(QStringLiteral("pushButtonOutput"));

        gridLayout_7->addWidget(pushButtonOutput, 8, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_6, 4, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 4, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_7->addWidget(label_4, 0, 1, 1, 1);

        spinBoxMaxIterations = new QSpinBox(groupBox);
        spinBoxMaxIterations->setObjectName(QStringLiteral("spinBoxMaxIterations"));
        spinBoxMaxIterations->setMaximum(100000);
        spinBoxMaxIterations->setSingleStep(50);

        gridLayout_7->addWidget(spinBoxMaxIterations, 7, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_7->addWidget(label_6, 4, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_7->addWidget(label_5, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_7->addWidget(label_7, 7, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_7->addWidget(label_8, 6, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(widget_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableWidget = new QTableWidget(groupBox_3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_4->addWidget(tableWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(widget_4);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        textBrowser = new QTextBrowser(groupBox_4);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_5->addWidget(textBrowser, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);


        horizontalLayout->addWidget(widget_4);

        PointCloudDimClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PointCloudDimClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1264, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        PointCloudDimClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PointCloudDimClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PointCloudDimClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PointCloudDimClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PointCloudDimClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionImportSource);
        menu->addAction(actionImportTarget);
        menu->addSeparator();
        menu->addAction(action_change_dir);
        menu->addSeparator();
        menu->addAction(actionClose);
        menu_2->addAction(actionHelp);
        menu_3->addAction(actionMaximized);
        menu_3->addAction(actionMinimized);
        menu_3->addAction(actionNormal);
        menu_4->addAction(actionFPFHCalculate);
        menu_4->addAction(actionRegister);
        menu_4->addAction(actionDim);
        menu_4->addAction(actionOutput);

        retranslateUi(PointCloudDimClass);

        QMetaObject::connectSlotsByName(PointCloudDimClass);
    } // setupUi

    void retranslateUi(QMainWindow *PointCloudDimClass)
    {
        PointCloudDimClass->setWindowTitle(QApplication::translate("PointCloudDimClass", "\347\202\271\344\272\221\345\260\272\345\257\270\350\207\252\345\212\250\346\265\213\351\207\217", Q_NULLPTR));
        actionImportSource->setText(QApplication::translate("PointCloudDimClass", "\345\257\274\345\205\245\346\272\220\347\202\271\344\272\221", Q_NULLPTR));
        actionImportTarget->setText(QApplication::translate("PointCloudDimClass", "\345\257\274\345\205\245\347\233\256\346\240\207\347\202\271\344\272\221", Q_NULLPTR));
        actionDimInfo->setText(QApplication::translate("PointCloudDimClass", "\345\257\274\345\205\245\345\260\272\345\257\270\344\277\241\346\201\257", Q_NULLPTR));
        actionClose->setText(QApplication::translate("PointCloudDimClass", "\345\205\263\351\227\255", Q_NULLPTR));
        actiond_5->setText(QApplication::translate("PointCloudDimClass", "d", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("PointCloudDimClass", "\344\275\277\347\224\250\350\257\264\346\230\216", Q_NULLPTR));
        actionFPFHCalculate->setText(QApplication::translate("PointCloudDimClass", "\350\256\241\347\256\227FPFH", Q_NULLPTR));
        actionRegister->setText(QApplication::translate("PointCloudDimClass", "\351\205\215\345\207\206", Q_NULLPTR));
        actionDim->setText(QApplication::translate("PointCloudDimClass", "\345\260\272\345\257\270\346\265\213\351\207\217", Q_NULLPTR));
        actionOutput->setText(QApplication::translate("PointCloudDimClass", "\347\273\223\346\236\234\345\257\274\345\207\272", Q_NULLPTR));
        actionMaximized->setText(QApplication::translate("PointCloudDimClass", "\346\234\200\345\244\247\345\214\226", Q_NULLPTR));
        actionMinimized->setText(QApplication::translate("PointCloudDimClass", "\346\234\200\345\260\217\345\214\226", Q_NULLPTR));
        actionImportCAD->setText(QApplication::translate("PointCloudDimClass", "\345\257\274\345\205\245CAD\346\250\241\345\236\213", Q_NULLPTR));
        actionNormal->setText(QApplication::translate("PointCloudDimClass", "\350\277\230\345\216\237", Q_NULLPTR));
        actionSampling->setText(QApplication::translate("PointCloudDimClass", "\351\207\207\346\240\267", Q_NULLPTR));
        action_change_dir->setText(QApplication::translate("PointCloudDimClass", "\345\210\207\346\215\242\345\267\245\344\275\234\347\233\256\345\275\225", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("PointCloudDimClass", "\350\256\241\347\256\227FPFH\345\217\212\351\205\215\345\207\206", Q_NULLPTR));
        label->setText(QApplication::translate("PointCloudDimClass", "VoxelGrid\346\273\244\346\263\242\345\231\250\344\275\223\347\264\240", Q_NULLPTR));
        label_2->setText(QApplication::translate("PointCloudDimClass", "\350\256\241\347\256\227\346\263\225\347\272\277\345\215\212\345\276\204", Q_NULLPTR));
        label_3->setText(QApplication::translate("PointCloudDimClass", "\350\256\241\347\256\227FPFH\345\215\212\345\276\204", Q_NULLPTR));
        pushButtonFPFHCalculate->setText(QApplication::translate("PointCloudDimClass", "\350\256\241\347\256\227", Q_NULLPTR));
        pushButtonRegister->setText(QApplication::translate("PointCloudDimClass", "\351\205\215\345\207\206", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PointCloudDimClass", "\345\260\272\345\257\270\346\265\213\351\207\217", Q_NULLPTR));
        pushButtonDim->setText(QApplication::translate("PointCloudDimClass", "\345\260\272\345\257\270\346\265\213\351\207\217", Q_NULLPTR));
        pushButtonOutput->setText(QApplication::translate("PointCloudDimClass", "\347\273\223\346\236\234\345\257\274\345\207\272", Q_NULLPTR));
        label_4->setText(QApplication::translate("PointCloudDimClass", "\345\271\263\351\235\242\346\217\220\345\217\226gap", Q_NULLPTR));
        label_6->setText(QApplication::translate("PointCloudDimClass", "\350\277\221\351\202\273\347\202\271\344\270\252\346\225\260", Q_NULLPTR));
        label_5->setText(QApplication::translate("PointCloudDimClass", "\345\234\206\346\237\261\351\235\242\346\217\220\345\217\226gap     ", Q_NULLPTR));
        label_7->setText(QApplication::translate("PointCloudDimClass", "\346\234\200\345\244\247\350\277\255\344\273\243\346\254\241\346\225\260", Q_NULLPTR));
        label_8->setText(QApplication::translate("PointCloudDimClass", "\346\263\225\347\272\277\346\235\203\351\207\215", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("PointCloudDimClass", "\346\265\213\351\207\217\347\273\223\346\236\234\345\217\212\350\257\257\345\267\256", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("PointCloudDimClass", "\345\244\204\347\220\206\347\212\266\346\200\201\346\230\276\347\244\272", Q_NULLPTR));
        menu->setTitle(QApplication::translate("PointCloudDimClass", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("PointCloudDimClass", "\345\270\256\345\212\251", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("PointCloudDimClass", "\347\252\227\345\217\243", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("PointCloudDimClass", "\347\274\226\350\276\221", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PointCloudDimClass: public Ui_PointCloudDimClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTCLOUDDIM_H
