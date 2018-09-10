#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T15:04:04
#
#-------------------------------------------------
#C_OBS_ROOT=$$_PRO_FILE_PWD_/../vendor/obs
C_OBS_ROOT=$$PWD/../../vendor/obs
message(C_OBS_ROOT$${C_OBS_ROOT})

include(./LJ_ADAPTER/ljobsadapter.pri)

C_RELEASE_DEBUG=debug
INCLUDEPATH +=$${C_OBS_ROOT}/libobs

PLATFORM_NAME=win
DEBUG_RELEASE_NAME=release
DEBUG_RELEASE_SUBFIX=
mac{
    PLATFORM_NAME=mac
    QT += macextras
}

CONFIG(debug, debug|release) {
    DEBUG_RELEASE_NAME=debug
    DEBUG_RELEASE_SUBFIX=d
}
#DEFINES *= LJ_OBS

C_LIB_PATH=$${C_OBS_ROOT}/$${PLATFORM_NAME}/lib/$${DEBUG_RELEASE_NAME}
#C_LIB_PATH=$${C_OBS_ROOT}/$${PLATFORM_NAME}/lib/$${DEBUG_RELEASE_NAME}

win32{
    LIBS += -luser32  -lkernel32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
    LIBS += -L$$PWD/libs/win -lagora_rtc_sdk  -lw32-pthreads

#    LIBS += -L$${C_DEPENDENCIES_PATH}/win32/bin -llibcurl -lavcodec -lavfilter -lavdevice -lavutil -lswscale -lavformat -lswresample -lfreetype

    INCLUDEPATH +=$$PWD/include
}
mac{
#    message(C_LIB_PATH$${C_LIB_PATH})
#    C_DEPENDENCIES_PATH=$${C_OBS_ROOT}/deps
#    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreFoundation.framework
#    LIBS += -framework AppKit

#    LIBS += -L$${C_LIB_PATH} -lobs-frontend-api -lobs -lobsglad -lfile-updater -ljansson -llibff
##    LIBS += -L$${C_LIB_PATH} -lobs-frontend-api -lobs -lobsglad -lfile-updater -ljansson
#    LIBS += -lcurl -lobjc -lSystem -lc++
#    LIBS += -L$${C_LIB_PATH} -lavcodec -lavfilter -lavdevice -lavutil -lswscale -lavformat -lswresample -lfreetype
}

#INCLUDEPATH +=$${C_OBS_ROOT}/deps/libff
#INCLUDEPATH +=$${C_OBS_ROOT}/deps/libff/libff
#INCLUDEPATH +=$$PWD/UI
#INCLUDEPATH +=$$PWD/UI/obs-frontend-api
