include(view/view.pri)
include(control/control.pri)
include(databaseHandler/databaseHandler.pri)
include(ftpHandler/ftpHandler.pri)

QT       += core gui widgets quick qml multimedia sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

CONFIG += c++11

RESOURCES += \
    btnIcons.qrc \
    assets.qrc \
    icons.qrc

HEADERS += \
    enum.h \
    standardpaths.h \
    translator.h

SOURCES += \
    main.cpp \
    translator.cpp

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ios {
   IOS_ICON.files = $$files($$PWD/ios/*.png)
   LAUNCH_IMAGES.files = $$files($$PWD/ios/LaunchImage*.png)
   DATABASES.files = $$system("find $$PWD/assets/ -name '*.sqlite'")
   DATABASES.path = Documents
   QMAKE_BUNDLE_DATA += IOS_ICON
   QMAKE_BUNDLE_DATA += LAUNCH_IMAGES
   QMAKE_BUNDLE_DATA += DATABASES
   QMAKE_INFO_PLIST = ios/Info.plist
   QMAKE_LFLAGS += -F $$PWD/opencv/opencv2.framework
   LIBS += \
    -F $$PWD/opencv2.framework \
    -framework opencv2 \
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

DISTFILES += \
    ftpHandler/ftpHandler.pri

