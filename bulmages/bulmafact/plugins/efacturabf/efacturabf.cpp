/***************************************************************************
 *   Copyright (C) 2006 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
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

#include <QMenu>
#include <QAction>
#include <QObject>
#include <QMessageBox>
#include <QToolButton>

#include <stdio.h>

#include "efacturabf.h"
#include "efactura.h"
// #include "efacturaenvio.h"
#include "efacturarecepcion.h"
#include "company.h"
#include "funcaux.h"
// Exportacion
#include "facturaview.h"
#include "efqtoolbutton.h"
// Importacion
#include "facturasplist.h"
#include "efqtoolbutton_importar.h"

efacturabf::efacturabf() {}

efacturabf::~efacturabf() {}

/// Esto es lo que se activa al hacer click sobre el menu
void efacturabf::elslot() {
	EFactura *ef = new EFactura((company *)empresaBase());
	ef->show();
	
// 	EFacturaEnvio *efv = new EFacturaEnvio(empresaBase());
// 	efv->show();
	
// 	EFacturaRecepcion *efr = new EFacturaRecepcion(empresaBase());
// 	efr->show();
	
//     fprintf(stderr,"Sa ha activado el slot\n");
//     QMessageBox::warning(0,
//                          "Titulo de la ventana",
//                          "Mensaje.",
//                          QMessageBox::Ok,
//                          QMessageBox::Cancel);
}

void efacturabf::elslot1() {
	EFacturaRecepcion *efr = new EFacturaRecepcion((company *)empresaBase());
	efr->show();
}

void efacturabf::inicializa(bulmafact *bges) {
	/// Creamos la conexion de la base de datos
	setEmpresaBase(bges->getcompany());
	
	/// Creamos el menu.
// 	QMenu *pPluginMenu = new QMenu("&Factura Electronica");
// 	
// 	QAction *accion = new QAction("&Configuracion de e-factura", 0);
// 	accion->setStatusTip("Muestra statustip");
// 	accion->setWhatsThis("Muestra que es esto");
// 	
// 	QAction *accion1 = new QAction("&Recepcion de e-facturas", 0);
// 	accion1->setStatusTip("Muestra statustip");
// 	accion1->setWhatsThis("Muestra que es esto");
// 
// 	connect(accion, SIGNAL(activated()), this, SLOT(elslot()));
// 	connect(accion1, SIGNAL(activated()), this, SLOT(elslot1()));
// 	
// 	/// Anyadimos los submenus al menu de efactura
// 	pPluginMenu->addAction(accion);
// 	pPluginMenu->addAction(accion1);
// 
// 	/// Anyadimos la nueva opcion al menu principal del programa.
// 	bges->menuBar()->addMenu(pPluginMenu);
}


void entryPoint(bulmafact *bges) {
	_depura("Estoy dentro del plugin de e-factura", 0);
	
	efacturabf *efact = new efacturabf();
	efact->inicializa(bges);
	/// SOLO A MODO DE EJEMPLO: se modifica el titulo de la ventana principal
	/// del programa para indicar que el plugin se ha cargado.
	bges->setWindowTitle("Prueba de plugin e-factura.");
	
	_depura("Acaba el entry point de e-factura", 0);
}

/// Dibuja el boton de exportar en el formulario de factura a cliente

int FacturaView_FacturaView(FacturaView *fac) {
	_depura("FacturaView_FacturaView", 0);
	
	EFQToolButton *mui_exporta_efactura = new EFQToolButton(fac, fac->mui_plugbotones);
	mui_exporta_efactura->setObjectName(QString::fromUtf8("exporta"));
	mui_exporta_efactura->setMinimumSize(QSize(32, 32));
	mui_exporta_efactura->setIcon(QIcon(QString::fromUtf8("/usr/share/bulmages/efactura/efactura.png")));
	mui_exporta_efactura->setIconSize(QSize(22, 22));
	mui_exporta_efactura->setStatusTip("Exportar eFactura");
	mui_exporta_efactura->setToolTip("Exportar eFactura");

       QHBoxLayout *m_hboxLayout1 = fac->mui_plugbotones->findChild<QHBoxLayout *>("hboxLayout1");
       if (!m_hboxLayout1) {
                m_hboxLayout1 = new QHBoxLayout(fac->mui_plugbotones);
                m_hboxLayout1->setSpacing(5);
                m_hboxLayout1->setMargin(5);
                m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       } // end if

	m_hboxLayout1->addWidget(mui_exporta_efactura);
	
	_depura("END FacturaView_FacturaView", 0);
	
	return 0;
}

/// Dibuja el boton de importar en el listado de facturas de proveedor

int FacturasProveedorList_FacturasProveedorList_Post(FacturasProveedorList *listfac) {
	_depura("FacturasProveedorList_FacturasProveedorList_Post", 0);
	
	EFQToolButtonImportar *mui_importa_efactura = new EFQToolButtonImportar(listfac, listfac->mui_plugbotones);
	mui_importa_efactura->setObjectName(QString::fromUtf8("importa"));
	mui_importa_efactura->setMinimumSize(QSize(32, 32));
	mui_importa_efactura->setIcon(QIcon(QString::fromUtf8("/usr/share/bulmages/efactura/efactura.png")));
	mui_importa_efactura->setIconSize(QSize(22, 22));
	mui_importa_efactura->setStatusTip("Importar eFactura");
	mui_importa_efactura->setToolTip("Importar eFactura");

       QHBoxLayout *m_hboxLayout1 = listfac->mui_plugbotones->findChild<QHBoxLayout *>("hboxLayout1");
       if (!m_hboxLayout1) {
                m_hboxLayout1 = new QHBoxLayout(listfac->mui_plugbotones);
                m_hboxLayout1->setSpacing(5);
                m_hboxLayout1->setMargin(5);
                m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       } // end if
	m_hboxLayout1->addWidget(mui_importa_efactura);

	_depura("END FacturasProveedorList_FacturasProveedorList_Post", 0);
	
 	return 0;
}