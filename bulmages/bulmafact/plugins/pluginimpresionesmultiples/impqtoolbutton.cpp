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
#include "impqtoolbutton.h"
#include "funcaux.h"

/// Necesarios para importacion de efactura
#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>
#include <QTextStream>
#include "facturapview.h"
#include "fixed.h"

#include "presupuestolist.h"
#include "presupuestoview.h"
#include "pedidosclientelist.h"
#include "pedidoclienteview.h"
#include "albaranclienteview.h"
#include "albaranclientelist.h"
#include "facturaview.h"
#include "cobroslist.h"
#include "cobroview.h"
#include "company.h"
#include "dbrecord.h"


ImpQToolButton::ImpQToolButton(PresupuestoList *pres, PedidosClienteList *ped, AlbaranClienteList *alb,  FacturasList *fac, CobrosList *cob , QWidget *parent) : QToolButton(parent) {
    _depura("ImpQToolButton::ImpQToolButton", 0);
    m_presupuestoList = pres;
    m_pedidosClienteList = ped;
    m_albaranClienteList = alb;
    m_facturasList = fac;
    m_cobrosList = cob;

    setBoton();
    _depura("END ImpQToolButton::ImpQToolButton", 0);
}

ImpQToolButton::~ImpQToolButton() {}

void ImpQToolButton::setBoton() {
    _depura("ImpQToolButton::setBoton", 0);
    connect(this, SIGNAL(clicked()), this, SLOT(click()));
    setObjectName(QString::fromUtf8("exporta"));
    setStatusTip("Imprimir elementos seleccionados");
    setToolTip("Imprimir elementos seleccionados");
    setMinimumSize(QSize(32, 32));
    setIcon(QIcon(QString::fromUtf8(":/Genericos32x32/images/png/i_print1.png")));
    setIconSize(QSize(22, 22));
    _depura("END ImpQToolButton::setBoton", 0);
}

