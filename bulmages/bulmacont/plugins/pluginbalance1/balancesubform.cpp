/***************************************************************************
 *   Copyright (C) 2003 by Tomeu Borras Riera                              *
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

#include <QMenu>

#include "balancesubform.h"


///
/**
\param parent
**/
BalanceSubForm::BalanceSubForm ( QWidget *parent, const char * ) : SubForm2Bc ( parent )
{
    _depura ( "BalanceSubForm::BalanceSubForm", 0 );
    setDBTableName ( "borrador" );
    setFileConfig ( "balancesubform" );
    setDBCampoId ( "idborrador" );
    addSHeader ( "idcuenta", DBCampo::DBint, DBCampo::DBNotNull | DBCampo::DBPrimaryKey, SHeader::DBNoView | SHeader::DBNoWrite, tr ( "idcuenta" ) );
    addSHeader ( "tipocuenta", DBCampo::DBint, DBCampo::DBNotNull | DBCampo::DBPrimaryKey, SHeader::DBNoView | SHeader::DBNoWrite, tr ( "tipocuenta" ) );
    addSHeader ( "codigo", DBCampo::DBint, DBCampo::DBNotNull | DBCampo::DBPrimaryKey, SHeader::DBNoView | SHeader::DBNoWrite, tr ( "codigo" ) );
    addSHeader ( "descripcion", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "descripcion" ) );
    addSHeader ( "asaldo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "asaldo" ) );
    addSHeader ( "tdebe", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "tdebe" ) );
    addSHeader ( "thaber", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "thaber" ) );
    addSHeader ( "tsaldo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "tsaldo" ) );
    addSHeader ( "ejdebe", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ejdebe" ) );
    addSHeader ( "ejhaber", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ejhaber" ) );
    addSHeader ( "ejsaldo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ejsaldo" ) );
    setinsercion ( FALSE );
    _depura ( "END BalanceSubForm::BalanceSubForm", 0 );
}


///
/**
\return
**/
void BalanceSubForm::contextMenuEvent ( QContextMenuEvent * )
{
    _depura ( "SubForm2Bc::contextMenuEvent", 0 );
    QAction *del = NULL;
    int row = currentRow();
    if ( row < 0 ) {
        return;
    } // end if
    int col = currentColumn();
    if ( row < 0 ) {
        return;
    } // end if
    QMenu *popup = new QMenu ( this );
    QAction *mostapunte = popup->addAction ( "Mostrar asiento" );
    popup->addSeparator();
    QAction *mostextractodia = popup->addAction ( "Mostrar extracto (dia)" );
    QAction *mostextractomes = popup->addAction ( "Mostrar extracto (mes)" );
    QAction *mostextractoano = popup->addAction ( "Mostrar extracto (ano)" );


    if ( m_delete )
        del = popup->addAction ( tr ( "Borrar registro" ) );
    popup->addSeparator();
    QAction *ajustc = popup->addAction ( tr ( "Ajustar columa" ) );
    QAction *ajustac = popup->addAction ( tr ( "Ajustar altura" ) );
    QAction *ajust = popup->addAction ( tr ( "Ajustar columnas" ) );
    QAction *ajusta = popup->addAction ( tr ( "Ajustar alturas" ) );
    popup->addSeparator();
    QAction *verconfig = popup->addAction ( tr ( "Ver configurador de subformulario" ) );
    QAction *opcion = popup->exec ( QCursor::pos() );

    if ( opcion == mostapunte ) {
        boton_asiento();
    } // end if
    if ( opcion == del ) {
        borrar ( row );
    } // end if
    if ( opcion == ajust ) {
        resizeColumnsToContents();
    } // end if
    if ( opcion == ajusta ) {
        resizeRowsToContents();
    } // end if
    if ( opcion == ajustc ) {
        resizeColumnToContents ( col );
    } // end if
    if ( opcion == ajustac ) {
        resizeRowToContents ( row );
    } // end if
    if ( opcion == verconfig ) {
        showConfig();
    } // end if
    if ( opcion == mostextractodia ) {
        boton_extracto1 ( 0 );
    } // end if
    if ( opcion == mostextractomes ) {
        boton_extracto1 ( 1 );
    } // end if
    if ( opcion == mostextractoano ) {
        boton_extracto1 ( 2 );
    } // end if
    delete popup;
    _depura ( "END SubForm2Bc::contextMenuEvent", 0 );
}
