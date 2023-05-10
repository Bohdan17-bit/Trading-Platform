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
    candles/chartview.cpp \
    main.cpp \
    piechart/drilldownchart.cpp \
    piechart/drilldownslice.cpp \
    storage/database.cpp \
    tablemodel/tablemodeltradehistory.cpp \
    utils/moneyconverter.cpp \
    utils/sound.cpp \
    utils/txtreader.cpp \
    visitor/user.cpp \
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
    candles/chartview.h \
    piechart/drilldownchart.h \
    piechart/drilldownslice.h \
    storage/database.h \
    tablemodel/tablemodeltradehistory.h \
    utils/moneyconverter.h \
    utils/sound.h \
    utils/txtreader.h \
    visitor/user.h \
    window/loginwindow.h \
    window/piechartwindow.h \
    window/portfoliowindow.h \
    window/tradewindow.h \
    ui_loginwindow.h \
    ui_piechartwindow.h \
    ui_portfoliowindow.h \
    ui_tradewindow.h

FORMS += \
    window/loginwindow.ui \
    window/piechartwindow.ui \
    window/portfoliowindow.ui \
    window/tradewindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../dlls/openssl_x32
INCLUDEPATH += ../dlls/openssl_x64

DISTFILES += \
    TradePlatform_en.ts \
    images/arrow-left.png \
    images/arrow-right.png \
    images/candlestick.png \
    images/chart.png \
    images/economics.png \
    images/en.png \
    images/exit.png \
    images/green_triangle.png \
    images/icon.ico \
    images/icon.png \
    images/loading.gif \
    images/red_triangle.png \
    images/ua.png \
    sound/click-error.wav \
    sound/closing_effect.wav \
    sound/interface-hover.wav \
    sound/interface_click.wav \
    sound/joystick_trigger.wav \
    sound/process_complete.wav

TRANSLATIONS += TradePlatform_en.ts
