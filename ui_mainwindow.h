/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 15 22:26:53 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QGridLayout *gridLayout;
    QPushButton *open_file_b;
    QPushButton *open_folder_b;
    QPushButton *move_up_b;
    QPushButton *move_down_b;
    QPushButton *show_song_info_b;
    QPushButton *remove_selected_b;
    QPushButton *open_in_player_b;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(0, 0));
        listView->setWordWrap(true);

        horizontalLayout->addWidget(listView);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        open_file_b = new QPushButton(centralWidget);
        open_file_b->setObjectName(QString::fromUtf8("open_file_b"));
        open_file_b->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(open_file_b, 0, 0, 1, 1);

        open_folder_b = new QPushButton(centralWidget);
        open_folder_b->setObjectName(QString::fromUtf8("open_folder_b"));
        open_folder_b->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(open_folder_b, 0, 1, 1, 1);

        move_up_b = new QPushButton(centralWidget);
        move_up_b->setObjectName(QString::fromUtf8("move_up_b"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(move_up_b->sizePolicy().hasHeightForWidth());
        move_up_b->setSizePolicy(sizePolicy);
        move_up_b->setMinimumSize(QSize(50, 50));
        move_up_b->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(move_up_b, 1, 0, 1, 1);

        move_down_b = new QPushButton(centralWidget);
        move_down_b->setObjectName(QString::fromUtf8("move_down_b"));
        move_down_b->setEnabled(true);
        move_down_b->setMinimumSize(QSize(50, 50));
        move_down_b->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(move_down_b, 1, 1, 1, 1);

        show_song_info_b = new QPushButton(centralWidget);
        show_song_info_b->setObjectName(QString::fromUtf8("show_song_info_b"));
        show_song_info_b->setEnabled(true);
        show_song_info_b->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(show_song_info_b, 2, 0, 1, 1);

        remove_selected_b = new QPushButton(centralWidget);
        remove_selected_b->setObjectName(QString::fromUtf8("remove_selected_b"));
        remove_selected_b->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(remove_selected_b, 2, 1, 1, 1);

        open_in_player_b = new QPushButton(centralWidget);
        open_in_player_b->setObjectName(QString::fromUtf8("open_in_player_b"));
        open_in_player_b->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(open_in_player_b, 3, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(true);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TLPlaylistCreator", 0, QApplication::UnicodeUTF8));
        open_file_b->setText(QString());
        open_folder_b->setText(QString());
        move_up_b->setText(QString());
        move_down_b->setText(QString());
        show_song_info_b->setText(QString());
        remove_selected_b->setText(QString());
        open_in_player_b->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
