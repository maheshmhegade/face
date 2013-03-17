/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Mar 17 23:16:14 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *controlLO;
    QPushButton *capturePB;
    QPushButton *faceDetectPB;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *faceOneLO;
    QGraphicsView *faceOneGV;
    QLineEdit *lineEdit;
    QPushButton *saveFaceOnePB;
    QVBoxLayout *faceTwoLO;
    QGraphicsView *faceTwoGV;
    QLineEdit *lineEdit_2;
    QPushButton *saveFaceTwoPB;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(669, 329);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        controlLO = new QVBoxLayout();
        controlLO->setSpacing(6);
        controlLO->setObjectName(QString::fromUtf8("controlLO"));
        capturePB = new QPushButton(centralWidget);
        capturePB->setObjectName(QString::fromUtf8("capturePB"));

        controlLO->addWidget(capturePB);

        faceDetectPB = new QPushButton(centralWidget);
        faceDetectPB->setObjectName(QString::fromUtf8("faceDetectPB"));

        controlLO->addWidget(faceDetectPB);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        controlLO->addWidget(pushButton_5);


        verticalLayout_2->addLayout(controlLO);

        verticalSpacer = new QSpacerItem(128, 128, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        faceOneLO = new QVBoxLayout();
        faceOneLO->setSpacing(6);
        faceOneLO->setObjectName(QString::fromUtf8("faceOneLO"));
        faceOneGV = new QGraphicsView(centralWidget);
        faceOneGV->setObjectName(QString::fromUtf8("faceOneGV"));

        faceOneLO->addWidget(faceOneGV);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        faceOneLO->addWidget(lineEdit);

        saveFaceOnePB = new QPushButton(centralWidget);
        saveFaceOnePB->setObjectName(QString::fromUtf8("saveFaceOnePB"));

        faceOneLO->addWidget(saveFaceOnePB);


        horizontalLayout->addLayout(faceOneLO);

        faceTwoLO = new QVBoxLayout();
        faceTwoLO->setSpacing(6);
        faceTwoLO->setObjectName(QString::fromUtf8("faceTwoLO"));
        faceTwoGV = new QGraphicsView(centralWidget);
        faceTwoGV->setObjectName(QString::fromUtf8("faceTwoGV"));

        faceTwoLO->addWidget(faceTwoGV);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        faceTwoLO->addWidget(lineEdit_2);

        saveFaceTwoPB = new QPushButton(centralWidget);
        saveFaceTwoPB->setObjectName(QString::fromUtf8("saveFaceTwoPB"));

        faceTwoLO->addWidget(saveFaceTwoPB);


        horizontalLayout->addLayout(faceTwoLO);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 669, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        capturePB->setText(QApplication::translate("MainWindow", "Start/Stop Capture", 0, QApplication::UnicodeUTF8));
        faceDetectPB->setText(QApplication::translate("MainWindow", "Detect Face", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "Show LIve", 0, QApplication::UnicodeUTF8));
        saveFaceOnePB->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        saveFaceTwoPB->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
