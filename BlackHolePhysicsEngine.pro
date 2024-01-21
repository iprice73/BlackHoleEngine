QT       += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blackhole.cpp \
    charttool.cpp \
    main.cpp \
    mainwindow.cpp \
    particle.cpp \
    particleinserter.cpp \
    particlesystem.cpp \
    renderarea.cpp \
    stellarobject.cpp

HEADERS += \
    blackhole.h \
    charttool.h \
    mainwindow.h \
    particle.h \
    particleinserter.h \
    particlesystem.h \
    renderarea.h \
    stellarobject.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
