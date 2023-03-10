QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apiaddressbuilder.cpp \
    apiservice.cpp \
    apiserviceresponse.cpp \
    candlegraphbuilder.cpp \
    candlesticklist.cpp \
    candlesticklistbuilder.cpp \
    chartview.cpp \
    database.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    loginwindow.cpp \
    main.cpp \
    piechartwindow.cpp \
    portfoliowindow.cpp \
    tablemodeltradehistory.cpp \
    timeconverter.cpp \
    tradewindow.cpp \
    txtreader.cpp \
    user.cpp

HEADERS += \
    apiaddressbuilder.h \
    apiservice.h \
    apiserviceresponse.h \
    candlegraphbuilder.h \
    candlesticklist.h \
    candlesticklistbuilder.h \
    chartview.h \
    database.h \
    drilldownchart.h \
    drilldownslice.h \
    loginwindow.h \
    piechartwindow.h \
    portfoliowindow.h \
    tablemodeltradehistory.h \
    timeconverter.h \
    tradewindow.h \
    txtreader.h \
    user.h

FORMS += \
    loginwindow.ui \
    piechartwindow.ui \
    portfoliowindow.ui \
    tradewindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/arrow-left.png \
    images/arrow-right.png \
    images/candlestick.png \
    images/chart.png \
    images/economics.png \
    images/exit.png \
    images/green_triangle.png \
    images/icon.ico \
    images/icon.png \
    images/red_triangle.png
