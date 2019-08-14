#-------------------------------------------------
#
# Project created by QtCreator 2018-08-07T12:03:31
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = missile_attack
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


SOURCES += \
    src/base.cpp \
    src/building.cpp \
    src/buildingexplosion.cpp \
    src/bullet.cpp \
    src/cannon.cpp \
    src/enemy.cpp \
    src/enemyexplosion.cpp \
    src/game.cpp \
    src/main.cpp \
    src/stats.cpp \

HEADERS += \
    src/base.h \
    src/building.h \
    src/buildingexplosion.h \
    src/bullet.h \
    src/cannon.h \
    src/enemy.h \
    src/enemyexplosion.h \
    src/game.h \
    src/stats.h \

FORMS +=

RESOURCES += \
    res.qrc
