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

#ifndef PLUGINBL_IMPORTCSV_H
#define PLUGINBL_IMPORTCSV_H

#include "blfunctions.h"
#include "blpostgresqlclient.h"
#include "bccompany.h"
#include "bfcompany.h"
#include "blmainwindow.h"
#include "pdefs_pluginbl_importcsv.h"


extern "C" PLUGINBL_IMPORTCSV_EXPORT int entryPoint ( BlMainWindow * );
extern "C" PLUGINBL_IMPORTCSV_EXPORT int BfCompany_createMainWindows_Post ( BfCompany * );
extern "C" PLUGINBL_IMPORTCSV_EXPORT int BcCompany_createMainWindows_Post ( BcCompany * );


#endif
