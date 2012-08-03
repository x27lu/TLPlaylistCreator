/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Jun 22 23:45:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     157,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     260,   11,   11,   11, 0x08,
     279,   11,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     325,   11,   11,   11, 0x08,
     341,   11,   11,   11, 0x08,
     361,   11,   11,   11, 0x08,
     384,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,
     421,   11,   11,   11, 0x08,
     445,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0activate_deactivate_move_buttons()\0"
    "change_display_method()\0check_existence()\0"
    "clear()\0move_down()\0move_up()\0"
    "open_in_player()\0open_playlist_file()\0"
    "open_playlist_file_helper()\0"
    "open_playlist_file_helper_clear_first()\0"
    "open_song_file()\0open_song_files()\0"
    "open_song_folder()\0remove_entries()\0"
    "remove_selected()\0run_sort()\0"
    "save_playlist()\0save_playlist_new()\0"
    "save_playlist_update()\0show_about_window()\0"
    "show_quickinfo()\0show_song_information()\0"
    "test()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activate_deactivate_move_buttons(); break;
        case 1: change_display_method(); break;
        case 2: check_existence(); break;
        case 3: clear(); break;
        case 4: move_down(); break;
        case 5: move_up(); break;
        case 6: open_in_player(); break;
        case 7: open_playlist_file(); break;
        case 8: open_playlist_file_helper(); break;
        case 9: open_playlist_file_helper_clear_first(); break;
        case 10: open_song_file(); break;
        case 11: open_song_files(); break;
        case 12: open_song_folder(); break;
        case 13: remove_entries(); break;
        case 14: remove_selected(); break;
        case 15: run_sort(); break;
        case 16: save_playlist(); break;
        case 17: save_playlist_new(); break;
        case 18: save_playlist_update(); break;
        case 19: show_about_window(); break;
        case 20: show_quickinfo(); break;
        case 21: show_song_information(); break;
        case 22: test(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
