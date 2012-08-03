#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QSizePolicy>
#include <QStatusBar>
#include <QStringListModel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include <iostream>

class Popup1 : public QDialog
{
    Q_OBJECT
public:
    Popup1(QString window_title,
           QString data1,
           QString data2,
           QString b1_title,
           QString b2_title); // constructor
    ~Popup1(); // destructor
    QPushButton *b1, *b2;
private:
    QLabel *data1_l, *data2_l;
    //QTextEdit *contents;
    //QScrollArea *data2_scroll;
};

class Popup2 : public QDialog
{
    Q_OBJECT
public:
    Popup2(QString window_title,
           QString data,
           QString b1_title,
           QString b2_title); // constructor
    ~Popup2(); // destructor
    QPushButton *b1, *b2;
private:
    QLabel *data_l;
};

class Popup3 : public QDialog
{
    Q_OBJECT
public:
    Popup3(QString window_title,
           QString data,
           QString b_title); // constructor
    ~Popup3(); // destructor
    QPushButton *b;
private:
    QLabel *data_l;
};

/*
  used by the updating playlist and the changing display method functions
  */
class Popup4 : public QDialog
{
    Q_OBJECT
public:
    Popup4(QString window_title,
           QString instruction,
           QString b_name,
           QStringList *status_sl,
           QStringList *lview_sl,
           int *selected_index); // constructor
    ~Popup4();
    QPushButton *b;
private:
    int *selected_index; // duplicate pointer
    QLabel *instruction_l;
    QStringList *status_sl; // duplicate pointer
    QStringListModel *lview_slm;
    QListView *lview;
    QStatusBar *dir_view;
private slots:
    void get_index_then_close();
    void show_dir();
};

class Popup_change_display_method : public QDialog
{
    Q_OBJECT
public:
    Popup_change_display_method(int *selected_index); // constructor
private:
    int *selected_index; // duplicate pointer
    QPushButton *b_filename_no_ext, *b_filename, *b_dir, *b_tag;
};

#endif // POPUP_H
