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

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QVBoxLayout>

#include <map>

#include "blwindowlistdock.h"


///
/**
\param parent
**/
BlListWidget::BlListWidget ( QWidget * parent ) : QListWidget ( parent )
{
    _depura ( "BlListWidget::BlListWidget", 0 );
    _depura ( "END BlListWidget::BlListWidget", 0 );
}


///
/**
**/
BlListWidget::~BlListWidget()
{
    _depura ( "BlListWidget::~BlListWidget", 0 );
    _depura ( "END BlListWidget::~BlListWidget", 0 );
}


///
/**
\param l
\param p
**/
BlListWidgetItem::BlListWidgetItem ( BlListWidget *l, QPixmap &p ) : QListWidgetItem ( l )
{
    _depura ( "BlListWidgetItem::BlListWidgetItem", 0 );
    setIcon ( QIcon ( p ) );
    m_list = l;
    _depura ( "END BlListWidgetItem::BlListWidgetItem", 0 );
}


///
/**
**/
BlListWidgetItem::~BlListWidgetItem()
{
    _depura ( "BlListWidget::~BlListWidgetItem", 0 );
    _depura ( "END BlListWidget::~BlListWidgetItem", 0 );
}


///
/**
\param m
**/
void BlListWidgetItem::setObject ( QObject *m )
{
    _depura ( "BlListWidgetItem::setObject", 0 );
    m_obj = m;
    _depura ( "END BlListWidgetItem::setObject", 0 );
}


///
/**
\param m
**/
void BlListWidgetItem::setNombre ( QString m )
{
    _depura ( "BlListWidgetItem::setNombre", 0 );
    m_nombre = m;
    setText ( m );
    _depura ( "END BlListWidgetItem::setNombre", 0 );
}


///
/**
\return
**/
QObject *BlListWidgetItem::object()
{
    _depura ( "BlListWidgetItem::object", 0 );
    _depura ( "END BlListWidgetItem::object", 0 );
    return m_obj;
}


///
/**
\return
**/
QString BlListWidgetItem::nombre()
{
    _depura ( "BlListWidgetItem::nombre", 0 );
    _depura ( "END BlListWidgetItem::nombre", 0 );
    return m_nombre;
}


///
/**
\param w
**/
void BlWindowListDock::setWorkspace ( BlWorkspace *w )
{
    _depura ( "BlWindowListDock::setWorkspace", 0 );
    m_pWorkspace = w;
    _depura ( "END BlWindowListDock::setWorkspace", 0 );
}


///
/**
\param a
**/
BlWindowListDock::BlWindowListDock ( QWidget *a ) : QDockWidget ( a )
{
    _depura ( "BlWindowListDock::BlWindowListDock", 0 );
    m_listBox = new BlListWidget ( this );
    m_listBox->setIconSize ( QSize ( 32, 32 ) );
    m_listBox->setContentsMargins ( 0, 0, 0, 0 );
    m_listBox->setSpacing ( 0 );
    m_listBox->setWindowTitle ( _( "Indexador" ) );
    setWindowTitle ( _( "Indexador" ) );
    setFocusPolicy ( Qt::StrongFocus );
    setWidget ( m_listBox );
    setObjectName ("Indexador");
    connect ( m_listBox, SIGNAL ( itemDoubleClicked ( QListWidgetItem * ) ), this, SLOT ( dclicked() ) );
    connect ( m_listBox, SIGNAL ( itemClicked ( QListWidgetItem * ) ), this, SLOT ( clicked() ) );
    _depura ( "END BlWindowListDock::BlWindowListDock", 0 );
}


///
/**
**/
void BlWindowListDock::dclicked()
{
    _depura ( "BlWindowListDock::dclicked", 0 );
    QWidget *widget = ( QWidget * ) ( ( BlListWidgetItem * ) m_listBox->currentItem() ) ->object();
    if ( widget != NULL ) {
        if ( widget->isMaximized() == TRUE ) {
            widget->showNormal();
        } else {
            widget->showMaximized();
        } // end if
    } // end if
    _depura ( "END BlWindowListDock::dclicked", 0 );
}


///
/**
**/
void BlWindowListDock::clicked()
{
    _depura ( "BlWindowListDock::clicked", 0 );
    QWidget *widget = ( QWidget * ) ( ( BlListWidgetItem * ) m_listBox->currentItem() ) ->object();
    if ( widget != NULL ) {
        widget->show();
        widget->parentWidget() ->raise();
        m_pWorkspace->setActiveWindow ( widget );
    } // end if
    _depura ( "END BlWindowListDock::clicked", 0 );
}


///
/**
**/
BlWindowListDock::~BlWindowListDock()
{
    _depura ( "BlWindowListDock::~BlWindowListDock", 0 );
    delete m_listBox;
    _depura ( "END BlWindowListDock::~BlWindowListDock", 0 );
}


///
/**
**/
void BlWindowListDock::vaciar()
{
    _depura ( "BlWindowListDock::vaciar", 0 );
    /// Buscamos la ventana correspondiente y la borramos.
    int i = 0;
    while ( i < m_listBox->count() ) {
        BlListWidgetItem * m = ( BlListWidgetItem * ) m_listBox->item ( i );
        if ( ( ( QWidget * ) m->object() ) ->testAttribute ( Qt::WA_DeleteOnClose ) ) {
            delete m->object();
        } else {
            i++;
        } // end if
    } // end while
    _depura ( "END BlWindowListDock::vaciar", 0 );
}


///
/**
\return
**/
int BlWindowListDock::numVentanas()
{
    _depura ( "BlWindowListDock::numVentanas", 0 );
    _depura ( "END BlWindowListDock::numVentanas", 0 );
    return m_listBox->count();
}


