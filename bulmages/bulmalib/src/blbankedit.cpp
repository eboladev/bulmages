/***************************************************************************
 *   Copyright (C) 2008 by Tomeu Borras Riera                              *
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

#include "blbankedit.h"


int pesosdc[] = {6,3,7,9,10,5,8,4,2,1};


///  Inicializa el objeto y hace todas las conexiones necesarias.
/**
\param parent
**/
BlBankEdit::BlBankEdit ( QWidget *parent ) : BlWidget ( parent )
{
    _depura ( "BlBankEdit::BlBankEdit", 0 );
    setupUi ( this );
    QObject::connect ( m_cuenta, SIGNAL ( returnPressed() ), this, SLOT ( s_returnPressed() ) );
    QObject::connect ( m_cuenta, SIGNAL ( editingFinished() ), this, SLOT ( s_cuentalostFocus() ) );
    QObject::connect ( m_cuenta, SIGNAL ( editingFinished() ), this, SIGNAL ( editingFinished() ) );
    _depura ( "END BlBankEdit::BlBankEdit", 0 );
}


/// No requiere de acciones especiales en el destructor.
/**
**/
BlBankEdit::~BlBankEdit()
{
    _depura ( "BlBankEdit::~BlBankEdit", 0 );
    _depura ( "END BlBankEdit::~BlBankEdit", 0 );
}


/// Comprueba que los DC son correctos y si no lo son da un mensaje de aviso
void BlBankEdit::checkDC() {
	_depura ( "BlBankEdit::checkDC", 0 );
	QString cad1 = m_entidad->text() + m_oficina->text(); 
	QString cad2 = m_cuenta->text();
	int dc1 = 0;
	int dc2 = 0;

	/// Si no hay cuenta bancaria puesta entonces no hacemos comprobaciones.
	if (cad1.size() + cad2.size() == 0)
		return;


	int resparcial = 0;
	for (int i= 0; i < 8; i++) {
		resparcial += cad1[8-i-1].digitValue() * pesosdc[i];
	} // end for
	dc1 = 11 - (resparcial % 11);
	if (dc1 == 11) dc1 = 0;
	if (dc1 == 10) dc1 = 1;

	int resparcial1 = 0;
	for (int i= 0; i < 10; i++) {
		resparcial1 += cad2[10-i-1].digitValue() * pesosdc[i];
	} // end for
	dc2 = 11 - (resparcial1 % 11);
	if (dc2 == 11) dc2 = 0;
	if (dc2 == 10) dc2 = 1;

	QString dc = QString::number(dc1) + QString::number(dc2);

	/// Si los digitos de control no se corresponden damos un error.
	if (dc != m_dc->text()) {
		mensajeInfo("Cuenta bancaria incorrecta");
		throw -1;
	} // end if
	_depura ( "END BlBankEdit::checkDC", 0 );
}


///
/**
\param val
**/
void BlBankEdit::setText ( QString val )
{
    _depura ( "BlBankEdit::setText", 0 );
    s_cuentalostFocus();
    m_entidad->setText(val.left(4));
    m_oficina->setText(val.left(8).right(4));
    m_dc->setText(val.left(10).right(2));
    m_cuenta->setText ( val.left(20).right(10) );
    _depura ( "END BlBankEdit::setText", 0 );
}


///
/**
\param val
**/
void BlBankEdit::setFieldValue ( QString val )
{
    _depura ( "BlBankEdit::setFieldValue", 0 );
    setText ( val );
    _depura ( "END BlBankEdit::setFieldValue", 0 );
}




///
/**
\return
**/
QString BlBankEdit::text()
{
    _depura ( "BlBankEdit::text", 0 );
    _depura ( "END BlBankEdit::text", 0 );
    s_cuentalostFocus();
    QString val = m_entidad->text() + m_oficina->text() + m_dc->text() + m_cuenta->text();
    checkDC();
    return val;
}


///
/**
\return
**/
QString BlBankEdit::fieldValue()
{
    _depura ( "BlBankEdit::fieldValue", 0 );
    _depura ( "END BlBankEdit::fieldValue", 0 );
    return text();
}


///
/**
**/
void BlBankEdit::s_returnPressed()
{
    _depura ( "BlBankEdit::s_enterPressed", 0 );
    s_cuentalostFocus();
    emit returnPressed();
    _depura ( "END BlBankEdit::s_enterPressed", 0 );
}


///
/**
**/
void BlBankEdit::selectAll()
{
    _depura ( "BlBankEdit::selectAll", 0 );
    m_cuenta->selectAll();
    _depura ( "END BlBankEdit::selectAll", 0 );
}


///
/**
**/
void BlBankEdit::setFocus()
{
    _depura ( "BlBankEdit::setFocus", 0 );
    m_cuenta->setFocus ( Qt::OtherFocusReason );
    _depura ( "END BlBankEdit::setFocus", 0 );
}


///
/**
\param texto
\return
**/
void BlBankEdit::s_cuentatextChanged ( const QString &texto )
{
    _depura ( "BlBankEdit::s_fechatextChanged", 0 );
/*
    if ( texto == "+" )
        s_searchFecha();
    if ( texto == "*" )
        m_cuenta->setText ( QDate::currentDate().toString ( "dd/MM/yyyy" ) );
    m_cuenta->setText ( normalizafecha ( texto ).toString ( "dd/MM/yyyy" ) );
    if ( texto == "" ) {
        m_cuenta->setText ( "" );
        return;
    } // end if
*/
    emit ( valueChanged ( m_entidad->text() + m_oficina->text() + m_dc->text() + m_cuenta->text() ) );
    _depura ( "END BlBankEdit::s_fechatextChanged", 0 );
}



///
/**
**/
void BlBankEdit::s_cuentalostFocus()
{
    _depura ( "BlBankEdit::s_cuentalostFocus", 0 );
    QString fech = m_entidad->text() + m_oficina->text() + m_dc->text() + m_cuenta->text();
    if ( fech != "" )
        s_cuentatextChanged ( fech );
    _depura ( "END BlBankEdit::s_cuentalostFocus", 0 );
}
