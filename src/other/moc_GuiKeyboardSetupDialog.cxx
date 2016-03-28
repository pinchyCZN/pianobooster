/****************************************************************************
** Meta object code from reading C++ file 'GuiKeyboardSetupDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/GuiKeyboardSetupDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiKeyboardSetupDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuiKeyboardSetupDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      33,   23,   23,   23, 0x08,
      42,   23,   23,   23, 0x08,
      71,   23,   23,   23, 0x08,
     101,   23,   23,   23, 0x08,
     130,   23,   23,   23, 0x08,
     168,  160,   23,   23, 0x08,
     203,  197,   23,   23, 0x08,
     237,  197,   23,   23, 0x08,
     271,   23,   23,   23, 0x08,
     307,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GuiKeyboardSetupDialog[] = {
    "GuiKeyboardSetupDialog\0\0accept()\0"
    "reject()\0on_rightTestButton_pressed()\0"
    "on_rightTestButton_released()\0"
    "on_wrongTestButton_pressed()\0"
    "on_wrongTestButton_released()\0clicked\0"
    "on_resetButton_clicked(bool)\0index\0"
    "on_rightSoundCombo_activated(int)\0"
    "on_wrongSoundCombo_activated(int)\0"
    "on_lowestNoteEdit_editingFinished()\0"
    "on_highestNoteEdit_editingFinished()\0"
};

void GuiKeyboardSetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GuiKeyboardSetupDialog *_t = static_cast<GuiKeyboardSetupDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->on_rightTestButton_pressed(); break;
        case 3: _t->on_rightTestButton_released(); break;
        case 4: _t->on_wrongTestButton_pressed(); break;
        case 5: _t->on_wrongTestButton_released(); break;
        case 6: _t->on_resetButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_rightSoundCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_wrongSoundCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_lowestNoteEdit_editingFinished(); break;
        case 10: _t->on_highestNoteEdit_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GuiKeyboardSetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GuiKeyboardSetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GuiKeyboardSetupDialog,
      qt_meta_data_GuiKeyboardSetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GuiKeyboardSetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GuiKeyboardSetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GuiKeyboardSetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuiKeyboardSetupDialog))
        return static_cast<void*>(const_cast< GuiKeyboardSetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GuiKeyboardSetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
