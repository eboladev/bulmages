/***************************************************************************
 *   Copyright (C) 2003 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/// Este fichero contiene la implementacion de la clase 'configuracion' que se encarga
/// de recoger todos los parametros de configuracion de la aplicacion y los centraliza
/// en un unico objeto que luego es instanciado como objeto global 'confpr'
/// De este modo cualquier objeto de la aplicacion puede consultar
/// (sin demasiados problemas cual es la configuracion que le corresponde).

#include "QTextStream"
#include <QDir>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef WIN32
    #include <unistd.h>
#endif

#include "configuracion.h"
#include "funcaux.h"


#include "abreempresaview.h"


/// El objeto global confpr es la instancia de la clase configuracion. Este objeto
/// puede ser accedido desde todas las clases de la aplicacion.
configuracion *confpr;

/// Constructor de la clase que hace directamente la lectura de los posibles
/// archivos que pueden tener informacion de configuracion. Como parametro
/// reciben el nombre del programa y buscan en este orden su archivo de configuracion.
///
/// 1) /etc/bulmages/ -> Opciones genericas para todos los usuarios.
/// 2) /home/~/.bulmages/  -> Opciones especificas para cada usuario.
///
/// Las opciones se iran cargando desde las mas genericas a las mas especificas.
/// Estas ultimas prevaleceran a las genericas cuando existan.
///
/// Dentro de cada directorio hay las siguientes preferencias a la hora de aplicar
/// las configuraciones:
///
/// 1) bulmages.conf -> archivo para todos los programas del paquete Bulmages.
/// 2) bulmaxxx.conf -> archivo especifico a un solo programa del paquete.
///
/// NOTA: No se puede utilizar _depura dentro de esta clase porque necesita
/// valores que no se disponen antes de leer el archivo de configuraci&oacute;n.
configuracion::configuracion(QString nombreprograma) {
    /// Definimos los directorios donde buscar primero.
#ifdef WIN32
    m_dirGlobalConf = "C:/bulmages/";
#else
    m_dirGlobalConf = "/etc/bulmages/";
#endif
    QString mensaje;
    QFile genericGlobalConfFile;
    QFile programGlobalConfFile;
    QFile genericLocalConfFile;
    QFile programLocalConfFile;
    QDir dirGlobalConf(m_dirGlobalConf);
    QString dirusuario = getenv("HOME");
    m_dirLocalConf = dirusuario + "/.bulmages/";
    m_genericGlobalConfFile = "bulmages.conf";
    m_programGlobalConfFile = nombreprograma + ".conf";
    m_genericLocalConfFile = m_genericGlobalConfFile;
    m_programLocalConfFile = m_programGlobalConfFile;

    /// Comprobamos la existencia de los directorios y archivos de configuracion.
    /// Directorios y archivos obligatorios (sale si no existe):
    if (!dirGlobalConf.exists()) {
        mensaje = "--> ERROR: El directorio '" + m_dirGlobalConf + "' no existe. Debe crearlo. <--\n";
        fprintf(stderr, mensaje.toAscii().constData());
        exit(-1);
    } else {
        if (!genericGlobalConfFile.exists(m_dirGlobalConf + m_genericGlobalConfFile)) {
            mensaje = "--> ERROR: El archivo '" + m_dirGlobalConf + m_genericGlobalConfFile + "' no existe. Debe crearlo. <--\n";
            fprintf(stderr, mensaje.toAscii().constData());
            exit(-1);
        } else {
            /// 1) Leemos la configuracion del archivo generico global.
            mensaje = "--> El archivo '" + m_dirGlobalConf + m_genericGlobalConfFile + "' existe. Se va a leer.<--\n";
            fprintf(stderr, mensaje.toAscii().constData());
            leeconfig(m_dirGlobalConf + m_genericGlobalConfFile);
        }// end if
    } // end if

    /// Directorios y archivos opcionales:
    if (!programGlobalConfFile.exists(m_dirGlobalConf + m_programGlobalConfFile)) {
        mensaje = "--> El archivo '" + m_dirGlobalConf + m_programGlobalConfFile + "' no existe. <--\n";
        fprintf(stderr, mensaje.toAscii().constData());
    } else {
        /// 2) Leemos la configuracion del archivo especifico global.
        mensaje = "--> El archivo '" + m_dirGlobalConf + m_programGlobalConfFile + "' existe. Se va a leer.<--\n";
        fprintf(stderr, mensaje.toAscii().constData());
        leeconfig(m_dirGlobalConf + m_programGlobalConfFile);
    }// end if

    /// Comprobamos si el usuario tiene creado su '/home/~/.bulmages/' directorio
    /// de configuracion.
    if (!dirGlobalConf.exists(m_dirLocalConf)) {
        if (dirGlobalConf.mkdir(m_dirLocalConf) == TRUE) {
            mensaje = "--> Se ha creado el directorio '" + m_dirLocalConf + "'. <--\n";
            fprintf(stderr, mensaje.toAscii().constData());
        } else {
            mensaje = "--> ERROR: No se ha podido crear el directorio '" + m_dirLocalConf + "'. <--\n";
            fprintf(stderr, mensaje.toAscii().constData());
            exit(-1);
        }// end if
    } // end if

    if (!genericLocalConfFile.exists(m_dirLocalConf + m_genericLocalConfFile)) {
        mensaje = "--> El archivo '" + m_dirLocalConf + m_genericLocalConfFile + "' no existe. <--\n";
        fprintf(stderr, mensaje.toAscii().constData());
    } else {
        /// 3) Leemos la configuracion del archivo generico local.
        mensaje = "--> El archivo '" + m_dirLocalConf + m_genericLocalConfFile + "' existe. Se va a leer.<--\n";
        fprintf(stderr, mensaje.toAscii().constData());
        leeconfig(m_dirLocalConf + m_genericLocalConfFile);
    }// end if

    if (!programLocalConfFile.exists(m_dirLocalConf + m_programLocalConfFile)) {
        mensaje = "--> El archivo '" + m_dirLocalConf + m_programLocalConfFile + "' no existe. <--\n";
        fprintf(stderr, mensaje.toAscii().constData());
    } else {
        /// 4) Leemos la configuracion del archivo especifico local.
        mensaje = "--> El archivo '" + m_dirLocalConf + m_programLocalConfFile + "' existe. Se va a leer.<--\n";
        fprintf(stderr, mensaje.toAscii().constData());
        leeconfig(m_dirLocalConf + m_programLocalConfFile);
    }// end if

    setValor(CONF_DIR_USER, m_dirLocalConf);
    setValor(CONF_PRIVILEGIOS_USUARIO, "1");
    setValor(CONF_LOGIN_USER, "");
    setValor(CONF_PASSWORD_USER, "");
}


/// El destructor de la clase no hace nada porque no hay que liberar memoria.
configuracion::~configuracion() {}


/// Puesto que la configuracion funciona sobre un array y sobre defines en dicho array
/// esta funcion dado un define devuelve el nombre utilizado.
/// Esta funcion es util para hacer la insercion inicial de elementos
/// Tambien es util para hacer nosotros el guardado de los parametros.
QString configuracion::nombre(int i) {
    if (i == CONF_BG_APUNTES)
        return "CONF_BG_APUNTES";
    if (i == CONF_FG_APUNTES)
        return "CONF_FG_APUNTES";
    if (i == CONF_BG_APUNTESA)
        return "CONF_BG_APUNTESA";
    if (i == CONF_FG_APUNTESA)
        return "CONF_FG_APUNTESA";
    if (i == CONF_FONTSIZE_APUNTES)
        return "CONF_FONTSIZE_APUNTES";
    if (i == CONF_FONTFAMILY_APUNTES)
        return "CONF_FONTFAMILY_APUNTES";
    if (i == CONF_BG_DIARIO)
        return "CONF_BG_DIARIO";
    if (i == CONF_BG_ALT_DIARIO)
        return "CONF_BG_ALT_DIARIO";
    if (i == CONF_FG_DIARIO1)
        return "CONF_FG_DIARIO1";
    if (i == CONF_FG_DIARIO2)
        return "CONF_FG_DIARIO2";
    if (i == CONF_FONTFAMILY_DIARIO)
        return "CONF_FONTFAMILY_DIARIO";
    if (i == CONF_FONTSIZE_DIARIO)
        return "CONF_FONTSIZE_DIARIO";
    if (i == CONF_CONTRAPARTIDA_DIARIO)
        return "CONF_CONTRAPARTIDA_DIARIO";
    if (i == CONF_CANAL_DIARIO)
        return "CONF_CANAL_DIARIO";
    if (i == CONF_CCOSTE_DIARIO)
        return "CONF_CCOSTE_DIARIO";
    if (i == CONF_BG_EXTRACTO)
        return "CONF_BG_EXTRACTO";
    if (i == CONF_BG_BALANCE)
        return "CONF_BG_BALANCE";
    if (i == CONF_BG_BALANCETREE)
        return "CONF_BG_BALANCETREE";
    if (i == CONF_CONTRAPARTIDA_EXTRACTO)
        return "CONF_CONTRAPARTIDA_EXTRACTO";
    if (i == CONF_CANAL_EXTRACTO)
        return "CONF_CANAL_EXTRACTO";
    if (i == CONF_CCOSTE_EXTRACTO)
        return "CONF_CCOSTE_EXTRACTO";
    if (i == CONF_CONTRAPARTIDA_APUNTES)
        return "CONF_CONTRAPARTIDA_APUNTES";
    if (i == CONF_CANAL_APUNTES)
        return "CONF_CANAL_APUNTES";
    if (i == CONF_CCOSTE_APUNTES)
        return "CONF_CCOSTE_APUNTES";
    if (i == CONF_METABASE)
        return "CONF_METABASE";
    if (i == CONF_SERVIDOR)
        return "CONF_SERVIDOR";
    if (i == CONF_PUERTO)
        return "CONF_PUERTO";
    if (i == CONF_FLIP)
        return "CONF_FLIP";
    if (i == CONF_PYTHON)
        return "CONF_PYTHON";
    if (i == CONF_DIR_TMP)
        return "CONF_DIR_TMP";
    if (i == CONF_PDF)
        return "CONF_PDF";
    if (i == CONF_NAVEGADOR)
        return "CONF_NAVEGADOR";
    if (i == CONF_EDITOR)
        return "CONF_EDITOR";
    if (i == CONF_SPLASH)
        return "CONF_SPLASH";
    if (i == CONF_SPLASH_BULMAFACT)
        return "CONF_SPLASH_BULMAFACT";
    if (i == CONF_BACKGROUND)
        return "CONF_BACKGROUND";
    if (i == CONF_EJECUTABLES)
        return "CONF_EJECUTABLES";
    if (i == CONF_PLANTILLA)
        return "CONF_PLANTILLA";
    if (i == CONF_TRADUCCION)
        return "CONF_TRADUCCION";
    if (i == CONF_DIR_TRADUCCION)
        return "CONF_DIR_TRADUCCION";
    if (i == CONF_ARCHIVO_LOG)
        return "CONF_ARCHIVO_LOG";
    if (i == CONF_DIR_REPORTS)
        return "CONF_DIR_REPORTS";
    if (i == CONF_DIR_KUGAR)
        return "CONF_DIR_KUGAR";
    if (i == CONF_DIR_OPENREPORTS)
        return "CONF_DIR_OPENREPORTS";
    if (i == CONF_PLUGINS_BULMACONT)
        return "CONF_PLUGINS_BULMACONT";
    if (i == CONF_PLUGINS_BULMAFACT)
        return "CONF_PLUGINS_BULMAFACT";
    if (i == CONF_PLUGINS_BULMAGES)
        return "CONF_PLUGINS_BULMAGES";
    if (i == CONF_DIR_IMG_ARTICLES)
        return "CONF_DIR_IMG_ARTICLES";
    if (i == CONF_DIR_IMG_PERSONAL)
        return "CONF_DIR_IMG_PERSONAL";
    if (i == CONF_FONTFAMILY_BULMAGES)
        return "CONF_FONTFAMILY_BULMAGES";
    if (i == CONF_FONTSIZE_BULMAGES)
        return "CONF_FONTSIZE_BULMAGES";
    if (i == CONF_PROGDATA)
        return "CONF_PROGDATA";
    if (i == CONF_NUM_AUT_PRESUP)
        return "CONF_NUM_AUT_PRESUP";
    if (i == CONF_NUM_AUT_FACTURA)
        return "CONF_NUM_AUT_FACTURA";
    if (i == CONF_NUM_AUT_ALBARAN)
        return "CONF_NUM_AUT_ALBARAN";
    if (i == CONF_MOSTRAR_ALMACEN)
        return "CONF_MOSTRAR_ALMACEN";
    if (i == CONF_BG_LISTPRESUPUESTOS)
        return "CONF_BG_LISTPRESUPUESTOS";
    if (i == CONF_BG_LINPRESUPUESTOS)
        return "CONF_BG_LINPRESUPUESTOS";
    if (i == CONF_BG_DESCPRESUPUESTOS)
        return "CONF_BG_DESCPRESUPUESTOS";
    if (i == CONF_BG_LISTPEDIDOSCLIENTE)
        return "CONF_BG_LISTPEDIDOSCLIENTE";
    if (i == CONF_BG_LINPEDIDOSCLIENTE)
        return "CONF_BG_LINPEDIDOSCLIENTE";
    if (i == CONF_BG_DESCPEDIDOSCLIENTE)
        return "CONF_BG_DESCPEDIDOSCLIENTE";
    if (i == CONF_BG_LISTALBARANESCLIENTE)
        return "CONF_BG_LISTALBARANESCLIENTE";
    if (i == CONF_BG_LINALBARANESCLIENTE)
        return "CONF_BG_LINALBARANESCLIENTE";
    if (i == CONF_BG_DESCALBARANESCLIENTE)
        return "CONF_BG_DESCALBARANESCLIENTE";
    if (i == CONF_BG_LISTFACTURASCLIENTE)
        return "CONF_BG_LISTFACTURASCLIENTE";
    if (i == CONF_BG_LINFACTURASCLIENTE)
        return "CONF_BG_LINFACTURASCLIENTE";
    if (i == CONF_BG_DESCFACTURASCLIENTE )
        return "CONF_BG_DESCFACTURASCLIENTE";
    if (i == CONF_BG_LISTARTICULOS)
        return "CONF_BG_LISTARTICULOS";
    if (i == CONF_DIR_CANUALES)
        return "CONF_DIR_CANUALES";
    if (i == CONF_DEBUG)
        return "CONF_DEBUG";
    if (i == CONF_ALERTAS_DB)
        return "CONF_ALERTAS_DB";
    return "";
}


/// This method writes the configuration of the system to the home bulmages.conf file
/// Este metodo escribe la configuracion del sistema en el fichero bulmages.conf del
/// 'home' del usuario.
void configuracion::saveconfig() {
    QString dir1 = getenv("HOME");
    dir1 = dir1 + "/.bulmages/" + m_dirLocalConf;

    QFile file(dir1);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream filestr(&file);
    for (int i = 0; i < 1000; i++) {
        if (nombre(i) != "") {
            filestr << nombre(i).toAscii().data();
            filestr << "   ";
            filestr << valor(i).toAscii().data();
            filestr << endl;
        } // end if
    } // end for
    file.close();
}


/// This method reads the configuration params from a file 'fich' that
/// contains the configuration.
/// Lee la configuracion del fichero de configuracion pasado y rellena la estructura.
bool configuracion::leeconfig(QString fich) {
    _depura("configuracion::leeconfig", 0);
    QFile arch(fich);
    if (arch.open(QIODevice::ReadOnly)) {
        fprintf(stderr, "Leyendo configuracion\n");
        QTextStream in(&arch);
        while (!in.atEnd()) {
            QString cad = in.readLine();
            /// Hacemos la lectura de lineas de configuracion multilinea.
            while (cad.endsWith("\\")) {
                cad = cad.left(cad.length() - 2) + in.readLine().trimmed();
            } // end while

            for (int i = 0; i < 1000; i++) {
                if (cad.startsWith(nombre(i)) && nombre(i) != "") {
                    _depura("[" + nombre(i) + "]" + "--->" + cad, 0);
                    cad = cad.right(cad.length() - nombre(i).length());
                    cad = cad.trimmed();
                    m_valores[i] = cad;
                } // end if
            } // end for
        } // end while
        arch.close();
        fprintf(stderr, "FIN Leyendo configuracion\n");
        return TRUE;
    } // end if
    _depura("END configuracion::leeconfig", 0);
    return FALSE;
}


/// Devuelve el valor de un campo determinado.
/// \param i Par&aacute;metro del que se quiere el valor.
/// \return El valor que tiene dicho par&aacute;metro.
QString configuracion::valor(int i) {
    if (m_valores.contains(i)) {
        return (m_valores[i]);
    } // end if
    return "";
}


/// Establece el valor de un campo determinado con la tupla que se pasa como par&aacute;metro.
/// \param i El &iacute;ndice del par&aacute;metro a cambiar.
/// \param valor El valor que tomar&iacute;a dicho par&aacute;metro.
void configuracion::setValor(int i, QString valor) {
    m_valores[i] = valor;
}
