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

#include <QMessageBox>

#include "canualesview.h"
#include "canualesprintview.h"
#include "importbalance.h"
#include "empresa.h"

#define COL_ARCHIVO 0
#define COL_NOMBRE 1


CAnualesView::CAnualesView(empresa *emp, QWidget *parent)
        : Ficha(parent) {
    _depura("CAnualesView::CAnualesView", 0);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setupUi(this);
    m_companyact = emp;
    m_modo = 0;
    inicializatabla();
    m_companyact->meteWindow(windowTitle(), this);
    _depura("END CAnualesView::CAnualesView", 0);
}


CAnualesView::~CAnualesView() {
    _depura("CAnualesView::~CAnualesView\n", 0);
    m_companyact->sacaWindow(this);
    _depura("END CAnualesView::~CAnualesView\n", 0);
}


void CAnualesView::setmodoselector() {
    m_modo = 1;
}


void CAnualesView::setmodoeditor() {
    m_modo = 0;
}


QString CAnualesView::nomBalance() {
    return m_nomBalance;
}


QString CAnualesView::idBalance() {
    return m_idBalance;
}


void CAnualesView::inicializatabla() {
    _depura("CAnualesView::inicializatabla", 0);

    mui_listado->clear();
    mui_listado->setColumnCount(2);
    QStringList headerlabels;
    headerlabels << tr("Archivo") << tr("Archivo");
    mui_listado->setHorizontalHeaderLabels(headerlabels);

    mui_listado->setColumnWidth(COL_ARCHIVO, 290);
    mui_listado->setColumnWidth(COL_NOMBRE, 290);
    mui_listado->hideColumn(COL_ARCHIVO);

    QDir dir(confpr->valor(CONF_DIR_CANUALES));

    dir.setFilter(QDir::Files );
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    mui_listado->setRowCount(list.size());

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(fileInfo.filePath(), 0);
        mui_listado->setItem(i, COL_ARCHIVO, newItem1);

        /// Cogemos el nombre y lo mostramos.
        QDomDocument doc;
        QFile f(newItem1->text());
        if (!f.open(QIODevice::ReadOnly)) {
            return;
        } // end if
        if (!doc.setContent(&f)) {
            f.close();
            return;
        } // end if
        f.close();
        QDomElement nodo = doc.namedItem("BALANCE").namedItem("TITULO").toElement();
        QTableWidgetItem *newItem2 = new QTableWidgetItem(nodo.text(), 0);

        mui_listado->setItem(i, COL_NOMBRE, newItem2);
    } // end for
    _depura("END CAnualesView::inicializatabla", 0);
}


void CAnualesView::on_mui_listado_itemDoubleClicked(QTableWidgetItem *) {
    _depura("CAnualesView::on_listado_itemDoubleclicked", 0);
    imprimir();
    _depura("END CAnualesView::on_listado_itemDoubleclicked", 0);
}


void CAnualesView::imprimir() {
    _depura("CAnualesView::imprimir", 0);
    QString idbalance = mui_listado->item(mui_listado->currentRow(), COL_ARCHIVO)->text();
    CAnualesPrintView *b = new CAnualesPrintView(m_companyact, 0);
    b->setidbalance(idbalance);
    b->exec();
    delete b;
    _depura("END CAnualesView::imprimir", 0);

}
