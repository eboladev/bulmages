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

#include "cambiactaview.h"
#include "listcuentasview1.h"
#include "empresa.h"

#define CONEXIONBASE empresaactual->bdempresa()
#define NUMDIGITOS   empresaactual->numdigitosempresa()


cambiactaview::cambiactaview(empresa *emp, QWidget *parent, Qt::WFlags flag)
        : QDialog(parent, flag) {
    _depura("cambiactaview::cambiactaview", 0);
    setupUi(this);
    empresaactual = emp;
    mui_codigoorigen->setempresa(emp);
    mui_codigodestino->setempresa(emp);
    _depura("END cambiactaview::cambiactaview", 0);
}


cambiactaview::~cambiactaview() {}


void cambiactaview::accept() {
    _depura("cambiactaview::accept", 0);
    QString origen = mui_codigoorigen->text();
    QString destino = mui_codigodestino->text();
    QString ainicial = asientoinicial->text();
    QString afinal = asientofinal->text();
    QString finicial = fechainicial->text();
    QString ffinal = fechafinal->text();
    /// Modificamos los borradores.
    QString query = "UPDATE borrador SET idcuenta = id_cuenta('" + destino + "') WHERE idcuenta = id_cuenta('" + origen + "')";
    if (ainicial != "") {
        query = query + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento >= " + ainicial + ")";
    } // end if
    if (afinal != "") {
        query = query + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento <= " + afinal + ")";
    } // end if
    if (finicial != "") {
        query = query + " AND fecha >= '" + finicial + "'";
    } // end if
    if (ffinal != "") {
        query = query + " AND fecha <= '" + ffinal + "'";
    } // end if

    /// Modificamos las contrapartidas de los borradores.
    QString query2 = "UPDATE borrador SET contrapartida = id_cuenta('" + destino + "') WHERE contrapartida = id_cuenta('" + origen + "')";
    if (ainicial != "") {
        query2 = query2 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento >= " + ainicial + ")";
    } // end if
    if (afinal != "") {
        query2 = query2 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento <= " + afinal + ")";
    } // end if
    if (finicial != "") {
        query2 = query2 + " AND fecha >= '" + finicial + "'";
    } // end if
    if (ffinal != "") {
        query2 = query2 + " AND fecha <= '" + ffinal + "'";
    } // end if

    /// Modificamos tambi&eacute;n los apuntes.
    QString query1 = "UPDATE apunte SET idcuenta = id_cuenta('" + destino + "') WHERE idcuenta = id_cuenta('" + origen + "')";
    if (ainicial != "") {
        query1 = query1 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento >= " + ainicial + ")";
    } // end if
    if (afinal != "") {
        query1 = query1 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento <= " + afinal + ")";
    } // end if
    if (finicial != "") {
        query1 = query1 + " AND fecha >= '" + finicial + "'";
    } // end if
    if (ffinal != "") {
        query1 = query1 + " AND fecha <= '" + ffinal + "'";
    } // end if

    /// Modificamos tambi&eacute;n las contrapartidas de los apuntes.
    QString query3 = "UPDATE apunte SET contrapartida = id_cuenta('" + destino + "') WHERE contrapartida = id_cuenta('" + origen + "')";
    if (ainicial != "") {
        query3 = query3 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento >= "+ainicial+")";
    } // end if
    if (afinal != "") {
        query3 = query3 + " AND idasiento IN (SELECT idasiento FROM asiento WHERE ordenasiento <= "+afinal+")";
    } // end if
    if (finicial != "") {
        query3 = query3 + " AND fecha >= '" + finicial + "'";
    } // end if
    if (ffinal != "") {
        query3 = query3 + " AND fecha <= '" + ffinal + "'";
    } // end if

    /// Modificamos los registros de IVA.
    QString query4 = "UPDATE registroiva SET contrapartida = id_cuenta('" + destino + "') WHERE contrapartida = id_cuenta('" + origen + "')";
    if (ainicial != "") {
        query4 = query4 + " AND idborrador IN (SELECT idborrador FROM borrador,asiento WHERE ordenasiento >= " + ainicial + " AND borrador.idasiento = asiento.idasiento)";
    } // end if
    if (afinal != "") {
        query4 = query4 + " AND idborrador IN (SELECT idborrador FROM borrador,asiento WHERE ordenasiento <= " + afinal + " AND borrador.idasiento = asiento.idasiento)";
    } // end if
    if (finicial != "") {
        query4 = query4 + " AND ffactura >= '" + finicial + "'";
    } // end if
    if (ffinal != "") {
        query4 = query4 + " AND ffactura <= '" + ffinal + "'";
    } // end if
    CONEXIONBASE->begin();
    CONEXIONBASE->ejecuta(query);
    CONEXIONBASE->ejecuta(query1);
    CONEXIONBASE->ejecuta(query2);
    CONEXIONBASE->ejecuta(query3);
    CONEXIONBASE->ejecuta(query4);
    CONEXIONBASE->commit();
    done(1);
    _depura("END cambiactaview::accept", 0);
}
