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
    main.cpp \
    mainwindow.cpp \
    picobject.cpp

HEADERS += \
    level_01.h \
    level_02.h \
    level_03.h \
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

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    resource/lev_02/dedka.png \
    resource/lev_02/fomka.png \
    resource/lev_02/fon.png \
    resource/lev_02/level_2.jpg \
    resource/lev_02/leyka.png \
    resource/lev_02/lopata.png \
    resource/lev_02/molotok.png \
    resource/lev_02/mysl.png \
    resource/lev_02/repa.png \
    resource/lev_02/salut.gif \
    resource/lev_02/saray.jpg \
    resource/lev_02/serp.png \
    resource/lev_02/topor.png \
    resource/lev_02/vedro.png \
    resource/lev_02/vily.png

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../repka2.pro


}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/release/ -lssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/debug/ -lssl
else:unix: LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/ -lssl

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''
