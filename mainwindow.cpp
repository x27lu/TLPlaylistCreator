#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "popup.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    version = "2012-08-02";

    ui->setupUi(this);

    // initialize the lists and song count
    init_media_data();

    // add actions to menu
    init_menu_items();

    // initialize buttons icons
    init_button_icons();

    // connect signals and slots
    init_signals_and_slots();

    player_process = NULL;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_media_data()
{
    // for storing directories
    dir_sl = new QStringList();

    // for storing filenames
    filename_sl = new QStringList();

    // for storing formats
    format_sl = new QStringList();

    // for displaying files (some formatting)
    filename_no_ext_sl = new QStringList();
    display_slm = new QStringListModel();
    display_slm->setStringList(*filename_no_ext_sl);

    //ui->listView->setModel(display_slm);
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    ui->listView->setModel(display_slm);

    ui->listView->installEventFilter(this);

    num_opened_playlists = 0;
    // for storing playlist directories
    playlist_dir_sl = new QStringList();
    // for storing playlist filenames
    playlist_filename_sl = new QStringList();


    display_method = FILENAME_NO_EXT;
    display_method_select_sl = new QStringList();
    display_method_example_sl = new QStringList();

    display_method_select_sl->append("Filenames with no extensions");
    display_method_example_sl->append("'song1'");
    display_method_select_sl->append("Filenames with extensions");
    display_method_example_sl->append("'song1.mp3'");
    display_method_select_sl->append("Full directories");
    display_method_example_sl->append("'/media/mmc1/Music/song1.mp3'");
    display_method_select_sl->append("Audio tag data");
    display_method_example_sl->append("'artist1 - title1'");
}

void MainWindow::init_menu_items()
{
    test_a = new QAction(tr("Test"), this);
    //ui->menuBar->addAction(test_a);

    open_playlist_a = new QAction(tr("Open Playlist"), this);
    ui->menuBar->addAction(open_playlist_a);

    save = new QAction(tr("Save Playlist"), this);
    ui->menuBar->addAction(save);

    check_existence_a = new QAction(tr("Check File Existence"), this);
    ui->menuBar->addAction(check_existence_a);

    sort_a = new QAction(tr("Sort"), this);
    ui->menuBar->addAction(sort_a);

    clear_all = new QAction(tr("Clear All"), this);
    ui->menuBar->addAction(clear_all);

    change_display_method_a = new QAction(tr("Change Display Method"), this);
    ui->menuBar->addAction(change_display_method_a);

    about_program = new QAction(tr("About TLPlaylistCreator"), this);
    ui->menuBar->addAction(about_program);

    about_qt = new QAction(tr("About Qt"), this);
    ui->menuBar->addAction(about_qt);

    // initial status message
    ui->statusBar->showMessage("Welcome!");

}

void MainWindow::init_button_icons()
{
    QIcon newfile_icon;
    newfile_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/open-music-file-64x64.png"));
    ui->open_file_b->setIcon(newfile_icon);
    //ui->open_file_b->setIconSize(QSize(32, 32));

    QIcon newfolder_icon;
    newfolder_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/open-music-folder-64x64.png"));
    ui->open_folder_b->setIcon(newfolder_icon);
    //ui->open_folder_b->setIconSize(QSize(32, 32));

    QIcon up_icon;
    up_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/up-arrow-64x64.png"));
                      //QIcon::Normal, QIcon::Off);
    ui->move_up_b->setIcon(up_icon);
    //ui->move_up_b->setIconSize(QSize(32, 32));

    QIcon down_icon;
    down_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/down-arrow-64x64.png"));
                        //QIcon::Normal, QIcon::Off);
    ui->move_down_b->setIcon(down_icon);
    //ui->move_down_b->setIconSize(QSize(32, 32));

    QIcon songinfo_icon;
    songinfo_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/song-info-64x64.png"));
    ui->show_song_info_b->setIcon(songinfo_icon);

    QIcon remove_icon;
    remove_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/remove-64x64.png"));
    ui->remove_selected_b->setIcon(remove_icon);

    QIcon open_in_player_icon;
    open_in_player_icon.addPixmap(QPixmap("/usr/share/tl-playlist-creator/play-playlist-64x64.png"));
    ui->open_in_player_b->setIcon(open_in_player_icon);
}

