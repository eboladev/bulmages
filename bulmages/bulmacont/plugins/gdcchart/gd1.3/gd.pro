# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src/gdcchart
# Target is a library:  gdcchart.lib

SOURCES += gd.cpp \
	    gddemo.cpp \
	    gdfontg.cpp \
	    gdfontl.cpp \
	    gdfontmb.cpp \
	    gdfonts.cpp \
	    gdfontt.cpp \
	    mathmake.cpp \
	    mtables.cpp 

HEADERS += gdfontg.h \
	    gdfontl.h \
	    gdfontmb.h \
	    gdfonts.h \
	    gdfontt.h \
	    gd.h
	    
TEMPLATE = lib 
CONFIG += release \
          warn_on \
	  staticlib

TARGET = gd.lib



win32 {
    DEFINES += WIN32
}