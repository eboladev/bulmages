/***************************************************************************
 *   Copyright (C) 2002 by Tomeu Borras Riera                              *
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

#ifndef ASIENTOSVIEW_H
#define ASIENTOSVIEW_H

#include "ui_asientolistbase.h"
#include "listado.h"


class empresa;


/// Muestra un listado de todos los asientos existentes e informa de si est&aacute;n
/// abiertos o cerrados.
/** */
class AsientosView : public Listado, public Ui_AsientoListBase {
    Q_OBJECT

private:
    void rellenaListaEjercicio();

public:
    AsientosView(empresa *, QWidget *parent = 0, Qt::WFlags flag = 0, edmode editmodo = EditMode);
    ~AsientosView();
    void presentar();
    void imprimir();

public slots:
    virtual void on_mui_list_cellDoubleClicked(int, int);
};

#endif
