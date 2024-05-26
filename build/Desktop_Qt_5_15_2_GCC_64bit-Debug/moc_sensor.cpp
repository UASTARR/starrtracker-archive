/****************************************************************************
** Meta object code from reading C++ file 'sensor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ui/sensor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Sensor_t {
    QByteArrayData data[19];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Sensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Sensor_t qt_meta_stringdata_Sensor = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Sensor"
QT_MOC_LITERAL(1, 7, 19), // "setLocationMarker_1"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "setLocationMarker_2"
QT_MOC_LITERAL(4, 48, 9), // "writeData"
QT_MOC_LITERAL(5, 58, 4), // "data"
QT_MOC_LITERAL(6, 63, 11), // "handleError"
QT_MOC_LITERAL(7, 75, 1), // "s"
QT_MOC_LITERAL(8, 77, 15), // "handleDataReady"
QT_MOC_LITERAL(9, 93, 7), // "GpsData"
QT_MOC_LITERAL(10, 101, 22), // "handleConnectionStatus"
QT_MOC_LITERAL(11, 124, 6), // "status"
QT_MOC_LITERAL(12, 131, 16), // "connectionStatus"
QT_MOC_LITERAL(13, 148, 14), // "openSerialPort"
QT_MOC_LITERAL(14, 163, 15), // "closeSerialPort"
QT_MOC_LITERAL(15, 179, 15), // "on_prev_clicked"
QT_MOC_LITERAL(16, 195, 15), // "on_next_clicked"
QT_MOC_LITERAL(17, 211, 20), // "on_resetBtn1_clicked"
QT_MOC_LITERAL(18, 232, 20) // "on_resetBtn2_clicked"

    },
    "Sensor\0setLocationMarker_1\0\0"
    "setLocationMarker_2\0writeData\0data\0"
    "handleError\0s\0handleDataReady\0GpsData\0"
    "handleConnectionStatus\0status\0"
    "connectionStatus\0openSerialPort\0"
    "closeSerialPort\0on_prev_clicked\0"
    "on_next_clicked\0on_resetBtn1_clicked\0"
    "on_resetBtn2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Sensor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       3,    2,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   84,    2, 0x08 /* Private */,
       6,    1,   87,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,    2,    2,
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,    5,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Sensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Sensor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setLocationMarker_1((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->setLocationMarker_2((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 2: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->handleDataReady((*reinterpret_cast< const GpsData(*)>(_a[1]))); break;
        case 5: _t->handleConnectionStatus((*reinterpret_cast< const status(*)>(_a[1]))); break;
        case 6: _t->openSerialPort(); break;
        case 7: _t->closeSerialPort(); break;
        case 8: _t->on_prev_clicked(); break;
        case 9: _t->on_next_clicked(); break;
        case 10: _t->on_resetBtn1_clicked(); break;
        case 11: _t->on_resetBtn2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Sensor::*)(QVariant , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Sensor::setLocationMarker_1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Sensor::*)(QVariant , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Sensor::setLocationMarker_2)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Sensor::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Sensor.data,
    qt_meta_data_Sensor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Sensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Sensor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Sensor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Sensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Sensor::setLocationMarker_1(QVariant _t1, QVariant _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Sensor::setLocationMarker_2(QVariant _t1, QVariant _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
