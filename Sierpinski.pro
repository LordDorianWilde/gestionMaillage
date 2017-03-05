#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T03:27:41
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sierpinski
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    gasket.cpp \
    maillage.cpp \
    parseroff.cpp \
    sommet.cpp \
    triangle.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    gasket.h \
    maillage.h \
    parseroff.h \
    sommet.h \
    triangle.h

FORMS    += mainwindow.ui
