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

#include "plugintotalivainc.h"
#include "btcompany.h"
#include "total.h"
#include "blplugins.h"
#include "ticket.h"
#include "blapplication.h"
#include "bldockwidget.h"


/// Una factura puede tener multiples bases imponibles. Por eso definimos el tipo base
/// como un QMap.
typedef QMap<QString, BlFixed> base;
Total *g_tot = NULL;
BlDockWidget *g_doc1 = NULL;


///
/**
\return
**/
int entryPoint ( BulmaTPV *tpv )
{
    _depura ( "plugintotal::entryPoint", 0 );

    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale(LC_ALL, "");
    bindtextdomain ("plugintotalivainc", confpr->valor(CONF_DIR_TRADUCCION).toAscii().constData());

    /// Vamos a probar con un docwindow.
    g_doc1 = new BlDockWidget ( _("Total"), tpv, "plugintotaldock" );
    g_doc1->setFeatures ( QDockWidget::AllDockWidgetFeatures );
    g_doc1->setGeometry ( 100, 100, 100, 500 );
    g_doc1->resize ( 330, 400 );
    tpv->addDockWidget ( Qt::LeftDockWidgetArea, g_doc1 );
    g_doc1->cargaconf();
    g_doc1->show();

    _depura ( "END plugintotal::entryPoint", 0 );
    return 0;
}

int BtCompany_createMainWindows_Post ( BtCompany *etpv )
{
    _depura ( "plugintotal::BtCompany_createMainWindows_Post", 0 );

    g_tot = new Total ( etpv, g_doc1 );
    g_doc1->setWidget ( g_tot );
    _depura ( "END plugintotal::BtCompany_createMainWindows_Post", 0 );

    return 0;
}


///
/**
\return
**/
int exitPoint ( BulmaTPV *tpv )
{
    _depura ( "plugintotal::exitPoint", 0 );
    delete g_doc1;
    _depura ( "END plugintotal::exitPoint", 0 );
    return 0;
}

int Ticket_pintar ( Ticket *tick )
{
    _depura ( "plugintotal::Ticket_pintar", 0 );

    base basesimp;
    base basesimpreqeq;
    BlDbRecord *linea;

    BtCompany *emp = ( BtCompany * ) tick->mainCompany();

    /// Impresion de los contenidos.
    QString l;

    BlFixed total("0.00");
    BlFixed descuentolinea ( "0.00" );
    for ( int i = 0; i < tick->listaLineas() ->size(); ++i ) {
        linea = tick->listaLineas() ->at ( i );
        BlFixed cant ( linea->dbValue ( "cantlalbaran" ) );
        BlFixed pvpund ( linea->dbValue ( "pvpivainclalbaran" ) );
        BlFixed cantpvp = cant * pvpund;
	total = total + cantpvp;
    } // end for

    /// Pintamos el total
    if ( g_tot )
        g_tot->mui_total->setText ( total.toQString() );

    _depura ( "END plugintotal::Ticket_pintar", 0 );

    return 0;

}

