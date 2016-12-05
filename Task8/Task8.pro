QT += xml
QT += widgets
QMAKE_CXXFLAGS=-std=c++11

HEADERS += \
    addressbookparser.h \
    contact.h \
    textedit.h

SOURCES += \
    addressbookparser.cpp \
    main.cpp \
    textedit.cpp
