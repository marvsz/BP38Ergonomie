include(view/view.pri)
include(model/model.pri)
QT       += core gui quick qml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

CONFIG += c++11

RESOURCES += \
    btnIcons.qrc \
    timerIcons.qrc \
    declarative-camera.qrc \
    specialPurposeIcons.qrc

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
   QMAKE_BUNDLE_DATA += ICON_FILES
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
    View/view.pri

TRANSLATIONS = ergo_trans_de.ts
