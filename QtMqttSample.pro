QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    3rdparty/qtmqtt/v5.12.7/prebuilt/include

win32 {
# x64
    Debug:LIBS += -L"$${PWD}/3rdparty/qtmqtt/v5.12.7/prebuilt/lib/msvc2017_64" -lQt5Mqttd
    Release:LIBS += -L"$${PWD}/3rdparty/qtmqtt/v5.12.7/prebuilt/lib/msvc2017_64" -lQt5Mqtt
}

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# copy runtime dependencies
win32 {
    DESTDIR_WIN = $${OUT_PWD}
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN = $${PWD}
    PWD_WIN ~= s,/,\\,g
    Debug:SUB_DIR = debug
    Release:SUB_DIR = release

    # copy mosquitto runtime dll
    Debug:QMAKE_POST_LINK += $$quote((robocopy $${PWD_WIN}\\3rdparty\\qtmqtt\\v5.12.7\\prebuilt\\lib\\msvc2017_64 $${DESTDIR_WIN}\\$${SUB_DIR} Qt5Mqttd.dll /NS /NC /NP /NFL /NDL /NJH /NJS) ^& IF %ERRORLEVEL% LEQ 4 exit /B 0$$escape_expand(\\n\\t))
    Release:QMAKE_POST_LINK += $$quote((robocopy $${PWD_WIN}\\3rdparty\\qtmqtt\\v5.12.7\\prebuilt\\lib\\msvc2017_64 $${DESTDIR_WIN}\\$${SUB_DIR} Qt5Mqtt.dll /NS /NC /NP /NFL /NDL /NJH /NJS) ^& IF %ERRORLEVEL% LEQ 4 exit /B 0$$escape_expand(\\n\\t))
}
