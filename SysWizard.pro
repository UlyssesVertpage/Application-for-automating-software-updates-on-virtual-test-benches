QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



## >>>>>>>>>>>>>>>>>>>>>>> WSL-UBUNTU >>>>>>>>>>>>>>>>>>>>>>>
#LIBS += -L ./libLua5.4 -lLua5.4
## LIBS += -L$$PWD/../build/libLua5.4 -llibLua5.4
#INCLUDEPATH += $$PWD/libLua5.4

## QMAKE_CC = gcc-4.8.5
## QMAKE_CXX = g++-4.8.5
## QMAKE_LINK = g++-4.8.5

## Абсолютные пути к GCC 4.8.5
##QMAKE_CC = /usr/local/gcc-4.8.5/bin/gcc
##QMAKE_CXX = /usr/local/gcc-4.8.5/bin/g++
##QMAKE_LINK = /usr/local/gcc-4.8.5/bin/g++
##QMAKE_LINK_SHLIB = /usr/local/gcc-4.8.5/bin/g++

## Для clang
##QMAKE_CXXFLAGS += -Wno-everything       # :-1: предупреждение: unrecognized command line option "-Wno-everything" [enabled by default]
#QMAKE_CXXFLAGS += -fpermissive
## <<<<<<<<<<<<<<<<<<<<<<< WSL-UBUNTU <<<<<<<<<<<<<<<<<<<<<<<









# >>>>>>>>>>>>>>>>>>>>>>> ASTRA >>>>>>>>>>>>>>>>>>>>>>>

 #INCLUDEPATH += /usr/local/include /usr/include/lua5.4
 #INCLUDEPATH += -I/usr/local/include -I/usr/include/lua5.4

 ### Из-за теневой сборки ищет сразу внутри build папки, поэтому ./Lua5.4 находится.
 # LIBS += -L ./Lua5.4 -lLua5.4
 LIBS += -L ./libLua5.4 -lLua5.4

 # Подключаем libssh2-1-dev
 # LIBS += -lssh2
 #LIBS += -L /usr/lib/x86_64-linux-gnu -lssh2
 #INCLUDEPATH += /usr/include


 # "-ldl" только для динамической загрузки библиотек и функций по типу dlopen(), dlclose() и т.д..

 #LIBS += -L ../build/Lua5.4 -lLua5.4

 #LIBS += -LLua5.4 -L/usr/local/lib -llua -ldl
 #LIBS += -L/Lua5.4 -llua -ldl
 #LIBS += -L/usr/local/lib -llua
 #LIBS += -L/Lua5.4 -llua

 #LIBS += -L Lua5.4 -ldl
 #LIBS += -llua -ldl
 #LIBS += -llua5.4 -ldl
 #LIBS += -L/usr/local/lib -ldl
 #LIBS += -L/usr/local/lib -llua -ldl


# <<<<<<<<<<<<<<<<<<<<<<< ASTRA <<<<<<<<<<<<<<<<<<<<<<<












# >>>>>>>>>>>>>>>>>>>>>>> WINDOWS >>>>>>>>>>>>>>>>>>>>>>>

# # QMAKE_CXXFLAGS += /utf-8

# # Если используете qmake, добавьте CONFIG += force_debug_info в .pro файл, чтобы PDB генерировались и в режиме Release.
# # CONFIG += force_debug_info

# # Чтобы на Windows внутри папки для сборки не генерировалось папок debug и release
# CONFIG -= debug_and_release # debug_and_release_target


# INCLUDEPATH += $$PWD/libLua5.4
# # INCLUDEPATH += $$PWD/LuaLib_5_5


# # NOTE: На самом деле мы используем QProcess.. Поэтому скорее всего этот API нам не понадобится.
# # Подключаем libssh2-1-dev
# #LIBS += -lssh2
# #LIBS += -L /usr/lib/x86_64-linux-gnu -lssh2
# #INCLUDEPATH += /usr/include


# # "-ldl" только для динамической загрузки библиотек и функций по типу dlopen(), dlclose() и т.д..

# LIBS += -L$$PWD/../build/libLua5.4 -llibLua5.4
# # LIBS += -L$$PWD/../build/LuaLib_5_5 -lLuaLib_5_5

