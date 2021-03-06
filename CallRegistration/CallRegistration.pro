QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    accountmodel.cpp \
    appealcitizensmodel.cpp \
    checkpasswordadmin.cpp \
    dbconnect.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    account.h \
    accountmodel.h \
    appealcitizensmodel.h \
    checkpasswordadmin.h \
    dbconnect.h \
    log.h \
    mainwindow.h

FORMS += \
    account.ui \
    checkpasswordadmin.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
