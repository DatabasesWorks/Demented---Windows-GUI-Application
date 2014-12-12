#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T12:17:53
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demented
TEMPLATE = app

//QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        login.cpp \
    manager.cpp \
    database.cpp \
    itemselect.cpp \
    objectinfo.cpp \
    menu.cpp \
    adminmenu.cpp \
    masterlog.cpp \
    logobject.cpp \
    import.cpp \
    edit.cpp \
    manageuser.cpp \
    edituser.cpp \
    addusers.cpp

HEADERS  += login.h \
    manager.h \
    database.h \
    itemselect.h \
    objectinfo.h \
    menu.h \
    adminmenu.h \
    masterlog.h \
    logobject.h \
    import.h \
    edit.h \
    manageuser.h \
    edituser.h \
    addusers.h

FORMS    += login.ui \
    manager.ui \
    itemselect.ui \
    menu.ui \
    adminmenu.ui \
    masterlog.ui \
    logobject.ui \
    import.ui \
    edit.ui \
    manageuser.ui \
    edituser.ui \
    addusers.ui
