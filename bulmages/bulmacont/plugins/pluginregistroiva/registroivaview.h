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

#ifndef REGISTROIVAVIEW_H
#define REGISTROIVAVIEW_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

#include "ui_registroivabase.h"
#include "registroiva.h"
#include "postgresiface2.h"
#include "ficha.h"
#include "fixed.h"
#include "dialogchanges.h"


class empresa;


class RegistroIvaView : public RegistroIva, public Ui_RegistroIvaBase {
    Q_OBJECT

private:
    cursor2 *m_cursorcombo;
    /// Cursor para las formas de pago.
    cursor2 *m_cursorFPago;

public:
    RegistroIvaView(empresa *, QWidget *);
    virtual ~RegistroIvaView();
    void manageArticle(int);
    virtual void pintaidregistroiva(const QString &) {}
    ;
    virtual void pintacontrapartida(const QString &val) {
        m_contrapartida->setidcuenta(val);
    };
    virtual void pintabaseimp(const QString &val) {
        Fixed total(val);
        total = total + Fixed(iva());
        m_baseImponible->setText(val);
        m_totalFactura->setText(total.toQString());
    };
    virtual void pintaiva(const QString &val) {
        Fixed total(val);
        total = total + Fixed(baseimp());
        m_totalFactura->setText(total.toQString());
        m_importeiva->setText(val);
    };
    virtual void pintaffactura(const QString &val) {
        m_ffactura->setText(val);
    };
    virtual void pintafemisionregistroiva(const QString &val) {
        m_femisionregistroiva->setText(val);
    };
    virtual void pintaserieregistroiva(const QString &val) {
        m_serieregistroiva->setText(val);
    };
    virtual void pintafactura(const QString &val) {
        m_factura->setText(val);
    };
    virtual void pintaidborrador(const QString &) {}
    ;
    virtual void pintaregularizacion(const QString &) {}
    ;
    virtual void pintaplan349(const QString &) {}
    ;
    virtual void pintanumorden(const QString &val) {
        m_numorden->setText(val);
    };
    virtual void pintacif(const QString &val) {
        m_cif->setText(val);
    };
    virtual void pintaidfpago(const QString &) {}
    ;
    virtual void pintafactemitida(const QString &val) {
        if (val == "t" || val == "TRUE")
            m_factEmitida->setChecked(TRUE);
        else
            m_factSoportada->setChecked(TRUE);
    };
virtual void pintarectificaaregistroiva(const QString &) {}
    ;
    virtual void pintaincregistro(const QString &val) {
        if (val == "t" || val == "TRUE")
            m_incregistroIVA->setChecked(TRUE);
        else
            m_incregistroIVA->setChecked(FALSE);
    };

    virtual void recalculaIva() {
        Fixed base = mui_listIva->sumarCampo("baseiva");
        Fixed iva = mui_listIva->sumarCampo("ivaiva");
        setbaseimp(base.toQString());
        setiva(iva.toQString());
        pintabaseimp(base.toQString());
        pintaiva(iva.toQString());
    };
    virtual int guardar();
    int cargar(QString id);
    virtual int borrar() {
        return RegistroIva::borrar();
    };

private:
    void generarPedidoCliente();
    void cargarComboFPago(QString);

public slots:
    virtual void on_mui_generarPrevisiones_clicked();
    /// Este slot se activa cuando hay cambios en los subformularios.
    virtual void on_mui_listIva_editFinish(int, int) {
        _depura("RegistroIvaView::on_mui_listIva_editFinish", 0);
	recalculaIva();
        _depura("END RegistroIvaView::on_mui_listIva_editFinish", 0);
    };
};

#endif
