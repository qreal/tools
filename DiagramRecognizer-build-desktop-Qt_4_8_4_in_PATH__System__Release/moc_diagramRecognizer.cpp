/****************************************************************************
** Meta object code from reading C++ file 'diagramRecognizer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DiagramRecognizer/diagramRecognizer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diagramRecognizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DiagramRecognizer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      53,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      96,   18,   18,   18, 0x0a,
     104,   18,   18,   18, 0x0a,
     116,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DiagramRecognizer[] = {
    "DiagramRecognizer\0\0mDiagram,mBitmap,mFormSegmentator\0"
    "print(PathVector,Bitmap*,FormSegmentator*)\0"
    "clear()\0recognize()\0recognizeImage()\0"
};

void DiagramRecognizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DiagramRecognizer *_t = static_cast<DiagramRecognizer *>(_o);
        switch (_id) {
        case 0: _t->print((*reinterpret_cast< PathVector(*)>(_a[1])),(*reinterpret_cast< Bitmap*(*)>(_a[2])),(*reinterpret_cast< FormSegmentator*(*)>(_a[3]))); break;
        case 1: _t->clear(); break;
        case 2: _t->recognize(); break;
        case 3: _t->recognizeImage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DiagramRecognizer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DiagramRecognizer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DiagramRecognizer,
      qt_meta_data_DiagramRecognizer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DiagramRecognizer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DiagramRecognizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DiagramRecognizer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DiagramRecognizer))
        return static_cast<void*>(const_cast< DiagramRecognizer*>(this));
    return QWidget::qt_metacast(_clname);
}

int DiagramRecognizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DiagramRecognizer::print(PathVector _t1, Bitmap * _t2, FormSegmentator * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
