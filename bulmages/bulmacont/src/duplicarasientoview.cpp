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

#include "duplicarasientoview.h"
#include "empresa.h"
#include "funcaux.h"

#define NUMDIGITOS   empresaactual->numdigitosempresa()


DuplicarAsientoView::DuplicarAsientoView(empresa *emp, QWidget *parent, Qt::WFlags flag)
        : QDialog(parent, flag) {
    _depura("DuplicarAsientoView::DuplicarAsientoView", 0);
    setupUi(this);
    empresaactual = emp;
    fdinicial->setText(QDate::currentDate().toString("dd/MM/yyyy"));
    _depura("END DuplicarAsientoView::DuplicarAsientoView", 0);
}


DuplicarAsientoView::~DuplicarAsientoView() {
    _depura("DuplicarAsientoView::~DuplicarAsientoView", 0);
    _depura("END DuplicarAsientoView::~DuplicarAsientoView", 0);
}


void DuplicarAsientoView::inicializa(QString ainicial, QString afinal) {
    _depura("DuplicarAsientoView::inicializa", 0);
    aoinicial->setText(ainicial);
    aofinal->setText(afinal);
    QString query = "SELECT * FROM asiento WHERE ordenasiento = " + ainicial;
    empresaactual->begin();
    cursor2 *cur = empresaactual->cargacursor(query, "hola");
    empresaactual->commit();
    if (!cur->eof()) {
        foinicial->setText(cur->valor("fecha").left(10));
    } // end if
    delete cur;
    aoinicial->selectAll();
    aoinicial->setFocus();
    _depura("END DuplicarAsientoView::inicializa", 0);
}


void DuplicarAsientoView::lostFocus() {
    _depura("DuplicarAsientoView::lostFocus", 0);
    QString ainicial = aoinicial->text();
    QString query = "SELECT * FROM asiento WHERE ordenasiento = " + ainicial;
    empresaactual->begin();
    cursor2 *cur = empresaactual->cargacursor(query, "hola");
    empresaactual->commit();
    if (!cur->eof()) {
        foinicial->setText(cur->valor("fecha").left(10));
    } // end if
    delete cur;
    _depura("END DuplicarAsientoView::lostFocus", 0);
}



void DuplicarAsientoView::on_mui_aceptar_clicked() {
    _depura("DuplicarAsientoView::on_mui_aceptar_clicked", 0);
    QString asientoi = aoinicial->text();
    QString asientof = aofinal->text();
    QString query1, query2;
    QString textidasiento;
    //int ordeninicial = 0;
    //int idasientoinicial = 0;

    QString idasiento;
    QString ordenasiento;

    QString textordeninicial;
    QDate fedinicial = normalizafecha(fdinicial->text());

/*
    /// Buscamos el orden asiento para la duplicaci&oacute;n.
    QString query = "SELECT max(ordenasiento) AS orden FROM asiento ";
    empresaactual->begin();
    cursor2 *cur = empresaactual->cargacursor(query);
    if (!cur->eof()) {
        ordeninicial = atoi(cur->valor("orden").toAscii()) + 1;
    } // end if
    delete cur;

    query1 = "SELECT max(idasiento) AS maxim FROM asiento";
    cursor2 *cursaux = empresaactual->cargacursor(query1);
    if (!cursaux->eof()) {
        idasiento = atoi(cursaux->valor("maxim").toAscii());
        idasientoinicial = atoi(cursaux->valor("maxim").toAscii()) + 1;
    } // end if
    delete cursaux;
*/

    query1 = "SELECT * FROM asiento WHERE ordenasiento >= " + asientoi + " AND ordenasiento <= " + asientof +" AND EXTRACT (YEAR FROM fecha) = EXTRACT (YEAR FROM '" + fedinicial.toString("dd/MM/yyyy") + "'::date)";
    cursor2 *curasiento = empresaactual->cargacursor(query1);
    while (!curasiento->eof()) {

        query1 = "INSERT INTO asiento (descripcion, fecha, comentariosasiento) VALUES('" + curasiento->valor("descripcion") + "','" + fedinicial.toString("dd/MM/yyyy") + "','" + curasiento->valor("comentariosasiento") + "')";
        empresaactual->ejecuta(query1);


    query1 = "SELECT * FROM asiento  ORDER BY idasiento DESC LIMIT 1";
    cursor2 *cursaux = empresaactual->cargacursor(query1);
    if (!cursaux->eof()) {
        idasiento = cursaux->valor("idasiento");
        ordenasiento = cursaux->valor("ordenasiento");
    } // end if
    delete cursaux;



        query2 = "SELECT * FROM borrador WHERE idasiento = " + curasiento->valor("idasiento");
        cursor2 *curborrador = empresaactual->cargacursor(query2);

        while (!curborrador->eof()) {
            QString textiddiario = curborrador->valor("iddiario");
            if (textiddiario == "") {
                textiddiario = "NULL";
            } // end if
            QString textfecha = curborrador->valor("fecha");
            textfecha = fedinicial.toString("dd/MM/yyyy");
            QString textconceptocontable = curborrador->valor("conceptocontable");
            QString textidcuenta = curborrador->valor("idcuenta");
            if (textidcuenta == "") {
                textidcuenta = "NULL";
            } // end if
            QString textdescripcion = curborrador->valor("descripcion");
            QString textdebe = curborrador->valor("debe");
            QString texthaber = curborrador->valor("haber");
            QString textcontrapartida = curborrador->valor("contrapartida");
            if (textcontrapartida == "") {
                textcontrapartida = "NULL";
            } // end if
            QString textorden = curborrador->valor("orden");
            if (textorden == "") {
                textorden = "0";
            } // end if
            query2 = "INSERT INTO borrador (orden, idasiento, iddiario, fecha, conceptocontable, idcuenta, descripcion, debe, haber, contrapartida) VALUES (" + textorden + ","+idasiento + "," + textiddiario + ",'" + textfecha + "','" + textconceptocontable + "'," + textidcuenta + ",'" + textdescripcion + "'," + textdebe + "," + texthaber + "," + textcontrapartida + ")";
            empresaactual->ejecuta(query2);
            curborrador->siguienteregistro();
        } // end while
        delete curborrador;
    query2 = "SELECT cierraasiento("+idasiento+")";
    cursor2 *cur = empresaactual->cargacursor(query2);
    delete cur;
        curasiento->siguienteregistro();
    } // end while
    delete curasiento;
    empresaactual->commit();
    done(1);
    _depura("END DuplicarAsientoView::on_mui_aceptar_clicked", 0);
}
