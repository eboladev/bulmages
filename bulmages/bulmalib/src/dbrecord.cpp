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

#include "dbrecord.h"
#include "funcaux.h"

#include <QFile>
#include <QTextStream>
#include <QLocale>


bool DBCampo::cambiado() {
    return m_valorcampo != m_valorcampoorig;
}


void DBCampo::resetCambio() {
    m_valorcampoorig = m_valorcampo;
}


DBCampo::~DBCampo() {
    _depura("DBCampo::~DBCampo", 1);
}


postgresiface2 *DBCampo::conexionbase() {
    return m_conexionbase;
}


void DBCampo::setconexionbase(postgresiface2 *comp) {
    m_conexionbase = comp;
}


DBCampo::dbtype DBCampo::tipo() {
    return m_tipo;
}


int DBCampo::set(QString val) {
    m_valorcampo = val;
    return 0;
}


int DBCampo::restrictcampo() {
    return m_restrict;
}


QString DBCampo::nomcampo() {
    return m_nomcampo;
}


QString DBCampo::nompresentacion() {
    return m_nompresentacion;
}


QString DBCampo::valorcampo() {
    return m_valorcampo;
}


DBCampo::DBCampo(postgresiface2 *com, QString nom, dbtype typ, int res, QString nomp) {
    m_conexionbase = com;
    m_nomcampo = nom;
    m_tipo = typ;
    m_restrict = res;
    m_nompresentacion = nomp;
    m_valorcampo = "";
    m_valorcampoorig = "";
}


QString DBCampo::valorcampoprep(int &error) {
    _depura("DBCampo::valorcampoprep", 0);
    error = 0;
    if ((m_restrict & DBNotNull) && !(m_restrict & DBAuto)) {
        if (m_valorcampo == "") {
            mensajeAviso("El campo '" + m_nompresentacion + "' no puede estar vacio.");
            error = -1;
            return "";
        } // end if
    } // end if
    switch (m_tipo) {
    case DBint:
        if (m_valorcampo == "")
            return "NULL";
        return "'" + m_conexionbase->sanearCadena(m_valorcampo) + "'";
    case DBvarchar:
        if (m_valorcampo == "")
            return "NULL";
        return "'" + m_conexionbase->sanearCadena(m_valorcampo) + "'";
    case DBdate:
        if (m_valorcampo == "")
            return "NULL";
        return "'" + m_conexionbase->sanearCadena(m_valorcampo) + "'";
    case DBnumeric:
        if (m_valorcampo == "")
            return "NULL";
        m_valorcampo.replace(",", ".");
        return "'" + m_conexionbase->sanearCadena(m_valorcampo) + "'";
    case DBboolean:
        if (m_valorcampo == "")
            return "NULL";
        if (m_valorcampo == "f" || m_valorcampo == "t")
            return "'" + m_conexionbase->sanearCadena(m_valorcampo) + "'";
        return m_conexionbase->sanearCadena(m_valorcampo);
    } // end switch
    error = -1;
    _depura("Error en la conversion de tipos", 2);
    _depura("END DBCampo::valorcampoprep", 10);
    return "";
}


void DBRecord::setconexionbase(postgresiface2 *comp) {
    m_conexionbase = comp;
}


postgresiface2 *DBRecord::conexionbase() {
    return m_conexionbase;
}


void DBRecord::setDBTableName(QString nom) {
    m_tablename = nom;
}


void DBRecord::setNuevo(bool n) {
    m_nuevoCampo = n;
}


QString DBRecord::tableName() {
    return m_tablename;
}


QString DBRecord::campoId() {
    return m_campoid;
}


void DBRecord::setDBCampoId(QString nom) {
    m_campoid = nom;
}


QList<DBCampo *> *DBRecord::lista() {
    return &m_lista;
}


void DBRecord::vaciar() {
    DBclear();
}


