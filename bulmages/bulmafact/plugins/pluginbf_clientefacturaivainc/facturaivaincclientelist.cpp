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

#include <QtWidgets/QCheckBox>
#include "blfile.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QTextStream>

#include "facturaivaincclientelist.h"
#include "facturaivaincclienteview.h"
#include "blplugins.h"
#include "bfcompany.h"
#include "blfunctions.h"


///
/**
**/
void FacturaIVAIncClienteListSubform::load()
{
    BL_FUNC_DEBUG
    QString SQLQuery = "SELECT * FROM factura";
    BlSubForm::load ( SQLQuery );
    
}


///
/**
\param query
**/
void FacturaIVAIncClienteListSubform::load ( QString query )
{
    BL_FUNC_DEBUG
    BlSubForm::load ( query );
    
}


///
/**
\param val
**/
void FacturaIVAIncClienteList::setidcliente ( QString val )
{
    BL_FUNC_DEBUG
    m_cliente->setId ( val );
    
}


///
/**
\return
**/
QString FacturaIVAIncClienteList::idfactura()
{
    BL_FUNC_DEBUG
    
    return mdb_idfactura;
}


///
/**
**/
void FacturaIVAIncClienteList::crear()
{
    BL_FUNC_DEBUG
    FacturaIVAIncClienteView *acv = new FacturaIVAIncClienteView ( ( BfCompany * ) mainCompany(), 0 );
    mainCompany()->m_pWorkspace->addSubWindow ( acv );
    acv->inicializar();
    acv->pintar();
    
    /// Si se crea el nuevo factura desde la lista de facturaes de un cliente,
    /// entonces se crea el factura para este cliente.
    if (m_cliente->id() != "") {
	acv->mui_idcliente->setId( m_cliente->id() );
    } // end if

    acv->show();
    acv->mui_descfactura->setFocus ( Qt::OtherFocusReason );
    
}


/** Constructor de la clase sin inicializacion de company. Usando este
    constructor no se olvide de usar setcompany para que la clase no de
    excepciones.
    El constructor crea la pantalla, la pone en editmodo por defecto y la mete
    en el listado de ventanas.
    Usando esta clase tampoco se inicializan bien los widgets que contiene.
*/
/**
\param parent
\param flag
\param editmodo
\return
**/
FacturaIVAIncClienteList::FacturaIVAIncClienteList ( QWidget *parent, Qt::WindowFlags flag, edmode editmodo )
        : BlFormList ( NULL, parent, flag, editmodo )
{
    BL_FUNC_DEBUG
    setupUi ( this );
    /// Disparamos los plugins.
    int res = g_plugins->run ( "FacturaIVAIncClienteList_FacturaIVAIncClienteList", this );
    if ( res != 0 )
        return;
    mdb_idfactura = "";
    setPlantilla( "facturaivainc" );
    
    setSubForm ( mui_list );
    hideBusqueda();
    iniciaForm();
    /// Llamamos a los scripts
    blScript(this);
    
}


