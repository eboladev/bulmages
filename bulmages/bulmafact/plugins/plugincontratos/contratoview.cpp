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

#include <QCloseEvent>
#include <QComboBox>
#include <QLayout>
#include <QMessageBox>
#include <QObject>
#include <QToolButton>
#include <QWidget>

#include <fstream>

#include "facturaview.h"
#include "company.h"
#include "contrato.h"
#include "contratoview.h"
#include "funcaux.h"
#include "plugins.h"

/** Inicializa la pantalla.
    Inicializa todos los componentes y mete la pantalla en el workSpace.
*/
ContratoView::ContratoView(company *comp, QWidget *parent)
        : Contrato(comp, parent) {
    _depura("ContratoView::ContratoView", 0);
    setAttribute(Qt::WA_DeleteOnClose);
    try {
        setupUi(this);

        /// Disparamos los plugins.
        int res = g_plugins->lanza("ContratoView_ContratoView", this);
        if (res != 0)
            return;

        subform2->setEmpresaBase(comp);
        mui_lineas->setEmpresaBase(comp);
        mui_idcliente->setEmpresaBase(comp);
        mui_refcontrato->setEmpresaBase(comp);

        /// Inicializamos FichaBf
        setListaLineas(mui_lineas);
        comp->meteWindow(windowTitle(), this, FALSE);
    } catch (...) {
        mensajeInfo(tr("Error al crear la contrato"));
    }
    _depura("END ContratoView::ContratoView");
}


/** Al destruir la clase provocamos que se refresque el listado de contratos.
    Para que salga actualizado.
*/
ContratoView::~ContratoView() {
    _depura("ContratoView::~ContratoView", 0);
    _depura("END ContratoView::~ContratoView", 0);
}


/** Inicializa los subformularios y resetea el control de cambios.
*/
void ContratoView::inicializar() {
    _depura("ContratoView::inicializar", 0);
    subform2->inicializar();
    dialogChanges_cargaInicial();
    _depura("END ContratoView::inicializar", 0);
}







/** Carga una contrato de la base de datos.
    Deleta toda la carga a la clase \ref Contrato 
    Cambia el titulo de la ventana y reseta el control de cambios.
*/
int ContratoView::cargar(QString id) {
    _depura("ContratoView::cargar", 0);
    try {
        Contrato::cargar(id);
        if (DBvalue("idcontrato") != "") {
            setWindowTitle(tr("Contrato") + " " + DBvalue("refcontrato") + " " + DBvalue("idcontrato"));
            empresaBase()->meteWindow(windowTitle(), this);
        } // end if
        mui_lineas->cargar(id);
        subform2->cargar("SELECT * FROM factura LEFT JOIN cliente ON cliente.idcliente = factura.idcliente LEFT JOIN almacen ON factura.idalmacen = almacen.idalmacen  WHERE factura.idcliente ="+DBvalue("idcliente")+ " AND reffactura = '"+DBvalue("refcontrato")+"'");
        dialogChanges_cargaInicial();
    } catch (...) {
        return -1;
    } // end try
    _depura("END ContratoView::cargar", 0);
    return 0;
}


/** Guardado de la ficha en la base de datos.
    Utiliza los metodos setXXX para establecer los valores de la Ficha en el DBRecord
    y luego llama a \ref Contrato::guardar() para el guardado en la base de datos.
*/
/// \TODO: Una vez hecho el guardado deberia hacer una carga y dejar de resetear el
/// control de cambios que deberia estar en el metodo de carga.
int ContratoView::guardar() {
    _depura("ContratoView::guardar", 0);
    try {
        setDBvalue("refcontrato", mui_refcontrato->text());
        setDBvalue("nomcontrato", mui_nomcontrato->text());
        setDBvalue("idcliente", mui_idcliente->idcliente());
        setDBvalue("fincontrato", mui_fincontrato->text());
        setDBvalue("ffincontrato", mui_ffincontrato->text());
        setDBvalue("loccontrato", mui_loccontrato->text());
        setDBvalue("descontrato", mui_descontrato->toPlainText());
        setDBvalue("periodicidadcontrato",mui_periodicidadcontrato->periodo());
        Contrato::guardar();
        dialogChanges_cargaInicial();
    } catch (...) {
        _depura("ContratoView::guardar error al guardar", 0);
        throw -1;
    } // end try
    _depura("END ContratoView::guardar", 0);
    return 0;
}


