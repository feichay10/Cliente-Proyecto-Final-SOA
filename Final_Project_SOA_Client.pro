QT       += core gui sql network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtask.cpp \
    lib_flot.cpp \
    main.cpp \
    mainwindow.cpp \
    rmalgorithm.cpp \
    svcon.cpp \
    qcustomplot.cpp

HEADERS += \
    addtask.h \
    lib_flot.h \
    mainwindow.h \
    rmalgorithm.h \
    svcon.h \
    qcustomplot.h

FORMS += \
    addtask.ui \
    filter_image.ui \
    mainwindow.ui \
    svcon.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