/** Constructor de la clase.
    Inicializa toda la ventana y los widgets que esta contiene.
    Hace una presentacion inicial de los facturaes de cliente.
    Pone la pantalla en modo de edicion por defecto  a no ser que se especifique lo contrario.
    Mete la ventana en el workspace.
*/
/**
\param comp
\param parent
\param flag
\param editmodo
\return
**/
FacturaIVAIncClienteList::FacturaIVAIncClienteList ( BfCompany *comp, QWidget *parent, Qt::WindowFlags flag, edmode editmodo )
        : BlFormList ( comp, parent, flag, editmodo )
{
    BL_FUNC_DEBUG
    setupUi ( this );
    /// Disparamos los plugins.
    int res = g_plugins->run ( "FacturaIVAIncClienteList_FacturaIVAIncClienteList", this );
    if ( res != 0 )
        return;
    m_cliente->setMainCompany ( comp );
    m_articulo->setMainCompany ( comp );
    mui_list->setMainCompany ( comp );
    setSubForm ( mui_list );
    iniciaForm();

    /// Establecemos los parametros de busqueda del Cliente
    m_cliente->setLabel ( _ ( "Cliente:" ) );
    m_cliente->setTableName ( "cliente" );
    setPlantilla( "facturaivainc" );
    m_cliente->m_valores["cifcliente"] = "";
    m_cliente->m_valores["nomcliente"] = "";

    /// Iniciamos el buscador de trabajadores.
    m_idtrabajador->setMainCompany ( mainCompany() );
    m_idtrabajador->setQuery ( "SELECT * FROM trabajador ORDER BY apellidostrabajador, nomtrabajador" );
    m_idtrabajador->setTableName ( "trabajador" );
    m_idtrabajador->setFieldId ( "idtrabajador" );
    m_idtrabajador->m_valores["apellidostrabajador"] = "";
    m_idtrabajador->m_valores["nomtrabajador"] = "";
    m_idtrabajador->setAllowNull ( true );
    m_idtrabajador->setId("");
    
    /// Cargamos los filtros guardados.
    cargaFiltrosXML();
    
    presentar();
    mdb_idfactura = "";
    if ( editMode() )
        mainCompany() ->insertWindow ( windowTitle(), this );
    hideBusqueda();
    /// Hacemos el tratamiento de los permisos que desabilita botones en caso de no haber suficientes permisos.
    trataPermisos ( "factura" );
    /// Llamamos a los scripts
    blScript(this);
    
}


///
/**
\return
**/
void FacturaIVAIncClienteList::iniciaForm()
{
    BL_FUNC_DEBUG
    /// Disparamos los plugins.
    int res = g_plugins->run ( "FacturaIVAIncClienteList_iniciaForm", this );
    if ( res != 0 )
        return;
    mui_procesada->insertItem ( 0, _ ( "Todos los facturaivaincs" ) );
    mui_procesada->insertItem ( 1, _ ( "FacturaIVAIncs procesados" ) );
    mui_procesada->insertItem ( 2, _ ( "FacturaIVAIncs no procesados" ) );
    mui_procesada->setCurrentIndex ( 2 );
    
}


///
/**
\param comp
**/
void FacturaIVAIncClienteList::setMainCompany ( BfCompany *comp )
{
    BL_FUNC_DEBUG
    BlMainCompanyPointer::setMainCompany ( comp );
    m_cliente->setMainCompany ( comp );
    m_articulo->setMainCompany ( comp );
    mui_list->setMainCompany ( comp );
    
    
    /// Iniciamos el buscador de trabajadores.
    m_idtrabajador->setMainCompany ( mainCompany() );
    m_idtrabajador->setQuery ( "SELECT * FROM trabajador ORDER BY apellidostrabajador, nomtrabajador" );
    m_idtrabajador->setTableName ( "trabajador" );
    m_idtrabajador->setFieldId ( "idtrabajador" );
    m_idtrabajador->m_valores["apellidostrabajador"] = "";
    m_idtrabajador->m_valores["nomtrabajador"] = "";
    m_idtrabajador->setAllowNull ( true );   
    m_idtrabajador->setId("");
    
    
}


/** Destructor de la clase */
/**
**/
FacturaIVAIncClienteList::~FacturaIVAIncClienteList()
{
    BL_FUNC_DEBUG
    
}


