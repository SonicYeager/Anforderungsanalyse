QT += quick

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller.cpp \
        main.cpp \
        qmladapter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_LFLAGS += /STACK:256000000

HEADERS += \
    controller.h \
    qmladapter.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BackEnd/x64/Release/ -lBackEnd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BackEnd/x64/Debug/ -lBackEnd

INCLUDEPATH += $$PWD/../BackEnd/BackEnd
DEPENDPATH += $$PWD/../BackEnd/BackEnd

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../BackEnd/x64/Release/libBackEnd.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../BackEnd/x64/Debug/libBackEnd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../BackEnd/x64/Release/BackEnd.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../BackEnd/x64/Debug/BackEnd.lib