///
/**
\param index
\return
**/
QObject *BlWindowListDock::ventana ( int index )
{
    _depura ( "BlWindowListDock::ventana", 0 );
    BlListWidgetItem *m = ( BlListWidgetItem * ) m_listBox->item ( index );
    _depura ( "END BlWindowListDock::ventana", 0 );
    return m->object();
}


///
/**
**/
void BlWindowListDock::vaciarCompleto()
{
    _depura ( "BlWindowListDock::vaciarCompleto", 0 );
    /// Buscamos la ventana correspondiente y la borramos.
    int i = 0;
    while ( i < m_listBox->count() ) {
        BlListWidgetItem * m = ( BlListWidgetItem * ) m_listBox->item ( i );
        delete m->object();
    } // end while
    _depura ( "END BlWindowListDock::vaciarCompleto", 0 );
}


/// This function provides the ability of push a window in the dock window
/// nombre This QString is the name of the window that was shown in the listbox
/// obj This QObject * contains the pointer of the window for furtner reference.
/**
\param nombre
\param obj
\param compdup
\return
**/
int BlWindowListDock::meteWindow ( QString nombre, QObject *obj, bool compdup )
{
    _depura ( "BlWindowListDock::meteWindow", 0, nombre );
    try {
        int i = 0;
        while ( i < m_listBox->count() ) {
            BlListWidgetItem * m = ( BlListWidgetItem * ) m_listBox->item ( i );
            /// Si la ventana ya esta en la lista.
            if ( m->object() == obj ) {
                _depura ( "END BlWindowListDock::meteWindow", 0, "Ya existe" + nombre );
                m->setNombre ( nombre );
                return 0;
            } // end if

            /// Comprobamos ventanas duplicadas.
            if ( m->nombre() == nombre && compdup ) {
                ( ( QWidget * ) m->object() ) ->hide();
                ( ( QWidget * ) m->object() ) ->show();
                nombre = nombre + "(i)";
//                sacaWindow ( obj );
//                throw - 1;
            } // end if
            i++;
        } // end while
        if ( i >= m_listBox->count() ) {
            QPixmap icon = ( ( QWidget * ) obj ) ->windowIcon().pixmap ( 32, 32 );
            BlListWidgetItem *m = new BlListWidgetItem ( m_listBox, icon );
            m->setObject ( obj );
            m->setNombre ( nombre );
        } // end if
    } catch ( ... ) {
        _depura ( "END BlWindowListDock::meteWindow", 0, " ventana duplicada" );
        return - 1;
    } // end try
    _depura ( "END BlWindowListDock::meteWindow", 0 );
    return 0;
}


/// Sirve para seleccionar una ventana listada en el Indexador.
/**
\param nombre
\param obj
\return
**/
int BlWindowListDock::seleccionaWindow ( QString nombre, QObject *obj )
{
    _depura ( "BlWindowListDock::seleccionaWindow", 0 );
    try {
        int i = 0;
        while ( i < m_listBox->count() ) {
            BlListWidgetItem * m = ( BlListWidgetItem * ) m_listBox->item ( i );
            /// Encuentra la ventana en la lista.
            if ( m->object() == obj ) {
                _depura ( "END BlWindowListDock::seleccionaWindow", 0, "Se ha encontrado la ventana" + nombre );
                m_listBox->setCurrentItem ( m );
                return 0;
            } // end if
            i++;
        } // end while
    } catch ( ... ) {
        throw - 1;
    } // end try
    _depura ( "END BlWindowListDock::seleccionaWindow", 0 );
    return 0;
}


/// Deselecciona todas las entradas del Indexador.
/**
\return
**/
int BlWindowListDock::deSeleccionaWindow()
{
    _depura ( "BlWindowListDock::deSeleccionaWindow", 0 );
    try {
        m_listBox->clearSelection();
    } catch ( ... ) {
        _depura ( "BlWindowListDock::deSeleccionaWindow", 2, "Error en la Seleccion" );
        throw - 1;
    } // end try
    _depura ( "END BlWindowListDock::deSeleccionaWindow", 0 );
    return 0;
}


///
/**
\param obj
**/
void BlWindowListDock::sacaWindow ( QObject *obj )
{
    _depura ( "BlWindowListDock::sacaWindow", 0 );
    /// Buscamos la entrada correspondiente dentro del Indexador y la borramos.
    int i = 0;
    while ( i < m_listBox->count() ) {
        BlListWidgetItem * m = ( BlListWidgetItem * ) m_listBox->item ( i );
        if ( m->object() == obj ) {
            _depura ( "Ventana encontrada y vamos a sacarla", 0, m->nombre() );
            m_listBox->takeItem ( i );
            delete m;
            break;
        } // end if
        i++;
    } // end while
    /// Deseleccionamos cualquier elemento del listado para que no se quede marcado si
    /// ninguna otra ventana recoge el foco.
    deSeleccionaWindow();
    _depura ( "END BlWindowListDock::sacaWindow", 0 );
}


///
/**
\param visible
**/
void BlWindowListDock::cambiaVisible ( bool visible )
{
    _depura ( "BlWindowListDock::cambiaVisible", 0 );
    if ( visible == TRUE ) {
        this->show();
    } else {
        this->hide();
    } // end if
    _depura ( "END BlWindowListDock::cambiaVisible", 0 );
}


///
/**
**/
void BlWindowListDock::closeEvent ( QCloseEvent * )
{
    _depura ( "BlWindowListDock::closeEvent", 0 );
    emit ( cambiaEstadoVisible ( FALSE ) );
    _depura ( "END BlWindowListDock::closeEvent", 0 );
}