void MainWindow::init_signals_and_slots()
{
    connect(ui->open_file_b, SIGNAL(clicked()), this, SLOT(open_song_files()));
    connect(ui->open_folder_b, SIGNAL(clicked()), this, SLOT(open_song_folder()));
    connect(ui->move_up_b, SIGNAL(clicked()), this, SLOT(move_up()));
    connect(ui->move_down_b, SIGNAL(clicked()), this, SLOT(move_down()));
    connect(ui->show_song_info_b, SIGNAL(clicked()), this, SLOT(show_song_information()));
    connect(ui->remove_selected_b, SIGNAL(clicked()), this, SLOT(remove_selected()));
    connect(ui->open_in_player_b, SIGNAL(clicked()), this, SLOT(open_in_player()));

    connect(test_a, SIGNAL(triggered()), this, SLOT(test()));
    connect(open_playlist_a, SIGNAL(triggered()), this, SLOT(open_playlist_file()));
    connect(save, SIGNAL(triggered()), this, SLOT(save_playlist()));
    connect(check_existence_a, SIGNAL(triggered()), this, SLOT(check_existence()));
    connect(sort_a, SIGNAL(triggered()), this, SLOT(run_sort()));
    connect(clear_all, SIGNAL(triggered()), this, SLOT(clear()));
    connect(change_display_method_a, SIGNAL(triggered()), this, SLOT(change_display_method()));
    connect(about_program, SIGNAL(triggered()), this, SLOT(show_about_window()));
    connect(about_qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(show_quickinfo()));
    //connect(ui->listView, SIGNAL()
    //connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(activate_deactivate_move_buttons()));
    //connect(ui->listView, SIGNAL(indexesMoved(QModelIndexList)), this, SLOT(show_quickinfo()));
    //connect(song_info_window_close, SIGNAL(clicked()), this, SLOT(close_song_information()));
}

bool MainWindow::extension_ok(QString dir)
{
    return ((dir.right(4)).compare(".m3u", Qt::CaseInsensitive) == 0);
}

bool MainWindow::is_extended_data(QString line)
{
    // can't possibly contain #EXTM3U nor #EXTINF
    if (line.length() < 7) {
        return false;
    }
    else {
        if (line.left(7) == "#EXTM3U")
            return true;
        else if (line.left(7) == "#EXTINF")
            return true;
        else
            return false;
    }
}

string MainWindow::run_ReadTag(QString dir)
{
    cout << "aha0 " << dir.toStdString() << endl;

    dir.replace(" ", "\\ ");
    dir.replace("'", "\\'");
    dir.replace("&", "\\&");
    //cout << dir.toStdString() << endl;

    QString command = "./ReadTag file://";
    command.append(dir);

    cout << "aha1 " << command.toStdString() << endl;
    FILE* pipe = popen(command.toStdString().c_str(), "r");

    if (!pipe) return "[ERROR]";

    string output = "";

    char buffer[128];

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            output += buffer;
    }

    pclose(pipe);
    return output;
}



/*
  input: the filename containing the extension, or an absolute directory, e.g.
         "song.mp3", "/home/user/song.mp3"
  output: the extension, in all uppercase characters, e.g. "MP3"
  */
QString MainWindow::extract_extension(QString dir)
{
    int loc_dot = dir.lastIndexOf(".");
    return (dir.right(dir.length() - loc_dot - 1)).toUpper();
}

/*
  input: the filename containing the extension, e.g. "song.mp3"
  output: the filename without the extension, e.g. "song"
  */
QString MainWindow::remove_extension(QString file_name)
{
    int loc_dot = file_name.lastIndexOf(".");
    return file_name.left(loc_dot);
}

/*
  input: an absolute directory, e.g. "/home/user/list.m3u"
  output: the filename of the playlist, e.g. "list.m3u"
  */
QString MainWindow::trim_directory(QString dir)
{
    int loc_last_slash = dir.lastIndexOf("/");
    return dir.right(dir.length() - loc_last_slash - 1);
}