/** Carga el listado de la base de datos y lo presenta.
    Tambien carga el total y lo presenta.
*/
/**
**/
void FacturaIVAIncClienteList::presentar()
{
    BL_FUNC_DEBUG

    mui_list->load ( "SELECT *, totalfactura AS total, bimpfactura AS base, impfactura AS impuestos FROM factura LEFT JOIN  cliente ON factura.idcliente = cliente.idcliente LEFT JOIN almacen ON factura.idalmacen = almacen.idalmacen LEFT JOIN forma_pago ON factura.idforma_pago = forma_pago.idforma_pago WHERE 1 = 1 " + generarFiltro() );

    /// Hacemos el calculo del total.
    BlDbRecordSet *cur = mainCompany() ->loadQuery ( "SELECT SUM(totalfactura) AS total FROM factura LEFT JOIN cliente ON factura.idcliente=cliente.idcliente LEFT JOIN almacen ON almacen.idalmacen = factura.idalmacen where 1 = 1 " + generarFiltro() );
    /// Esta consulta podria resultar NULA y debe tratarse el caso
    if ( cur ) {
        m_total->setText ( cur->value( "total" ) );
        delete cur;
    } // end if

    
}


/**  Este metodo se activa cuando bien pulsando sobre el boton de editar
     o bien haciendo doble click en el modo de edicion se desea invocar la accion
     Editar el elemento si estamos en modo editmode o cerrar la ventana y emitir
     un signal selected() si estamos en el modo selector.

     Primero determina el idfactura seleccionado, luego crea la instancia de
     la ventana de edicion FacturaIVAIncClienteView y lo mete en el workspace.
     Por ultimo hace que dicha ventana carge de la base de datos el idfactura
     seleccionado.
*/
/**
\param row
\return
**/
void FacturaIVAIncClienteList::editar ( int row )
{
    BL_FUNC_DEBUG
    mdb_idfactura = mui_list->dbValue ( QString ( "idfactura" ), row );
    if ( editMode() ) {
        FacturaIVAIncClienteView * prov = new FacturaIVAIncClienteView ( ( BfCompany * ) mainCompany(), 0 );
        if ( prov->load ( mdb_idfactura ) ) {
            delete prov;
            return;
        } // end if
        mainCompany() ->m_pWorkspace->addSubWindow ( prov );
        prov->show();
    } else {
        emit ( selected ( mdb_idfactura ) );
    } // end if
    
}



/** Responde a la pulsacion del boton borrar en el formulario.
    Carga el elemento seleccionado e invoca a su metodo de borrar.
*/
/// \todo: Comprobar que se libera bien la memoria.
/// \todo: Intentar que no se tenga que recargar todo el listado y que simplemente se borre la fila seleccionada.
/**
\return
**/
void FacturaIVAIncClienteList::remove()
{
    BL_FUNC_DEBUG
    int a = mui_list->currentRow();
    if ( a < 0 ) {
        blMsgInfo ( _ ( "Debe seleccionar una linea" ), this );
        return;
    } // end if
    try {
        mdb_idfactura = mui_list->dbValue ( QString ( "idfactura" ) );
        if ( editMode() ) {
            FacturaIVAIncClienteView * acv = new FacturaIVAIncClienteView ( ( BfCompany * ) mainCompany(), 0 );
            if ( acv->load ( mdb_idfactura ) )
                throw - 1;
            acv->on_mui_borrar_clicked();
            acv->close();
        } // end if
        presentar();
    } catch ( ... ) {
        blMsgInfo ( _ ( "Error al borrar el factura a cliente" ), this );
    } // end try
    
}


/** La impresion de listados es estandarizada por la clase BlDbRecord
*/
void FacturaIVAIncClienteList::imprimir()
{
    BL_FUNC_DEBUG
    printPDF ( _ ( "FacturaIVAInces a clientes" ) );
    
}


