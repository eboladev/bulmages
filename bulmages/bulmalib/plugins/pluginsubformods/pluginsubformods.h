/***************************************************************************
 *   Copyright (C) 2007 by Fco. Javier M. C.                               *
 *   fcojavmc@todo-redes.com                                               *
 *                                                                         *
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

#ifdef Q_WS_WIN
# define MY_EXPORT __declspec(dllexport)
#else
# define MY_EXPORT
#endif

#include <QMenu>
#include <QApplication>

#include "postgresiface2.h"
#include "blwidget.h"
#include "subform3.h"


extern "C" MY_EXPORT int entryPoint(QApplication *);
extern "C" MY_EXPORT int SubForm3_SubForm3_Post(SubForm3 *);

class myplugsubformods : public QObject {
    Q_OBJECT

public:
    myplugsubformods(SubForm3 *);
    ~myplugsubformods();
    void sacaods();

public slots:
    virtual void s_pintaMenu(QMenu *);
    virtual void s_trataMenu(QAction *);
};