/*
StringListGroup* MainWindow::sort(StringListGroup* list)
{
    int sl_length = list->dir_sl->length();

    if (sl_length <= 1)
        return list;

    //QString pivot = list->filename_sl->at(0);
    QString first_dir = list->dir_sl->at(0);
    QString first_display = list->filename_no_ext_sl->at(0);
    QString first_filename = list->filename_sl->at(0);
    QString first_format = list->format_sl->at(0);

    StringListGroup *slg_left = new StringListGroup();
    slg_left->dir_sl = new QStringList();
    slg_left->filename_no_ext_sl = new QStringList();
    slg_left->filename_sl = new QStringList();
    slg_left->format_sl = new QStringList();
    StringListGroup *slg_right = new StringListGroup();
    slg_right->dir_sl = new QStringList();
    slg_right->filename_no_ext_sl = new QStringList();
    slg_right->filename_sl = new QStringList();
    slg_right->format_sl = new QStringList();

    QString cur_filename;
    for (int i = 1; i < sl_length; i++) {
        cur_filename = list->filename_sl->at(i);
        if (QString::compare(cur_filename, first_filename, Qt::CaseInsensitive) <= 0) {
            slg_left->dir_sl->append(list->dir_sl->at(i));
            slg_left->filename_no_ext_sl->append(list->filename_no_ext_sl->at(i));
            slg_left->filename_sl->append(cur_filename);
            slg_left->format_sl->append(list->format_sl->at(i));
        }
        else {
            slg_right->dir_sl->append(list->dir_sl->at(i));
            slg_right->filename_no_ext_sl->append(list->filename_no_ext_sl->at(i));
            slg_right->filename_sl->append(cur_filename);
            slg_right->format_sl->append(list->format_sl->at(i));
        }
    }

    slg_left = sort(slg_left);
    slg_right = sort(slg_right);

    list->dir_sl->clear();
    list->filename_no_ext_sl->clear();
    list->filename_sl->clear();
    list->format_sl->clear();

    // append list set containing alphabetically higher filenames
    list->dir_sl->append(*(slg_left->dir_sl));
    list->filename_no_ext_sl->append(*(slg_left->filename_no_ext_sl));
    list->filename_sl->append(*(slg_left->filename_sl));
    list->format_sl->append(*(slg_left->format_sl));

    // append the elements at the pivot
    list->dir_sl->append(first_dir);
    list->filename_no_ext_sl->append(first_display);
    list->filename_sl->append(first_filename);
    list->format_sl->append(first_format);

    // append list set containing alphabetically lower filenames
    list->dir_sl->append(*(slg_right->dir_sl));
    list->filename_no_ext_sl->append(*(slg_right->filename_no_ext_sl));
    list->filename_sl->append(*(slg_right->filename_sl));
    list->format_sl->append(*(slg_right->format_sl));

    delete slg_left->dir_sl;
    delete slg_left->filename_no_ext_sl;
    delete slg_left->filename_sl;
    delete slg_left->format_sl;

    delete slg_right->dir_sl;
    delete slg_right->filename_no_ext_sl;
    delete slg_right->filename_sl;
    delete slg_right->format_sl;

    delete slg_left;
    delete slg_right;

    return list;
}
*/

void MainWindow::add_list_entry(QString dir)
{
    // complete directory is added to the directory list
    dir_sl->append(dir);

    // file name (with extension) is added to the filename list
    QString view_entry = trim_directory(dir);
    filename_sl->append(view_entry);

    // format directory is added to the format list
    format_sl->append(extract_extension(dir));

    // file name (without extension) is added to the display list
    view_entry = remove_extension(view_entry);
    filename_no_ext_sl->append(view_entry);
}

void MainWindow::refresh_view()
{
    switch (display_method)
    {
    case FILENAME_NO_EXT:
        display_slm->setStringList(*filename_no_ext_sl);
        break;
    case FILENAME:
        display_slm->setStringList(*filename_sl);
        break;
    case DIRECTORY:
        display_slm->setStringList(*dir_sl);
        break;
    case TAG:
        //
        break;
    }
    ui->listView->update();
}



void MainWindow::remove_entry(int row)
{
    dir_sl->removeAt(row);
    filename_sl->removeAt(row);
    format_sl->removeAt(row);
    filename_no_ext_sl->removeAt(row);
}

void MainWindow::show_num_songs()
{
    QString msg = QString::number(dir_sl->length());
    msg.append(" songs in total");
    ui->statusBar->showMessage(msg);
}

// slot functions

void MainWindow::activate_deactivate_move_buttons()
{
    int selected_index = ui->listView->currentIndex().row();
    int list_length = dir_sl->length();

    bool up_disabled = false;
    bool down_disabled = false;

    if (selected_index >= 0) {
        if (selected_index == 0)
            up_disabled = true;
        if (selected_index == list_length - 1)
            down_disabled = true;
        ui->move_up_b->setDisabled(up_disabled);
        ui->move_down_b->setDisabled(down_disabled);
    }
}

void MainWindow::change_display_method()
{
    int *selected_index = new int;
    *selected_index = display_method - FILENAME_NO_EXT;

    Popup4 p("Display Method", "Select the method used to display the entries", "Change",
             display_method_example_sl, display_method_select_sl, selected_index);
    p.exec();

    cout << "Selected display method #: " << *selected_index << endl;
    // we can't cast from int to enum
    switch(*selected_index)
    {
    case 0:
        display_method = FILENAME_NO_EXT;
        break;
    case 1:
        display_method = FILENAME;
        break;
    case 2:
        display_method = DIRECTORY;
        break;
    case 3:
        display_method = TAG;
        break;
    default:
        cout << "ERROR: unhandled case for selected_index in change_display_method" << endl;
    }
    delete selected_index;

    refresh_view();
}

