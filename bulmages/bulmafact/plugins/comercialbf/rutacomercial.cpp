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

#include <QFile>
#include <QTextStream>

#include "rutacomercial.h"
#include "company.h"
#include "configuracion.h"
#include "plugins.h"


RutaComercial::RutaComercial(company *comp, QWidget *parent) : FichaBf(comp, parent) {
    _depura("RutaComercial::RutaComercial", 0);
    setDBTableName("rutacomercial");
    setDBCampoId("idrutacomercial");
    addDBCampo("idrutacomercial", DBCampo::DBint, DBCampo::DBPrimaryKey, QApplication::translate("RutaComercial", "Identificador"));
    addDBCampo("fecharutacomercial", DBCampo::DBdate, DBCampo::DBNotNull, QApplication::translate("RutaComercial", "Fecha"));
    addDBCampo("idcliente", DBCampo::DBint, DBCampo::DBNotNull, QApplication::translate("RutaComercial", "Familia"));
    addDBCampo("comentariosrutacomercial", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate("RutaComercial", "Comentarios"));
    addDBCampo("horarutacomercial", DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate("RutaComercial", "Hora"));
    addDBCampo("refrutacomercial",  DBCampo::DBvarchar, DBCampo::DBNothing, QApplication::translate("RutaComercial", "Referencia"));
    _depura("END RutaComercial::RutaComercial", 0);
}


RutaComercial::~RutaComercial() {}


void RutaComercial::pintar() {
    _depura("RutaComercial::pintar", 0);
    /// Disparamos los plugins con presupuesto_imprimirPresupuesto.
    int res = g_plugins->lanza("RutaComercial_pintar", this);
    if (res != 0)
        return;
    _depura("funcion no sobrecargada", 2);
    _depura("END RutaComercial::pintar", 0);
}

int RutaComercial::cargar(QString id) {
    _depura("RutaComercial::cargar", 0);
    QString query = "SELECT * FROM rutacomercial WHERE idrutacomercial = " + id;
    cursor2 *cur = empresaBase()->cargacursor(query);
    if (!cur->eof())  {
        DBload(cur);
    }
    delete cur;
    _depura("END RutaComercial::cargar", 0);
    return 0;
}

