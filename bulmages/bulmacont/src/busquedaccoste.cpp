/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
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

#include <QComboBox>

#include "busquedaccoste.h"
#include "funcaux.h"
#include "empresa.h"


BusquedaCCoste::BusquedaCCoste(QWidget *parent, const char *)
        : QComboBox(parent) {
    _depura("BusquedaCCoste::BusquedaCCoste", 0);
    companyact = NULL;
    m_cursorcombo = NULL;
    connect(this, SIGNAL(activated(int)), this, SLOT(m_activated(int)));
    _depura("END BusquedaCCoste::BusquedaCCoste", 0);
}


BusquedaCCoste::~BusquedaCCoste() {
    _depura("BusquedaCCoste::~BusquedaCCoste", 0);
}


void BusquedaCCoste::setcompany(empresa *comp) {
    companyact = comp;
}


QString BusquedaCCoste::idc_coste() {
    int index= currentIndex();
    if (index > 0) {
        return(m_cursorcombo->valor("idc_coste", index - 1));
    } else {
        return "";
    } // end if
}


void BusquedaCCoste::m_activated(int index) {
    if (index > 0) {
        emit(valueChanged(m_cursorcombo->valor("idc_coste", index - 1)));
    } else {
        emit(valueChanged(""));
    } // end if
}


void BusquedaCCoste::setidc_coste(QString idc_coste) {
    _depura("BusquedaCCoste::setidc_coste", 0, idc_coste);
    if (m_cursorcombo != NULL) {
        delete m_cursorcombo;
    } // end if
    m_cursorcombo = companyact->cargacursor("SELECT * FROM c_coste");
    int i = 0;
    int i1 = 0;
    clear();
    addItem("--");
    while (!m_cursorcombo->eof()) {
        i ++;
        if (m_cursorcombo->valor("idc_coste") == idc_coste) {
            i1 = i;
        } // end if
        addItem(m_cursorcombo->valor("nombre"));
        m_cursorcombo->siguienteregistro();
    } //end while
    setCurrentIndex(i1);
    _depura("END BusquedaCCoste::setidc_coste", 0, idc_coste);
}


/// ===================================================================
/// Busqueda Cuenta Delegate para usar con los subforms
/// ===================================================================
/** Inicializa todos los componentes del Widget a NULL para que no haya posibles confusiones
    sobre si un elemento ha sido creado o no.
    Conecta el SIGNAL activated() con m_activated() para tratarlo.
*/
BusquedaCCosteDelegate::BusquedaCCosteDelegate(QWidget *parent)
        : QComboBox(parent) {
    _depura("BusquedaCCosteDelegate::BusquedaCCosteDelegate", 10);
    m_companyact = NULL;
    setEditable(true);
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
    connect(this, SIGNAL(editTextChanged(const QString &)), this, SLOT(s_editTextChanged(const QString &)));
    _depura("END BusquedaCCosteDelegate::BusquedaCCosteDelegate", 0);
}


void BusquedaCCosteDelegate::setcompany(empresa *comp) {
    m_companyact = comp;
}


/** Libera la memoria reservada.
*/
BusquedaCCosteDelegate::~BusquedaCCosteDelegate() {
    _depura("BusquedaCCosteDelegate::~BusquedaCCosteDelegate", 10);
    _depura("END BusquedaCCosteDelegate::~BusquedaCCosteDelegate", 0);
}


/** Permite indicar al Widget cual es la serie de factura seleccionada por defecto.
    Recarga cursor de serie_factura y cuando encuentra un registro cuyo codigoserie_factura coincide con el pasado
    como parametro lo establece como el registro activo por el comboBox.
*/
void BusquedaCCosteDelegate::s_editTextChanged(const QString &cod) {
    _depura("BusquedaCCosteDelegate::s_editTextChanged", 0);
    static bool semaforo = FALSE;
    QString codigo = cod;

    if (semaforo) {
        return;
    } else {
        semaforo = TRUE;
    } // end if

    m_cursorcombo = m_companyact->cargacursor("SELECT nombre FROM c_coste WHERE nombre LIKE '" + codigo + "%' ORDER BY nombre LIMIT 25");
    clear();

    ///TODO: La idea es que salga en el desplegable del combobox el listado de cuentas que
    /// coincidan con el texto escrito para poder elegirlo.
    while (!m_cursorcombo->eof()) {
        //addItem(m_cursorcombo->valor("codigo") + ".-" + m_cursorcombo->valor("descripcion"));
	addItem(m_cursorcombo->valor("nombre"));
        m_cursorcombo->siguienteregistro();
    }
    delete m_cursorcombo;
    setEditText(cod);

    semaforo = FALSE;
    _depura("END BusquedaCCosteDelegate::s_editTextChanged", 0);
}


