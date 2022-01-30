QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coordinatetransformer.cpp \
    ellipsoid.cpp \
    graphicpipeline.cpp \
    graphicwidget.cpp \
    invisibledeleter.cpp \
    lightprocessor.cpp \
    main.cpp \
    mainwindow.cpp \
    paramhandler.cpp \
    figure.cpp \
    pointtransformer.cpp \
    projecter.cpp \
    pyramid.cpp \
    rasterizer.cpp \
    tetrahedron.cpp

HEADERS += \
    coordinatetransformer.h \
    ellipsoid.h \
    figure.h \
    graphicpipeline.h \
    graphicwidget.h \
    invisibledeleter.h \
    lightprocessor.h \
    mainwindow.h \
    paramhandler.h \
    pointtransformer.h \
    projecter.h \
    pyramid.h \
    rasterizer.h \
    tetrahedron.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
