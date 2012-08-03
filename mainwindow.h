#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QAction>
#include <QCheckBox>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QItemSelectionModel>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndex>
#include <QProcess>
#include <QSize>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QStringListModel>
#include <QTextStream>
#include <QTime>
#include <QVBoxLayout>

#include <iostream>
#include <fstream>
#include <list>

namespace Ui {
    class MainWindow;
}


class StringListGroup
{
public:
    QStringList *dir_sl;
    QStringList *display_sl;
    QStringList *filename_sl;
    QStringList *format_sl;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //StringListGroup* sort(StringListGroup *list);

private slots:

    void activate_deactivate_move_buttons();
    void change_display_method();
    void check_existence();
    void clear();
    void move_down();
    void move_up();
    void open_in_player();
    void open_playlist_file();
    void open_playlist_file_helper();
    void open_playlist_file_helper_clear_first();
    void open_song_file();
    void open_song_files();
    void open_song_folder();
    void remove_bad_entries();
    void remove_duplicate_entries();
    void remove_selected();
    void run_sort();
    void save_playlist();
    void save_playlist_new();
    void save_playlist_update();
    void show_about_window();
    void show_quickinfo();
    void show_song_information();
    void test();

private:
    Ui::MainWindow *ui;
    enum Display_Method { FILENAME_NO_EXT, FILENAME, DIRECTORY, TAG };

    QAction *open_playlist_a, *save, *check_existence_a, *sort_a, *clear_all, *change_display_method_a, *about_program, *about_qt;
    QAction *test_a;

    QKeyEvent *listView_ke;

    QStringList *filename_no_ext_sl;
    QStringList *filename_sl;
    QStringList *dir_sl;
    QStringList *format_sl;

    Display_Method display_method;
    QStringList *display_method_select_sl;
    QStringList *display_method_example_sl;

    QStringListModel *display_slm;

    int num_opened_playlists;
    QStringList *playlist_dir_sl;
    QStringList *playlist_filename_sl;

    //int num_songs;
    QList<int> bad_entries, indexes_of_duplicates;
    QString playlist_dir;

    QProcess *player_process;

    QString version;

    // called by the constructor to initialize values
    void init_media_data();
    void init_menu_items();
    void init_button_icons();
    void init_signals_and_slots();


    bool extension_ok(QString dir);
    bool is_extended_data(QString line);
    int get_median_index(QString ***p_array, int compare_row, int a, int b, int c);
    void check_duplicate_entries();
    QString extract_extension(QString dir);
    QString remove_extension(QString file_name);
    QString trim_directory(QString dir);
    std::string run_ReadTag(QString dir);
    void add_list_entry(QString dir);    
    void refresh_view();
    void remove_entry(int row);
    void sort(QString ***p_array, int left_index, int right_index);
    void write_to_playlist(QString dir);
    void show_num_songs();
};

#endif // MAINWINDOW_H
