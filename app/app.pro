include(../MakeTen.pri)
include (views/views.pri)
include (models/models.pri)

QT       += core gui widgets 

TEMPLATE = app
TARGET   = $$IDE_APP_TARGET
DESTDIR  = $$IDE_APP_PATH
VERSION  = $$APP_VERSION


SOURCES += \
    main.cpp \
    maketenglobal.cpp

HEADERS += \
    maketenglobal.h


RESOURCES += \
    app.qrc

win32 {
    RC_FILE = app.rc
}
macx {
    ICON = icons/logo_128x128.icns
}

FORMS +=

DISTFILES += \
    icons/idea.svg

