/***************************************************************************
 *   Copyright (C) 2006 by Tomeu Borras Riera                              *
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

#include "listiva.h"
#include "empresa.h"
#include "funcaux.h"


ListIva::ListIva(empresa *comp) {
    companyact = comp;
    mdb_idregistroiva = "";
}


ListIva::ListIva() {
    _depura("Constructor de ListIva\n", 0);
    companyact = NULL;
    mdb_idregistroiva = "";
}


ListIva::~ListIva() {}


Iva *ListIva::linpos(int pos) {
    return m_lista.at(pos);
}


/// Carga l&iacute;neas de presupuesto.
int ListIva::cargaListIva(QString idregistroiva) {
    _depura("ListIva::cargaListIva\n", 0);
    int error = 0;
    vaciar();
    mdb_idregistroiva = idregistroiva;

    cursor2 * cur= companyact->cargacursor("SELECT * FROM  tipoiva LEFT JOIN (SELECT * FROM iva WHERE idregistroiva = " + idregistroiva + " ) AS t1 ON t1.idtipoiva = tipoiva.idtipoiva LEFT JOIN cuenta on tipoiva.idcuenta = cuenta.idcuenta  ORDER BY codigo");
    if (cur->error()) {
        error = 1;
    } // end if
    while (!cur->eof()) {
        /// Creamos un elemento del tipo linpresupuesto y lo agregamos a la lista.
        Iva *lin = new Iva(companyact, cur);
        m_lista.append(lin);
        cur->siguienteregistro();
    } // end while
    delete cur;

    /// Tratamiento de excepciones.
    if (error) {
        _depura("Error en la carga de Iva\n", 0);
        return 1;
    } // end if

    _depura("END ListIva::cargaListIva\n", 0);
    return 0;
}


void ListIva::guardaListIva() {
    _depura("ListIva::guardaListIva", 0);
    Iva *linea;

    QMutableListIterator<Iva*> m_ilista(m_lista);
    /// Vamos delante del primer elemento de la lista.
    m_ilista.toFront();
    /// Comprobamos que el primer elemento y siguientes existan.
    while (m_ilista.hasNext()) {
        /// Si existe el elemento nos desplazamos a el moviendo el cursor.
        linea = m_ilista.next();
        if (linea->baseiva() != "") {
            linea->guardaIva();
        } // end if
    } // end while

    _depura("END ListIva::guardaListIva", 0);
}


Fixed ListIva::calculabase() {
    Fixed base("0.00");
    Iva *linea;

    QMutableListIterator<Iva*> m_ilista(m_lista);
    /// Vamos delante del primer elemento de la lista.
    m_ilista.toFront();
    /// Comprobamos que el primer elemento y siguientes existan.
    while (m_ilista.hasNext()) {
        /// Si existe el elemento nos desplazamos a el moviendo el cursor.
        linea = m_ilista.next();
        base = base + Fixed(linea->baseiva());
    } // end while

    return base;
}


Fixed ListIva::calculaiva() {
    Fixed iva("0.00");
    Iva *linea;

    QMutableListIterator<Iva*> m_ilista(m_lista);
    /// Vamos delante del primer elemento de la lista.
    m_ilista.toFront();
    /// Comprobamos que el primer elemento y siguientes existan.
    while (m_ilista.hasNext()) {
        /// Si existe el elemento nos desplazamos a el moviendo el cursor.
        linea = m_ilista.next();
        iva = iva + Fixed(linea->ivaiva());
    } // end while

    return iva;
}


void ListIva::vaciar() {
    mdb_idregistroiva = "";
    m_lista.clear();
}


void ListIva::borrar() {
    if (mdb_idregistroiva != "")  {
        companyact->begin();
        int error = companyact->ejecuta("DELETE FROM iva WHERE idregistroiva = " + mdb_idregistroiva);
        if (error) {
            companyact->rollback();
            return;
        } // end if
        companyact->commit();
    } // end if
}


void ListIva::borraIva(int pos) {
    Iva *linea;
    linea = m_lista.at(pos);
    linea->borrar();
    m_lista.removeAt(pos);
    pintaListIva();
}
