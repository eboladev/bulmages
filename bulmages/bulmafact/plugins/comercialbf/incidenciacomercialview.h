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

#ifndef INCIDENCIACOMERCIALVIEW_H
#define INCIDENCIACOMERCIALVIEW_H

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>

#include "ui_incidenciacomercialbase.h"
#include "postgresiface2.h"
#include "incidenciacomercial.h"
#include "busquedacliente.h"
#include "busquedafecha.h"
#include "dialogchanges.h"




class IncidenciaComercialView : public IncidenciaComercial, private Ui_IncidenciaComercialBase {
    Q_OBJECT

public:
    IncidenciaComercialView(QWidget *parent = NULL);
    ~IncidenciaComercialView();
    IncidenciaComercialView(company *, QWidget *parent = NULL);
    void closeEvent(QCloseEvent *);
    virtual void pintar() {}
    ;
    void setEmpresaBase(company *comp);
    virtual int guardar();
    virtual int cargar(QString id);
};

#endif
