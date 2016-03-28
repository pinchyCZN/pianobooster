/****************************************************************************
** Meta object code from reading C++ file 'QtWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QtWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      17,    9,    9,    9, 0x08,
      24,    9,    9,    9, 0x08,
      34,    9,    9,    9, 0x08,
      42,    9,    9,    9, 0x08,
      62,    9,    9,    9, 0x08,
      79,    9,    9,    9, 0x08,
      95,    9,    9,    9, 0x08,
     119,    9,    9,    9, 0x08,
     143,    9,    9,    9, 0x08,
     163,    9,    9,    9, 0x08,
     181,    9,    9,    9, 0x08,
     204,    9,    9,    9, 0x08,
     224,    9,    9,    9, 0x08,
     245,    9,    9,    9, 0x08,
     260,    9,    9,    9, 0x08,
     275,    9,    9,    9, 0x08,
     289,    9,    9,    9, 0x08,
     308,    9,    9,    9, 0x08,
     323,    9,    9,    9, 0x08,
     335,    9,    9,    9, 0x08,
     347,    9,    9,    9, 0x08,
     361,    9,    9,    9, 0x08,
     379,    9,    9,    9, 0x08,
     393,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtWindow[] = {
    "QtWindow\0\0open()\0help()\0website()\0"
    "about()\0keyboardShortcuts()\0"
    "openRecentFile()\0showMidiSetup()\0"
    "showPreferencesDialog()\0showSongDetailsDialog()\0"
    "showKeyboardSetup()\0toggleSidePanel()\0"
    "onFullScreenStateAct()\0enableFollowTempo()\0"
    "disableFollowTempo()\0on_rightHand()\0"
    "on_bothHands()\0on_leftHand()\0"
    "on_playFromStart()\0on_playPause()\0"
    "on_faster()\0on_slower()\0on_nextSong()\0"
    "on_previousSong()\0on_nextBook()\0"
    "on_previousBook()\0"
};

void QtWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtWindow *_t = static_cast<QtWindow *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->help(); break;
        case 2: _t->website(); break;
        case 3: _t->about(); break;
        case 4: _t->keyboardShortcuts(); break;
        case 5: _t->openRecentFile(); break;
        case 6: _t->showMidiSetup(); break;
        case 7: _t->showPreferencesDialog(); break;
        case 8: _t->showSongDetailsDialog(); break;
        case 9: _t->showKeyboardSetup(); break;
        case 10: _t->toggleSidePanel(); break;
        case 11: _t->onFullScreenStateAct(); break;
        case 12: _t->enableFollowTempo(); break;
        case 13: _t->disableFollowTempo(); break;
        case 14: _t->on_rightHand(); break;
        case 15: _t->on_bothHands(); break;
        case 16: _t->on_leftHand(); break;
        case 17: _t->on_playFromStart(); break;
        case 18: _t->on_playPause(); break;
        case 19: _t->on_faster(); break;
        case 20: _t->on_slower(); break;
        case 21: _t->on_nextSong(); break;
        case 22: _t->on_previousSong(); break;
        case 23: _t->on_nextBook(); break;
        case 24: _t->on_previousBook(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtWindow,
      qt_meta_data_QtWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtWindow))
        return static_cast<void*>(const_cast< QtWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
