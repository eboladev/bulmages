/***************************************************************************
 *   Copyright (C) 2006 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
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

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>
#include <QMenu>
#include <QAction>


#include "fixed.h"
#include "empresabase.h"
#include "dbrecord.h"
#include "eqtoolbutton.h"
#include "funcaux.h"

///
/**
\param parent
**/
EQToolButton::EQToolButton(QWidget *parent) : QWidget(parent) {
    _depura("EQToolButton::EQToolButton", 0);
      connect (parent, SIGNAL(pintaMenu(QMenu *)), this, SLOT(pintaMenu(QMenu *)));
      connect (parent, SIGNAL(trataMenu(QAction *)), this, SLOT(trataMenu(QAction *)));
    m_ficha = (Ficha *) parent;
    _depura("END EQToolButton::EQToolButton", 0);
}


///
/**
**/
EQToolButton::~EQToolButton() {
    _depura("EQToolButton::~EQToolButton", 0);
    _depura("END EQToolButton::~EQToolButton", 0);
}


///
/**
\param menu El menu sobre el que pintar la opcion
**/
void EQToolButton::pintaMenu(QMenu *menu) {
    _depura("EQToolButton::pintaMenu", 0);
    QMenu *ajust = menu->addMenu(tr("Informes Personales"));

     /// Buscamos ficheros que tengan el nombre de la tabla
     QDir dir(confpr->valor(CONF_DIR_OPENREPORTS));
     dir.setFilter(QDir::Files | QDir::NoSymLinks);
     dir.setSorting(QDir::Size | QDir::Reversed);
     /// Hacemos un filtrado de busqueda
     QStringList filters;
     filters << "*" + m_ficha->tableName() + "*.rml";
     dir.setNameFilters(filters);


     QFileInfoList list = dir.entryInfoList();
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
	 ajust->addAction(fileInfo.fileName());
     }
    _depura("END EQToolButton::pintaMenu", 0);
}


///
/**
\param menu El menu sobre el que pintar la opcion
**/
void EQToolButton::trataMenu(QAction *action) {
    _depura("EQToolButton::trataMenu", 0);

     /// Buscamos ficheros que tengan el nombre de la tabla
     QDir dir(confpr->valor(CONF_DIR_OPENREPORTS));
     dir.setFilter(QDir::Files | QDir::NoSymLinks);
     dir.setSorting(QDir::Size | QDir::Reversed);
     /// Hacemos un filtrado de busqueda
     QStringList filters;
     filters << "*" + m_ficha->tableName() + "*.rml";
     dir.setNameFilters(filters);


     QFileInfoList list = dir.entryInfoList();
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
	 if (action->text() == fileInfo.fileName()) {
		m_ficha->generaRML(fileInfo.fileName());
		invocaPDF(fileInfo.fileName().left(fileInfo.fileName().size()-4));
	 } // end if
     }
    _depura("END EQToolButton::trataMenu", 0);
}


