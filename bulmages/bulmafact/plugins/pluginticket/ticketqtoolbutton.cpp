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

#include <QWidget>
#include "ticketqtoolbutton.h"
#include "funcaux.h"


#include <stdio.h>
#include <stdlib.h>

#include <QFile>
#include <QTextStream>


#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>
#include "facturapview.h"
#include "presupuestoview.h"
#include "fixed.h"


#include "facturaview.h"
#include "company.h"
#include "dbrecord.h"


TicketQToolButton::TicketQToolButton(PresupuestoView *pres, PedidoClienteView *ped, AlbaranClienteView *alb, FacturaView *fac , QWidget *parent) : QToolButton(parent) {
    _depura("TicketQToolButton::TicketQToolButton", 0);
    m_presupuestoView = pres;
    m_pedidoClienteView = ped;
    m_albaranClienteView = alb;
    m_facturaView = fac;
    setBoton();
    _depura("END TicketQToolButton::TicketQToolButton", 0);
}

TicketQToolButton::~TicketQToolButton() {}

void TicketQToolButton::setBoton() {
    _depura("TicketQToolButton::setBoton", 0);
    connect(this, SIGNAL(clicked()), this, SLOT(click()));
    setObjectName(QString::fromUtf8("exporta"));
    setStatusTip("Imprimir Ticket");
    setToolTip("Imprimir Ticket");
    setMinimumSize(QSize(32, 32));
    setIcon(QIcon(QString::fromUtf8("/usr/share/bulmages/icons/ticket.png")));
    setIconSize(QSize(22, 22));
    _depura("END TicketQToolButton::setBoton", 0);
}


