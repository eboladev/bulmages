/***************************************************************************
*   Copyright (C) 2006 by Tomeu Borras Riera                              *
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

#include "bx11embedcontainer.h"


///
/**
\param parent
**/
BX11EmbedContainer::BX11EmbedContainer ( EmpresaBase *emp, QWidget *parent ) : QX11EmbedContainer ( parent ), PEmpresaBase ( emp )
{
    _depura ( "END BX11EmbedContainer::BX11EmbedContainer", 0 );
}


///
/**
**/
BX11EmbedContainer::~BX11EmbedContainer()
{
    _depura ( "BX11EmbedContainer::~BX11EmbedContainer", 0, this->windowTitle() );
    sacaWindow();
    _depura ( "END BX11EmbedContainer::~BX11EmbedContainer", 0 );
}


///
/**
\return
**/
int BX11EmbedContainer::sacaWindow()
{
    _depura ( "BX11EmbedContainer::sacaWindow", 0 );
    discardClient();
    if ( empresaBase() != NULL ) {
        empresaBase() ->sacaWindow ( this );
    } // end if
    _depura ( "END BX11EmbedContainer::sacaWindow", 0 );
    return 0;
}

