/****************************************************************************
** Meta object code from reading C++ file 'tables.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../tables.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tables.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tables_t {
    QByteArrayData data[12];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tables_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tables_t qt_meta_stringdata_Tables = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Tables"
QT_MOC_LITERAL(1, 7, 14), // "setRowsClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 20), // "setRandomDataClicked"
QT_MOC_LITERAL(4, 44, 10), // "minClicked"
QT_MOC_LITERAL(5, 55, 10), // "avgClicked"
QT_MOC_LITERAL(6, 66, 10), // "maxClicked"
QT_MOC_LITERAL(7, 77, 16), // "tableCellChanged"
QT_MOC_LITERAL(8, 94, 3), // "row"
QT_MOC_LITERAL(9, 98, 7), // "collumn"
QT_MOC_LITERAL(10, 106, 13), // "searchClicked"
QT_MOC_LITERAL(11, 120, 11) // "sortClicked"

    },
    "Tables\0setRowsClicked\0\0setRandomDataClicked\0"
    "minClicked\0avgClicked\0maxClicked\0"
    "tableCellChanged\0row\0collumn\0searchClicked\0"
    "sortClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tables[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    2,   59,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tables::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tables *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setRowsClicked(); break;
        case 1: _t->setRandomDataClicked(); break;
        case 2: _t->minClicked(); break;
        case 3: _t->avgClicked(); break;
        case 4: _t->maxClicked(); break;
        case 5: _t->tableCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->searchClicked(); break;
        case 7: _t->sortClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tables::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Tables.data,
    qt_meta_data_Tables,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tables::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tables::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tables.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Tables::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