void ContratoView::on_m_cliente_valueChanged(QString id) {
    _depura("ContratoView::on_m_cliente_valueChanged", 0);
    subform2->setIdCliente(id);
    _depura("END ContratoView::on_m_cliente_valueChanged", 0);
}


void ContratoView::pintaidcliente(QString id) {
    mui_idcliente->setidcliente(id);
}


void ContratoView::pintafincontrato(QString id) {
    mui_fincontrato->setText(id);
}


void ContratoView::pintaffincontrato(QString id) {
    mui_ffincontrato->setText(id);
}


void ContratoView::pintadescontrato(QString id) {
    mui_descontrato->setText(id);
}


void ContratoView::pintarefcontrato(QString id) {
    mui_refcontrato->setText(id);
}


void ContratoView::pintanomcontrato(QString id) {
    mui_nomcontrato->setText(id);
}


void ContratoView::pintaperiodicidadcontrato(QString id) {
    _depura("ContratoView::pintaperiodicidadcontrato", 0, id);
    mui_periodicidadcontrato->setperiodo(id);
}

void ContratoView::pintaloccontrato(QString id) {
    mui_loccontrato->setText(id);
}


void ContratoView::on_subform2_itemDoubleClicked(QTableWidgetItem *) {
    _depura("ContratoView::on_subform2_itemDoubleClicked", 0);
    QString idfactura = subform2->DBvalue(QString("idfactura"), subform2->currentRow());
    FacturaView *prov = empresaBase()->newFacturaView();
    if (prov->cargar(idfactura)) {
        delete prov;
        return;
    } // end if
    empresaBase()->m_pWorkspace->addWindow(prov);
    prov->show();
    _depura("END ContratoView::on_subform2_itemDoubleClicked", 0);
}