DBRecord::DBRecord(postgresiface2 *con) {
    _depura("DBRecord::DBRecord", 0);
    m_conexionbase = con;
    m_nuevoCampo = TRUE;
    _depura("END DBRecord::DBRecord", 0);
}


DBRecord::~DBRecord() {
    _depura("DBRecord::~DBRecord", 0);
    m_lista.clear();
    _depura("END DBRecord::~DBRecord", 0);
}


int DBRecord::DBload(cursor2 *cur) {
    _depura("DBRecord::DBload", 0);
    m_nuevoCampo = FALSE;
    DBCampo *campo;
    int error = 0;
    for (int i = 0; i < m_lista.size(); ++i) {
        campo = m_lista.at(i);
        if (! (campo->restrictcampo() & DBCampo::DBNoLoad)) {
            QString nom = campo->nomcampo();
            QString val = cur->valor(nom);
            if ((campo->restrictcampo() & DBCampo::DBPrimaryKey) && (val == ""))
                m_nuevoCampo = TRUE;
            if ((campo->restrictcampo() & DBCampo::DBDupPrimaryKey) && (val == ""))
                m_nuevoCampo = TRUE;
            error += campo->set
                     (val);
            /// Al ser una carga consideramos que los cambios estan inicializados.
            campo->resetCambio();
        } // end if
    } // end for
    _depura("END DBRecord::DBload", 0);
    return error;
}


void DBRecord::DBclear() {
    _depura("DBRecord::DBclear", 0);
    m_nuevoCampo = TRUE;
    DBCampo *campo;
    for(int i = 0; i < m_lista.size(); ++i) {
        campo = m_lista.at(i);
        campo->set
        ("");
    } // end for
    _depura("END DBRecord::DBclear", 0);
}


int DBRecord::DBsave(QString &id) {
    _depura("DBRecord::DBsave - " + id, 0);
    try {
        DBCampo *campo;
        QString listcampos = "";
        QString listvalores = "";
        QString queryupdate = "";
        QString separador = "";
        QString separador1 = "";
        QString separadorwhere = "";
        QString querywhere = "";
        int err = 0;
        for (int i = 0; i < m_lista.size(); ++i) {
            campo = m_lista.at(i);
            if (campo->restrictcampo() & DBCampo::DBDupPrimaryKey) {
                QString lin = campo->valorcampoprep(err);
                if (err)
                    throw (-1);
                querywhere += separadorwhere + campo->nompresentacion() + " = " + lin;
                separadorwhere = " AND ";
            } // end if
            if (!(campo->restrictcampo() & DBCampo::DBNoSave)) {
                /// Si el campo es requerido y no esta entonces salimos sin dar error.
                /// No es lo mismo que los not null ya que estos si dan error
                if (campo->restrictcampo() & DBCampo::DBRequired) {
                    if (campo->valorcampo() == "")
                        return 0;
                } // end if
                if (campo->restrictcampo() & DBCampo::DBPrimaryKey) {
                    QString lin = campo->valorcampoprep(err);
                    if (err)
                        throw -1;
                    querywhere += separadorwhere + campo->nomcampo() + " = " + lin;
                    separadorwhere = " AND ";
                } // end if
                if (campo->valorcampoprep(err) != "") {
                    queryupdate += separador1 + campo->nomcampo() + "=" + campo->valorcampoprep(err);
                    separador1 = ", ";
                } // end if
                if (err)
                    throw -1;
                if ((campo->valorcampoprep(err) != "NULL") && (campo->valorcampoprep(err) != "")) {
                    listcampos += separador + campo->nomcampo();
                    listvalores += separador + campo->valorcampoprep(err);
                    if (err)
                        throw -1;
                    separador = ", ";
                } // end if
                /// Si es el ID entonces lo asignamos porque ya tiene el valor correspondiente.
                if (m_campoid == campo->nomcampo()) {
                    id = campo->valorcampo();
                } // end if
            } // end if
        } // end for
        if (m_nuevoCampo) {
            QString query = "INSERT INTO " + m_tablename + " (" + listcampos + ") VALUES (" + listvalores + ")";
            m_conexionbase->ejecuta(query);
            _depura(query, 0);
            cursor2 *cur = m_conexionbase->cargacursor("SELECT " + m_campoid + " FROM " + m_tablename + " ORDER BY " + m_campoid + " DESC LIMIT 1");
            id = cur->valor(m_campoid);
            delete cur;
        } else {
            QString query = "UPDATE " + m_tablename + " SET " + queryupdate + " WHERE " + querywhere;
            _depura(query, 0);
            m_conexionbase->ejecuta(query);
        } // end if
        m_nuevoCampo = FALSE;
        return 0;
    } catch (...) {
        _depura("EXCEPTION DBRecord::DBsave", 0);
        throw -1;
    } // end try
    _depura("END DBRecord::DBSave", 0);
}


