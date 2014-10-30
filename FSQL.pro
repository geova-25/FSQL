TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fsql_manager.cpp \
    register.cpp \
    filemanager.cpp \
    registermanager.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fsql_manager.h \
    register.h \
    filemanager.h \
    vectorrelacional.h \
    nodorelacional.h \
    registermanager.h \
    vector3d.h \
    nodo3d.h

