/***************************************************************************
 *   Copyright (C) 2005 by Alvaro de Miguel                                *
 *   alvaro.demiguel@gmail.com                                             *
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

#include <QCloseEvent>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QObject>
#include <QToolButton>
#include <QWidget>

#include "compraventaview.h"
#include "articulolist.h"
#include "clientslist.h"
#include "cobroview.h"
#include "company.h"
#include "configuracion.h"
#include "facturaslist.h"
#include "facturaview.h"
#include "funcaux.h"
#include "informereferencia.h"
#include "listdescalbaranclienteview.h"
#include "listlinalbaranclienteview.h"
#include "pedidoclienteview.h"
#include "pedidosclientelist.h"
#include "postgresiface2.h"
#include "presupuestolist.h"
#include "presupuestoview.h"
#include "plugins.h"


/** Constructor de la clase corresponde a la parte visual de la ficha de cliente.
    Inicializa la ventana y todos sus componentes.
    Mete la ventana en el WorkSpace.
*/
/**
\param comp
\param parent
\return
**/
CompraVentaView::CompraVentaView ( Company *comp, QWidget *parent )
        : FichaBf ( comp, parent )
{
    _depura ( "CompraVentaView::CompraVentaView", 0 );
    setAttribute ( Qt::WA_DeleteOnClose );
    try {
        setupUi ( this );

	m_albaranp = new FichaBf(comp, parent);
	m_albaranp->setDBTableName("albaranp");
        m_albaranp->setDBCampoId ( "idalbaranp" );
        m_albaranp->addDBCampo ( "idalbaranp", DBCampo::DBint, DBCampo::DBPrimaryKey, QApplication::translate ( "AlbaranProveedor", "Id albaran proveedor" ) );
        m_albaranp->addDBCampo ( "numalbaranp", DBCampo::DBint, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Numero albaran proveedor" ) );
        m_albaranp->addDBCampo ( "fechaalbaranp", DBCampo::DBdate, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Fecha albaran proveedor" ) );
        m_albaranp->addDBCampo ( "comentalbaranp", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Comentario albaran proveedor" ) );
        m_albaranp->addDBCampo ( "idproveedor", DBCampo::DBint, DBCampo::DBNotNull, QApplication::translate ( "AlbaranProveedor", "Id proveedor" ) );
        m_albaranp->addDBCampo ( "idforma_pago", DBCampo::DBint, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Id forma de pago" ) );
        m_albaranp->addDBCampo ( "idalmacen", DBCampo::DBint, DBCampo::DBNotNull, QApplication::translate ( "AlbaranProveedor", "Id almacen" ) );
        m_albaranp->addDBCampo ( "refalbaranp", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Referencia albaran proveedor" ) );
        m_albaranp->addDBCampo ( "descalbaranp", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranProveedor", "Descripcion albaran proveedor" ) );

        subform3->setEmpresaBase ( comp );
        m_descuentos3->setEmpresaBase ( comp );
        m_albaranp->setListaLineas ( subform3 );
        m_albaranp->setListaDescuentos ( m_descuentos3 );


        setTitleName ( tr ( "Compra Venta" ) );
        setDBTableName ( "albaran" );
        setDBCampoId ( "idalbaran" );
        addDBCampo ( "idalbaran", DBCampo::DBint, DBCampo::DBPrimaryKey, QApplication::translate ( "AlbaranCliente", "Id albaran" ) );
        addDBCampo ( "idcliente", DBCampo::DBint, DBCampo::DBNotNull, QApplication::translate ( "AlbaranCliente", "Cliente" ) );
        addDBCampo ( "idalmacen", DBCampo::DBint, DBCampo::DBNotNull, QApplication::translate ( "AlbaranCliente", "Almacen" ) );
        addDBCampo ( "numalbaran", DBCampo::DBint, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Numero de albaran" ) );
        addDBCampo ( "fechaalbaran", DBCampo::DBdate, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Fecha de creacion" ) );
        addDBCampo ( "contactalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Persona de contacto" ) );
        addDBCampo ( "telalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Telefono de contacto" ) );
        addDBCampo ( "comentalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Comentario" ) );
        addDBCampo ( "comentprivalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Comentario privado" ) );
        addDBCampo ( "idforma_pago", DBCampo::DBint, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Forma de pago" ) );
        addDBCampo ( "idtrabajador", DBCampo::DBint, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Trabajador" ) );
        addDBCampo ( "procesadoalbaran", DBCampo::DBboolean, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Procesado" ) );
        addDBCampo ( "descalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Descripcion" ) );
        addDBCampo ( "refalbaran", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate ( "AlbaranCliente", "Referencia" ) );

        /// Disparamos los plugins.
        int res = g_plugins->lanza ( "CompraVentaView_CompraVentaView", this );
        if ( res != 0 )
            return;

        subform2->setEmpresaBase ( comp );
        m_descuentos->setEmpresaBase ( comp );
        mui_idalmacen->setEmpresaBase ( comp );
        mui_idforma_pago->setEmpresaBase ( comp );
        mui_idcliente->setEmpresaBase ( comp );
        mui_idtrabajador->setEmpresaBase ( comp );
        mui_refalbaran->setEmpresaBase ( comp );

        setListaLineas ( subform2 );
        setListaDescuentos ( m_descuentos );

        /// Inicializamos para que no se queden sin ser pintada.
        mui_idforma_pago->setValorCampo ( "0" );
        mui_idalmacen->setValorCampo ( "0" );
        mui_idtrabajador->setValorCampo ( "0" );

        meteWindow ( windowTitle(), this, FALSE );

        /// Disparamos los plugins por flanco descendente.
        g_plugins->lanza ( "CompraVentaView_CompraVentaView_Post", this );
    } catch ( ... ) {
        mensajeInfo ( tr ( "Error al crear el albaran a cliente" ), this );
    } // end try
    _depura ( "END CompraVentaView::CompraVentaView", 0 );
}


/** Destructor de la clase.
    Indica al listado que debe actualizarse.
*/
/// \TODO: Este metodo deberia mejorarse para que indicase al listado que
/// solo debe eliminar una fila del mismo.
/**
**/
CompraVentaView::~CompraVentaView()
{
    _depura ( "CompraVentaView::~CompraVentaView", 0 );
    delete m_albaranp;
    empresaBase() ->refreshAlbaranesCliente();
    _depura ( "END CompraVentaView::~CompraVentaView", 0 );
}


/// Inicializa todos los elementos del formulario
/**
**/
void CompraVentaView::inicializar()
{
    _depura ( "CompraVentaView::inicializar", 0 );
    subform2->inicializar();
    m_descuentos->inicializar();
    dialogChanges_cargaInicial();
    _depura ( "END CompraVentaView::inicializar", 0 );
}



/// Pinta los totales en las casillas correspondientes
/**
\param iva
\param base
\param total
\param desc
\param irpf
\param reqeq
**/
void CompraVentaView::pintatotales ( Fixed iva, Fixed base, Fixed total, Fixed desc, Fixed irpf, Fixed reqeq )
{
    _depura ( "CompraVentaView::pintatotales", 0 );
    m_totalBases->setText ( base.toQString() );
    m_totalTaxes->setText ( iva.toQString() );
    m_totalalbaran->setText ( total.toQString() );
    m_totalDiscounts->setText ( desc.toQString() );
    m_totalIRPF->setText ( QString ( irpf.toQString() ) );
    m_totalReqEq->setText ( QString ( reqeq.toQString() ) );
    _depura ( "END CompraVentaView::pintatotales", 0 );
}



/// Se encarga de generar una factura a partir de un albar&aacute;n.
/** Primero de todo busca una factura por referencia que tenga este albaran.
    Si dicha factura existe entonces la cargamos y terminamos.
    Si no existe dicha factura el sistema avisa y permite crear una poniendo
    Todos los datos del albaran automaticamente en ella.
*/
/**
\return
**/
void CompraVentaView::generarFactura()
{
    _depura ( "CompraVentaView::generarFactura", 0 );

    FacturaView *bud = NULL;
    cursor2 *cur = NULL;

    try {
        /// Comprueba si disponemos de los datos m&iacute;nimos. Si no se hace esta
        /// comprobaci&oacute;n la consulta a la base de datos ser&aacute; erronea y al hacer
        /// el siguiente cur->eof() el programa fallar&aacute;.
        /// Comprobamos que existe una factura con esos datos, y en caso afirmativo lo mostramos.

        QString SQLQuery = "";

        if ( DBvalue ( "refalbaran" ).isEmpty() || DBvalue ( "idcliente" ).isEmpty() ) {
            /// El albaran no se ha guardado y no se dispone en la base de datos
            /// de estos datos. Se utilizan en su lugar los del formulario.
            /// Verifica que exista, por lo menos, un cliente seleccionado.
            if ( mui_idcliente->idcliente().isEmpty() ) {
                mensajeInfo ( tr ( "Tiene que seleccionar un cliente" ), this );
                return;
            } else {
                SQLQuery = "SELECT * FROM factura WHERE reffactura = '" + mui_refalbaran->text() + "' AND idcliente = " + mui_idcliente->idcliente();
            } // end if
        } else {
            SQLQuery = "SELECT * FROM factura WHERE reffactura = '" + DBvalue ( "refalbaran" ) + "' AND idcliente = " + DBvalue ( "idcliente" );
        } // end if

        cur = empresaBase() ->cargacursor ( SQLQuery );

        if ( !cur->eof() ) {
            /// Informamos que ya hay una factura y que la abriremos.
            /// Si no salimos de la funci&oacute;n.
            if ( QMessageBox::question ( this,
                                         tr ( "Factura existente" ),
                                         tr ( "Existe una factura a este cliente con la misma referencia que este albaran. Desea abrirla para verificar?" ),
                                         tr ( "&Si" ), tr ( "&No" ), QString::null, 0, 1 ) ) {
                return;
            }
            bud = empresaBase() ->newFacturaView();
            empresaBase() ->m_pWorkspace->addWindow ( bud );
            bud->cargar ( cur->valor ( "idfactura" ) );
            bud->show();
            return;
        } // end if
        delete cur;

        /// Creamos la factura.
        bud = empresaBase() ->newFacturaView();
        empresaBase() ->m_pWorkspace->addWindow ( bud );

        /// Cargamos un elemento que no existe para inicializar bien la clase.
        bud->cargar ( "0" );

        /// Traspasamos los datos a la factura.
        recogeValores();
        bud->setDBvalue ( "comentfactura", DBvalue ( "comentalbaran" ) );
        bud->setDBvalue ( "idforma_pago", DBvalue ( "idforma_pago" ) );
        bud->setDBvalue ( "reffactura", DBvalue ( "refalbaran" ) );
        bud->setDBvalue ( "idcliente", DBvalue ( "idcliente" ) );
        bud->setDBvalue ( "idalmacen", DBvalue ( "idalmacen" ) );

        QString l;
        SDBRecord *linea, *linea1;
        for ( int i = 0; i < m_listalineas->rowCount(); ++i ) {
            linea = m_listalineas->lineaat ( i );
            if ( linea->DBvalue ( "idarticulo" ) != "" ) {
                linea1 = bud->getlistalineas() ->lineaat ( bud->getlistalineas() ->rowCount() - 1 );
                /// Haciendo el nuevo registro antes nos evitamos problemas de foco.
                bud->getlistalineas() ->nuevoRegistro();
                bud->getlistalineas() ->setProcesarCambios ( FALSE );
                linea1->setDBvalue ( "codigocompletoarticulo", linea->DBvalue ( "codigocompletoarticulo" ) );
                linea1->setDBvalue ( "desclfactura", linea->DBvalue ( "desclalbaran" ) );
                linea1->setDBvalue ( "cantlfactura", linea->DBvalue ( "cantlalbaran" ) );
                linea1->setDBvalue ( "pvplfactura", linea->DBvalue ( "pvplalbaran" ) );
                linea1->setDBvalue ( "ivalfactura", linea->DBvalue ( "ivalalbaran" ) );
                linea1->setDBvalue ( "descuentolfactura", linea->DBvalue ( "descuentolalbaran" ) );
                linea1->setDBvalue ( "idarticulo", linea->DBvalue ( "idarticulo" ) );
                linea1->setDBvalue ( "nomarticulo", linea->DBvalue ( "nomarticulo" ) );
                bud->getlistalineas() ->setProcesarCambios ( TRUE );
                linea1->refresh();
            } // end if
        } // end for

        /// Traspasamos los descuentos.
        for ( int i = 0; i < m_listadescuentos->rowCount(); ++i ) {
            linea1 = m_listadescuentos->lineaat ( i );
            if ( linea1->DBvalue ( "proporciondalbaran" ) != "" ) {
                linea = bud->getlistadescuentos() ->lineaat ( bud->getlistadescuentos() ->rowCount() - 1 );
                bud->getlistadescuentos() ->setProcesarCambios ( FALSE );
                linea->setDBvalue ( "conceptdfactura", linea1->DBvalue ( "conceptdalbaran" ) );
                linea->setDBvalue ( "proporciondfactura", linea1->DBvalue ( "proporciondalbaran" ) );
                bud->getlistadescuentos() ->setProcesarCambios ( TRUE );
                bud->getlistadescuentos() ->nuevoRegistro();
            } // end if
        } // end for

        bud->pintar();
        bud->calculaypintatotales();
        bud->show();

        mui_procesadoalbaran->setChecked ( TRUE );

    } catch ( ... ) {
        mensajeInfo ( tr ( "Error inesperado" ), this );
        if ( cur ) delete cur;
        if ( bud ) delete bud;
    } // end try

    _depura ( "END CompraVentaView::generarFactura", 0 );
}


/// Se encarga de agregar un albaran a una factura ya existente.
/// Para ello presenta un selector de factura y permite escoger a que factura
/// Agregar el albaran.
/**
**/
void CompraVentaView::agregarFactura()
{
    /// Pedimos la factura a la que agregar.
    _depura ( "CompraVentaView::agregarFactura", 0 );
    QDialog *diag = new QDialog ( 0 );
    diag->setWindowTitle ( tr ( "Seleccione la factura a la que agregar el albaran." ) );
    diag->setModal ( true );

    /// \TODO: Debe pasar por company la creacion del listado
    FacturasList *fac = new FacturasList ( empresaBase(), diag, 0, FacturasList::SelectMode );
    connect ( fac, SIGNAL ( selected ( QString ) ), diag, SLOT ( accept() ) );

    /// Hacemos que las opciones de filtrado del listado ya est&eacute;n bien.
    fac->m_cliente->setidcliente ( DBvalue ( "idcliente" ) );
    fac->on_mui_actualizar_clicked();

    /// Lanzamos el di&aacute;logo.
    diag->exec();
    QString idfactura = fac->idfactura();
    delete diag;

    /// Si no hay idfactura es que hemos abortado y por tanto cancelamos la operaci&oacute;n.
    if ( idfactura == "" )
        return;

    /// Creamos la factura.
    FacturaView *bud = empresaBase() ->newFacturaView();
    bud->cargar ( idfactura );

    /// Agregamos en los comentarios que se ha a&ntilde;adido este albar&aacute;n.
    bud->setDBvalue ( "comentfactura", bud->DBvalue ( "comentfactura" ) + tr ( "Num. albaran" ) + DBvalue ( "numalbaran" ) + "\n" );

    empresaBase() ->m_pWorkspace->addWindow ( bud );
    /// \TODO EN TEORIA SE DEBERIA COMPROBAR QUE LA FACTURA ES DEL MISMO CLIENTE,
    /// PERO POR AHORA PASAMOS DE HACERLO.
    QString l;
    SDBRecord *linea, *linea1;
    for ( int i = 0; i < m_listalineas->rowCount(); ++i ) {
        linea = m_listalineas->lineaat ( i );
        if ( linea->DBvalue ( "idarticulo" ) != "" ) {
            linea1 = bud->getlistalineas() ->lineaat ( bud->getlistalineas() ->rowCount() - 1 );
            bud->getlistalineas() ->setProcesarCambios ( FALSE );
            linea1->setDBvalue ( "desclfactura", linea->DBvalue ( "desclalbaran" ) );
            linea1->setDBvalue ( "cantlfactura", linea->DBvalue ( "cantlalbaran" ) );
            linea1->setDBvalue ( "pvplfactura", linea->DBvalue ( "pvplalbaran" ) );
            linea1->setDBvalue ( "descuentolfactura", linea->DBvalue ( "descuentolalbaran" ) );
            linea1->setDBvalue ( "idarticulo", linea->DBvalue ( "idarticulo" ) );
            linea1->setDBvalue ( "codigocompletoarticulo", linea->DBvalue ( "codigocompletoarticulo" ) );
            linea1->setDBvalue ( "nomarticulo", linea->DBvalue ( "nomarticulo" ) );
            linea1->setDBvalue ( "ivalfactura", linea->DBvalue ( "ivalalbaran" ) );
            bud->getlistalineas() ->setProcesarCambios ( TRUE );
            bud->getlistalineas() ->nuevoRegistro();
        } // end if
    } // end for
    bud->calculaypintatotales();
    bud->show();
    mui_procesadoalbaran->setChecked ( TRUE );
    _depura ( "END CompraVentaView::agregarFactura", 0 );
}


/// Crea un nuevo cobro para el albar&aacute;n seleccionado.
/// Util con cobros anticipados a la factura. El cobro tendra
/// la misma cantidad, referencia y cliente que el albaran.
/// Este metodo crea una pantalla de cobro y le pone los datos necesarios.
/**
**/
void CompraVentaView::on_mui_cobrar_clicked()
{
    _depura ( "CompraVentaView::on_mui_cobrar_clicked", 0 );
    recogeValores();
    CobroView *bud = empresaBase() ->newCobroView();
    bud->setDBvalue ( "idcliente", DBvalue ( "idcliente" ) );
    bud->setDBvalue ( "cantcobro", m_totalalbaran->text() );
    bud->setDBvalue ( "refcobro", DBvalue ( "refalbaran" ) );
    bud->setDBvalue ( "comentcobro", DBvalue ( "descalbaran" ) );
    bud->pintar();
    bud->show();
    _depura ( "END CompraVentaView::on_mui_cobrar_clicked", 0 );
}


///
/**
\param id
**/
void CompraVentaView::on_mui_idcliente_valueChanged ( QString id )
{
    _depura ( "CompraVentaView::on_m_cliente_valueChanged", 0 );
    subform2->setIdCliente ( id );
    mui_idforma_pago->setIdCliente ( id );
    _depura ( "END CompraVentaView::on_m_cliente_valueChanged", 0 );
}






/// Este slot se activa cuando hay cambios en los subformularios.
/**
**/
void CompraVentaView::s_pintaTotales()
{
    _depura ( "CompraVentaView::s_pintaTotales", 0 );
    calculaypintatotales();
    _depura ( "END CompraVentaView::s_pintaTotales", 0 );
}


///
/**
**/
void CompraVentaView::on_mui_facturar_clicked()
{
    _depura ( "CompraVentaView::on_mui_facturar_clicked", 0 );
    generarFactura();
    _depura ( "END CompraVentaView::on_mui_facturar_clicked", 0 );
}


///
/**
**/
void CompraVentaView::on_mui_agregarafactura_clicked()
{
    _depura ( "CompraVentaView::on_mui_agregarafactura_clicked", 0 );
    agregarFactura();
    _depura ( "END CompraVentaView::on_mui_agregarafactura_clicked", 0 );
}


///
/**
**/
void CompraVentaView::on_m_descuentos_editFinish ( int, int )
{
    _depura ( "CompraVentaView::on_m_descuentos_editFinish", 0 );
    calculaypintatotales();
    _depura ( "END CompraVentaView::on_m_descuentos_editFinish", 0 );
}


///
/**
**/
void CompraVentaView::on_subform2_editFinish ( int, int )
{
    _depura ( "CompraVentaView::on_subform2_editFinish", 0 );
    calculaypintatotales();
    _depura ( "END CompraVentaView::on_subform2_editFinish", 0 );
}



/** Metodo de borrar un albaran. Se encarga de mandar a la base de datos
    la instruccion necesaria para el borrado de un albaran y controlar
    los posibles errores que se produzcan.
    Tambi&eacute;n borra todas las lineas y las lineas de descuento que se refieren
    a el albaran que se pretende borrar.
*/
/// \todo: Este metodo deberia poderse delegar en DBRecord, o por lo menos la parte del borrado del registro.
/// \todo: Hace falta meter el metodo dentro del sistema de excepciones try catch.
/**
\return
**/
int CompraVentaView::borrarPre()
{
    _depura ( "CompraVentaView::borrar", 0 );
    m_listalineas->borrar();
    m_listadescuentos->borrar();
    _depura ( "END CompraVentaView::borrar", 0 );
    return 0;
}



void CompraVentaView::on_mui_idcliente_valueChanged() {
	mensajeInfo("Cliente cambiado");
}


/** Este m&eacute;todo carga un AlbaranCliente. Tambi&eacute;n carga las lineas
    de albar&aacute;n y los descuentos de albar&aacute;n.
    Tras la carga tambi&eacute;n invoca un repintado del albaran para que se vea
    correctamente la pantalla.
*/
/**
\param idalbaran
\return
**/
int CompraVentaView::cargarPost ( QString idalbaran )
{
    _depura ( "CompraVentaView::cargar", 0 );
	try {
	m_listalineas->cargar ( idalbaran );
	m_listadescuentos->cargar ( idalbaran );
	
	/// Establecemos los valores del albaran de proveedor por si acaso el albaran de proveedor no existiese.
	m_albaranp->setDBvalue("refalbaranp", DBvalue("refalbaran"));


	/// Buscamos si hay algun albaran de proveedor y lo cargamos.
	QString query = "SELECT * FROM albaranp WHERE refalbaranp='" + DBvalue("refalbaran")+"'";
	cursor2 *cur = empresaBase()->cargacursor(query);
	if (!cur->eof()) {
		m_albaranp->cargar(cur->valor("idalbaranp"));
		m_albaranp->m_listalineas->cargar(cur->valor("idalbaranp"));
		m_albaranp->m_listadescuentos->cargar(cur->valor("idalbaranp"));
	} // end if
	delete cur;
	
	/// Disparamos los plugins con presupuesto_imprimirPresupuesto.
	g_plugins->lanza ( "AlbaranCliente_cargarPost_Post", this );
	
	calculaypintatotales();
	_depura ( "END CompraVentaView::cargar", 0 );
	return 0;
	} catch(...) {
		_depura("error en la funcion CompraVentaView::cargar",2);
		return 0;
	} // end try
}


/** Este m&eacute;todo se encarga de hacer el guardado del albar&aacute; en la
    base de datos. Una vez guardado se guardan las lineas de albar&aacute;n y los
    descuentos de albar&aacute;n. Tras hacer el guardado se hace una carga del albaran
    para recuperar los datos que haya podido escribir la base de datos automaticamente.
    Dichos datos son la referencia y el n&uacute;mero de albar&aacute;n.

    Si todo funciona bien este m&eacute;todo devuelve 0. Si se produce algun error
    se genera una excepcion -1.
*/
/**
\return
**/
void CompraVentaView::on_mui_guardar_clicked()
{
    _depura ( "CompraVentaView::on_mui_guardar_clicked", 0 );
    mensajeInfo ( "CompraVentaView::on_mui_guardar_clicked" );
	DBRecord::guardar();
    m_listalineas->setColumnValue ( "idalbaran", DBvalue ( "idalbaran" ) );
    m_listalineas->guardar();
    m_listadescuentos->setColumnValue ( "idalbaran", DBvalue ( "idalbaran" ) );
    m_listadescuentos->guardar();

	mensajeInfo("guardamos el proveedor");
	m_albaranp->setDBvalue("refalbaranp", DBvalue("refalbaran"));

	m_albaranp->DBRecord::guardar();
    m_albaranp->m_listalineas->setColumnValue ( "idalbaranp", m_albaranp->DBvalue ( "idalbaranp" ) );
    m_albaranp->m_listadescuentos->setColumnValue ( "idalbaranp", m_albaranp->DBvalue ( "idalbaranp" ) );
	m_albaranp->m_listalineas->guardar();
	m_albaranp->m_listadescuentos->guardar();

    _depura ( "END CompraVentaView::on_mui_guardar_clicked", 0 );
}

void CompraVentaView::on_mui_refalbaran_returnPressed() {
	QString nuevaref = mui_refalbaran->text();
	QString idalbaran = "";
	QString query = "SELECT * FROM albaran WHERE refalbaran='"+nuevaref+"'";
	cursor2 *cur = empresaBase()->cargacursor(query);
	if (!cur->eof()) {
		idalbaran = cur->valor("idalbaran");
		cargar(idalbaran);
		m_listalineas->cargar ( idalbaran );
		m_listadescuentos->cargar ( idalbaran );
	} // end if
	delete cur;


	/// Si no existe albaran de cliente hay que cargar el albaran de proveedor.
	/// Establecemos los valores del albaran de proveedor por si acaso el albaran de proveedor no existiese.
	m_albaranp->setDBvalue("refalbaranp", DBvalue("refalbaran"));


	/// Buscamos si hay algun albaran de proveedor y lo cargamos.
	QString query1 = "SELECT * FROM albaranp WHERE refalbaranp='" + nuevaref+"'";
	cursor2 *cur1 = empresaBase()->cargacursor(query1);
	if (!cur1->eof()) {
		m_albaranp->cargar(cur1->valor("idalbaranp"));
		m_albaranp->m_listalineas->cargar(cur1->valor("idalbaranp"));
		m_albaranp->m_listadescuentos->cargar(cur1->valor("idalbaranp"));
	} // end if
	delete cur1;
	

}