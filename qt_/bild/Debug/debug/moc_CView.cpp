/****************************************************************************
** Meta object code from reading C++ file 'CView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../View/CView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CView_t {
    QByteArrayData data[11];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CView_t qt_meta_stringdata_CView = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 13),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 15),
QT_MOC_LITERAL(4, 37, 21),
QT_MOC_LITERAL(5, 59, 8),
QT_MOC_LITERAL(6, 68, 16),
QT_MOC_LITERAL(7, 85, 4),
QT_MOC_LITERAL(8, 90, 10),
QT_MOC_LITERAL(9, 101, 7),
QT_MOC_LITERAL(10, 109, 3)
    },
    "CView\0tableViewObjs\0\0tableViewMapWin\0"
    "tableViewMapObjAccess\0onLOFlag\0"
    "QListWidgetItem*\0item\0onWMapFlag\0"
    "VERWIN&\0ver\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a,
       3,    0,   40,    2, 0x0a,
       4,    0,   41,    2, 0x0a,
       5,    1,   42,    2, 0x0a,
       8,    1,   45,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void CView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CView *_t = static_cast<CView *>(_o);
        switch (_id) {
        case 0: _t->tableViewObjs(); break;
        case 1: _t->tableViewMapWin(); break;
        case 2: _t->tableViewMapObjAccess(); break;
        case 3: _t->onLOFlag((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onWMapFlag((*reinterpret_cast< VERWIN(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CView.data,
      qt_meta_data_CView,  qt_static_metacall, 0, 0}
};


const QMetaObject *CView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CView.stringdata))
        return static_cast<void*>(const_cast< CView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
