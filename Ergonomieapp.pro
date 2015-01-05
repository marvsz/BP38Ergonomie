include(view/view.pri)
include(model/model.pri)
include(control/control.pri)
include(databaseHandler/databaseHandler.pri)
QT       += core gui quick qml multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

CONFIG += c++11

RESOURCES += \
    btnIcons.qrc \
    timerIcons.qrc \
    declarative-camera.qrc \
    specialPurposeIcons.qrc \
    assets.qrc

HEADERS += \
    enum.h \
    stopwatch.h \

SOURCES += \
    main.cpp \
    stopwatch.cpp \

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ios {
   ICON_FILES.files = $$system("find $$PWD/ios/icons/ -name '*.png'")
   ICON_FILES.path = ./
   LAUNCH_FILES.files = $$system("find $$PWD/ios/launchimage/ -name '*.png'")
   LAUNCH_FILES.path = ./
   DATABASES.files = $$system("find $$PWD/android/assets/ -name '*.sqlite'")
   DATABASES.path = Documents
   QMAKE_BUNDLE_DATA += ICON_FILES
   QMAKE_BUNDLE_DATA += LAUNCH_FILES
   QMAKE_BUNDLE_DATA += DATABASES
   QMAKE_INFO_PLIST = ios/Info.plist
}

unix {
    macx{
        QMAKE_CXXFLAGS += -stdlib=libc++
        QMAKE_CXXFLAGS += -std=c++11
        QMAKE_CXXFLAGS += -mmacosx-version-min=10.8
        QMAKE_LFLAGS += -mmacosx-version-min=10.8
    }
}

OTHER_FILES += \
    android/AndroidManifest.xml

TRANSLATIONS = ergo_trans_de.ts

deployment.files += myfile.sqlite
deployment.path = /assets
INSTALLS += deployment