void ImpQToolButton::click() {
    _depura("ImpQToolButton::click", 0);

    QString res = "";

    if (m_presupuestoList != NULL) {
        m_companyact = (company *)m_presupuestoList->empresaBase();
        SubForm3 *sub = m_presupuestoList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idpresupuesto");

                PresupuestoView *pres = m_companyact->nuevoPresupuestoView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("presupuesto");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"presupuesto.pdf "+confpr->valor(CONF_DIR_USER)+"presupuesto"+id+".pdf";
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"presupuesto"+id+".pdf ";
            } // end if
        } // end for
    }

    if (m_facturasList != NULL) {
        m_companyact = (company *)m_facturasList->empresaBase();
        SubForm3 *sub = m_facturasList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idfactura");

                FacturaView *pres = m_companyact->newFacturaView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("factura");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"factura.pdf "+confpr->valor(CONF_DIR_USER)+"factura"+id+".pdf";
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"factura"+id+".pdf ";
            } // end if
        } // end for
    } // end if

    if (m_pedidosClienteList != NULL) {
        m_companyact = (company *)m_pedidosClienteList->empresaBase();
        SubForm3 *sub = m_pedidosClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idpedidocliente");

                PedidoClienteView *pres = m_companyact->newPedidoClienteView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("pedidocliente");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"pedidocliente.pdf "+confpr->valor(CONF_DIR_USER)+"pedidocliente"+id+".pdf";
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"pedidocliente"+id+".pdf ";
            } // end if
        } // end for
    } // end if


    if (m_albaranClienteList != NULL) {
        m_companyact = (company *)m_albaranClienteList->empresaBase();
        SubForm3 *sub = m_albaranClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idalbaran");

                AlbaranClienteView *pres = m_companyact->newAlbaranClienteView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("albaran");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"albaran.pdf "+confpr->valor(CONF_DIR_USER)+"albaran"+id+".pdf";
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"albaran"+id+".pdf ";
            } // end if
        } // end for
    } // end if

    /// TRATAMOS LOS COBROS CUYO LISTADO ES ESPECIAL.
    if (m_cobrosList != NULL) {
        m_companyact = (company *)m_cobrosList->empresaBase();
        SubForm3 *sub = m_cobrosList->mui_list;
        QString txt = "";


        QString archivo = confpr->valor(CONF_DIR_OPENREPORTS) +"recibos.rml";
        QString archivod = confpr->valor(CONF_DIR_USER) + "recibos.rml";
        QString archivologo = confpr->valor(CONF_DIR_OPENREPORTS) + "logo.jpg";


        /// Copiamos el archivo.
#ifdef WINDOWS

        archivo = "copy " + archivo + " " + archivod;
#else

        archivo = "cp " + archivo + " " + archivod;
#endif

        system (archivo.toAscii().constData());
        /// Copiamos el logo
#ifdef WINDOWS

        archivologo = "copy " + archivologo + " " + confpr->valor(CONF_DIR_USER) + "logo.jpg";
#else

        archivologo = "cp " + archivologo + " " + confpr->valor(CONF_DIR_USER) + "logo.jpg";
#endif

        system(archivologo.toAscii().constData());
        QFile file;
        file.setFileName(archivod);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        QString buff = stream.readAll();
        file.close();



        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idcobro");

                Cobro *pres = new Cobro(m_companyact, 0);
                pres->cargar(id);

                QString col = QString::number(2- (i%3));
                if (col == "0") col = "";

                txt += " <storyPlace x=\"0cm\" y=\"0cm\" width=\"15cm\" height=\"1cm\">\n";
                txt += " <setFont name=\"Courier\" size=\"8\"/>\n";
                txt += " <drawString x=\"4.7cm\" y=\""+col+"7.6cm\">"+pres->DBvalue("idcobro")+"</drawString>\n";
                txt += " <drawString x=\"7.2cm\" y=\""+col+"7.6cm\">PALMA DE MALLORCA</drawString>\n";
                txt += " <drawString x=\"14.2cm\" y=\""+col+"7.6cm\">EUROS "+pres->DBvalue("cantcobro")+"</drawString>\n";

                txt += " <drawString x=\"5.7cm\" y=\""+col+"6.8cm\">"+pres->DBvalue("fechacobro")+"</drawString>\n";
                txt += " <drawString x=\"12.4cm\" y=\""+col+"6.8cm\">"+pres->DBvalue("fechacobro")+"</drawString>\n";

		if (pres->DBvalue("idbanco") != "") {
			QString query = "SELECT * FROM banco WHERE idbanco ="+pres->DBvalue("idbanco");
			cursor2 *cur1 = m_companyact->cargacursor(query);
			if (!cur1->eof()){
				txt += " <drawString x=\"9.4cm\" y=\""+col+"4.4cm\">"+cur1->valor("nombanco")+"</drawString>\n";
				txt += " <drawString x=\"9.4cm\" y=\""+col+"4cm\">"+cur1->valor("pobbanco")+"</drawString>\n";
				txt += " <drawString x=\"12.4cm\" y=\""+col+"3.5cm\">"+cur1->valor("codentidadbanco")+" "+cur1->valor("codagenciabanco")+" "+cur1->valor("dcbanco")+" "+cur1->valor("numcuentabanco")+"</drawString>\n";
			} // end if
			delete cur1;
		} // end if


		if (pres->DBvalue("idcliente") != "") {
			QString query = "SELECT * FROM cliente WHERE idcliente ="+pres->DBvalue("idcliente");
			cursor2 *cur = m_companyact->cargacursor(query);
			if (!cur->eof()){
				txt += " <drawString x=\"4.8cm\" y=\""+col+"2.3cm\">"+cur->valor("nomcliente")+"</drawString>\n";
				txt += " <drawString x=\"4.8cm\" y=\""+col+"1.9cm\">"+cur->valor("nomaltcliente")+"</drawString>\n";
				txt += " <drawString x=\"4.8cm\" y=\""+col+"1.5cm\">"+cur->valor("dircliente")+"</drawString>\n";
				txt += " <drawString x=\"4.8cm\" y=\""+col+"1.1cm\">"+cur->valor("cpcliente")+" "+cur->valor("provcliente")+"</drawString>\n";
			} // end if
			delete cur;
		} // end if

                txt += " <drawString x=\"4.8cm\" y=\""+col+"5.6cm\">a</drawString>\n";
                txt += " <drawString x=\"4.8cm\" y=\""+col+"5.2cm\">"+num2texto(pres->DBvalue("cantcobro"))+"</drawString>\n";

                txt += " </storyPlace>\n";

                if (i % 3 == 2)
                    txt += "<nextFrame/>\n";

                delete pres;

            } // end if

        } // end for


        buff.replace("[story]", txt);

        res = confpr->valor(CONF_DIR_USER)+"recibos.pdf ";


        /// En la version para windows hay problemas con las imagenes,
        /// por eso de momento lo dejamos asi.
