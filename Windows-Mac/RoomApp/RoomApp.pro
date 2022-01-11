QT += core gui webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoomApp
TEMPLATE = app

CONFIG += c++11
CONFIG += debug_and_release warn_on
CONFIG += thread exceptions rtti stl

# set path for auto-generated ui header files
UI_DIR = ./auto-generated/ui_auto_gen
RCC_DIR += ./auto-generated

LIBS += -L"."
DEPENDPATH += .
MOC_DIR += ./auto-generated
OBJECTS_DIR += ./auto-generated/release

DESTDIR = ../bin

include(RoomApp.pri)
include(RoomModule.pri)
RESOURCES += $$PWD/Resource/RoomApp.qrc

INCLUDEPATH += $$PWD/../Module/include
DEPENDPATH += $$PWD/../Module/include
INCLUDEPATH += $$PWD/../utils
INCLUDEPATH += $$PWD/../utils/jsoncpp
INCLUDEPATH += $$PWD/../Common
INCLUDEPATH += $$PWD/../Common/MessageDispatcher

INCLUDEPATH += $${SOURCE_PATHS}
DEPENDPATH += $${SOURCE_PATHS}

INCLUDEPATH += $$PWD/App
INCLUDEPATH += $$PWD/App/Common

QMAKE_CFLAGS_RELEASE   = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE   = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

win32{
INCLUDEPATH += $$PWD/../SDK/LiteAVSDK/CPlusPlus/Win32/include/
INCLUDEPATH += $$PWD/../SDK/LiteAVSDK/CPlusPlus/Win32/include/TRTC
INCLUDEPATH += $$PWD/../SDK/ImSDK/Win/include/
INCLUDEPATH += $$PWD/../utils/BugReport/
INCLUDEPATH += $$PWD/3rdParty/zlib/include/
INCLUDEPATH += $$PWD/../utils/usersig/win/include
DEPENDPATH += $$PWD/../utils/usersig/win/include

LIBS += $$PWD/../SDK/LiteAVSDK/CPlusPlus/Win32/lib/liteav.lib \
        $$PWD/../SDK/ImSDK/Win/lib/Win32/imsdk.lib \
        $$PWD/3rdParty/zlib/x86/zlibstatic.lib
LIBS += -lgdi32 -luser32
}

macx {
QMAKE_INFO_PLIST += Info.plist

# 添加库依赖
LIBS += "-F$$PWD/../utils/usersig/mac"
LIBS += "-F$$PWD/../SDK/LiteAVSDK/CPlusPlus/Mac"
LIBS += "-F$$PWD/../SDK/ImSDK/Mac"
LIBS += -framework TXLiteAVSDK_TRTC_Mac
LIBS += -framework ImSDKForMac_CPP
LIBS += -framework Accelerate
LIBS += -framework AudioUnit
LIBS += -lbz2
LIBS += -lresolv
#without c++11 & AppKit library compiler can't solve address for symbols
LIBS += -framework AppKit

# 添加TXLiteAVSDK_TRTC_Mac.framework头文件
INCLUDEPATH += $$PWD/../SDK/LiteAVSDK/CPlusPlus/Mac/TXLiteAVSDK_TRTC_Mac.framework/Headers/cpp_interface
INCLUDEPATH += $$PWD/../SDK/LiteAVSDK/CPlusPlus/Mac/TXLiteAVSDK_TRTC_Mac.framework/Headers

# 添加ImSDKForMac.framework头文件
INCLUDEPATH += $$PWD/../SDK/ImSDK/Mac/ImSDKForMac_CPP.framework/Headers

macx: LIBS += -L$$PWD/../utils/usersig/mac -lTXLiteAVTestUserSig
macx: PRE_TARGETDEPS += $$PWD/../utils/usersig/mac/libTXLiteAVTestUserSig.a
QMAKE_CXXFLAGS += -std=gnu++11
#CONFIG += console

INCLUDEPATH += $$PWD/../utils/usersig/mac/include
DEPENDPATH += $$PWD/../utils/usersig/mac/include

DISTFILES += $$PWD/../utils/usersig/mac/libTXLiteAVTestUserSig.a
}


