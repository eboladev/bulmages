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

#include "pluginbf_printercocina.h"
#include "blcombobox.h"

///
/**
\return
**/
int entryPoint ( BfBulmaFact * )
{
    _depura ( "Estoy dentro del plugin de Impresion en Cocina", 0 );
    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale ( LC_ALL, "" );
    bindtextdomain ( "pluginbf_printercocina", g_confpr->valor ( CONF_DIR_TRADUCCION ).toAscii().constData() );

    return 0;
}





/// Al crear la ventana de trabajadores tambien creamos un combo box para el tipo de trabajador.
/**
\param trab
\return
**/

int ArticuloView_ArticuloView_Post ( ArticuloView *trab )
{
    _depura ( "ArticuloView_ArticuloView_Post", 0 );

    trab->addDbField ( "idprintercocina", BlDbField::DbNumeric, BlDbField::DbNothing, _ ( "Impresion en Cocina" ) );


    QHBoxLayout *hboxLayout160 = new QHBoxLayout();
    hboxLayout160->setSpacing ( 2 );
    hboxLayout160->setMargin ( 0 );
    hboxLayout160->setObjectName ( QString::fromUtf8 ( "hboxLayout19" ) );

    QLabel *textLabel2_9_26 = new QLabel ( trab->m_frameplugin );
    textLabel2_9_26->setObjectName ( QString::fromUtf8 ( "textLabel2_9_9" ) );
    hboxLayout160->addWidget ( textLabel2_9_26 );
    textLabel2_9_26->setText ( "Impresora de Cocina." );

    /// Datos por defecto.
    BlComboBox *pcocina = new BlComboBox (trab->m_frameplugin);
    pcocina->setObjectName ( QString::fromUtf8 ( "mui_idprintercocina" ));
    pcocina->setMainCompany ( trab->mainCompany() );
    pcocina->setQuery ( "SELECT * FROM printercocina  ORDER BY nombreprintercocina" );
    pcocina->setTableName ( "printercocina" );
    pcocina->setFieldId ( "idprintercocina" );
    pcocina->m_valores["nombreprintercocina"] = "";
    pcocina->m_valores["colaprintercocina"] = "";
    pcocina->setAllowNull ( TRUE );
    pcocina->setId ( "" );
    hboxLayout160->addWidget ( pcocina );

    /// Comprobamos que exista el layout.
    QVBoxLayout *m_hboxLayout1 = trab->m_frameplugin->findChild<QVBoxLayout *> ( "hboxLayout1" );
    if ( !m_hboxLayout1 ) {
        m_hboxLayout1 = new QVBoxLayout ( trab->m_frameplugin );
        m_hboxLayout1->setSpacing ( 0 );
        m_hboxLayout1->setMargin ( 0 );
        m_hboxLayout1->setObjectName ( QString::fromUtf8 ( "hboxLayout1" ) );
    } // end if
    m_hboxLayout1->addLayout ( hboxLayout160 );
    return 0;
}


