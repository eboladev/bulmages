/***************************************************************************
 *   Copyright (C) 2006 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
 *									   *
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

#include "efactura.h"
#include "funcaux.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QString>

/// Constructor de la clase EFactura (el form)
/// Pasamos como parametro la empresa para poder usar metodos de BD para
/// guardar los datos de configuracion

EFactura::EFactura(company *emp, QWidget *parent) : FichaBf(emp, parent) {
	
	_depura("EFactura::EFactura", 2);
	
	QString query;
	
	setupUi(this);  // Para que el form se inicialice bien
	
// 	query = "SELECT valor FROM configuracion WHERE nombre = 'eFactura_server'";
// 	cursor2 *cur1 = empresaBase()->cargacursor(query);
// 	mui_URLServidorTiempo->setText(cur1->valor("valor"));
// 	delete cur1;
// 	
// 	query = "SELECT valor FROM configuracion WHERE nombre = 'eFactura_certificado'";
// 	cursor2 *cur2 = empresaBase()->cargacursor(query);
// 	mui_ficheroECertificado->setText(cur2->valor("valor"));
// 	delete cur2;
// 	
// 	query = "SELECT valor FROM configuracion WHERE nombre = 'eFactura_server_valida'";
// 	cursor2 *cur3 = empresaBase()->cargacursor(query);
// 	mui_URLServidorValidaCert->setText(cur3->valor("valor"));
// 	delete cur3;
	
	_depura("END EFactura::EFactura", 2);
}

/// Destructor

EFactura::~EFactura() {}

/// Funcionalidad del boton guardar

void EFactura::on_mui_guardar_clicked() {
	
	_depura("EFactura::on_mui_guardar_clicked", 0);
	
	QString query;
	
	if (mui_URLServidorTiempo->isModified()) {
		query = "DELETE FROM configuracion WHERE nombre = 'eFactura_server'";
		empresaBase()->ejecuta(query);
		
		query = "INSERT INTO configuracion (nombre, valor) VALUES ('eFactura_server', '";
		query += mui_URLServidorTiempo->text();
		query += "')";
		empresaBase()->ejecuta(query);
	}
	
	/// Como el setText() pone siempre a false el valor de retorno de isModified()
	/// hay que hacer siempre el update del campo que indica la ruta del fichero
	/// de certificado digital
	
	query = "DELETE FROM configuracion WHERE nombre = 'eFactura_certificado'";
	empresaBase()->ejecuta(query);
	
	query = "INSERT INTO configuracion (nombre, valor) VALUES ('eFactura_certificado', '";
	query += mui_ficheroECertificado->text();
	query += "')";
	empresaBase()->ejecuta(query);

	_depura("END EFactura::on_mui_guardar_clicked", 0);
}

/// Funcionalidad del boton Examinar en el apartado del certificado

void EFactura::on_mui_examinaECertificado_clicked() {
	_depura("EFactura::on_mui_examinar_clicked", 0);
	
	QString s = QFileDialog::getOpenFileName(
			this,
			"Escoja un fichero por favor",
			"/home",
			"Todos los archivos (*)"
			);

	/// Si se le da a cancelar, s devuelve NULL y se queda el campo de texto vacio
	
	if (s != "")
		mui_ficheroECertificado->setText(s);
	
	_depura("END EFactura::on_mui_examinar_clicked", 0);
}

/// Funcionalidad del boton cancelar

void EFactura::on_mui_cancelar_clicked() {
	_depura("EFactura::on_mui_cancelar_clicked", 0);
	
// 	QString query = "SELECT * FROM configuracion";
// 	cursor2 *cur = empresaBase()->cargacursor(query);
// 	
// 	while(!cur->eof()) {
// 		_depura(cur->valor("nombre"), 0);
// 		cur->siguienteregistro();
// 	} // end while
// 	
// 	delete cur;
// 	
// 	query = "UPDATE configuracion SET nombre='nombre' WHRE nombre='elnombre'";
// 	empresaBase()->begin();
// 	empresaBase()->ejecuta(query);
// 	empresaBase()->rollback();
	_depura("END EFactura::on_mui_cancelar_clicked", 0);
}