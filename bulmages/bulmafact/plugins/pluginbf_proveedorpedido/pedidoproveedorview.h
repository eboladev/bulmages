/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org                                                 *
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

#ifndef PEDIDOPROVEEDORVIEW_H
#define PEDIDOPROVEEDORVIEW_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

#include "ui_pedidoproveedorbase.h"
#include "listlinpedidoproveedorview.h"
#include "listdescpedidoproveedorview.h"
#include "bldatesearch.h"
#include "busquedaformapago.h"
#include "busquedaalmacen.h"
#include "busquedatrabajador.h"
#include "bldialogchanges.h"
#include "blfixed.h"
#include "bfform.h"


class company;


/// Muestra y administra la ventana con la informaci&oacute;n de un pedido a proveedor.
/** */
class PedidoProveedorView : public BfForm, public Ui_PedidoProveedorBase
{
    Q_OBJECT

public:
    PedidoProveedorView ( BfCompany *, QWidget *parent = 0 );
    ~PedidoProveedorView();
    void inicialize();
    void pintatotales ( BlFixed iva, BlFixed base, BlFixed total, BlFixed desc, BlFixed irpf, BlFixed reqeq );
    virtual int cargarPost ( QString );
    virtual int guardarPost();
    virtual int borrarPre();
    virtual void imprimir();

public slots:
    virtual void on_mui_proveedor_valueChanged ( QString );
    virtual void on_mui_descuentos_editFinish ( int, int );
    virtual void on_mui_lineasDetalle_editFinish ( int, int );
};

#endif
