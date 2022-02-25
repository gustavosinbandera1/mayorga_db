QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# sudo apt install libqt5sql5-psql
QTPLUGIN += QPSQL
QT_DEBUG_PLUGINS=1

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/databaseManager
INCLUDEPATH += $$PWD/products
INCLUDEPATH += $$PWD/customers
INCLUDEPATH += $$PWD/login
INCLUDEPATH += $$PWD/orders
INCLUDEPATH += $$PWD/address
INCLUDEPATH += $$PWD/delegates
INCLUDEPATH += $$PWD/models
INCLUDEPATH += $$PWD/administrators

SOURCES += \
    address/addressdto.cpp \
    address/addressmodel.cpp \
    address/addressview.cpp \
    administrators/registeruserDTO.cpp \
    models/customtablemodel.cpp \
    delegates/comboBoxDelegate.cpp \
    customers/customersModel.cpp \
    customers/userDTO.cpp \
    databaseManager/dbmanager.cpp \
    delegates/lineeditordelegate.cpp \
    login/login.cpp \
    main.cpp \
    mainwindow.cpp \
    orders/detailsDialog.cpp \
    orders/orderform.cpp \
    orders/ordersmodel.cpp \
    orders/ordersview.cpp \
    products/productsModel.cpp \
    customers/usersview.cpp \
    products/productsdto.cpp \
    products/productsview.cpp \
    delegates/spinboxDelegate.cpp

HEADERS += \
    address/addressdto.h \
    address/addressmodel.h \
    address/addressview.h \
    administrators/registeruserDTO.h \
    administrators/ui_registeradmindialog \
    models/customtablemodel.h \
    delegates/comboBoxDelegate.h \
    customers/customersModel.h \
    customers/userDTO.h \
    databaseManager/db_config.h \
    databaseManager/dbmanager.h \
    delegates/lineeditordelegate.h \
    login/login.h \
    mainwindow.h \
    orders/detailsDialog.h \
    orders/orderform.h \
    orders/ordersmodel.h \
    orders/ordersview.h \
    products/productsModel.h \
    customers/usersview.h \
    products/productsdto.h \
    products/productsview.h \
    delegates/spinboxDelegate.h

FORMS += \
    #address/addressmodel.ui \
    address/addressdto.ui \
    address/addressview.ui \
    administrators/registeruserDTO.ui \
    login/login.ui \
    mainwindow.ui \
    orders/detailsDialog.ui \
    orders/orderform.ui \
    orders/ordersview.ui \
    products/productsdto.ui \
    products/productsview.ui \
    userscontrolform.ui \
    customers/usersview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    initialData.sql \
    tableStructure.sql
