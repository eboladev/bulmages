/***************************************************************************
 *   Copyright (C) 2007 by Tomeu Borras Riera                              *
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

#ifndef REGIVAQTOOLBUTTON_H
#define REGIVAQTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QString>
#include "empresa.h"
#include "funcaux.h"
#include <QtXml/QDomDocument>
#include <QMap>
#include <QString>


#include "asiento1view.h"



class RegIVAQToolButton : public QToolButton {
	Q_OBJECT

private:
	Empresa *m_companyact;
	Asiento1View *m_asiento1View;	

public:
	RegIVAQToolButton(Asiento1View * , QWidget *parent = NULL);
	~RegIVAQToolButton();
	void setBoton();
public slots:
	virtual void click();

};

#endif