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
#include <QToolButton>

#include "pluginproyectos.h"
#include "tiptrab.h"
#include "listado.h"
#include "listproyectosview.h"



///
/**
**/
mytiptrab::mytiptrab()
{
    _depura ( "mytiptrab::mytiptrab", 0 );
    _depura ( "END mytiptrab::mytiptrab", 0 );
}


///
/**
**/
mytiptrab::~mytiptrab()
{
    _depura ( "mytiptrab::~mytiptrab", 0 );
    _depura ( "END mytiptrab::~mytiptrab", 0 );
}


///
/**
**/
void mytiptrab::elslot()
{
    _depura ( "mytiptrab::elslot", 0 );
    /// Agregamos el subformulario de proyectos.
    ListProyectosView *l = new ListProyectosView ( m_bulmacont->empresaactual(), 0, 0, Listado::EditMode );
    l->setObjectName ( QString::fromUtf8 ( "mui_proyectos" ) );
    m_bulmacont->workspace() ->addWindow ( l );
    l->show();
    _depura ( "END mytiptrab::elslot", 0 );
}


///
/**
\param bges
**/
void mytiptrab::inicializa ( Bulmacont *bges )
{
    /// Creamos el men&uacute;.
    m_bulmacont = bges;
    QAction *accion = new QAction ( "&Proyectos", 0 );
    accion->setStatusTip ( "Proyectos" );
    accion->setWhatsThis ( "Proyectos" );
    connect ( accion, SIGNAL ( activated() ), this, SLOT ( elslot() ) );
    /// A&ntilde;adimos la nueva opci&oacute;n al men&uacute; principal del programa.
    bges->menuMaestro->insertAction ( bges->actionPaises, accion );
}


///
/**
\param bges
\return
**/
int entryPoint ( Bulmacont *bges )
{
    _depura ( "Estoy dentro del plugin de proyectos", 0 );
    mytiptrab *plug = new mytiptrab();
    plug->inicializa ( bges );
    return 0;
}

///
/**
\param ccoste
\return
**/
int ccosteview_ccosteview ( ccosteview *ccoste )
{
    _depura ( "ccosteview_ccosteview", 0 );

    /// Agregamos el subformulario de proyectos.
    ListProyectosView *l = new ListProyectosView ( ccoste->empresaBase(), ccoste, 0, Listado::SelectMode );
    l->setObjectName ( QString::fromUtf8 ( "mui_proyectos" ) );
    l->mui_actualizar->setDisabled ( TRUE );
    ccoste->tabWidget->addTab ( l, "Proyectos Asociados" );
    return 0;
}


///
/**
\param ficha
\return
**/
int Ficha_cargar ( Ficha *ficha )
{
    ListProyectosView * l = ficha->findChild<ListProyectosView *> ( "mui_proyectos" );
    if ( l )
        l->mui_listado->cargar ( "SELECT * FROM presupuestoc WHERE idc_coste = " + ficha->DBvalue ( "idc_coste" ) );
    return 0;
}
