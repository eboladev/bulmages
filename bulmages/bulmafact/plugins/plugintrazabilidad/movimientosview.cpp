/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
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

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "busquedaarticulo.h"
#include "busquedacliente.h"
#include "busquedafecha.h"
#include "company.h"
#include "configuracion.h"
#include "movimientosview.h"
#include "funcaux.h"
#include "plugins.h"
#include "ficha.h"
#include "empresabase.h"

/** Prepara todos los componentes i los inicializa a NULL para que no haya dudas sobre si
    ya han sido inicializados o no.
    Inicializando la clase con este constructor precisa que sea establecido el company con setcompany.
*/
/*
MovimientosView::MovimientosView(QWidget *parent, edmode editmodo)
        : FichaBf(NULL, parent, 0) {
    _depura("MovimientosView::MovimientosView", 0);
    setAttribute(Qt::WA_DeleteOnClose);
    setupUi(this);
    iniciaForm();
    m_modo = editmodo;
    mdb_idfactura = "";
    if (m_modo == EditMode) {
        meteWindow(windowTitle(), this);
    } // end if
    hideBusqueda();
    _depura("END MovimientosView::MovimientosView", 0);
}
*/


/** Inicializa todos los componentes y prepara la ventana para funcionar.
*/
MovimientosView::MovimientosView(company *comp, QWidget *parent, edmode editmodo)
        : FichaBf(comp, parent, 0) {
    _depura("MovimientosView::MovimientosView", 0);
    setAttribute(Qt::WA_DeleteOnClose);
    setupUi(this);
    iniciaForm();
    m_cliente->setEmpresaBase(empresaBase());
    m_articulo->setEmpresaBase(empresaBase());
    mui_list->setEmpresaBase(empresaBase());
    presenta();
    m_modo = editmodo;
    mdb_idfactura = "";
    if (m_modo == EditMode) {
        meteWindow(windowTitle(), this);
    } // end if
    hideBusqueda();
    _depura("END MovimientosView::MovimientosView", 0);
}


void MovimientosView::iniciaForm() {
    _depura("MovimientosView::iniciaForm");
    /// Disparamos los plugins.
    int res = g_plugins->lanza("MovimientosView_MovimientosView", this);
    if (res != 0)
        return;
    mui_procesada->insertItem(0, tr("Todas las facturas"));
    mui_procesada->insertItem(1, tr("Facturas procesadas"));
    mui_procesada->insertItem(2, tr("Facturas no procesadas"));
    _depura("END MovimientosView::iniciaForm");
}


/** No precisa de acciones especiales en el destructor de la clase.
*/
MovimientosView::~MovimientosView() {
    _depura("MovimientosView::~MovimientosView", 0);
    empresaBase()->sacaWindow(this);
    _depura("END MovimientosView::~MovimientosView", 0);
}


/** Hace la carga del subformulario y el calculo de los totales.
*/
void MovimientosView::presenta() {
    _depura("MovimientosView::presenta", 0);

    mui_list->cargar("SELECT * FROM movimiento LEFT JOIN articulo ON movimiento.idarticulo=articulo.idarticulo LEFT JOIN almacen ON movimiento.idalmacen = almacen.idalmacen ORDER BY idmovimiento");

    _depura("END MovimientosView::presenta", 0);
}


/** Funcion auxiliar que genera la clausula WHERE de la consulta del listado a partir de las opciones de filtrado que el usuario haya especificado.
*/
QString MovimientosView::generaFiltro() {
    _depura("MovimientosView::generaFiltro", 0);
    /// Tratamiento de los filtros.
    QString filtro = "";

    _depura("END MovimientosView::generaFiltro", 0);
    return (filtro);
}




/** SLOT que responde a la pulsacion del boton de imprimir.
    La impresion de listados esta completamente delegada en SubForm2Bf
*/
void MovimientosView::on_mui_imprimir_clicked() {
    _depura("MovimientosView::on_mui_imprimir_clicked", 0);
    mui_list->imprimirPDF(tr("Facturas a clientes"));
    _depura("MovimientosView::on_mui_imprimir_clicked", 0);
}





/// =============================================================================
///                    SUBFORMULARIO
/// =============================================================================
/** Prepara el subformulario para trabajar con la tabla factura.
*/
MovimientosSubform::MovimientosSubform(QWidget *parent, const char *) : SubForm2Bf(parent) {
    _depura("MovimientosSubform::MovimientosSubform", 0);
    /// Disparamos los plugins.
    int res = g_plugins->lanza("MovimientosSubform_MovimientosSubform", this);
    if (res != 0)
        return;
    setDBTableName("movimiento");
    setDBCampoId("idmovimiento");
    addSHeader("idmovimiento", DBCampo::DBint, DBCampo::DBPrimaryKey, SHeader::DBNone | SHeader::DBNoWrite, tr("idarticulo"));
    addSHeader("fechamovimiento", DBCampo::DBdate, DBCampo::DBNotNull, SHeader::DBNone , tr("Fecha"));
    addSHeader("idarticulo", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNone | SHeader::DBNoWrite, tr("Id Articulo"));
    addSHeader("codigocompletoarticulo", DBCampo::DBvarchar, DBCampo::DBNothing, SHeader::DBNone | SHeader::DBNoWrite, tr("Codigo Articulo"));
    addSHeader("nomarticulo", DBCampo::DBvarchar, DBCampo::DBNothing, SHeader::DBNone | SHeader::DBNoWrite, tr("Nombre Articulo"));
    addSHeader("cantidadmovimiento", DBCampo::DBnumeric, DBCampo::DBNotNull, SHeader::DBNone , tr("Cantidad"));
    addSHeader("lotemovimiento", DBCampo::DBvarchar, DBCampo::DBNothing, SHeader::DBNone, tr("Lote"));
    addSHeader("idalmacen", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNone | SHeader::DBNoWrite, tr("Id Almacen"));
    addSHeader("codigoalmacen", DBCampo::DBvarchar, DBCampo::DBNothing, SHeader::DBNone | SHeader::DBNoWrite, tr("Codigo Almacen"));
    addSHeader("nomalmacen", DBCampo::DBvarchar, DBCampo::DBNothing, SHeader::DBNone | SHeader::DBNoWrite, tr("Nombre Almacen"));
    addSHeader("idlalbaran", DBCampo::DBint, DBCampo::DBNothing, SHeader::DBNone, tr("Id Albaran Cliente"));
    addSHeader("idlalbaranp", DBCampo::DBint, DBCampo::DBNothing, SHeader::DBNone, tr("Id Albaran Proveedor"));

    setinsercion(TRUE);
    setDelete(FALSE);
    setSortingEnabled(FALSE);
    _depura("END MovimientosSubform::MovimientosSubform", 0);
}
