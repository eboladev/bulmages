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

#include "pluginticket.h"
#include "funcaux.h"
#include "facturaview.h"
#include "presupuestoview.h"
#include "ticketqtoolbutton.h"


int entryPoint(bulmafact *bges) {
    _depura("Estoy dentro del plugin de envio de e-mail", 0);
    return 0;
}




/*
int PresupuestoView_PresupuestoView(PresupuestoView *l) {
       _depura("PresupuestoView_PresupuestoView", 0);
       TicketQToolButton *mui_exporta_efactura2 = new TicketQToolButton(l, NULL, NULL,  NULL, l->mui_plugbotones);
       QHBoxLayout *m_hboxLayout1 = new QHBoxLayout(l->mui_plugbotones);
       m_hboxLayout1->setSpacing(5);
       m_hboxLayout1->setMargin(5);
       m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       m_hboxLayout1->addWidget(mui_exporta_efactura2);
       _depura("END PresupuestoView_PresupuestoView", 0);
       return 0;
}

int PedidoClienteView_PedidoClienteView(PedidoClienteView *l) {
       _depura("PedidoClienteView_PedidoClienteView", 0);
       TicketQToolButton *mui_exporta_efactura2 = new TicketQToolButton(NULL, l, NULL, NULL, l->mui_plugbotones);
       QHBoxLayout *m_hboxLayout1 = new QHBoxLayout(l->mui_plugbotones);
       m_hboxLayout1->setSpacing(5);
       m_hboxLayout1->setMargin(5);
       m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       m_hboxLayout1->addWidget(mui_exporta_efactura2);
       _depura("END PedidoClienteView_PedidoClienteView", 0);
       return 0;
}
*/
int AlbaranClienteView_AlbaranClienteView(AlbaranClienteView *l) {
       _depura("AlbaranClienteView_AlbaranClienteView", 0);
//================================
       TicketQToolButton *mui_exporta_efactura2 = new TicketQToolButton(NULL, NULL, l, NULL, l->mui_plugbotones);

       QHBoxLayout *m_hboxLayout1 = l->mui_plugbotones->findChild<QHBoxLayout *>("hboxLayout1");
       if (!m_hboxLayout1) {
                m_hboxLayout1 = new QHBoxLayout(l->mui_plugbotones);
                m_hboxLayout1->setSpacing(5);
                m_hboxLayout1->setMargin(5);
                m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       } // end if
       m_hboxLayout1->addWidget(mui_exporta_efactura2);
//================================
       _depura("END AlbaranClienteView_AlbaranClienteView", 0);
       return 0;
}

int FacturaView_FacturaView(FacturaView *l) {
       _depura("FacturaView_FacturaView", 0);
//================================
       TicketQToolButton *mui_exporta_efactura2 = new TicketQToolButton(NULL, NULL, NULL, l, l->mui_plugbotones);

       QHBoxLayout *m_hboxLayout1 = l->mui_plugbotones->findChild<QHBoxLayout *>("hboxLayout1");
       if (!m_hboxLayout1) {
                m_hboxLayout1 = new QHBoxLayout(l->mui_plugbotones);
                m_hboxLayout1->setSpacing(5);
                m_hboxLayout1->setMargin(5);
                m_hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
       } // end if
       m_hboxLayout1->addWidget(mui_exporta_efactura2);
//================================
       _depura("END FacturaView_FacturaView", 0);
       return 0;
}