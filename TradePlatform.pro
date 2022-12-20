QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apiaddressbuilder.cpp \
    apiservice.cpp \
    candlegraphbuilder.cpp \
    database.cpp \
    loginwindow.cpp \
    main.cpp \
    portfoliowindow.cpp \
    timeconverter.cpp \
    tradewindow.cpp \
    txtreader.cpp

HEADERS += \
    apiaddressbuilder.h \
    apiservice.h \
    candlegraphbuilder.h \
    database.h \
    loginwindow.h \
    portfoliowindow.h \
    timeconverter.h \
    tradewindow.h \
    txtreader.h

FORMS += \
    loginwindow.ui \
    portfoliowindow.ui \
    tradewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/arrow-left.png \
    images/arrow-right.png \
    images/exit.png \
    images/green_triangle.png \
    images/red_triangle.png