void MainWindow::check_existence()
{
    bad_entries.clear(); // initialize

    for (int i = 0; i < dir_sl->length(); i++) {
        QFile file(dir_sl->at(i));
        if (!file.exists()) {
            cout << "entry " << i << " does not exist" << endl;
            bad_entries.append(i);
        }
    }

    int num_bad_entries = bad_entries.length();

    if (num_bad_entries == 0) {
        cout << "all entries exist" << endl;

        QMessageBox all_ok;

        QString all_ok_contents;
        all_ok.setWindowTitle("Results");
        all_ok_contents = "All entries exist";
        all_ok.setText(all_ok_contents);

        all_ok.exec();
    }
    else {
        cout << "not all entries exist" << endl;

        QString desc = "The following ";
        desc.append(QString::number(num_bad_entries));
        desc.append(" entries do not exist, would you like to remove them?\n");

        QString songs;
        for (int i = 0; i < num_bad_entries; i++) {
            songs.append("[");
            songs.append(QString::number(bad_entries.at(i) + 1));
            songs.append("/");
            songs.append(QString::number(dir_sl->length()));
            songs.append("]:\n");
            songs.append(dir_sl->at(bad_entries.at(i)));
            songs.append("\n\n");
        }

        Popup1 some_wrong("Results", desc, songs, "Remove", "Keep");
        connect(some_wrong.b1, SIGNAL(clicked()), this, SLOT(remove_bad_entries()));
        some_wrong.exec();
        refresh_view();
        show_num_songs();
    }

}

void MainWindow::clear()
{
    dir_sl->clear();
    filename_sl->clear();
    format_sl->clear();
    filename_no_ext_sl->clear();

    /*delete dir_sl;
    dir_sl = new QStringList();
    delete filename_sl;
    filename_sl = new QStringList();
    delete format_sl;
    format_sl = new QStringList();
    delete filename_no_ext_sl;
    filename_no_ext_sl = new QStringList();*/


    refresh_view();
    show_num_songs();
}

void MainWindow::move_down()
{
    int selected_index = ui->listView->currentIndex().row();
    // if there is something selected and it's not the last
    if (selected_index >= 0 && selected_index < dir_sl->length() - 1) {
        dir_sl->swap(selected_index, selected_index + 1);
        filename_sl->swap(selected_index, selected_index + 1);
        format_sl->swap(selected_index, selected_index + 1);
        filename_no_ext_sl->swap(selected_index, selected_index + 1);
        refresh_view();
        QModelIndex new_index = display_slm->index(selected_index + 1);
        ui->listView->setCurrentIndex(new_index); // set index
        show_quickinfo(); // display info about selected song in status bar
    }
}

void MainWindow::move_up()
{
    int selected_index = ui->listView->currentIndex().row();
    // if there is something selected and it's not the first
    if (selected_index > 0) {
        dir_sl->swap(selected_index, selected_index - 1);
        filename_sl->swap(selected_index, selected_index - 1);
        format_sl->swap(selected_index, selected_index - 1);
        filename_no_ext_sl->swap(selected_index, selected_index - 1);
        refresh_view();
        QModelIndex new_index = display_slm->index(selected_index - 1);
        ui->listView->setCurrentIndex(new_index); // set index
        show_quickinfo(); // display info about selected song in status bar
    }
}

void MainWindow::open_in_player()
{
    //write_to_playlist("/usr/share/tl-playlist-creator/.temp.m3u");
    write_to_playlist("/home/user/.temp.m3u");
    cout << "Created temporary playlist" << endl;

    QString command = "dbus-send --print-reply --dest=com.nokia.mediaplayer "
                      "/com/nokia/mediaplayer com.nokia.mediaplayer.mime_open "
                      //"string:file:///usr/share/tl-playlist-creator/.temp.m3u";
                      "string:file:///home/user/.temp.m3u";
    //command = "vlc /usr/share/tl-playlist-creator/.temp.m3u";

    if (player_process == NULL)
        player_process = new QProcess();
    else
        player_process->close();

    cout << "Starting media player" << endl;
    player_process->start(command);
}

void MainWindow::open_playlist_file()
{
    playlist_dir = QFileDialog::getOpenFileName(this,
                                                tr("Select playlist"),
                                                "/",
                                                tr("M3U Playlist(*.m3u)"));

    cout << "Open playlist: " << playlist_dir.toStdString() << endl;

    // if user did indeed select a file
    if (playlist_dir != "") {

        // only ask if user wants to keep existing songs if he/she had added any
        // otherwise there is no point in asking
        if (dir_sl->length() > 0) {
            QString options_contents = "Do you want to remove what you already have, or "
                                       "just append the contents of this playlist?";
            Popup2 options("Select option", options_contents, "Remove", "Append");
            connect(options.b1, SIGNAL(clicked()), this, SLOT(open_playlist_file_helper_clear_first()));
            connect(options.b2, SIGNAL(clicked()), this, SLOT(open_playlist_file_helper()));
            options.exec();
        }
        else {
            open_playlist_file_helper();
        }

    }
}

