/***************************************************************************
 *                                                                         *
 *   BulmaTPV remote client for Nintendo DS console.                       *
 *   -----------------------------------------------                       *
 *                                                                         *
 *   Copyright (C) 2010 by Fco. Javier M. C.                               *
 *   comercial@todo-redes.com                                              *
 *   http://www.todo-redes.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#ifndef BNDSARTICLE_H
#define BNDSARTICLE_H


#include <nds.h>
#include <stdio.h>
#include <string>

using namespace std;


class BndsArticle
{

    string m_idArticle;
    string m_nomArticle;
    string m_pvpArticle;

public:
    BndsArticle();
    ~BndsArticle();
    void setIdArticle(string id);
    void setNomArticle(string nombre);
    virtual void setPvpArticle(string pvp);
    string idArticle();
    string nomArticle();
    float pvpArticle();

};

#endif

