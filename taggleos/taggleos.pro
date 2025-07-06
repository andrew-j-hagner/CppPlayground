QT += core widgets

CONFIG += c++20

TARGET = taggleos
TEMPLATE = app

# Source files
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tagmanager.cpp \
    src/datastore.cpp \
    src/models/tag.cpp \
    src/models/data.cpp \
    src/widgets/tagwidget.cpp \
    src/widgets/searchwidget.cpp

# Header files
HEADERS += \
    src/mainwindow.h \
    src/tagmanager.h \
    src/datastore.h \
    src/models/tag.h \
    src/models/data.h \
    src/widgets/tagwidget.h \
    src/widgets/searchwidget.h

# Include directories
INCLUDEPATH += src src/models src/widgets

# Output directory
DESTDIR = bin

# Object files directory
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

# Enable warnings
QMAKE_CXXFLAGS += -Wall -Wextra

# Windows specific
win32 {
    CONFIG += windows
    QMAKE_CXXFLAGS += -std=c++20
}

# Linux/Unix specific
unix {
    QMAKE_CXXFLAGS += -std=c++20
}

# Debug configuration
CONFIG(debug, debug|release) {
    DEFINES += DEBUG
    TARGET = $$TARGET"_debug"
}

# Release configuration
CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O2
}
