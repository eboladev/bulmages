/***************************************************************************
 *   Copyright (C) 2007 by Tomeu Borras Riera                              *
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

#ifndef CONTRATO_H
#define CONTRATO_H

#include <QString>

#include "fixed.h"
#include "company.h"
#include "dbrecord.h"
#include "fichabf.h"

/// Administra los datos de una contrato a cliente.
/** Intermedia entre la base de datos y la pantalla de presentacion.
*/
class Contrato : public FichaBf {
Q_OBJECT

public:
    Contrato(company *, QWidget *parent);
    virtual ~Contrato();
    /// Establece cu&aacute;l es la lista subformulario del presupuesto. Normalmente para
    /// apuntar listlinpresupuestoview.

    company *_company();
    virtual int cargar(QString);
    void pintar();
    virtual int guardar();
    virtual int  borrar();

    void vaciaContrato();

    virtual void pintaidcliente(QString);
    virtual void pintarefcontrato(QString);
    virtual void pintafincontrato(QString );
    virtual void pintadescontrato(QString);
    virtual void pintanomcontrato(QString);
    virtual void pintaffincontrato(QString);
    virtual void pintaloccontrato(QString);
    virtual void pintaperiodicidadcontrato(QString);
    virtual void inicialize();
    virtual QString calculateValues();

};

#endif
