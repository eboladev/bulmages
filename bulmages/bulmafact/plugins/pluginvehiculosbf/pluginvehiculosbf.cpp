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

#include <stdio.h>

#include <QAction>
#include <QObject>
#include <QMessageBox>
#include <QLineEdit>
#include <QTabWidget>

#include "company.h"
#include "pluginvehiculosbf.h"
#include "funcaux.h"
#include "vehiculoview.h"



myplugin::myplugin() {}


myplugin::~myplugin() {}


void myplugin::elslot() {
    VehiculoView *vehiculoview = new VehiculoView((company *) m_conexionbase);
    m_bulmafact->workspace()->addWindow(vehiculoview);
    vehiculoview->show();
}


void myplugin::inicializa(bulmafact *bges) {
    /// Creamos el men&uacute;.
    m_conexionbase = bges->getcompany();
    m_bulmafact = bges;
    QMenu *pPluginMenu = new QMenu("&Vehiculos");
    QAction *accion = new QAction("&Nuevo vehiculo", 0);
    accion->setStatusTip("Vehiculos");
    accion->setWhatsThis("Vehiculos");
    connect(accion, SIGNAL(activated()), this, SLOT(elslot()));
    pPluginMenu->addAction(accion);
    /// A&ntilde;adimos la nueva opci&oacute;n al men&uacute; principal del programa.
    bges->menuBar()->addMenu(pPluginMenu);
}


int entryPoint(bulmafact *bges) {
    _depura("Punto de Entrada del plugin PluginVehiculosBF", 0);
    myplugin *plug = new myplugin();
    plug->inicializa(bges);
    _depura("END Punto de Entrada del plugin PluginVehiculosBF", 0);
    return 0;
}
