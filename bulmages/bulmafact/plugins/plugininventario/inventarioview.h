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

#ifndef INVENTARIOVIEW_H
#define INVENTARIOVIEW_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

#include "ui_inventariobase.h"
#include "inventario.h"
#include "busquedafecha.h"
#include "postgresiface2.h"
#include "ficha.h"


/// Muestra y administra la ventana con los datos de un inventario.
/** */
class InventarioView : public Ficha, public Ui_InventarioBase, public Inventario {
    Q_OBJECT

public:
    InventarioView(company *, QWidget *parent = 0);
    ~InventarioView();
    void pintaidinventario(QString);
    void pintafechainventario(QString id);
    void pintanominventario(QString id);
    virtual int sacaWindow();

public slots:
    virtual void on_mui_guardar2_clicked();
    virtual void on_mui_aceptar_clicked();
    virtual void on_mui_borrar2_clicked();
    virtual void on_mui_pregenerar_clicked();
};

#endif
