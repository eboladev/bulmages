/***************************************************************************
 *   Copyright (C) 2009 by Tomeu Borras Riera                              *
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

#ifndef PLUGINBF_ASIENTO_H
#define PLUGINBF_ASIENTO_H

#include "bfbulmafact.h"
#include "blpostgresqlclient.h"
#include "bfcompany.h"
#include "pdefs_pluginbf_asiento.h"
#include "bcasientoview.h"
#include "bcasientointeligenteview.h"
#include "blaction.h"

#include "facturaview.h"
#include "facturapview.h"
#include "cobroview.h"
#include "pagoview.h"
#include "bltoolbutton.h"

extern "C" PLUGINBF_ASIENTO_EXPORT BcAsientoView *g_asiento;
extern "C" PLUGINBF_ASIENTO_EXPORT BcAsientoInteligenteView *g_asientoInteligente;
extern "C" PLUGINBF_ASIENTO_EXPORT int entryPoint ( BfBulmaFact * );
extern "C" PLUGINBF_ASIENTO_EXPORT int SNewBcAsientoView ( BfCompany * );
extern "C" PLUGINBF_ASIENTO_EXPORT int SNewBcAsientoInteligenteView ( BfCompany *);
extern "C" PLUGINBF_ASIENTO_EXPORT int BlAction_actionTriggered(BlAction *);
extern "C" PLUGINBF_ASIENTO_EXPORT int BlSubForm_preparaMenu ( BlSubForm * );
extern "C" PLUGINBF_ASIENTO_EXPORT int BlSubForm_BlSubForm_Post ( BlSubForm * );

extern "C" PLUGINBF_ASIENTO_EXPORT int FacturaView_FacturaView ( FacturaView * );
extern "C" PLUGINBF_ASIENTO_EXPORT int BlToolButton_released(BlToolButton *); 
extern "C" PLUGINBF_ASIENTO_EXPORT int FacturaView_afterSave_Post(FacturaView *);

extern "C" PLUGINBF_ASIENTO_EXPORT int CobroView_CobroView ( CobroView * );
extern "C" PLUGINBF_ASIENTO_EXPORT int CobroView_afterSave_Post(CobroView *);

extern "C" PLUGINBF_ASIENTO_EXPORT int FacturaProveedorView_FacturaProveedorView ( FacturaProveedorView * );
extern "C" PLUGINBF_ASIENTO_EXPORT int FacturaProveedorView_afterSave_Post(FacturaProveedorView *);

extern "C" PLUGINBF_ASIENTO_EXPORT int PagoView_PagoView ( PagoView * );
extern "C" PLUGINBF_ASIENTO_EXPORT int PagoView_afterSave_Post(PagoView *);

#endif

