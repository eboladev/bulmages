/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   Copyright (C) 2006 by Fco. Javier M. C.                               *
 *   fcojavmc@todo-redes.com                                               *
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

#include <QMenu>
#include <QAction>
#include <QObject>
#include <QMessageBox>

#include <stdio.h>

#include "plugin.h"
#include "company.h"
#include "funcaux.h"


myplugin::myplugin() {}


myplugin::~myplugin() {}


void myplugin::elslot() {
    fprintf(stderr, "Sa ha activado el slot\n");
    QMessageBox::warning(0,
                         "Titulo de la ventana",
                         "Mensaje.",
                         QMessageBox::Ok,
                         QMessageBox::Cancel);
}


void myplugin::inicializa(bulmafact *bges) {
    QMenu *pPluginMenu;
    /// Miramos si existe un menu Herramientas
    pPluginMenu = bges->menuBar()->findChild<QMenu *>("Herramientas");

    /// Creamos el men&uacute;.
    if (!pPluginMenu) {
        pPluginMenu = new QMenu("&Herramientas", bges->menuBar());
        pPluginMenu->setObjectName(QString::fromUtf8("Herramientas"));
    } // end if
    /// Creamos el men&uacute;.

    QAction *accion = new QAction("&Prueba de plugin", 0);
    accion->setStatusTip("Muestra statustip");
    accion->setWhatsThis("Muestra que es esto");
    connect(accion, SIGNAL(activated()), this, SLOT(elslot()));
    pPluginMenu->addAction(accion);
    /// A&ntilde;adimos la nueva opci&oacute;n al men&uacute; principal del programa.
    bges->menuBar()->insertMenu(bges->menuVentana->menuAction(), pPluginMenu);
}


void entryPoint(bulmafact *bges) {
    _depura("Estoy dentro del plugin de demo", 0);
    myplugin *plug = new myplugin();
    plug->inicializa(bges);
    /// S&Oacute;LO A MODO DE EJEMPLO: se modifica el t&iacute;tulo de la ventana principal
    /// del programa para indicar que el plugin se ha cargado.
    bges->setWindowTitle("Prueba de plugin.");
}
