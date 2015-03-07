include(view/view.pri)
include(control/control.pri)
include(databaseHandler/databaseHandler.pri)
include(ftpHandler/ftpHandler.pri)
include(xmlHandler/xmlHandler.pri)

QT += core gui widgets quick qml multimedia sql network

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

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    INCLUDEPATH +=  -F $$PWD/assets/opencv/android/sdk/native/jni/include/opencv2/ \
                    -F $$PWD/assets/opencv/android/sdk/native/jni/include/opencv/

    OPENCV_LIB_PATH = $$PWD/assets/opencv/android/sdk/native/libs/armeabi-v7a
    OPENCV_3RD_PARTY_LIB_PATH = $$PWD/assets/opencv/android/sdk/native/3rdparty/libs/armeabi-v7a

    LIBS += \
        $$OPENCV_LIB_PATH/libopencv_calib3d.a \
        $$OPENCV_LIB_PATH/libopencv_features2d.a \
        $$OPENCV_LIB_PATH/libopencv_flann.a \
        $$OPENCV_LIB_PATH/libopencv_photo.a \
        $$OPENCV_LIB_PATH/libopencv_video.a \
        $$OPENCV_LIB_PATH/libopencv_ml.a \
        $$OPENCV_LIB_PATH/libopencv_objdetect.a \
        $$OPENCV_LIB_PATH/libopencv_imgproc.a \
        $$OPENCV_LIB_PATH/libopencv_contrib.a \
        $$OPENCV_LIB_PATH/libopencv_legacy.a \
        $$OPENCV_LIB_PATH/libopencv_ocl.a \
        $$OPENCV_LIB_PATH/libopencv_stitching.a \
        $$OPENCV_LIB_PATH/libopencv_superres.a \
        $$OPENCV_LIB_PATH/libopencv_ts.a \
        $$OPENCV_LIB_PATH/libopencv_videostab.a \
        $$OPENCV_LIB_PATH/libopencv_highgui.a \
        $$OPENCV_LIB_PATH/libopencv_androidcamera.a \
        $$OPENCV_LIB_PATH/libopencv_core.a

    LIBS += \
        $$OPENCV_3RD_PARTY_LIB_PATH/liblibtiff.a \
        $$OPENCV_3RD_PARTY_LIB_PATH/liblibjpeg.a \
        $$OPENCV_3RD_PARTY_LIB_PATH/liblibjasper.a \
        $$OPENCV_3RD_PARTY_LIB_PATH/liblibpng.a \
        $$OPENCV_3RD_PARTY_LIB_PATH/libIlmImf.a \
        $$OPENCV_3RD_PARTY_LIB_PATH/libtbb.a
}

ios {
    IOS_ICON.files = $$files($$PWD/ios/*.png)
    LAUNCH_IMAGES.files = $$files($$PWD/ios/LaunchImage*.png)
    DATABASES.files = $$system("find $$PWD/assets/ -name '*.sqlite'")
    DATABASES.path = Documents
    QMAKE_BUNDLE_DATA += IOS_ICON
    QMAKE_BUNDLE_DATA += LAUNCH_IMAGES
    QMAKE_BUNDLE_DATA += DATABASES
    QMAKE_INFO_PLIST = ios/Info.plist
    INCLUDEPATH +=  -F $$PWD/assets/opencv/ios/opencv2.framework/Headers/ \
    QMAKE_LFLAGS += -F $$PWD/assets/opencv/ios/opencv2.framework
    LIBS += \
        -F $$PWD/assets/opencv/ios/ \
        -framework opencv2
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

TRANSLATIONS = translations/ergo_trans_de.ts \
                translations/ergo_trans_en.ts

deployment.files += myfile.sqlite
deployment.path = /assets
INSTALLS += deployment

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        /Users/mariusgassen/Documents/Qt/ErgonomieApp/android/libs/armeabi-v7a/libopencv_info.so \
        /Users/mariusgassen/Documents/Qt/ErgonomieApp/android/libs/armeabi-v7a/libopencv_java.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r2.2.0.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r2.3.3.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r3.0.1.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.0.0.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.0.3.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.1.1.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.2.0.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.3.0.so \
        $$PWD/android/libs/armeabi-v7a/libnative_camera_r4.4.0.so
}

