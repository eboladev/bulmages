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

#include <QMessageBox>
#include <QWidget>
#include <QObject>
#include <QComboBox>
#include <QToolButton>
#include <QLayout>

#include <fstream>

#include "inventarioview.h"
#include "company.h"
#include "listcontrolstockview.h"
#include "inventario.h"
#include "funcaux.h"


InventarioView::InventarioView(company *comp, QWidget *parent)
        : Ficha(parent), Inventario(comp) {
    _depura("InventarioView::InventarioView", 0);
    setAttribute(Qt::WA_DeleteOnClose);
    setupUi(this);
    /// Usurpamos la identidad de mlist y ponemos nuestro propio widget con sus cosillas.
    subform2->setEmpresaBase(comp);
    setListControlStock(subform2);
    comp->meteWindow(windowTitle(), this);
    _depura("END InventarioView::InventarioView", 0);
}


InventarioView::~InventarioView() {}


void InventarioView::on_mui_guardar2_clicked() {
    _depura("InventarioView::on_mui_guardar2_clicked", 0);
    if (mui_nominventario->text() == "") {
        mensajeInfo(tr("Tiene que escribir una descripcion de inventario antes de guardar"));
        return;
    } // end if
    setfechainventario(mui_fechainventario->text());
    setnominventario(mui_nominventario->text());
    Inventario::guardar();
    _depura("END InventarioView::on_mui_guardar2_clicked", 0);
}


int InventarioView::sacaWindow() {
    _depura("InventarioView::sacaWindow", 0);
    companyact->sacaWindow(this);
    return 0;
    _depura("END InventarioView::sacaWindow", 0);
}


/// Esta funci&oacute;n se ejecuta cuando se ha pulsado sobre el bot&oacute;n de borrar.
void InventarioView::on_mui_borrar2_clicked() {
    _depura("InventarioView::on_mui_borrar2_clicked", 0);
    if (DBvalue("idinventario") != "") {
        if (QMessageBox::question(this,
                                  tr("Borrar inventario"),
                                  tr("Esta a punto de borrar un inventario. Desea continuar?"),
                                  tr("Si"), tr("No"), 0, 1, 0) == 0) {
            Inventario::borrar();
        } // end if
    } // end if
    _depura("END InventarioView::on_mui_borrar2_clicked", 0);
}



void InventarioView::pintaidinventario(QString) {}

void InventarioView::pintafechainventario(QString id) {
    mui_fechainventario->setText(id);
}

void InventarioView::pintanominventario(QString id) {
    mui_nominventario->setText(id);
}

void InventarioView::on_mui_aceptar_clicked() {
	_depura("InventarioView::on_mui_aceptar_clicked", 0);
    setfechainventario(mui_fechainventario->text());
    setnominventario(mui_nominventario->text());
    if (!Inventario::guardar()) {
        close();
    } // end if
	_depura("END InventarioView::on_mui_aceptar_clicked", 0);
}

void InventarioView::on_mui_pregenerar_clicked() {
    pregenerar();
}