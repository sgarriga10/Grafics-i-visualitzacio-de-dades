/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_phong;
    QAction *action_gouraud;
    QAction *action_toon;
    QAction *action_obre_fitxer;
    QAction *action_gouraud_tex;
    QAction *action_phong_tex;
    QAction *action_bump_mapping;
    QAction *action_environmental_mapping;
    QAction *action_afegeix_llum_puntual;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuModels;
    QMenu *menuShaders;
    QMenu *menuTextures;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(533, 451);
        action_phong = new QAction(MainWindow);
        action_phong->setObjectName(QStringLiteral("action_phong"));
        action_gouraud = new QAction(MainWindow);
        action_gouraud->setObjectName(QStringLiteral("action_gouraud"));
        action_toon = new QAction(MainWindow);
        action_toon->setObjectName(QStringLiteral("action_toon"));
        action_obre_fitxer = new QAction(MainWindow);
        action_obre_fitxer->setObjectName(QStringLiteral("action_obre_fitxer"));
        action_gouraud_tex = new QAction(MainWindow);
        action_gouraud_tex->setObjectName(QStringLiteral("action_gouraud_tex"));
        action_phong_tex = new QAction(MainWindow);
        action_phong_tex->setObjectName(QStringLiteral("action_phong_tex"));
        action_bump_mapping = new QAction(MainWindow);
        action_bump_mapping->setObjectName(QStringLiteral("action_bump_mapping"));
        action_environmental_mapping = new QAction(MainWindow);
        action_environmental_mapping->setObjectName(QStringLiteral("action_environmental_mapping"));
        action_afegeix_llum_puntual = new QAction(MainWindow);
        action_afegeix_llum_puntual->setObjectName(QStringLiteral("action_afegeix_llum_puntual"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 533, 22));
        menuModels = new QMenu(menuBar);
        menuModels->setObjectName(QStringLiteral("menuModels"));
        menuShaders = new QMenu(menuBar);
        menuShaders->setObjectName(QStringLiteral("menuShaders"));
        menuTextures = new QMenu(menuBar);
        menuTextures->setObjectName(QStringLiteral("menuTextures"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuModels->menuAction());
        menuBar->addAction(menuShaders->menuAction());
        menuBar->addAction(menuTextures->menuAction());
        menuModels->addAction(action_obre_fitxer);
        menuModels->addSeparator();
        menuModels->addAction(action_afegeix_llum_puntual);
        menuShaders->addAction(action_gouraud);
        menuShaders->addAction(action_phong);
        menuShaders->addAction(action_toon);
        menuTextures->addAction(action_gouraud_tex);
        menuTextures->addAction(action_phong_tex);
        menuTextures->addAction(action_bump_mapping);
        menuTextures->addAction(action_environmental_mapping);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_phong->setText(QApplication::translate("MainWindow", "Phong Shader", 0));
#ifndef QT_NO_TOOLTIP
        action_phong->setToolTip(QApplication::translate("MainWindow", "Activar Phong Shader", 0));
#endif // QT_NO_TOOLTIP
        action_phong->setShortcut(QApplication::translate("MainWindow", "Alt+2", 0));
        action_gouraud->setText(QApplication::translate("MainWindow", "Gouraud Shader", 0));
#ifndef QT_NO_TOOLTIP
        action_gouraud->setToolTip(QApplication::translate("MainWindow", "Activar Gouraud Shader", 0));
#endif // QT_NO_TOOLTIP
        action_gouraud->setShortcut(QApplication::translate("MainWindow", "Alt+1", 0));
        action_toon->setText(QApplication::translate("MainWindow", "Toon Shader", 0));
#ifndef QT_NO_TOOLTIP
        action_toon->setToolTip(QApplication::translate("MainWindow", "Activar Toon Shader", 0));
#endif // QT_NO_TOOLTIP
        action_toon->setShortcut(QApplication::translate("MainWindow", "Alt+3", 0));
        action_obre_fitxer->setText(QApplication::translate("MainWindow", "Obre Fitxer .obj", 0));
#ifndef QT_NO_TOOLTIP
        action_obre_fitxer->setToolTip(QApplication::translate("MainWindow", "Obre Fitxer .obj", 0));
#endif // QT_NO_TOOLTIP
        action_obre_fitxer->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0));
        action_gouraud_tex->setText(QApplication::translate("MainWindow", "GouraudTex", 0));
        action_gouraud_tex->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0));
        action_phong_tex->setText(QApplication::translate("MainWindow", "PhongTex", 0));
        action_phong_tex->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0));
        action_bump_mapping->setText(QApplication::translate("MainWindow", "Bump-mapping", 0));
        action_bump_mapping->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", 0));
        action_environmental_mapping->setText(QApplication::translate("MainWindow", "Environmental-mapping", 0));
        action_environmental_mapping->setShortcut(QApplication::translate("MainWindow", "Ctrl+4", 0));
        action_afegeix_llum_puntual->setText(QApplication::translate("MainWindow", "Llum Actual", 0));
        menuModels->setTitle(QApplication::translate("MainWindow", "Models", 0));
        menuShaders->setTitle(QApplication::translate("MainWindow", "Shaders", 0));
        menuTextures->setTitle(QApplication::translate("MainWindow", "Textures", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
