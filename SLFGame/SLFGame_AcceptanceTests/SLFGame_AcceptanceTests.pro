QT += testlib
QT -= gui
QT += network

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

TEMPLATE = app

SOURCES +=  tst_acceptance.cpp \
    ../SLFGameUI/QmlAdapter.cpp \
    ../SLFGameUI/controller.cpp

win32:CONFIG(Release, Debug|Release): LIBS += -L$$PWD/../SLFGameBackend/x64/Release/ -lSLFGameBackend
else:win32:CONFIG(Debug, Debug|Release): LIBS += -L$$PWD/../SLFGameBackend/x64/Debug/ -lSLFGameBackend

INCLUDEPATH += $$PWD/../SLFGameBackend
DEPENDPATH += $$PWD/../SLFGameBackend

win32-g++:CONFIG(Release, Debug|Release): PRE_TARGETDEPS += $$PWD/../SLFGameBackend/x64/Release/libSLFGameBackend.a
else:win32-g++:CONFIG(Debug, Debug|Release): PRE_TARGETDEPS += $$PWD/../SLFGameBackend/x64/Debug/libSLFGameBackend.a
else:win32:!win32-g++:CONFIG(Release, Debug|Release): PRE_TARGETDEPS += $$PWD/../SLFGameBackend/x64/Release/SLFGameBackend.lib
else:win32:!win32-g++:CONFIG(Debug, Debug|Release): PRE_TARGETDEPS += $$PWD/../SLFGameBackend/x64/Debug/SLFGameBackend.lib

HEADERS += \
    ../SLFGameUI/QmlAdapter.h \
    ../SLFGameUI/controller.h
