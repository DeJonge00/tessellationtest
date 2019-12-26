QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamewindow.cpp \
    logic/loading/characterloader.cpp \
    logic/world_objects/bullet.cpp \
    logic/loading/objectloader.cpp \
    logic/character.cpp \
    logic/chunk.cpp \
    logic/fpscounter.cpp \
    logic/gameloopthread.cpp \
    logic/loading/initscenes.cpp \
    logic/world.cpp \
    logic/world_objects/floor.cpp \
    logic/world_objects/phasedobject.cpp \
    logic/world_objects/rotatingobject.cpp \
    logic/world_objects/worldobject.cpp \
    main.cpp \
    mainwindow.cpp \
    rendering/linerenderer.cpp \
    rendering/renderer.cpp \
    rendering/simpleobjectspipeline.cpp \
    rendering/tessellationpipeline.cpp

HEADERS += \
    common_functions.h \
    gamewindow.h \
    logic/world_objects/bullet.h \
    logic/character.h \
    logic/chunk.h \
    logic/object_structs/face.h \
    logic/fpscounter.h \
    logic/gameloopthread.h \
    logic/object_structs/halfedge.h \
    logic/object_structs/vertex.h \
    logic/world.h \
    logic/world_objects/floor.h \
    logic/world_objects/phasedobject.h \
    logic/world_objects/rotatingobject.h \
    logic/world_objects/worldobject.h \
    mainwindow.h \
    rendering/renderer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