void MainWindow::open_playlist_file_helper()
{
    QFile file(playlist_dir);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "ERROR: cannot open file in read mode" << endl;
        ui->statusBar->showMessage("CANNOT OPEN! (file could not be read)");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = (in.readLine()).trimmed();
        // not an empty line
        if (line != "") {
            // ignore extended M3U directives like #EXTM3U and #EXTINF
            if (!is_extended_data(line)) {
                add_list_entry(line);
            }
        }
    } // end while

    file.close();

    refresh_view();
    check_existence();
    check_duplicate_entries();
    show_num_songs();

    if (playlist_dir_sl->indexOf(playlist_dir)) {
        playlist_dir_sl->append(playlist_dir);
        playlist_filename_sl->append(remove_extension(trim_directory(playlist_dir)));
        num_opened_playlists++;
    }
}

void MainWindow::open_playlist_file_helper_clear_first()
{
    clear();
    open_playlist_file_helper();
}

void MainWindow::open_song_file()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Select file"),
                                                    "/",
                                                    tr("Music files(*.aac *eaac *.flac *.m4a *.mp3 *.wav *.wma)"));

    cout << "Open file: " << filename.toStdString() << endl;

    if (filename != "") {
        add_list_entry(filename);
        check_duplicate_entries();
        refresh_view();
        show_num_songs();
    }
}

void MainWindow::open_song_files()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                          tr("Select files"),
                                                          "/",
                                                          tr("Music files(*.aac *.eaac *.flac *.m4a *.mp3 *.wav *.wma)"));

    int num_filenames = filenames.length();
    cout << "Open this number of files: " << num_filenames << endl;

    if (num_filenames != 0) {
        for (int i = 0; i < num_filenames; i++) {
            add_list_entry(filenames.at(i));
        }
        remove_duplicate_entries();
        refresh_view();
        show_num_songs();
    }
}

void MainWindow::open_song_folder()
{
    QString folder_name = QFileDialog::getExistingDirectory(this,
                                                            tr("Select folder"),
                                                            "/",
                                                            QFileDialog::ShowDirsOnly);


    cout << "Open folder: " << folder_name.toStdString() << endl;


    if (folder_name != "") {
        QDir dir(folder_name);

        QStringList filters;
        filters << "*.aac" << "*.eaac" << "*.flac" << "*.mp3" << "*.m4a" << "*.wav" << "*.wma";
        dir.setNameFilters(filters);

        QStringList folder_files = dir.entryList();
        int num_files = folder_files.length();
        QString filename;
        for (int i = 0; i < num_files; i++) {
            filename = folder_name;
            filename.append("/");
            filename.append(folder_files.at(0));
            add_list_entry(filename);
            folder_files.removeAt(0);
        }

        check_duplicate_entries();
        refresh_view();
        show_num_songs();
    }

}

void MainWindow::remove_bad_entries()
{
    // this is very important, the loop after this will not work properly if the indexes
    // are not in ascending order
    qSort(bad_entries);

    for (int i = 0; i < bad_entries.length(); i++) {
        // during multiple deletions, a row which is to be deleted after another
        // will have its position moved up prior to its deletion
        // for example, if rows 2, 3, 4 are to be deleted consecutively, it will
        // actually be three deletions at row 2
        remove_entry(bad_entries.at(i) - i);
    }
}

bool compare_dir_and_index(QPair<QString,int> pair1, QPair<QString,int> pair2)
{
    return (pair1.first.compare(pair2.first) < 0);
}

