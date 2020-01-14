#-------------------------------------------------
#
# Project created by QtCreator 2019-04-14T21:02:28
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LevelDesigner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Game/Ability.cpp \
    Game/Expression.cpp \
    Game/Sound.cpp \
    SpriteCreator/ResourceManager/AssetManager.cpp \
    SpriteCreator/ResourceManager/ExpressionDialog.cpp \
        main.cpp \
        mainwindow.cpp \
    graphicsview.cpp \
    sprite.cpp \
    SpriteCreator/spritecreator.cpp \
    Game/Spritesheet.cpp \
    Game/Entity.cpp \
    SpriteCreator/LevelDesigner.cpp \
    Game/Globals.cpp \
    Game/ResourceLoader.cpp \
    Game/ResourceGlobals.cpp \
    Game/Camera.cpp \
    SpriteCreator/ResourceManager.cpp \
    Game/Unit.cpp \
    SpriteCreator/ResourceOpenDialog.cpp \
    SpriteCreator/ResourceManager/UnitManager.cpp \
    SpriteCreator/ResourceManager/AbilityManager.cpp
HEADERS += \
    Game/Ability.h \
    Game/Expression.h \
    Game/Sound.h \
    SpriteCreator/ResourceManager/AssetManager.h \
    SpriteCreator/ResourceManager/ExpressionDialog.h \
        mainwindow.h \
    graphicsview.h \
    sprite.h \
    SpriteCreator/spritecreator.h \
    Game/Spritesheet.h \
    Game/Entity.h \
    SpriteCreator/LevelDesigner.h \
    Game/Globals.h \
    Game/ResourceLoader.h \
    Game/ResourceGlobals.h \
    Game/Camera.h \
    SpriteCreator/ResourceManager.h \
    Game/Unit.h \
    SpriteCreator/ResourceOpenDialog.h \
    SpriteCreator/ResourceManager/UnitManager.h \
    SpriteCreator/ResourceManager/AbilityManager.h \
    Game/StatDialog.h

FORMS += \
    SpriteCreator/ResourceManager/AssetManager.ui \
    SpriteCreator/ResourceManager/ExpressionDialog.ui \
        mainwindow.ui \
    SpriteCreator/spritecreator.ui \
    SpriteCreator/LevelDesigner.ui \
    SpriteCreator/ResourceManager.ui \
    SpriteCreator/ResourceOpenDialog.ui \
    SpriteCreator/ResourceManager/UnitManager.ui \
    SpriteCreator/ResourceManager/AbilityManager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Icons.qrc

DISTFILES += \
    Resources/Logbook