# <<<<<<<<<<<<<<<<<<<<<<< WINDOWS <<<<<<<<<<<<<<<<<<<<<<<












# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0






SOURCES += \
    AlgorithmExecution.cpp \
    GlobalData.cpp \
    Globals.cpp \
    GroupTable.cpp \
    Launcher.cpp \
    Loger.cpp \
    LogerCrashDumper.cpp \
    LogViewer.cpp \
    main.cpp \
    MainWindow.cpp \

HEADERS += \
    AlgorithmExecution.h \
    GlobalData.h \
    Globals.h \
    GroupTable.h \
    Launcher.h \
    Loger.h \
    LogerCrashDumper.h \
    LogViewer.h \
    MainWindow.h \


#FORMS += \
#    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    resources/Resources.qrc


























# QT       += core gui

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# # QMAKE_CXXFLAGS += /utf-8

# # Если используете qmake, добавьте CONFIG += force_debug_info в .pro файл, чтобы PDB генерировались и в режиме Release.
# # CONFIG += force_debug_info



# CONFIG += c++11
# # Чтобы на Windows внутри папки для сборки не генерировалось папок debug и release
# CONFIG -= debug_and_release # debug_and_release_target



# INCLUDEPATH += $$PWD/libLua5.4
# # INCLUDEPATH += $$PWD/LuaLib_5_5



# # NOTE: На самом деле мы используем QProcess.. Поэтому скорее всего этот API нам не понадобится.
# # Подключаем libssh2-1-dev
# #LIBS += -lssh2
# #LIBS += -L /usr/lib/x86_64-linux-gnu -lssh2
# #INCLUDEPATH += /usr/include



# # "-ldl" только для динамической загрузки библиотек и функций по типу dlopen(), dlclose() и т.д..

# LIBS += -L$$PWD/../build/libLua5.4 -llibLua5.4
# # LIBS += -L$$PWD/../build/LuaLib_5_5 -lLuaLib_5_5



# SOURCES += \
#     AlgorithmExecution.cpp \
#     GlobalData.cpp \
#     GroupTable.cpp \
#     Launcher.cpp \
#     Log2Console.cpp \
#     Loger.cpp \
#     LogViewer.cpp \
#     main.cpp \
#     MainWindow.cpp \

# HEADERS += \
#     AlgorithmExecution.h \
#     GlobalData.h \
#     Globals.h \
#     GroupTable.h \
#     Launcher.h \
#     Log2Console.h \
#     Loger.h \
#     LogViewer.h \
#     MainWindow.h \



# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target



# RESOURCES += \
#     Resources.qrc








































# QT       += core gui

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# CONFIG += c++11


# # INCLUDEPATH += ./SysWizard/libLua5.4
# INCLUDEPATH += ./libLua5.4
# #INCLUDEPATH += /usr/local/include /usr/include/lua5.4
# #INCLUDEPATH += -I/usr/local/include -I/usr/include/lua5.4


# # "-ldl" только для динамической загрузки библиотек и функций по типу dlopen(), dlclose() и т.д..

# LIBS += -L /libLua5.4 -lLua5.4

# #LIBS += -LLua5.4 -L/usr/local/lib -llua -ldl
# #LIBS += -L/Lua5.4 -llua -ldl
# #LIBS += -L/usr/local/lib -llua
# #LIBS += -L/Lua5.4 -llua

# #LIBS += -L Lua5.4 -ldl
# #LIBS += -llua -ldl
# #LIBS += -llua5.4 -ldl
# #LIBS += -L/usr/local/lib -ldl
# #LIBS += -L/usr/local/lib -llua -ldl




# # You can make your code fail to compile if it uses deprecated APIs.
# # In order to do so, uncomment the following line.
# #DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# SOURCES += \
#     main.cpp \
#     MainWindow.cpp

# HEADERS += \
#     MainWindow.h \


# #FORMS += \
# #    mainwindow.ui

# # Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

# # SUBDIRS += \
# #     libLua5.4/
# # #     libLua5.4/libLua5.4.pro \
# # #     libLua5.4/libLua5.4.pro
