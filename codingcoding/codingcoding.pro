QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    choosewindow.cpp \
    dialogwindow.cpp \
    floor.cpp \
    fullbutton.cpp \
    game.cpp \
    gameobject.cpp \
    main.cpp \
    mainwindow.cpp \
    musicloader.cpp \
    pausewindow.cpp \
    settlewindow.cpp \
    txtshow.cpp

HEADERS += \
    character.h \
    choosewindow.h \
    config.h \
    dialogwindow.h \
    floor.h \
    fullbutton.h \
    game.h \
    gameobject.h \
    mainwindow.h \
    musicloader.h \
    pausewindow.h \
    settlewindow.h \
    txtshow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    background/dialog.png \
    dialog.png \
    dialog1.txt \
    music/gamebgm.wav \
    text/dialog1.txt \
    text/dialog2.txt \
    text/dialog3.txt \
    text/dialog4.txt \
    text/dialog5.txt
