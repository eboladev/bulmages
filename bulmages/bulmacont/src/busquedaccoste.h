/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org Asociación Iglues -- Contabilidad Linux         *
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

#ifndef BUSQUEDACCOSTE_H
#define BUSQUEDACCOSTE_H

#include <QComboBox>
#include "postgresiface2.h"


class empresa;



class BusquedaCCosteDelegate : public QComboBox {
    Q_OBJECT

private:
    empresa *m_companyact;
    /// Este cursor almacena el listado de series de factura para poder trabajar con ellas.
    cursor2 *m_cursorcombo;
    QCompleter *completar;

public:
    BusquedaCCosteDelegate(QWidget *parent = 0);
    ~BusquedaCCosteDelegate();
    void setcompany(empresa *comp);

public slots:
    virtual void s_editTextChanged(const QString &);
};



class BusquedaCCoste : public QComboBox {
    Q_OBJECT

private:
    empresa *companyact;
    cursor2 *m_cursorcombo;

public:
    BusquedaCCoste(QWidget *parent = 0, const char *name = 0);
    ~BusquedaCCoste();
    void setcompany(empresa *comp);
    virtual void setidc_coste(QString idc_coste);
    QString idc_coste();

public slots:
    void m_activated(int index);

signals:
    void valueChanged(QString);
};

#endif
