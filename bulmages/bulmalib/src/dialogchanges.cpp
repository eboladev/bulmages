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

#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QComboBox>

#include "dialogchanges.h"
#include "funcaux.h"


dialogChanges::dialogChanges(QObject *ob) {
    _depura("dialogChanges::dialogChanges", 0);
    m_obje = ob;
    _depura("END dialogChanges::dialogChanges", 0);
}


dialogChanges::~dialogChanges() {}


void dialogChanges::dialogChanges_cargaInicial() {
    _depura("dialogChanges::dialogChanges_cargaInicial", 0);
    m_maxQText = 0;
    m_maxQLine = 0;
    m_maxQTable = 0;
    m_maxQComboBox = 0;

    QListIterator<QObject *> it_excluidos (m_listaExcluidos);

    /// TODO: 8/6/07 En pruebas.
    QList<QComboBox *> l4 = m_obje->findChildren<QComboBox *>();
    QListIterator<QComboBox *> it4 (l4);
    while (it4.hasNext()) {
        QComboBox *item = it4.next();
        if (item->objectName() != "") {

            /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
            it_excluidos.toFront();
            while (it_excluidos.hasNext()) {
                /// Comparamos
                if (it_excluidos.next() == (QObject *) item) {
                    _depura("Se ha encontrado objeto a excluir", 0);
                } else {
                    m_listaQComboBox[m_maxQComboBox++] = item;
                } // end if
            } // end while

        } // end if
    } // end while
    /// ---------------


    QList<QTextEdit *> l1 = m_obje->findChildren<QTextEdit *>();
    QListIterator<QTextEdit *> it1 (l1);
    while (it1.hasNext()) {
        QTextEdit *item = it1.next();
        if (item->objectName() != "") {

            /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
            it_excluidos.toFront();
            while (it_excluidos.hasNext()) {
                /// Comparamos
                if (it_excluidos.next() == (QObject *) item) {
                    _depura("Se ha encontrado objeto a excluir", 0);
                } else {
                    m_listaQText[m_maxQText++] = item;
                } // end if
            } // end while

        } // end if
    } // end while

    QList<QLineEdit *> l2 = m_obje->findChildren<QLineEdit *>();
    QListIterator<QLineEdit *> it2 (l2);
    while (it2.hasNext()) {
        QLineEdit *item = it2.next();
        if (item->objectName() != "") {

            /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
            it_excluidos.toFront();
            while (it_excluidos.hasNext()) {
                /// Comparamos
                if (it_excluidos.next() == (QObject *) item) {
                    _depura("Se ha encontrado objeto a excluir", 0);
                } else {
                    m_listaQLine[m_maxQLine++] = item;
                } // end if
            } // end while

        } // end if
    } // end while

    QList<QTableWidget *> l3 = m_obje->findChildren<QTableWidget *>();
    QListIterator<QTableWidget *> it3(l3);
    while (it3.hasNext()) {
        QTableWidget *item = it3.next();
        if (item->objectName() != "") {

            /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
            it_excluidos.toFront();
            while (it_excluidos.hasNext()) {
                /// Comparamos
                if (it_excluidos.next() == (QObject *) item) {
                    _depura("Se ha encontrado objeto a excluir", 0);
                } else {
                    m_listaQTable[m_maxQTable++] = item;
                } // end if
            } // end while

        } // end if
    } // end while

    valorinicial = calculateValues();
    _depura("END dialogChanges::dialogChanges_cargaInicial", 0, valorinicial.toAscii());
}


bool dialogChanges::dialogChanges_hayCambios() {
    _depura("dialogChanges::dialogChanges_hayCambios", 0);
    QString valorfinal = calculateValues();
    _depura(valorfinal.toAscii(), 0);
    _depura(valorinicial.toAscii(), 0);
    _depura("END dialogChanges::dialogChanges_hayCambios", 0);
    return !(valorinicial == calculateValues());
}