void TicketQToolButton::click() {
    _depura("ImpQToolButton::click", 0);



    if (m_albaranClienteView != NULL) {

        m_companyact = m_albaranClienteView->empresaBase();


        QFile file( "/dev/usblp0" );
        if ( !file.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
            _depura("Error en la Impresion de ticket", 2);
        } // end if


        file.write (QString("Conetxia Soluciones Informaticas S.L\n").toAscii());
        file.write (QString("====================================\n").toAscii());
        file.write(QString("Joaquin Turina, 1 Local 4\n").toAscii());
        file.write(QString("CP: 07004 Palma de Mallorca\n").toAscii());
        file.write(QString("Tel: 971 29 06 29\n").toAscii());
        /// Imprimimos espacios
        file.write ( "\n \n", 3);
        /// Imprimimos la fecha
        file.write( QString("Fecha: ").toAscii());
        QDate fecha = QDate::currentDate();
        QString sfecha = fecha.toString("d-M-yyyy");
        file.write( sfecha.toAscii());
        file.write ( "\n", 1);

        file.write( QString("Trabajador: ").toAscii());
        file.write( m_albaranClienteView->m_trabajador->currentText().toAscii());
        file.write ( "\n", 1);

        file.write( QString("Cliente: ").toAscii());
        file.write( m_albaranClienteView->m_cliente->cifcliente().toAscii());
        file.write ( " ", 1);
        file.write( m_albaranClienteView->m_cliente->nomcliente().toAscii());
        file.write ( "\n", 1);



        file.write( QString("Descripcion: ").toAscii());
        file.write( m_albaranClienteView->DBvalue("descalbaran").toAscii());
        file.write ( "\n", 1);

        /// Imprimimos espacios
        file.write ( "\n \n", 3);

        QString l;
        SDBRecord *linea;
        for (int i = 0; i < m_albaranClienteView->getlistalineas()->rowCount(); ++i) {
            linea = m_albaranClienteView->getlistalineas()->lineaat(i);
            if (linea->DBvalue( "idarticulo") != "") {
                QString str = linea->DBvalue("cantlalbaran").rightJustified(5,' ')+QString("   ")+linea->DBvalue("desclalbaran").leftJustified(23,' ', TRUE)+linea->DBvalue("pvplalbaran").rightJustified(10, ' ');
                file.write(str.toAscii());
                file.write ( "\n", 1);
            } // end if
        } // end for

        /// Imprimimos espacios
        file.write ( "\n \n", 3);

        /// Imprimimos la base imponible
        QString stotalbases = QString("Base Imp").rightJustified(30,' ');
        stotalbases = stotalbases + m_albaranClienteView->m_totalBases->text().rightJustified(10,' ');
        file.write(stotalbases.toAscii());
        file.write ( "\n", 1);

        /// Imprimimos el IVA
        QString stotaltases = QString("I.V.A.").rightJustified(30,' ');
        stotaltases = stotaltases + m_albaranClienteView->m_totalTaxes->text().rightJustified(10,' ');
        file.write(stotaltases.toAscii());
        file.write ( "\n", 1);

        /// Imprimimos el total
        file.write (QString("____________________\n").rightJustified(42,' ').toAscii());

        QString stotal = QString("TOTAL").rightJustified(30,' ');
        stotal = stotal + m_albaranClienteView->m_totalalbaran->text().rightJustified(10,' ');
        file.write(stotal.toAscii());
        file.write ( "\n", 1);


        /// Imprimimos espacios
        file.write ( "\n \n \n \n", 7);

        /// Preparamos para un codigo de barras
        /// Especificamos la altura del codigo de barras
        file.write ("\x1Dh\x40",3);
        /// Especificamos que los caracteres vayan debajo del codigo de barras
        file.write ( "\x1DH\x02",3);
        /// Establecemos el tipo de codificacion para el codigo de barras
        file.write ( "\x1D",1);
        file.write ( "f\x01",2);
        ;
        /// Ponemos el ancho de la fuente a uno
        file.write ( "\x1D\x77\x01",3);
        /// Imprimimos la palabra top con el juego de caracteres 04
        file.write ( "\x1Dk\x04",3);
        file.write (QString("ALB").toAscii());
        file.write (" ", 1);
        file.write (m_albaranClienteView->DBvalue("idalbaran").toAscii());
        file.write (" ", 1);
        file.write (m_albaranClienteView->DBvalue("numalbaran").toAscii());
        file.write (" ", 1);
        file.write (m_albaranClienteView->DBvalue("refalbaran").toAscii());
        file.write ("\x00", 1);

        /// Imprimimos el dibujo final
        /*
                file.write ("\x1B\x2A\x00\xD2\x00", 5);
                for (int i=0; i <15; i++) {
                    file.write ( "\x01\x02\x04\x08\x10\x20\x40\x80", 8);
                    file.write ("\x40\x20\x10\x08\x04\x02", 6);
                }
        */
        /// Imprimimos espacios
        file.write ( "\n \n \n \n \n", 9);


        /// El corte de papel.
        file.write ("\x1D\x56\x01", 3);
        file.close();
    } // end if

    if (m_facturaView != NULL) {
        m_companyact = m_facturaView->empresaBase();

        //==========================

        QFile file( "/dev/usblp0" );
        if ( !file.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
            _depura("Error en la Impresion de ticket", 2);
        } // end if


        file.write (QString("Conetxia Soluciones Informaticas S.L\n").toAscii());
        file.write (QString("====================================\n").toAscii());
        file.write(QString("Joaquin Turina, 1 Local 4\n").toAscii());
        file.write(QString("CP: 07004 Palma de Mallorca\n").toAscii());
        file.write(QString("Tel: 971 29 06 29\n").toAscii());
        /// Imprimimos espacios
        file.write ( "\n \n", 3);
        /// Imprimimos la fecha
        file.write( QString("Fecha: ").toAscii());
        QDate fecha = QDate::currentDate();
        QString sfecha = fecha.toString("d-M-yyyy");
        file.write( sfecha.toAscii());
        file.write ( "\n", 1);

        /*
        	file.write( QString("Trabajador: ").toAscii());
                file.write( m_facturaView->m_trabajador->currentText().toAscii());
                file.write ( "\n", 1);
        */
        file.write( QString("Cliente: ").toAscii());
        file.write( m_facturaView->m_cliente->cifcliente().toAscii());
        file.write ( " ", 1);
        file.write( m_facturaView->m_cliente->nomcliente().toAscii());
        file.write ( "\n", 1);



        file.write( QString("Descripcion: ").toAscii());
        file.write( m_facturaView->DBvalue("descfactura").toAscii());
        file.write ( "\n", 1);

        /// Imprimimos espacios
        file.write ( "\n \n", 3);

        QString l;
        SDBRecord *linea;
        for (int i = 0; i < m_facturaView->getlistalineas()->rowCount(); ++i) {
            linea = m_facturaView->getlistalineas()->lineaat(i);
            if (linea->DBvalue( "idarticulo") != "") {
                QString str = linea->DBvalue("cantlfactura").rightJustified(5,' ')+QString("   ")+linea->DBvalue("desclfactura").leftJustified(23,' ', TRUE)+linea->DBvalue("pvplfactura").rightJustified(10, ' ');
                file.write(str.toAscii());
                file.write ( "\n", 1);
            } // end if
        } // end for

        /// Imprimimos espacios
        file.write ( "\n \n", 3);

        /// Imprimimos la base imponible
        QString stotalbases = QString("Base Imp").rightJustified(30,' ');
        stotalbases = stotalbases + m_facturaView->m_totalBases->text().rightJustified(10,' ');
        file.write(stotalbases.toAscii());
        file.write ( "\n", 1);

        /// Imprimimos el IVA
        QString stotaltases = QString("I.V.A.").rightJustified(30,' ');
        stotaltases = stotaltases + m_facturaView->m_totalTaxes->text().rightJustified(10,' ');
        file.write(stotaltases.toAscii());
        file.write ( "\n", 1);

        /// Imprimimos el total
        file.write (QString("____________________\n").rightJustified(42,' ').toAscii());

        QString stotal = QString("TOTAL").rightJustified(30,' ');
        stotal = stotal + m_facturaView->m_totalfactura->text().rightJustified(10,' ');
        file.write(stotal.toAscii());
        file.write ( "\n", 1);


        /// Imprimimos espacios
        file.write ( "\n \n \n \n", 7);

        /// Preparamos para un codigo de barras
        /// Especificamos la altura del codigo de barras
        file.write ("\x1Dh\x40",3);
        /// Especificamos que los caracteres vayan debajo del codigo de barras
        file.write ( "\x1DH\x02",3);
        /// Establecemos el tipo de codificacion para el codigo de barras
        file.write ( "\x1D",1);
        file.write ( "f\x01",2);
        ;
        /// Ponemos el ancho de la fuente a uno
        file.write ( "\x1D\x77\x01",3);
        /// Imprimimos la palabra top con el juego de caracteres 04
        file.write ( "\x1Dk\x04",3);
        file.write (QString("FAC").toAscii());
        file.write (" ", 1);
        file.write (m_facturaView->DBvalue("idfactura").toAscii());
        file.write (" ", 1);
        file.write (m_facturaView->DBvalue("numfactura").toAscii());
        file.write (" ", 1);
        file.write (m_facturaView->DBvalue("reffactura").toAscii());
        file.write ("\x00", 1);

        /// Imprimimos el dibujo final
        /*
                file.write ("\x1B\x2A\x00\xD2\x00", 5);
                for (int i=0; i <15; i++) {
                    file.write ( "\x01\x02\x04\x08\x10\x20\x40\x80", 8);
                    file.write ("\x40\x20\x10\x08\x04\x02", 6);
                }
        */
        /// Imprimimos espacios
        file.write ( "\n \n \n \n \n", 9);


        /// El corte de papel.
        file.write ("\x1D\x56\x01", 3);
        file.close();
    } // end if

_depura("END ImpQToolButton::click", 0);
}