int DBRecord::setDBvalue(QString nomb, QString valor) {
    _depura("DBRecord::setDBvalue", 0);
    DBCampo *campo;
    int error = 0;
    int i = 0;
    campo = m_lista.value(i);
    while (campo && campo->nomcampo() != nomb)
        campo = m_lista.value(++i) ;
    if (!campo) {
        _depura("Campo " + nomb + " no encontrado", 2);
        return -1;
    } // end if
    if (campo->nomcampo() == nomb)
        error = campo->set(valor);
    _depura("END DBRecord::setDBvalue", 0);
    return error;
}


QString DBRecord::DBvalue(QString nomb) {
    _depura("DBRecord::value", 0, nomb);
    DBCampo *campo;
    int i = 0;
    campo = m_lista.value(i);
    while (campo && campo->nomcampo() != nomb)
        campo = m_lista.value(++i);
    if (!campo) {
        _depura("Campo " + nomb + " no encontrado", 2);
        return "";
    } // end if
    if (campo->nomcampo() == nomb) {
        return campo->valorcampo();
    } // end if
    return "";
}


bool DBRecord::exists(QString nomb) {
    _depura("DBRecord::exists", 0, nomb);
    DBCampo *campo;
    int i = 0;
    campo = m_lista.value(i);
    while (campo && campo->nomcampo() != nomb)
        campo = m_lista.value(++i);
    if (!campo) {
        return FALSE;
    } // end if
    if (campo->nomcampo() == nomb) {
        return TRUE;
    } // end if
    return FALSE;
}


QString DBRecord::DBvalueprep(QString nomb) {
    _depura("DBRecord::DBvalueprep", 0);
    DBCampo *campo;
    int i = 0;
    campo = m_lista.value(i);
    while (campo && campo->nomcampo() != nomb)
        campo = m_lista.value(++i);
    if (!campo) {
        mensajeAviso("No se ha encontrado el campo '" + nomb + "'.");
        return "";
    } // end if
    if (campo->nomcampo() == nomb) {
        int err;
        return campo->valorcampoprep(err);
    } // end if
    return "";
}


int DBRecord::addDBCampo(QString nom, DBCampo::dbtype typ, int res, QString nomp = "") {
    _depura("DBRecord::addDBCampo", 0);
    DBCampo *camp = new DBCampo(m_conexionbase, nom, typ, res, nomp);
    camp->set
    ("");
    m_lista.append(camp);
    _depura("END DBRecord::addDBCampo", 0);
    return 0;
}