#ifndef WINDOWS
        //   buff.replace("[detallearticulos]", detalleArticulos());
#endif

        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << buff;
            file.close();
        } // end if



        _depura("FichaBf::imprimir", 0);

        invocaPDF("recibos");

	return;


    } // end if





    QString comando = "kprinter "+res;
    system(comando.toAscii().data());
    comando = "rm "+res;
    system(comando.toAscii().data());
    _depura("END ImpQToolButton::click", 0);
}

// ==================================================================================

SelQToolButton::SelQToolButton(PresupuestoList *pres, PedidosClienteList *ped, AlbaranClienteList *alb,  FacturasList *fac , CobrosList *cob, QWidget *parent) : QToolButton(parent) {
    _depura("SelQToolButton::SelQToolButton", 0);
    m_presupuestoList = pres;
    m_pedidosClienteList = ped;
    m_albaranClienteList = alb;
    m_facturasList = fac;
    m_cobrosList = cob;
    setBoton();
    _depura("END SelQToolButton::SelQToolButton", 0);
}


SelQToolButton::~SelQToolButton() {}

void SelQToolButton::setBoton() {
    _depura("SelQToolButton::setBoton", 0);
    setObjectName(QString::fromUtf8("exporta"));
    setStatusTip("Invertir seleccion de elementos");
    setToolTip("Invertir seleccion de elementos");
    setMinimumSize(QSize(32, 32));
    setIcon(QIcon(QString::fromUtf8(":/Genericos32x32/images/png/i_invert.png")));
    setIconSize(QSize(22, 22));

    connect(this, SIGNAL(clicked()), this, SLOT(click()));
    _depura("END SelQToolButton::setBoton", 0);
}
void SelQToolButton::click() {
    _depura("ImpQToolButton::click", 0);

    // Es posible que esto se haya cargado antes de cargar el company por eso
    // No me fio de que la asignacion en el constructor haya ido bien y reasigno aqui

    QString res = "";

    if (m_presupuestoList != NULL) {
        m_companyact = (company *)m_presupuestoList->empresaBase();
        SubForm3 *sub = m_presupuestoList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            if (rec->DBvalue( "selector") == "TRUE") {
                rec->setDBvalue("selector", "FALSE");
            } else {
                rec->setDBvalue("selector", "TRUE");
            } // end if
        } // end for
    }

    if (m_pedidosClienteList != NULL) {
        m_companyact = (company *)m_pedidosClienteList->empresaBase();
        SubForm3 *sub = m_pedidosClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            if (rec->DBvalue( "selector") == "TRUE") {
                rec->setDBvalue("selector", "FALSE");
            } else {
                rec->setDBvalue("selector", "TRUE");
            } // end if
        } // end for
    }


    if (m_albaranClienteList != NULL) {
        m_companyact = (company *)m_albaranClienteList->empresaBase();
        SubForm3 *sub = m_albaranClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            if (rec->DBvalue( "selector") == "TRUE") {
                rec->setDBvalue("selector", "FALSE");
            } else {
                rec->setDBvalue("selector", "TRUE");
            } // end if
        } // end for
    }


    if (m_facturasList != NULL) {
        m_companyact = (company *)m_facturasList->empresaBase();
        SubForm3 *sub = m_facturasList->mui_list;
        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            if (rec->DBvalue( "selector") == "TRUE") {
                rec->setDBvalue("selector", "FALSE");
            } else {
                rec->setDBvalue("selector", "TRUE");
            } // end if
        } // end for
    }

    if (m_cobrosList != NULL) {
        m_companyact = (company *)m_cobrosList->empresaBase();
        SubForm3 *sub = m_cobrosList->mui_list;
        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            if (rec->DBvalue( "selector") == "TRUE") {
                rec->setDBvalue("selector", "FALSE");
            } else {
                rec->setDBvalue("selector", "TRUE");
            } // end if
        } // end for
    }

    _depura("END ImpQToolButton::click", 0);
}

