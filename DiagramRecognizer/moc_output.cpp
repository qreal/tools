/****************************************************************************
** Meta object code from reading C++ file 'output.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "output.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'output.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Output[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      55,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Output[] = {
    "Output\0\0RecognizedDiagram,newBitmap,newFormSegmentator\0"
    "draw(PathVector,Bitmap*,FormSegmentator*)\0"
};

void Output::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Output *_t = static_cast<Output *>(_o);
        switch (_id) {
        case 0: _t->draw((*reinterpret_cast< PathVector(*)>(_a[1])),(*reinterpret_cast< Bitmap*(*)>(_a[2])),(*reinterpret_cast< FormSegmentator*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Output::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Output::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Output,
      qt_meta_data_Output, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Output::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Output::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Output::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Output))
        return static_cast<void*>(const_cast< Output*>(this));
    return QWidget::qt_metacast(_clname);
}

int Output::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
