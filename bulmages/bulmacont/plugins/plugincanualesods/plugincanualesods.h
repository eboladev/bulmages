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

#ifdef Q_WS_WIN
# define MY_EXPORT __declspec(dllexport)
#else
# define MY_EXPORT
#endif

#include <QStringList>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QObject>
#include <QTextStream>

#include "bulmacont.h"
#include "postgresiface2.h"
#include "empresa.h"
#include "fixed.h"

extern "C" MY_EXPORT void entryPoint(Bulmacont *);

extern QApplication2 *theApp;


class pluginCAnualesODS : public QObject {
    Q_OBJECT

private:
    Fixed saldoCuenta(int cuenta);
    Fixed saldoCuentaAnt(int cuenta);
    QString ejercicioActual_fechaBalance;
    QString ejercicioAnterior_fechaBalance;

public:
    empresa *empresaact;
    postgresiface2 *conexionbase;

public:
    pluginCAnualesODS();
    ~pluginCAnualesODS();
    void inicializa(Bulmacont *);

public slots:
    void balanceSituacionODS();
    void formDatosBalance();
};
