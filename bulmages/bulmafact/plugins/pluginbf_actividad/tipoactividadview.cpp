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

#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QDialog>
#include <QCheckBox>

#include "tipoactividadview.h"
#include "bfcompany.h"


/// Constructor de la clase inicializa la clase y llama a la clase de pintar para que pinte.
/**
\param emp
\param parent
\return
**/
TipoActividadView::TipoActividadView ( BfCompany *emp, QWidget *parent )
        : BfForm ( emp, parent )
{
    _depura ( "TipoActividadView::TipoActividadView", 0 );

    setTitleName ( _( "TipoActividad" ) );
    setDbTableName ( "tipoactividad" );
    setAttribute ( Qt::WA_DeleteOnClose );
    setupUi ( this );
    mui_tab->setDisabled ( TRUE );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "TipoActividadView_TipoActividadView", this );
    if ( res != 0 ) {
        return;
    } // end if
    m_archivoimagen = "";
    setModoEdicion();
    m_cursortipoactividades = NULL;
    m_item = NULL;
    res = g_plugins->lanza ( "TipoActividadView_TipoActividadView_Post", this );
    if ( res != 0 ) {
        return;
    } // end if
    pintar();
    meteWindow ( windowTitle(), this, FALSE );
    _depura ( "END TipoActividadView::TipoActividadView", 0 );
}


///
/**
**/
void TipoActividadView::imprimir()
{
    _depura ( "TipoActividadView::imprimir", 0 );
    _depura ( "END TipoActividadView::imprimir", 0 );
}

/// Carga el query de la base de datos y carga el qlistview.
/**
**/
void TipoActividadView::pintar()
{
    _depura ( "TipoActividadView::pintar", 0 );

    mui_lista->clear();

    if ( m_cursortipoactividades != NULL ) {
        delete m_cursortipoactividades;
    } // end if
    m_cursortipoactividades = mainCompany() ->loadQuery ( "SELECT * FROM tipoactividad ORDER BY apellidostipoactividad" );
    while ( !m_cursortipoactividades->eof() ) {
        new QListWidgetItem ( m_cursortipoactividades->valor ( "apellidostipoactividad" ) + " " + m_cursortipoactividades->valor ( "nomtipoactividad" ), mui_lista );
        m_cursortipoactividades->nextRecord();
    } // end while

    /// Comprobamos cual es la cadena inicial.
    dialogChanges_cargaInicial();
    _depura ( "END TipoActividadView::pintar", 0 );
}


///
/**
**/
TipoActividadView::~TipoActividadView()
{
    _depura ( "TipoActividadView::~TipoActividadView", 0 );
    if ( m_cursortipoactividades != NULL ) {
        delete m_cursortipoactividades;
    } // end if
    _depura ( "END TipoActividadView::~TipoActividadView", 0 );
}


///
/**
\param cur
\return
**/
void TipoActividadView::on_mui_lista_currentItemChanged ( QListWidgetItem *cur, QListWidgetItem * )
{
    _depura ( "on_mui_lista_currentItemChanged", 0 );
    if ( !cur ) return;
    mui_tab->setEnabled ( TRUE );

    int row = mui_lista->row ( cur );
    trataModificado();
/*    
    m_nomtipoactividad->setText ( m_cursortipoactividades->valor ( "nomtipoactividad", row ) );
    mdb_idtipoactividad = m_cursortipoactividades->valor ( "idtipoactividad", row );
    m_apellidostipoactividad->setText ( m_cursortipoactividades->valor ( "apellidostipoactividad", row ) );
    m_nsstipoactividad->setText ( m_cursortipoactividades->valor ( "nsstipoactividad", row ) );
    m_dirtipoactividad->setText ( m_cursortipoactividades->valor ( "dirtipoactividad", row ) );
    m_teltipoactividad->setText ( m_cursortipoactividades->valor ( "teltipoactividad", row ) );
    m_moviltipoactividad->setText ( m_cursortipoactividades->valor ( "moviltipoactividad", row ) );
    m_emailtipoactividad->setText ( m_cursortipoactividades->valor ( "emailtipoactividad", row ) );
    if ( m_cursortipoactividades->valor ( "activotipoactividad", row ) == "t" ) {
        m_activotipoactividad->setChecked ( TRUE );
    } else {
        m_activotipoactividad->setChecked ( FALSE );
    } // end if
    m_item = cur;
    /// Comprobamos cual es la cadena inicial.
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "TipoActividadView_on_mui_lista_currentItemChanged_Post", this );
    if ( res != 0 ) {
        return;
    } // end if
*/    
    dialogChanges_cargaInicial();
    m_imagen->setPixmap ( QPixmap ( confpr->valor ( CONF_DIR_IMG_PERSONAL ) + mdb_idtipoactividad + ".jpg" ) );
    _depura ( "END on_mui_lista_currentItemChanged", 0 );
}


