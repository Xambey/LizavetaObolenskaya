QT += xml
QT += widgets
QMAKE_CXXFLAGS=-std=c++11
SOURCES += \
    main.cpp \
    textedit.cpp \
    addressbookparser.cpp

HEADERS += \
    addressbookparser.h \
    contact.h \
    textedit.h
