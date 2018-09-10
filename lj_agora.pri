
INCLUDEPATH += $$PWD/source
INCLUDEPATH += $$PWD/source/base
INCLUDEPATH += $$PWD/source/Agora

HEADERS += \
    $$PWD/source/base/cparamutils.h \
    $$PWD/source/Agora/agorartcengine.hpp \
    $$PWD/source/Agora/CicleBuffer.hpp \
    $$PWD/source/Agora/ExtendAudioFrameObserver.hpp \
    $$PWD/source/Agora/ExtendVideoFrameObserver.hpp

SOURCES += \
    $$PWD/source/base/cparamutils.cpp \
    $$PWD/source/Agora/agorartcengine.cpp \
    $$PWD/source/Agora/CicleBuffer.cpp \
    $$PWD/source/Agora/ExtendAudioFrameObserver.cpp \
    $$PWD/source/Agora/ExtendVideoFrameObserver.cpp

