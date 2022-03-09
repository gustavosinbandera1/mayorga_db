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
INCLUDEPATH += $$PWD/sql
INCLUDEPATH += $$PWD/products
INCLUDEPATH += $$PWD/customers
INCLUDEPATH += $$PWD/login
INCLUDEPATH += $$PWD/orders
INCLUDEPATH += $$PWD/address
INCLUDEPATH += $$PWD/client
INCLUDEPATH += $$PWD/shared/delegates
INCLUDEPATH += $$PWD/shared/models
INCLUDEPATH += $$PWD/shared/widgets
INCLUDEPATH += $$PWD/administrators

SOURCES += \
    address/addressdto.cpp \
    address/addressview.cpp \
   # administrators/userDTO.cpp \
    client/browser.cpp \
    customers/userdto.cpp \
    databaseManager/qsqlconnectiondialog.cpp \
    orders/loadDetailsDialog.cpp \
    orders/orderdetailview.cpp \
    #orderviewer.cpp \
    orders/orderviewer.cpp \
    shared/delegates/quantitytotaldelegate.cpp \
    shared/delegates/comboBoxDelegate.cpp \
    databaseManager/dbmanager.cpp \
    shared/delegates/lineeditordelegate.cpp \
    login/login.cpp \
    main.cpp \
    mainwindow.cpp \
    orders/orderform.cpp \
    orders/ordersview.cpp \
    customers/usersview.cpp \
    products/productsdto.cpp \
    products/productsview.cpp \
    shared/delegates/spinboxDelegate.cpp \
    shared/models/queryModel.cpp \
    shared/models/readWriteModel.cpp \
    shared/widgets/connectionwidget.cpp


HEADERS += \
    address/addressdto.h \
    address/addressview.h \
    administrators/ui_registeradmindialog \
    #administrators/userDTO.h \
    client/browser.h \
    customers/userdto.h \
    databaseManager/qsqlconnectiondialog.h \
    orders/loadDetailsDialog.h \
    orders/orderdetailview.h \
    #orderviewer.h \
    orders/orderviewer.h \
    shared/delegates/quantitytotaldelegate.h \
    shared/delegates/comboBoxDelegate.h \
    databaseManager/db_config.h \
    databaseManager/dbmanager.h \
    shared/delegates/lineeditordelegate.h \
    login/login.h \
    mainwindow.h \
    orders/orderform.h \
    orders/ordersview.h \
    customers/usersview.h \
    products/productsdto.h \
    products/productsview.h \
    shared/delegates/spinboxDelegate.h \
    shared/models/queryModel.h \
    shared/models/readWriteModel.h \
    shared/widgets/connectionwidget.h

FORMS += \
    address/addressdto.ui \
    address/addressview.ui \
    #administrators/userDTO.ui \
    client/browserwidget.ui \
    customers/userdto.ui \
    databaseManager/qsqlconnectiondialog.ui \
    login/login.ui \
    mainwindow.ui \
    orders/loadDetailsDialog.ui \
    orders/orderdetailview.ui \
    orders/orderform.ui \
    orders/ordersview.ui \
    #orders/orderviewer.ui \
    orders/orderviewer.ui \
    products/productsdto.ui \
    products/productsview.ui \
    userscontrolform.ui \
    customers/usersview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    sql/Combinear.qss \
    sql/Medize.qss \
    sql/initialData.sql \
    sql/tableStructure.sql \
    tableStructure.sql


copydata.commands = $(COPY_DIR) $$PWD/sql $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

