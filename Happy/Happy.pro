TEMPLATE = app
CONFIG -= qt

unix {
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
}


unix {
    DESTDIR = $$PWD/../run/linux
}

SOURCES += \
    happy.cpp