int DBRecord::borrar() {
    _depura("DBRecord::borrar", 0);
    try {
        DBCampo *campo;
        QString separadorwhere = "";
        QString querywhere = "";

        for (int i = 0; i < m_lista.size(); ++i) {
            campo = m_lista.at(i);
            if (campo->restrictcampo() & DBCampo::DBDupPrimaryKey) {
                int err;
                QString lin = campo->valorcampoprep(err);
                if (err)
                    throw -1;
                querywhere += separadorwhere + campo->nompresentacion() + " = " + lin;
                separadorwhere = " AND ";
            } // end if

            if (!(campo->restrictcampo() & DBCampo::DBNoSave)) {
                if (campo->restrictcampo() & DBCampo::DBPrimaryKey) {
                    int err;
                    QString lin = campo->valorcampoprep(err);
                    if (err)
                        throw -1;
                    querywhere += separadorwhere + campo->nomcampo() + " = " + lin;
                    separadorwhere = " AND ";
                } // end if
            } // end if
        } // end for

        if (m_nuevoCampo == FALSE) {
            m_conexionbase->ejecuta("DELETE FROM " + m_tablename + " WHERE " + querywhere);
        } // end if

        _depura("END DBRecord::borrar", 0);
        return 0;
    } catch (...) {
        mensajeInfo("se produjo un error al borrar el elemento");
        _depura("DBRecord::borrar() Error al borrar elemento", 3);
        throw -1;
    }
}


int DBRecord::guardar() {
    _depura("DBRecord::guardar", 0);
    QString id;
    try {
        DBsave(id);
        setDBvalue(m_campoid, id);
        _depura("END DBRecord::guardar", 0);
        return 0;
    } catch (...) {
        mensajeError("DBRecord:: Se ha producido un error al guardar los datos.");
        throw -100;
    } // end try
}


/// Esta funcion carga un articulo.
int DBRecord::cargar(QString id) {
    _depura("DBRecord::cargar", 0);
    QString query = "SELECT * FROM " + m_tablename + " WHERE " + m_campoid + " = " + id;
    cursor2 *cur = m_conexionbase->cargacursor(query);
    if (!cur->eof()) {
        DBload(cur);
    } // end if
    delete cur;
    _depura("END DBRecord::cargar", 0);
    return 0;
}


void DBRecord::imprimir() {
    /// Impresion de un Pedido de Proveedor
    /** Usa la plantilla pedidoproveedor.rml */
    _depura("DBRecord::imprimir", 0);
    DBCampo *campo;
    QString archivo = confpr->valor(CONF_DIR_OPENREPORTS) + "ficha.rml";
    QString archivod = confpr->valor(CONF_DIR_USER) + "ficha.rml";
    QString archivologo = confpr->valor(CONF_DIR_OPENREPORTS) + "logo.jpg";

    /// Copiamos el archivo.
#ifdef WINDOWS

    archivo = "copy " + archivo + " " + archivod;
#else

    archivo = "cp " + archivo + " " + archivod;
#endif

    system (archivo.toAscii().constData());

    /// Copiamos el logo.
#ifdef WINDOWS

    archivologo = "copy " + archivologo + " " + confpr->valor(CONF_DIR_USER) + "logo.jpg";
#else

    archivologo = "cp " + archivologo + " " + confpr->valor(CONF_DIR_USER) + "logo.jpg";
#endif

    system(archivologo.toAscii().constData());

    QFile file;
    file.setFileName(archivod);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString buff = stream.readAll();
    file.close();
    QString fitxersortidatxt = "";

    /// Impresion de la tabla de contenidos.
    for (int i = 0; i < m_lista.size(); ++i) {
        campo = m_lista.at(i);
        fitxersortidatxt += "<tr>\n";
        fitxersortidatxt += "   <td>" + campo->nomcampo() + "</td>\n";
        fitxersortidatxt += "   <td>" + campo->nompresentacion() + "</td>\n";
        fitxersortidatxt += "   <td>" + campo->valorcampo() + "</td>\n";
        fitxersortidatxt += "</tr>";
    } // end for

    buff.replace("[ficha]", m_tablename);
    buff.replace("[story]", fitxersortidatxt);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << buff;
        file.close();
    } // end if

    invocaPDF("ficha");
    _depura("END DBRecord::imprimir", 0);
}