QString dialogChanges::calculateValues() {
    _depura("dialogChanges::calculateValues", 0);
    QString values = retrieveValues("QTableWidget");
    values += retrieveValues("QLineEdit");
    values += retrieveValues("QTextEdit");
    values += retrieveValues("QComboBox");
    _depura("END dialogChanges::calculateValues", 0);
    return values;
}


void dialogChanges::dialogChanges_setQObjectExcluido(QObject *objetoexcluido) {
    _depura("dialogChanges::dialogChanges_setQObjectExcluido", 0);
    m_listaExcluidos.append(objetoexcluido);
    _depura("END dialogChanges::dialogChanges_setQObjectExcluido", 0);
}


QString dialogChanges::retrieveValues(QString qsWidget) {
    _depura("dialogChanges::retrieveValues", 0);
    QString values = "";
    QListIterator<QObject *> it_excluidos (m_listaExcluidos);


    /// TODO: 8/6/07 En pruebas.
    if (qsWidget == "QComboBox") {
        for (int i = 0; i < m_maxQComboBox; i++) {
            if (m_listaQComboBox[i] != NULL) {
                if (((QComboBox*)m_listaQComboBox[i])->objectName() != "") {

                    /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
                    it_excluidos.toFront();
                    while (it_excluidos.hasNext()) {
                        /// Comparamos
                        if (it_excluidos.next() == m_listaQComboBox[i]) {
                            _depura("Se ha encontrado objeto a excluir", 0);
                        } else {
                            values += ((QComboBox*)m_listaQComboBox[i])->currentIndex();
                        } // end if
                    } // end while

                } // end if
            } // end if
        } // end for
    } // end if
    /// --------------------



    if (qsWidget == "QLineEdit") {
        for (int i = 0; i < m_maxQLine; i++) {
            if (m_listaQLine[i] != NULL) {
                if (((QLineEdit*)m_listaQLine[i])->objectName() != "") {

                    /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
                    it_excluidos.toFront();
                    while (it_excluidos.hasNext()) {
                        /// Comparamos
                        if (it_excluidos.next() == m_listaQLine[i]) {
                            _depura("Se ha encontrado objeto a excluir", 0);
                        } else {
                            values += ((QLineEdit*)m_listaQLine[i])->text();
                        } // end if
                    } // end while

                } // end if
            } // end if
        } // end for
    } // end if
    if (qsWidget == "QTextEdit") {
        for (int i = 0; i < m_maxQText; i++) {
            if (m_listaQText[i] != NULL) {
                if (((QTextEdit*)m_listaQText[i])->objectName() != "")

                    /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
                    it_excluidos.toFront();
                    while (it_excluidos.hasNext()) {
                        /// Comparamos
                        if (it_excluidos.next() == m_listaQText[i]) {
                            _depura("Se ha encontrado objeto a excluir", 0);
                        } else {
                            values += ((QTextEdit*)m_listaQText[i])->toPlainText();
                        } // end if
                    } // end while

            } // end if
        } // end for
    } // end if
    if (qsWidget == "QTableWidget") {
        for (int i = 0; i < m_maxQTable; i++) {
            if (m_listaQTable[i] != NULL) {
                for (int k = 0; k < ((QTableWidget*)m_listaQTable[i])->rowCount(); k++) {
                    for (int l = 0; l < ((QTableWidget*)m_listaQTable[i])->columnCount(); l++) {

                        /// Itera por los QObjects que estan excluidos de comprobacion de cambios.
                        it_excluidos.toFront();
                        while (it_excluidos.hasNext()) {
                            /// Comparamos
                            if (it_excluidos.next() == m_listaQTable[i]) {
                                _depura("Se ha encontrado objeto a excluir", 0);
                            } else {
                                values += (((QTableWidget*)m_listaQTable[i]))->item(k, l)->text();
                            } // end if
                        } // end while

                    } // end for
                } // end for
            } // end if
        } // end for
    } // end if

    _depura("END dialogChanges::retrieveValues", 0);
    return values;
}
