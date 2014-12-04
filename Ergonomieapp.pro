include(view/view.pri)
include(model/model.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

RESOURCES += \
    btnIcons.qrc \
    resrc.qrc

HEADERS += \
    enum.h \
    stopwatch.h \
    transportation.h

SOURCES += \
    main.cpp \
    stopwatch.cpp \
    transportation.cpp

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ios {
    QMAKE_INFO_PLIST = ios/Info.plist
}

unix {
    macx{
        QMAKE_CXXFLAGS += -stdlib=libc++
        QMAKE_CXXFLAGS += -std=c++11
        QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
        QMAKE_LFLAGS += -mmacosx-version-min=10.7
    }
}

OTHER_FILES += \
    View/view.pri
