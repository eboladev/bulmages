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

#include "listltarifaview.h"
#include "funcaux.h"


ListLTarifaView::ListLTarifaView(QWidget *parent) : SubForm2Bf(parent) {
    _depura("ListLTarifaView::ListLTarifaView", 0);
    setDBTableName("ltarifa");
    setDBCampoId("idltarifa");
    addSHeader("nomtarifa", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Nombre tarifa"));
    addSHeader("nomalmacen", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Nombre almacen"));
    addSHeader("pvpltarifa", DBCampo::DBnumeric, DBCampo::DBRequired, SHeader::DBNone, tr("Precio de venta"));
    addSHeader("idarticulo", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID articulo"));
    addSHeader("idalmacen", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID almacen"));
    addSHeader("idtarifa", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID tarifa"));
    addSHeader("idltarifa", DBCampo::DBint, DBCampo::DBPrimaryKey, SHeader::DBNoView, tr("Nº de linea"));
    addSHeader("codigocompletoarticulo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoView, tr("Codigo completo del articulo"));
    addSHeader("nomarticulo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoView, tr("Nombre del articulo"));
    setinsercion(FALSE);
    _depura("END ListLTarifaView::ListLTarifaView", 0);
}


ListLTarifaView1::ListLTarifaView1(QWidget *parent) : SubForm2Bf(parent) {
    _depura("ListLTarifaView1::ListLTarifaView1", 0);
    setDBTableName("ltarifa");
    setDBCampoId("idltarifa");
    addSHeader("nomalmacen", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite , tr("Nombre almacen"));
    addSHeader("codigocompletoarticulo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr("Codigo completo del articulo"));
    addSHeader("nomarticulo", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite , tr("Nombre articulo"));
    addSHeader("pvpltarifa", DBCampo::DBnumeric, DBCampo::DBRequired, SHeader::DBNone, tr("Precio de venta"));
    addSHeader("idarticulo", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID articulo"));
    addSHeader("idalmacen", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID almacen"));
    addSHeader("idtarifa", DBCampo::DBint, DBCampo::DBNotNull, SHeader::DBNoView, tr("ID tarifa"));
    addSHeader("idltarifa", DBCampo::DBint, DBCampo::DBPrimaryKey, SHeader::DBNoView, tr("Nº de linea"));
    addSHeader("nomtarifa", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoView, tr("Nombre de la tarifa"));
    setinsercion(FALSE);
    _depura("ListLTarifaView1::ListLTarifaView1", 0);
}
