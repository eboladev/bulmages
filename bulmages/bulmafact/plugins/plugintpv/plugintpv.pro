# Archivo generado por el gestor qmake de kdevelop.
# Modificado por Tomeu Borras.
# -------------------------------------------------

TEMPLATE = lib

CONFIG += release \
          plugin \
          assistant

LIBS +=	 -rdynamic \
	 -lbulmalib

VERSION = 1.0.0

QMAKE_LIBDIR += ../../../installbulmages

unix{
    TARGET = ../../../installbulmages/plugins/plugintpv
    INCLUDEPATH = ../../../bulmalib/src \
		  .. \
		  ../../src/.ui \
		  /usr/include/qt4 \
                  /usr/include/qt4/Qt \
                  ../../src \
                  ../../../bulmalib/src/.ui \
                  /usr/include/Qt \
                  /usr/include/QtXml

    UI_DIR = .ui

    MOC_DIR = .moc

    OBJECTS_DIR = .obj

    bulmages_install_script.path = .
    bulmages_install_script.extra = echo; echo "**************************"; echo Para Instalar BULMAGES ejecute el script de instalaci�; echo "installbulmages"; echo que encontrara en la carpeta installbulmages.; echo Gracias.; echo "(El equipo de Bulmages)"; echo "**************************"; echo;
    exists(/usr/include/postgresql/libpq-fe.h){
	DEFINES += DISTRO_DEBIAN
	DEFINES += QT_THREAD_SUPPORT
    }
    exists(/usr/include/postgresql/8.0/libpq-fe.h){
	DEFINES += DISTRO_DEBIAN_8_0
	DEFINES += QT_THREAD_SUPPORT
    }
    exists(/usr/include/pgsql/libpq-fe.h){
	DEFINES += DISTRO_RED_HAT
    }
    exists(/usr/include/postgresql/pgsql/libpq-fe.h){
	DEFINES += DISTRO_GENTOO
	DEFINES += QT_THREAD_SUPPORT
    }
    exists(/usr/include/no_se_que/pgsql/libpq-fe.h){
	DEFINES += DISTRO_NO_SE_QUE
    }
}


FORMS +=  zlistbase.ui \
	  zbase.ui


SOURCES = plugintpv.cpp	\
	  zlist.cpp \
	  zview.cpp

HEADERS = plugintpv.h \
	  zlist.h \
	  zview.h