/** Este metodo ayuda a construir el query de filtrado construyendo la clausula
    WHERE a partir de las opciones de filtrado.
*/
/**
\return
**/
QString FacturaIVAIncClienteList::generarFiltro()
{
    /// Tratamiento de los filtros.
    BL_FUNC_DEBUG
    QString filtro = "";

    if ( m_filtro->text() != "" ) {
        filtro = " AND ( lower(descfactura) LIKE lower('%" + m_filtro->text() + "%') ";
        filtro += " OR reffactura LIKE '" + m_filtro->text() + "%' ";
        filtro += " OR lower(nomcliente) LIKE lower('%" + m_filtro->text() + "%')) ";
    } else {
        filtro = "";
    } // end if

    if ( m_cliente->id() != "" )
        filtro += " AND factura.idcliente='" + m_cliente->id() + "'";

    if ( m_articulo->idarticulo() != "" )
        filtro += " AND idfactura IN (SELECT DISTINCT idfactura FROM lfactura WHERE idarticulo='" + m_articulo->idarticulo() + "')";

    /// Tratamos los elementos procesados y no procesados.
    if ( mui_procesada->currentIndex() == 1 ) {
        /// Muestra solo las procesadas.
        filtro += " AND procesadafactura";
    } else if ( mui_procesada->currentIndex() == 2 ) {
        /// Muestra solo las NO procesadas.
        filtro += " AND NOT procesadafactura ";
    } // end if

    if ( m_fechain->text() != "" )
        filtro += " AND fechafactura >= '" + m_fechain->text() + "' ";

    if ( m_fechafin->text() != "" )
        filtro += " AND fechafactura <= '" + m_fechafin->text() + "' ";

    if (m_idtrabajador->id() != "") {
	filtro += " AND idtrabajador = " + m_idtrabajador->id();
    } // end if
    
    filtro += " AND ticketfactura = true";
    
    return ( filtro );
}


/// =============================================================================
///                    SUBFORMULARIO
/// =============================================================================
/** Constructor del subformulario de facturas a cliente.
    Configura el subformulario para que use la tabla factura.
*/
/**
\param parent
\return
**/
FacturaIVAIncClienteListSubform::FacturaIVAIncClienteListSubform ( QWidget *parent ) : BfSubForm ( parent )
{
    BL_FUNC_DEBUG

    /// Disparamos los plugins.
    int res = g_plugins->run ( "FacturaIVAIncClienteListSubform_FacturaIVAIncClienteListSubform", this );
    if ( res != 0 )
        return;
    setDbTableName ( "factura" );
    setDbFieldId ( "idfactura" );
    setFileConfig( "facturaivainc");
    addSubFormHeader ( "reffactura", BlDbField::DbInt, BlDbField::DbNotNull | BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite, _ ( "Referencia de factura" ) );
    addSubFormHeader ( "codigoalmacen", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Codigo de almacen" ) );
    addSubFormHeader ( "numfactura", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Numero de factura" ) );
    addSubFormHeader ( "descfactura", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Descripcion" ) );
    addSubFormHeader ( "fechafactura", BlDbField::DbDate, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Fecha de factura" ) );
    addSubFormHeader ( "nomcliente", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Nombre de cliente" ) );
    addSubFormHeader ( "idforma_pago", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "ID forma de pago" ) );
    addSubFormHeader ( "descforma_pago", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Descripcion de forma de pago" ) );
    addSubFormHeader ( "idtrabajador", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "ID trabajador" ) );
    addSubFormHeader ( "idcliente", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "ID cliente" ) );
    addSubFormHeader ( "idfactura", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "ID factura" ) );
    addSubFormHeader ( "comentfactura", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Comentarios del factura" ) );
    addSubFormHeader ( "idalmacen", BlDbField::DbInt, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "ID almacen" ) );
    addSubFormHeader ( "base", BlDbField::DbNumeric, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Base imponible" ) );
    addSubFormHeader ( "impuestos", BlDbField::DbNumeric, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Impuestos" ) );
    addSubFormHeader ( "total", BlDbField::DbNumeric, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Total" ) );
    setInsert ( false );
    setDelete ( false );
    setSortingEnabled ( true );
    
}


///
/**
**/
FacturaIVAIncClienteListSubform::~FacturaIVAIncClienteListSubform()
{
    BL_FUNC_DEBUG
    
}