void MainWindow::check_duplicate_entries()
{
    list< QPair<QString,int> > *dir_sl_sorted = new list< QPair<QString,int> >();
    for (int i = 0; i < dir_sl->length(); i++)
    {
        dir_sl_sorted->push_back(QPair<QString,int>(dir_sl->at(i), i));
    }

    dir_sl_sorted->sort(compare_dir_and_index);

    indexes_of_duplicates.clear();
    int i = 0;
    QString previous_entry = "";
    list< QPair<QString,int> >::iterator it;
    for (it = dir_sl_sorted->begin(); it != dir_sl_sorted->end(); it++)
    {
        if (it != dir_sl_sorted->begin() && previous_entry == (*it).first)
        {
            indexes_of_duplicates.append((*it).second);
        }
        previous_entry = (*it).first;
        cout << previous_entry.toStdString() << endl;
    }
    qSort(indexes_of_duplicates);

    // some entries are duplicates
    if (indexes_of_duplicates.length() > 0)
    {
        cout << "some duplicate entries" << endl;

        QString desc = "The following ";
        desc.append(QString::number(indexes_of_duplicates.length()));
        desc.append(" entries are already found in the playlist, would you like to remove these duplicates?\n");

        QString songs;
        for (int i = 0; i < indexes_of_duplicates.length(); i++) {
            songs.append("[");
            songs.append(QString::number(indexes_of_duplicates.at(i) + 1));
            songs.append("/");
            songs.append(QString::number(dir_sl->length()));
            songs.append("]:\n");
            songs.append(dir_sl->at(indexes_of_duplicates.at(i)));
            songs.append("\n\n");
        }

        Popup1 some_duplicates("Results", desc, songs, "Remove", "Keep");
        connect(some_duplicates.b1, SIGNAL(clicked()), this, SLOT(remove_duplicate_entries()));
        some_duplicates.exec();
        refresh_view();
        show_num_songs();
    }
}

// right now this is essentially a copy of remove_bad_entries(), this needs to be changed
void MainWindow::remove_duplicate_entries()
{
    // this is very important, the loop after this will not work properly if the indexes
    // are not in ascending order
    qSort(indexes_of_duplicates);

    for (int i = 0; i < indexes_of_duplicates.length(); i++) {
        // during multiple deletions, a row which is to be deleted after another
        // will have its position moved up prior to its deletion
        // for example, if rows 2, 3, 4 are to be deleted consecutively, it will
        // actually be three deletions at row 2
        remove_entry(indexes_of_duplicates.at(i) - i);
    }
}

void MainWindow::remove_selected()
{
    int selected_index = ui->listView->currentIndex().row();
    cout << selected_index << endl;
    if (selected_index >= 0) {
        remove_entry(selected_index);
        refresh_view();

        // if any songs are left, select an entry
        if (filename_no_ext_sl->length() > 0) {

            QModelIndex new_index;
            // deleted last entry in the list
            if (selected_index == filename_no_ext_sl->length()) {
                // sets selected at position one entry above (which is now the current last entry)
                //QModelIndex new_index = slm_display->createIndex(selected_index - 1, 0);
                new_index = display_slm->index(selected_index - 1);
            }
            else {
                // sets selected at same position
                new_index = display_slm->index(selected_index);
            }

            ui->listView->setCurrentIndex(new_index); // set index
            show_quickinfo(); // display info about selected song in status bar
        }
    }
}

int MainWindow::get_median_index(QString ***p_array, int compare_row, int a, int b, int c)
{
    QString str_at_a = *(p_array[a][compare_row]);
    QString str_at_b = *(p_array[b][compare_row]);
    QString str_at_c = *(p_array[c][compare_row]);

    if (str_at_a <= str_at_b && str_at_a <= str_at_c) {
        if (str_at_b <= str_at_c) return b;
        else return c;
    }
    else if (str_at_b <= str_at_a && str_at_b <= str_at_c) {
        if (str_at_a <= str_at_c) return a;
        else return c;
    }
    else if (str_at_c <= str_at_a && str_at_c <= str_at_b) {
        if (str_at_a <= str_at_b) return a;
        else return b;
    }
    else {
        cout << "ERROR - unhandled case in get_median" << endl;
        return -1;
    }
}

