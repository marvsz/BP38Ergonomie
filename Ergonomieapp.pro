include(view/view.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ergonomieapp
TEMPLATE = app

RESOURCES += \
    btnIcons.qrc \
    resrc.qrc

HEADERS += \
    enum.h \
    listcon.h \
    mainmenu.h \
    mainwindow.h \
    stopwatch.h \
    tool.h \
    toolview.h \
    viewcontroller.h \
    textqpushbutton.h \
    textcon.h \
    seperator.h \
    angle.h \
    arm.h \
    leg.h \
    head.h \
    torso.h \
    body.h

SOURCES += \
    listcon.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    stopwatch.cpp \
    tool.cpp \
    toolview.cpp \
    viewcontroller.cpp \
    textqpushbutton.cpp \
    textcon.cpp \
    angle.cpp \
    arm.cpp \
    leg.cpp \
    head.cpp \
    torso.cpp \
    body.cpp \


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
