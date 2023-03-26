QT       += core gui charts sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/apiaddressbuilder.cpp \
    api/apiservice.cpp \
    api/apiserviceresponse.cpp \
    candles/candlegraphbuilder.cpp \
    candles/candlesticklist.cpp \
    candles/candlesticklistbuilder.cpp \
    chartview.cpp \
    database.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    main.cpp \
    sound.cpp \
    tablemodeltradehistory.cpp \
    timeconverter.cpp \
    txtreader.cpp \
    user.cpp \
    window/loginwindow.cpp \
    window/piechartwindow.cpp \
    window/portfoliowindow.cpp \
    window/tradewindow.cpp

HEADERS += \
    api/apiaddressbuilder.h \
    api/apiservice.h \
    api/apiserviceresponse.h \
    candles/candlegraphbuilder.h \
    candles/candlesticklist.h \
    candles/candlesticklistbuilder.h \
    chartview.h \
    database.h \
    drilldownchart.h \
    drilldownslice.h \
    sound.h \
    tablemodeltradehistory.h \
    timeconverter.h \
    txtreader.h \
    user.h \
    window/loginwindow.h \
    window/piechartwindow.h \
    window/portfoliowindow.h \
    window/tradewindow.h \
    window/ui_loginwindow.h \
    window/ui_piechartwindow.h \
    window/ui_portfoliowindow.h \
    window/ui_tradewindow.h

FORMS += \
    window/loginwindow.ui \
    window/piechartwindow.ui \
    window/portfoliowindow.ui \
    window/tradewindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../api
INCLUDEPATH += ../dlls/openssl_x32
INCLUDEPATH += ../dlls/openssl_x64

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
    images/loading.gif \
    images/red_triangle.png \
    sound/click-error.wav \
    sound/closing_effect.wav \
    sound/interface-hover.wav \
    sound/interface_click.wav \
    sound/joystick_trigger.wav \
    sound/process_complete.wav