void MainWindow::sort(QString ***p_array, int left_index, int right_index)
{
    if (left_index == right_index)
        return;

    int middle_index = (left_index + right_index) / 2;

    int pivot_index = get_median_index(p_array, 0, left_index, middle_index, right_index);
    QString *pivot_value[4];
    pivot_value[0] = p_array[pivot_index][0];
    pivot_value[1] = p_array[pivot_index][1];
    pivot_value[2] = p_array[pivot_index][2];
    pivot_value[3] = p_array[pivot_index][3];

    list<QString*> l_filename_left, l_filename_right,
                   l_dir_left     , l_dir_right,
                   l_format_left  , l_format_right,
                   l_display_left , l_display_right;

    for (int i = left_index; i <= right_index; i++) {
        if (i != pivot_index) {
            //if (*(p_array[i][0]) <= *(pivot_value[0])) {
            if (QString::compare(*(p_array[i][0]), *(pivot_value[0]), Qt::CaseInsensitive) <= 0) {
                l_filename_left.push_back(p_array[i][0]);
                l_dir_left.push_back(p_array[i][1]);
                l_format_left.push_back(p_array[i][2]);
                l_display_left.push_back(p_array[i][3]);
            }
            else {
                l_filename_right.push_back(p_array[i][0]);
                l_dir_right.push_back(p_array[i][1]);
                l_format_right.push_back(p_array[i][2]);
                l_display_right.push_back(p_array[i][3]);
            }
        }
    }

    int cur_index = left_index;
    list<QString*>::iterator it_filename, it_dir, it_format, it_display;

    it_filename = l_filename_left.begin();
    it_dir = l_dir_left.begin();
    it_format = l_format_left.begin();
    it_display = l_display_left.begin();
    while (it_filename != l_filename_left.end()) {
        p_array[cur_index][0] = *it_filename;
        p_array[cur_index][1] = *it_dir;
        p_array[cur_index][2] = *it_format;
        p_array[cur_index][3] = *it_display;

        it_filename++;
        it_dir++;
        it_format++;
        it_display++;
        cur_index++;
    }
    // sort recursively only if there is at least one element on the left side
    if (cur_index > left_index) {
        sort(p_array, left_index, cur_index - 1);
    }

    pivot_index = cur_index; // updates the index of the pivot value
    p_array[pivot_index][0] = pivot_value[0];
    p_array[pivot_index][1] = pivot_value[1];
    p_array[pivot_index][2] = pivot_value[2];
    p_array[pivot_index][3] = pivot_value[3];
    cur_index++;

    it_filename = l_filename_right.begin();
    it_dir = l_dir_right.begin();
    it_format = l_format_right.begin();
    it_display = l_display_right.begin();
    while (it_filename != l_filename_right.end()) {
        p_array[cur_index][0] = *it_filename;
        p_array[cur_index][1] = *it_dir;
        p_array[cur_index][2] = *it_format;
        p_array[cur_index][3] = *it_display;

        it_filename++;
        it_dir++;
        it_format++;
        it_display++;
        cur_index++;
    }
    // sort recursively only if there is at least one element on the right side
    if (cur_index > pivot_index + 1) {
        sort(p_array, pivot_index + 1, right_index);
    }
}

void MainWindow::run_sort()
{
    cout << "sort" << endl;

    /*
    StringListGroup *slg = new StringListGroup();
    slg->dir_sl = dir_sl;
    slg->filename_sl = filename_sl;
    slg->format_sl = format_sl;
    slg->filename_no_ext_sl = filename_no_ext_sl;

    StringListGroup *slg_new = sort(slg);

    dir_sl = slg_new->dir_sl;
    filename_sl = slg_new->filename_sl;
    format_sl = slg_new->format_sl;
    filename_no_ext_sl = slg_new->filename_no_ext_sl;
    */

    if (dir_sl->length() > 0) {
        // two dimensional array on the heap
        QString ***data = new QString**[dir_sl->length()];
        for (int i = 0; i < dir_sl->length(); i++) {
            data[i] = new QString*[4];
        }
        //*(data[0][0]) = "test";

        int cur_index;
        QStringList::iterator it;
        for (cur_index = 0, it = filename_sl->begin(); it != filename_sl->end(); it++, cur_index++) {
            data[cur_index][0] = &(*it);
        }
        for (cur_index = 0, it = dir_sl->begin(); it != dir_sl->end(); it++, cur_index++) {
            data[cur_index][1] = &(*it);
        }
        for (cur_index = 0, it = format_sl->begin(); it != format_sl->end(); it++, cur_index++) {
            data[cur_index][2] = &(*it);
        }
        for (cur_index = 0, it = filename_no_ext_sl->begin(); it != filename_no_ext_sl->end(); it++, cur_index++) {
            data[cur_index][3] = &(*it);
        }


        if (display_method == FILENAME_NO_EXT)
            int ordering_sequence[1] = { 3 };
        else if (display_method == FILENAME)
            int ordering_sequence[1] = { 0 };
        else if (display_method == DIRECTORY)
            int ordering_sequence[1] = { 1 };
        else if (display_method == TAG)
            int ordering_sequence[1] = { 0 };

        sort(data, 0, dir_sl->length() - 1);

        /*
        for (int i = 0; i < num_songs; i++) {
            cout << (*(data[i][0])).toStdString() << " ";
        }
        cout << endl;
        */

        QStringList *filename_sl_new = new QStringList();
        QStringList *dir_sl_new = new QStringList();
        QStringList *format_sl_new = new QStringList();
        QStringList *filename_no_ext_sl_new = new QStringList();

        for (int i = 0; i < dir_sl->length(); i++) {
            filename_sl_new->append(*(data[i][0]));
            dir_sl_new->append(*(data[i][1]));
            format_sl_new->append(*(data[i][2]));
            filename_no_ext_sl_new->append(*(data[i][3]));
            delete [] data[i];
        }
        delete [] data;

        filename_sl->clear();
        dir_sl->clear();
        format_sl->clear();
        filename_no_ext_sl->clear();
        delete filename_sl;
        delete dir_sl;
        delete format_sl;
        delete filename_no_ext_sl;

        filename_sl = filename_sl_new;
        dir_sl = dir_sl_new;
        format_sl = format_sl_new;
        filename_no_ext_sl = filename_no_ext_sl_new;
    }

    refresh_view();
    ui->statusBar->showMessage("Sorted!");
}

