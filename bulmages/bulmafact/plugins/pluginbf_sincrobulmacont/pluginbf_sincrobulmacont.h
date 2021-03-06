/***************************************************************************
 *   Copyright (C) 2010 by Fco. Javier M. C.                               *
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

#ifndef PLUGINBF_SINCROBULMACONT_H
#define PLUGINBF_SINCROBULMACONT_H

#include "bfbulmafact.h"
#include "bcbulmacont.h"
#include "familiasview.h"
#include "fpagoview.h"
#include "bancoview.h"
#include "clienteview.h"
#include "provedit.h"
#include "pdefs_pluginbf_sincrobulmacont.h"


extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int entryPoint ( BfBulmaFact * );

/// Familias
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FamiliasView_FamiliasView ( FamiliasView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FamiliasView_Guardar_Pre ( FamiliasView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FamiliasView_Guardar_Post ( FamiliasView * );

/// Formas de pago
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FPagoView_FPagoView ( FPagoView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FPagoView_Guardar_Pre ( FPagoView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int FPagoView_Guardar_Post ( FPagoView * );


/// Bancos
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int BancoView_BancoView ( BancoView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int BancoView_Guardar_Pre ( BancoView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int BancoView_Guardar_Post ( BancoView * );


/// Proveedores
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ProveedorView_ProveedorView_Post ( ProveedorView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ProveedorView_cargarPost_Post ( ProveedorView *);
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ProveedorView_Guardar_Pre ( ProveedorView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ProveedorView_Guardar_Post ( ProveedorView * );


/// Clientes
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ClienteView_ClienteView_Post ( ClienteView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ClienteView_cargarPost_Post ( ClienteView *);
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ClienteView_Guardar_Pre ( ClienteView * );
extern "C" PLUGINBF_SINCROBULMACONT_EXPORT int ClienteView_Guardar_Post ( ClienteView * );


#endif

