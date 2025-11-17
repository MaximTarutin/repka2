QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    level_01.cpp \
    level_02.cpp \
    level_03.cpp \
    level_04.cpp \
    main.cpp \
    mainwindow.cpp \
    picobject.cpp

HEADERS += \
    level_01.h \
    level_02.h \
    level_03.h \
    level_04.h \
    mainwindow.h \
    picobject.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res1.qrc \
    res2.qrc \
    res3.qrc \
    res_sound.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/release/ -lssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/debug/ -lssl
else:unix: LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/ -lssl

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''