void ContratoView::on_mui_facturar_clicked() {
    _depura("ContratoView::on_mui_facturar_clicked", 0);
    int periodo = 1;
    QString query;
    bool end = FALSE;
    while(!end) {
	query = "SELECT ('"+DBvalue("fincontrato")+"'::DATE +"+QString::number(periodo-1)+"* '"+DBvalue("periodicidadcontrato")+"'::INTERVAL) AS finperiodo";
	query += ", ('"+DBvalue("fincontrato")+"'::DATE +"+QString::number(periodo)+"* '"+DBvalue("periodicidadcontrato")+"'::INTERVAL) AS ffinperiodo";
	cursor2 *cur1=empresaBase()->cargacursor(query);

        query = "SELECT count(idfactura) AS cuenta FROM factura WHERE ffactura >= '"+cur1->valor("finperiodo")+"'";
        query += " AND ffactura <  '"+cur1->valor("ffinperiodo")+"'";
	query += " AND reffactura = '"+DBvalue("refcontrato")+"'";
        query += " AND idcliente = "+DBvalue("idcliente");

        cursor2 *cur = empresaBase()->cargacursor(query);
        if(cur->valor("cuenta") != "0") {
		if (cur->valor("cuenta") != "1") {
			_depura("Detectada doble factura en un periodo", 2, cur->valor("cuenta"));
		} // end if
	} else {
            // GENERAMOS LA FACTURA
            FacturaView *fac = empresaBase()->newFacturaView();
            empresaBase()->m_pWorkspace->addWindow(fac);
            fac->cargar("0");
            fac->show();
            fac->setDBvalue("reffactura", DBvalue("refcontrato"));
            fac->setDBvalue("idcliente", DBvalue("idcliente"));
            fac->setDBvalue("descfactura", DBvalue("nomcontrato")+" Periodo:  "+cur1->valor("finperiodo").left(10)+ " -- "+cur1->valor("ffinperiodo").left(10));

            QString l;
            SDBRecord *linea, *linea1;
            for (int i = 0; i < m_listalineas->rowCount(); ++i) {
                linea = m_listalineas->lineaat(i);
                if (linea->DBvalue( "idarticulo") != "") {
                    linea1 = fac->getlistalineas()->lineaat(fac->getlistalineas()->rowCount() - 1);
                    linea1->setDBvalue("idarticulo", linea->DBvalue("idarticulo"));
                    linea1->setDBvalue("codigocompletoarticulo", linea->DBvalue("codigocompletoarticulo"));
                    linea1->setDBvalue("nomarticulo", linea->DBvalue("nomarticulo"));
                    linea1->setDBvalue("desclfactura", linea->DBvalue("desclcontrato"));
                    linea1->setDBvalue("descuentolfactura", "0");
                    linea1->setDBvalue("cantlfactura", linea->DBvalue("cantlcontrato"));
                    linea1->setDBvalue("pvplfactura", linea->DBvalue("pvplcontrato"));
                    fac->getlistalineas()->nuevoRegistro();
                } // end if
            } // end for
            fac->calculaypintatotales();
            fac->pintaFactura();
        } // end if
        delete cur;

        query = "SELECT (now() < '"+DBvalue("fincontrato")+"'::DATE + '"+DBvalue("periodicidadcontrato")+"'::INTERVAL *"+QString::number(periodo)+" ) AS dato";
        cur = empresaBase()->cargacursor(query);
        if(cur->valor("dato") == "t") {
            end = TRUE;
        }// end if
	delete cur1;
        periodo++;
    } // end while
    _depura("END ContratoView::on_mui_facturar_clicked", 0);
}

/// =============================================================================
///                    SUBFORMULARIO
/// =============================================================================
/** Prepara el subformulario para trabajar con la tabla factura.
*/
FacturasContratoListSubForm::FacturasContratoListSubForm(QWidget *parent, const char *) : SubForm2Bf(parent) {
    _depura("FacturasContratoListSubForm::FacturasContratoListSubForm", 0);
    setDBTableName("factura");
    setDBCampoId("idfactura");
    setFileConfig("contratofactura");
    addSHeader("numfactura", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Numero"));
    addSHeader("ffactura", DBCampo::DBdate, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Fecha"));
    addSHeader("nomcliente", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Nombre cliente"));
    addSHeader("telfactura", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Telefono factura"));
    addSHeader("bimpfactura", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Base imponible"));
    addSHeader("impfactura", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Impuestos"));
    addSHeader("totalfactura", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Total"));
    addSHeader("procesadafactura", DBCampo::DBboolean, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Procesada"));
    addSHeader("idfactura", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Id factura"));
    addSHeader("reffactura", DBCampo::DBint, DBCampo::DBNotNull | DBCampo::DBPrimaryKey, SHeader::DBNoView | SHeader::DBNoWrite, tr("Ref factura"));
    addSHeader("codigoserie_factura", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Serie"));
    addSHeader("cifcliente", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("CIF cliente"));
    addSHeader("codigoalmacen", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Codigo almacen"));
    addSHeader("contactfactura", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Contact factura"));
    addSHeader("comentfactura", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Comentario factura"));
    addSHeader("idtrabajador", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Id trabajador"));
    addSHeader("idcliente", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Id cliente"));
    addSHeader("idalmacen", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Id almacen"));
    setinsercion(FALSE);
    setDelete(FALSE);
    setSortingEnabled(TRUE);
    _depura("END FacturasContratoListSubForm::FacturasContratoListSubForm", 0);
}

