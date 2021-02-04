QT += quick

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        QmlAdapter.cpp \
        controller.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    QmlAdapter.h \
    controller.h

win32: LIBS += -L$$PWD/../SLFGameBackend/Debug/ -l SLFGameBackend

INCLUDEPATH += $$PWD/../SLFGameBackend/
DEPENDPATH += $$PWD/../SLFGameBackend/

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../SLFGameBackend/Debug/SLFGameBackend.lib