///
/**
\return
**/
void TipoActividadView::on_mui_guardar_clicked()
{
    _depura ( "TipoActividadView::on_mui_guardar_clicked", 0 );
/*

    try {
        /// Disparamos los plugins.
        int res = g_plugins->lanza ( "TipoActividadView_on_mui_guardar_clicked", this );
        if ( res != 0 ) {
            return;
        } // end if
        
        QString m_textactivotipoactividad = "FALSE";
        if ( m_activotipoactividad->isChecked() ) {
            m_textactivotipoactividad = "TRUE";
        } // end if
        QString query = "UPDATE tipoactividad SET ";
        query += "  nomtipoactividad='" + mainCompany() ->sanearCadena ( m_nomtipoactividad->text() ) + "'";
        query += ", apellidostipoactividad= '" + mainCompany() ->sanearCadena ( m_apellidostipoactividad->text() ) + "'";
        query += ", nsstipoactividad = '" + mainCompany() ->sanearCadena ( m_nsstipoactividad->text() ) + "'";
        query += ", dirtipoactividad = '" + mainCompany() ->sanearCadena ( m_dirtipoactividad->text() ) + "'";
        query += ", teltipoactividad = '" + mainCompany() ->sanearCadena ( m_teltipoactividad->text() ) + "'";
        query += ", moviltipoactividad = '" + mainCompany() ->sanearCadena ( m_moviltipoactividad->text() ) + "'";
        query += ", emailtipoactividad = '" + mainCompany() ->sanearCadena ( m_emailtipoactividad->text() ) + "'";
        query += ", activotipoactividad = " + mainCompany() ->sanearCadena ( m_textactivotipoactividad );
        query += " WHERE idtipoactividad=" + mainCompany() ->sanearCadena ( mdb_idtipoactividad );

        mainCompany() ->begin();
        mainCompany() ->runQuery ( query );
        mainCompany() ->commit();
        if ( m_cursortipoactividades != NULL ) {
            delete m_cursortipoactividades;
        } // end if

        m_cursortipoactividades = mainCompany() ->loadQuery ( "SELECT * FROM tipoactividad ORDER BY apellidostipoactividad" );

        if ( m_item ) {
            m_item->setText ( m_apellidostipoactividad->text() + m_nomtipoactividad->text() );
        } // end if
        if ( m_archivoimagen != "" ) {
            QString cadena = "cp " + m_archivoimagen + " " + confpr->valor ( CONF_DIR_IMG_PERSONAL ) + mdb_idtipoactividad + ".jpg";
            system ( cadena.toAscii().constData() );
        } // end if

		/// Emitimos la senyal apropiada en el qapplication2
		g_theApp->tablaCambiada1("tipoactividad");

        /// Comprobamos cual es la cadena inicial.
        dialogChanges_cargaInicial();
    } catch ( ... ) {
        mensajeInfo ( _( "Error al guardar el tipoactividad" ) );
        mainCompany() ->rollback();
    } // end try

*/
_depura ( "END TipoActividadView::on_mui_guardar_clicked", 0 );
}


///
/**
\return
**/
bool TipoActividadView::trataModificado()
{
    _depura ( "TipoActividadView::trataModificado", 0 );
    /// Si se ha modificado el contenido advertimos y guardamos.
    if ( dialogChanges_hayCambios() ) {
        if ( QMessageBox::warning ( this,
                                    _( "Guardar datos del tipoactividad" ),
                                    _( "Desea guardar los cambios?" ),
                                    _( "&Si" ), _( "&No" ), 0, 0, 1 ) == 0 )
            on_mui_guardar_clicked();
        return ( TRUE );
    } // end if
    _depura ( "END TipoActividadView::trataModificado", 0 );
    return ( FALSE );
}


/// SLOT que responde a la pulsacion del boton de nuevo tipo de iva.
/// Inserta en la tabla de ivas
/**
\return
**/
void TipoActividadView::on_mui_nuevo_clicked()
{
    _depura ( "TipoActividadView::on_mui_nuevo_clicked", 0 );
    try {
        /// Si se ha modificado el contenido advertimos y guardamos.
        trataModificado();
        QString query = "INSERT INTO tipoactividad (nomtipoactividad, apellidostipoactividad, nsstipoactividad) VALUES ('NUEVO TRABAJADOR','NUEVO TRABAJADOR','000000000000')";
        mainCompany() ->begin();
        mainCompany() ->runQuery ( query );
        BlDbRecordSet *cur = mainCompany() ->loadQuery ( "SELECT max(idtipoactividad) AS idtipoactividad FROM tipoactividad" );
        mainCompany() ->commit();
        mdb_idtipoactividad = cur->valor ( "idtipoactividad" );
        delete cur;
        pintar();
        _depura ( "END TipoActividadView::on_mui_nuevo_clicked", 0 );
    } catch ( ... ) {
        mensajeInfo ( _( "Error al crear un nuevo TipoActividad" ) );
        mainCompany() ->rollback();
    } // end try
}


/// SLOT que responde a la pulsacion del boton de borrar la familia que se esta editando.
/// Lo que hace es que se hace un update de todos los campos.
/**
\return
**/
void TipoActividadView::on_mui_borrar_clicked()
{
    _depura ( "TipoActividadView::on_mui_borrar_clicked", 0 );
    try {
        mui_tab->setDisabled ( TRUE );
        trataModificado();
        mainCompany() ->begin();
        QString query = "DELETE FROM tipoactividad WHERE idtipoactividad = " + mdb_idtipoactividad;
        mainCompany() ->runQuery ( query );
        mainCompany() ->commit();
        mdb_idtipoactividad = "";
        pintar();
        _depura ( "END TipoActividadView::on_mui_borrar_clicked", 0 );
    } catch ( ... ) {
        mensajeInfo ( _( "Error al borrar el TipoActividad" ) );
        mainCompany() ->rollback();
    }// end try
}


///
/**
\return
**/
void TipoActividadView::on_mui_imagen_clicked()
{
    _depura ( "TipoActividadView::on_mui_imagen_clicked", 0 );
    m_archivoimagen = QFileDialog::getOpenFileName ( this,
                      _( "Seleccione archivo" ),
                      "",
                      _( "Imagenes (*.jpg)" ) );
    m_imagen->setPixmap ( QPixmap ( m_archivoimagen ) );
    _depura ( "END TipoActividadView::on_mui_imagen_clicked", 0 );
}


///
/**
\return
**/
QString TipoActividadView::idtipoactividad()
{
    _depura ( "TipoActividadView::idtipoactividad", 0 );
    _depura ( "END TipoActividadView::idtipoactividad", 0 );
    return mdb_idtipoactividad;
}


