include(view/view.pri)
include(control/control.pri)
include(databaseHandler/databaseHandler.pri)

QT       += core gui quick qml multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

CONFIG += c++11

RESOURCES += \
    btnIcons.qrc \
    assets.qrc \
    icons.qrc

HEADERS += \
    enum.h

SOURCES += \
    main.cpp

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ios {
   IOS_ICON.files = $$files($$PWD/ios/icon*.png)
   LAUNCH_IMAGES.files = $$files($$PWD/ios/LaunchImage*.png)
   DATABASES.files = $$system("find $$PWD/assets/ -name '*.sqlite'")
   DATABASES.path = Documents
   QMAKE_BUNDLE_DATA += IOS_ICON
   QMAKE_BUNDLE_DATA += LAUNCH_IMAGES
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
    android/AndroidManifest.xml \
    icons/Timer/down.png \
    icons/Timer/down@2x.png \
    icons/Timer/left.png \
    icons/Timer/left@2x.png \
    icons/Timer/minus.png \
    icons/Timer/minus@2x.png \
    icons/Timer/pause.png \
    icons/Timer/pause@2x.png \
    icons/Timer/play.png \
    icons/Timer/play@2x.png \
    icons/Timer/record.png \
    icons/Timer/record@2x.png \
    icons/Timer/reset.png \
    icons/Timer/reset@2x.png \
    icons/Timer/right.png \
    icons/Timer/right@2x.png \
    icons/Timer/stop.png \
    icons/Timer/stop@2x.png \
    icons/Timer/up.png \
    icons/Timer/up@2x.png \
    icons/Timer/zoomIn.png \
    icons/Timer/zoomIn@2x.png \
    icons/Timer/zoomOut.png \
    icons/Timer/zoomOut@2x.png

TRANSLATIONS = ergo_trans_de.ts

deployment.files += myfile.sqlite
deployment.path = /assets
INSTALLS += deployment