void MainWindow::save_playlist()
{
    if (num_opened_playlists > 0) {
        Popup2 options("Save Method",
                       "You have opened playlist(s), do you want to update rather than save as new?",
                       "Yes",
                       "No");
        connect(options.b1, SIGNAL(clicked()), this, SLOT(save_playlist_update()));
        connect(options.b2, SIGNAL(clicked()), this, SLOT(save_playlist_new()));
        options.exec();
    }
    else {
        save_playlist_new();
    }
}

void MainWindow::save_playlist_new()
{
    QFileDialog fd;
    QString dir = fd.getSaveFileName(this,
                                     tr("Save As"),
                                     "/playlist.m3u",
                                     tr("M3U Playlist(*.m3u)"));

    cout << "Save file: [" << dir.toStdString() << "]" << endl;

    if (dir != "") {
        // write to the playlist (file will be created if it did not exist)
        write_to_playlist(dir);

        QString msg;
        msg.append("Playlist '");
        msg.append(remove_extension(trim_directory(dir)));
        msg.append("' has been saved!");
        ui->statusBar->showMessage(msg);
    }
}

void MainWindow::save_playlist_update()
{
    int *selected_index = new int;
    *selected_index = -1;
    Popup4 p("Update Playlist",
             "Select the playlist to update",
             "Update",
             playlist_dir_sl,
             playlist_filename_sl,
             selected_index);
    p.exec();

    cout << "Updating playlist #: " << *selected_index << endl;
    if (*selected_index >= 0) {
        QString selected_dir = playlist_dir_sl->at(*selected_index);
        QString selected_filename = playlist_filename_sl->at(*selected_index);

        // write to the playlist
        write_to_playlist(selected_dir);

        QString msg;
        msg.append("Playlist '");
        msg.append(selected_filename);
        msg.append("' has been updated!");
        ui->statusBar->showMessage(msg);
    }

    delete selected_index;
}

void MainWindow::write_to_playlist(QString dir)
{
    if (!extension_ok(dir)) {
        ui->statusBar->showMessage("NOT SAVED! (wrong extension used)");
        return;
    }

    QFile file(dir);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cout << "ERROR: cannot open file in write mode" << endl;
        ui->statusBar->showMessage("NOT SAVED! (file could not be written in this directory)");
        return;
    }

    QTextStream out(&file);    
    for (int i = 0; i < dir_sl->length(); i++) {
        out << dir_sl->at(i) << "\n";
    }

    file.close();
}

void MainWindow::show_about_window()
{
    QMessageBox about_window;

    QString about_window_contents_qstr = "TLPlaylistCreator 1.1 (build ";
    about_window_contents_qstr.append(version);
    about_window_contents_qstr.append(")\n\n");
    about_window_contents_qstr.append("Copyright 2010-2012 Xingzhe (Travis) Lu");

    about_window.setWindowTitle("About TLPlaylistCreator");
    about_window.setText(about_window_contents_qstr);

    about_window.exec();
}

void MainWindow::show_quickinfo()
{
    int selected_index = ui->listView->currentIndex().row();

    QString msg = "Song ";
    msg = msg.append(QString::number(selected_index + 1));
    msg = msg.append(" of ");
    msg = msg.append(QString::number(dir_sl->length()));

    ui->statusBar->showMessage(msg);
}

void MainWindow::show_song_information()
{
    int index = ui->listView->currentIndex().row();

    if (index >= 0) {
        QMessageBox song_info_window;
        song_info_window.setWindowTitle("Song information");

        QString song_info_window_contents_qstr = "File type: ";
        song_info_window_contents_qstr.append(format_sl->at(index));
        song_info_window_contents_qstr.append("\n\n");
        song_info_window_contents_qstr.append("Full filepath:\n");
        song_info_window_contents_qstr.append(dir_sl->at(index));

        song_info_window_contents_qstr.append("\n\n");
        cout << "aha " << (dir_sl->at(index)).toStdString() << endl;
        QString tag_data(run_ReadTag(dir_sl->at(index)).c_str());
        song_info_window_contents_qstr.append(tag_data);

        song_info_window.setText(song_info_window_contents_qstr);
        song_info_window.exec();
    }
}

void MainWindow::test()
{
    //cout << ui->listView->currentIndex().row() << endl;
    Popup3 testpop("window title", "data", "b_title");
    testpop.exec();
}
