/****************************************************************************
** Meta object code from reading C++ file 'GuiLoopingPopup.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/GuiLoopingPopup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiLoopingPopup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuiLoopingPopup[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x08,
      65,   59,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GuiLoopingPopup[] = {
    "GuiLoopingPopup\0\0bars\0"
    "on_loopBarsSpin_valueChanged(double)\0"
    "event\0closeEvent(QCloseEvent*)\0"
};

void GuiLoopingPopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GuiLoopingPopup *_t = static_cast<GuiLoopingPopup *>(_o);
        switch (_id) {
        case 0: _t->on_loopBarsSpin_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GuiLoopingPopup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GuiLoopingPopup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiLoopingPopup,
      qt_meta_data_GuiLoopingPopup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GuiLoopingPopup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GuiLoopingPopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GuiLoopingPopup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuiLoopingPopup))
        return static_cast<void*>(const_cast< GuiLoopingPopup*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiLoopingPopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
