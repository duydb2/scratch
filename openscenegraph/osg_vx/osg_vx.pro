TEMPLATE = app

# need these flags for gcc 4.8.x bug
QMAKE_LFLAGS += -Wl,--no-as-needed
LIBS += -lpthread
QMAKE_CXXFLAGS += -std=c++11

#openscenegraph
PATH_OPENSCENEGRAPH = /home/preet/Dev/env/sys/osg-3.2.1
PATH_OPENSCENEGRAPH_LIB = /home/preet/Dev/env/sys/osg-3.2.1/lib64
DEFINES += DEV_GL_DESKTOP

INCLUDEPATH += $${PATH_OPENSCENEGRAPH}/include
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB}/osgdb_freetyperd.so
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB}/osgdb_jpegrd.so
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB}/osgdb_pngrd.so
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losgViewer
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losgText
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losgGA
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losgUtil
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losgDB
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -losg
LIBS += -L$${PATH_OPENSCENEGRAPH_LIB} -lOpenThreads

# clipper
HEADERS += clipper.hpp
SOURCES += clipper.cpp


#SOURCES += vx_tilegen_async.cpp
SOURCES += vx_tilegen4.cpp