// ==================================================================================

EmailQToolButton::EmailQToolButton(PresupuestoList *pres, PedidosClienteList *ped, AlbaranClienteList *alb,  FacturasList *fac, CobrosList *cob , QWidget *parent) : QToolButton(parent) {
    _depura("EmailQToolButton::EmailQToolButton", 0);
    m_presupuestoList = pres;
    m_pedidosClienteList = ped;
    m_albaranClienteList = alb;
    m_facturasList = fac;
    m_cobrosList = cob;
    setBoton();
    _depura("END EmailQToolButton::EmailQToolButton", 0);
}

EmailQToolButton::~EmailQToolButton() {}

void EmailQToolButton::setBoton() {
    _depura("EmailQToolButton::setBoton", 0);
    connect(this, SIGNAL(clicked()), this, SLOT(click()));
    setObjectName(QString::fromUtf8("exporta"));
    setStatusTip("Enviar elementos seleccionados por e-mail");
    setToolTip("Enviar elementos seleccionados por e-mail");
    setMinimumSize(QSize(32, 32));
    setIcon(QIcon(QString::fromUtf8(":/Genericos32x32/images/png/i_mail.png")));
    setIconSize(QSize(22, 22));
    _depura("END EmailQToolButton::setBoton", 0);
}


void EmailQToolButton::click() {
    _depura("ImpQToolButton::click", 0);

    // Es posible que esto se haya cargado antes de cargar el company por eso
    // No me fio de que la asignacion en el constructor haya ido bien y reasigno aqui


    QString res = "";


    if (m_presupuestoList != NULL) {
        m_companyact = (company *)m_presupuestoList->empresaBase();
        SubForm3 *sub = m_presupuestoList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idpresupuesto");
                QString idcliente = rec->DBvalue("idcliente");
                QString query = "SELECT mailcliente from cliente WHERE idcliente="+idcliente;
                cursor2 *curs = m_companyact->cargacursor( query);
                QString email = curs->valor("mailcliente");

                PresupuestoView *pres = m_companyact->nuevoPresupuestoView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("presupuesto");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"presupuesto.pdf "+confpr->valor(CONF_DIR_USER)+"presupuesto"+id+".pdf";
                system(cad.toAscii().data());

                cad = "kmail -s \"Presupuesto "+id+"\" --body \" Adjunto remito presupuesto numero "+id+"\n Atentamente\n\" --attach "+confpr->valor(CONF_DIR_USER)+"presupuesto"+id+".pdf "+ email;
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"presupuesto"+id+".pdf ";
            } // end if
        } // end for
    } // end if



    if (m_pedidosClienteList != NULL) {
        m_companyact = (company *)m_pedidosClienteList->empresaBase();
        SubForm3 *sub = m_pedidosClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idpedidocliente");
                QString idcliente = rec->DBvalue("idcliente");
                QString query = "SELECT mailcliente from cliente WHERE idcliente="+idcliente;
                cursor2 *curs = m_companyact->cargacursor( query);
                QString email = curs->valor("mailcliente");

                PedidoClienteView *pres = m_companyact->newPedidoClienteView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("pedidocliente");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"pedidocliente.pdf "+confpr->valor(CONF_DIR_USER)+"pedidocliente"+id+".pdf";
                system(cad.toAscii().data());

                cad = "kmail -s \"Pedido Cliente "+id+"\" --body \" Adjunto remito pedido numero "+id+"\n Atentamente\n\" --attach "+confpr->valor(CONF_DIR_USER)+"pedidocliente"+id+".pdf "+ email;
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"pedidocliente"+id+".pdf ";
            } // end if
        } // end for
    } // end if




    if (m_albaranClienteList != NULL) {
        m_companyact = (company *)m_albaranClienteList->empresaBase();
        SubForm3 *sub = m_albaranClienteList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idalbaran");
                QString idcliente = rec->DBvalue("idcliente");
                QString query = "SELECT mailcliente from cliente WHERE idcliente="+idcliente;
                cursor2 *curs = m_companyact->cargacursor( query);
                QString email = curs->valor("mailcliente");

                PedidoClienteView *pres = m_companyact->newPedidoClienteView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("albaran");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"albaran.pdf "+confpr->valor(CONF_DIR_USER)+"albaran"+id+".pdf";
                system(cad.toAscii().data());

                cad = "kmail -s \"Albaran Cliente "+id+"\" --body \" Adjunto remito albaran numero "+id+"\n Atentamente\n\" --attach "+confpr->valor(CONF_DIR_USER)+"albaran"+id+".pdf "+ email;
                system(cad.toAscii().data());
                res += confpr->valor(CONF_DIR_USER)+"albaran"+id+".pdf ";
            } // end if
        } // end for
    } // end if




    if (m_facturasList != NULL) {
        m_companyact = (company *)m_facturasList->empresaBase();
        SubForm3 *sub = m_facturasList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idfactura");
                QString idcliente = rec->DBvalue("idcliente");
                QString num = rec->DBvalue("numfactura");
                QString serie = rec->DBvalue("codigoserie_factura");
                QString ref = rec->DBvalue("reffactura");
                QString fecha = rec->DBvalue("ffactura");

                QString query = "SELECT mailcliente from cliente WHERE idcliente="+idcliente;
                cursor2 *curs = m_companyact->cargacursor( query);
                QString email = curs->valor("mailcliente");

                FacturaView *pres = m_companyact->newFacturaView();
                pres->cargar(id);

                pres->generaRML();
                pres->close();

                generaPDF("factura");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"factura.pdf "+confpr->valor(CONF_DIR_USER)+"factura"+serie+num+".pdf";
                system(cad.toAscii().data());


                cad = "kmail -s \"Factura "+num+"\" --body \"Estimado cliente,\n\n";
                cad += "Adjunto le enviamos la factura número "+serie+num+" con fecha "+fecha+"\n";
                cad += "Sin otro particular, reciba un cordial saludo:\n\n\n";
                cad += "Departamento de Administración.\n\n";
                cad += "Conetxia Soluciones Informáticas S.L.\n";
                cad += "Tel. 971.29.06.29\n\"";
                cad += " --attach "+confpr->valor(CONF_DIR_USER)+"factura"+serie+num+".pdf "+ email;
                system(cad.toAscii().data());

                res += confpr->valor(CONF_DIR_USER)+"factura"+serie+num+".pdf ";
            } // end if
        } // end for
    } // end if

    if (m_cobrosList != NULL) {
        m_companyact = (company *)m_cobrosList->empresaBase();
        SubForm3 *sub = m_cobrosList->mui_list;

        /// Reseteamos los valores
        for (int i = 0; i < sub->rowCount(); i++) {
            SDBRecord *rec = sub->lineaat(i);
            rec->refresh();
            QString val = rec->DBvalue("selector");
            if (val == "TRUE") {
                QString id = rec->DBvalue("idcobro");
                QString idcliente = rec->DBvalue("idcliente");
                QString ref = rec->DBvalue("refcobro");
                QString fecha = rec->DBvalue("fcobro");

                QString query = "SELECT mailcliente from cliente WHERE idcliente="+idcliente;
                cursor2 *curs = m_companyact->cargacursor( query);
                QString email = curs->valor("mailcliente");

                CobroView *pres = m_companyact->newCobroView();
                pres->cargar(id);

                /*
                                pres->generaRML();
                                pres->close();
                */

                generaPDF("recibo");

                QString cad = "mv "+confpr->valor(CONF_DIR_USER)+"recibo.pdf "+confpr->valor(CONF_DIR_USER)+"recibo"+fecha+ref+".pdf";
                system(cad.toAscii().data());


                cad = "kmail -s \"Recibo "+fecha+ref+"\" --body \"Estimado cliente,\n\n";
                cad += "Adjunto le enviamos el recibo número "+fecha+ref+" con fecha "+fecha+"\n";
                cad += "Sin otro particular, reciba un cordial saludo:\n\n\n";
                cad += "Departamento de Administración.\n\n";
                cad += "Conetxia Soluciones Informáticas S.L.\n";
                cad += "Tel. 971.29.06.29\n\"";
                cad += " --attach "+confpr->valor(CONF_DIR_USER)+"recibo"+fecha+ref+".pdf "+ email;
                system(cad.toAscii().data());

                res += confpr->valor(CONF_DIR_USER)+"recibo"+fecha+ref+".pdf ";
            } // end if
        } // end for
    } // end if


    _depura("END ImpQToolButton::click", 0);
}

