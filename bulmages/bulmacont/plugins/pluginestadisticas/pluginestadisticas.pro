# Archivo generado por el gestor qmake de kdevelop.
# -------------------------------------------
# Subdirectorio relativo al directorio principal del proyecto: ./fuentes/src
# Destiono es una aplicaci??n: ../../installbulmages/bulmacont

TEMPLATE = lib 

	
CONFIG = qt \
         plugin \
         warn_on
	 
TARGET = ../../../installbulmages/plugins/estadisticas

VERSION = 1.0.0
DESTDIR = .
LIBS += -lqt-mt \
        -lpq \
	-rdynamic

INCLUDEPATH = ../../../bulmalib \
	      ../../src \
	      ../../src/.ui \
	      /usr/include/qt \
              /usr/lib/qt4/include/Qt \
              ../../src \
	      ../images \
              ../formularios \
              ../../../bulmalib/.ui \
              ../.ui 

HEADERS += estadisticasview.h \
           resmensualview.h \
	   pluginestadisticas.h \
	   estadisticas/tobarchart.h \
           estadisticas/topiechart.h \ 
	   estadisticas/tolinechart.h

SOURCES += estadisticasview.cpp \
           resmensualview.cpp \
	   pluginestadisticas.cpp \
	   estadisticas/tobarchart.cpp \
           estadisticas/tolinechart.cpp \
           estadisticas/topiechart.cpp


  estadisticas/tolinechartsetupui.ui.commands = $$IDL_COMPILER $$IDL_OPTIONS $$tolinechartsetupui.ui.target
  estadisticas/tolinechartsetupui.ui.target = tolinechartsetupui.ui
  estadisticasdlg.ui.commands = $$IDL_COMPILER $$IDL_OPTIONS $$estadisticasdlg.ui.target
  estadisticasdlg.ui.target = estadisticasdlg.ui

  estadisticasdlg.ui.target = contabilidad/estadisticasdlg.ui
  estadisticasdlg.ui.commands = $$IDL_COMPILER $$IDL_OPTIONS $$estadisticasdlg.ui.target
  resmensualdlg.ui.target = contabilidad/resmensualdlg.ui
  resmensualdlg.ui.commands = $$IDL_COMPILER $$IDL_OPTIONS $$resmensualdlg.ui.target
  DEFINES += ESTADISTICAS
  IDLS += estadisticasdlg.ui \
  resmensualdlg.ui\
  estadisticas/tolinechartsetupui.ui

  FORMS += estadisticasdlg.ui \
  resmensualdlg.ui \
  estadisticas/tolinechartsetupui.ui

  IMAGES += estadisticas/print.xpm

unix{
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  bulmages_install_script.path = .
  bulmages_install_script.extra = echo; echo "**************************"; echo Para Instalar BULMAGES ejecute el script de instalaci�n; echo "installbulmages"; echo que encontrara en la carpeta installbulmages.; echo Gracias.; echo "(El equipo de Bulmages)"; echo "**************************"; echo;
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
