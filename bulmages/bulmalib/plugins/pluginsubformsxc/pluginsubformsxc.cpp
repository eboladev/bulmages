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

#include <stdio.h>

#include "pluginsubformsxc.h"
#include "funcaux.h"

#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTextCodec>
#include <QLocale>

int entryPoint(QApplication *bges) {
    _depura("Punto de Entrada del plugin de SubformSXC\n", 0);
        /// Cargamos el sistema de traducciones una vez pasado por las configuraciones generales
        QTranslator *traductor = new QTranslator(0);
        if (confpr->valor(CONF_TRADUCCION) == "locales") {
            traductor->load(QString("pluginsubformsxc_") + QLocale::system().name(),
                            confpr->valor(CONF_DIR_TRADUCCION).toAscii().constData());
        } else {
            QString archivo = "pluginsubformsxc_" + confpr->valor(CONF_TRADUCCION);
           traductor->load(archivo, confpr->valor(CONF_DIR_TRADUCCION).toAscii().constData());
        } // end if
        theApp->installTranslator(traductor);
    _depura("END Punto de Entrada del plugin de SubformSXC\n", 0);
    return 0;
}


myplugsubformsxc::myplugsubformsxc(SubForm3 *parent) : QObject(parent) {
}


myplugsubformsxc::~myplugsubformsxc(){
}

void myplugsubformsxc::s_pintaMenu(QMenu *menu) {
    menu->addSeparator();
    QAction *ajustac = menu->addAction(tr("Exportar a Hoja de Calculo"));
}

void myplugsubformsxc::s_trataMenu(QAction *action) {
    _depura("myplugsubformsxc::s_trataMenu", 0);
    if (action->text() == tr("Exportar a Hoja de Calculo")) {
	sacaSXC();
    } // end if
}

void myplugsubformsxc::sacaSXC() {
    _depura("myplugsubformsxc::sacaSXC", 0);

    QString archivod = confpr->valor ( CONF_DIR_USER ) + "listadosxc.perl";
    SubForm3 * subf = (SubForm3 *) parent();


	QString fitxersortidatxt = "";

	fitxersortidatxt += "#!/usr/bin/perl\n";
	fitxersortidatxt += "# calc-example5 - Set Column sizes\n";
	fitxersortidatxt += "\n";
	fitxersortidatxt += "use ooolib;\n";
	fitxersortidatxt += "use utf8;\n";
	fitxersortidatxt += "\n";
	fitxersortidatxt += "# Set variables\n";
	fitxersortidatxt += "$doc = new ooolib(\"sxc\");\n";
	fitxersortidatxt += "$doc->oooSet(\"builddir\", \".\");\n";
	fitxersortidatxt += "$doc->oooSet(\"title\", \"Informe de Proveedores\");\n";
	fitxersortidatxt += "$doc->oooSet(\"subject\", \"Proveedores\");\n";
	fitxersortidatxt += "$doc->oooSet(\"comments\", \"Informe de Proveedores\");\n";
	fitxersortidatxt += "$doc->oooSet(\"author\", \"ooolib Example\");\n";
	fitxersortidatxt += "$doc->oooSet(\"meta1-name\", \"Programmer\");\n";
	fitxersortidatxt += "$doc->oooSet(\"meta1-value\", \"Tomeu Borrás\");\n";
	fitxersortidatxt += "\n";

	fitxersortidatxt += "$doc->oooSet(\"cell-auto\", \"1,0\");\n";
	fitxersortidatxt += "$doc->oooSet(\"bold\", \"on\");\n";
	fitxersortidatxt += "$doc->oooSet(\"text-size\", \"18\");\n";
	fitxersortidatxt += "$doc->oooSet(\"cell-loc\", 4, 1);\n";
	fitxersortidatxt += "$doc->oooData(\"cell-text\", \"INFORME ANUAL DE COMPRAS POR PROVEEDOR\");\n";
	fitxersortidatxt += "$doc->oooSet(\"text-size\", \"10\");\n";
	fitxersortidatxt += "$doc->oooSet(\"bold\", \"off\");\n";


	int y=1;
        int x = 1;
    /// Sacamos las cabeceras
    for (int h = 0; h < subf->mui_listcolumnas->rowCount(); ++h) {
        if (subf->mui_listcolumnas->item(h, 0)->checkState() == Qt::Checked) {

			fitxersortidatxt += "# Fila "+ QString::number ( y ) +"\n";
			fitxersortidatxt += "$doc->oooSet(\"bold\", \"on\");\n";
			fitxersortidatxt += "$doc->oooSet(\"cell-loc\", "+ QString::number ( x++ ) +", "+ QString::number ( y ) +");\n";
			fitxersortidatxt += "$doc->oooData(\"cell-text\", \"" +(subf->mui_listcolumnas->item(h, 2)->text()) +"\");\n";

			fitxersortidatxt += "$doc->oooSet(\"bold\", \"off\");\n";
			fitxersortidatxt += "\n";

        } // end if
    } // end for


    y += 2;

    /// Sacamos el contenido
    for (int i = 0; i < subf->mui_list->rowCount(); ++i) {

        int x = 1;
        for (int j = 0; j < subf->mui_listcolumnas->rowCount(); ++j) {

            if (subf->mui_listcolumnas->item(j, 0)->checkState() == Qt::Checked) {


			fitxersortidatxt += "# Fila "+ QString::number ( y ) +"\n";
			fitxersortidatxt += "$doc->oooSet(\"bold\", \"on\");\n";
			fitxersortidatxt += "$doc->oooSet(\"cell-loc\", "+ QString::number ( x++ ) +", "+ QString::number ( y ) +");\n";
			fitxersortidatxt += "$doc->oooData(\"cell-text\", \"" +(subf->mui_list->item(i, j)->text()) +"\");\n";

			fitxersortidatxt += "$doc->oooSet(\"bold\", \"off\");\n";
			fitxersortidatxt += "\n";

            } // end if
        } // end forXMLProtect(subf->mui_list->item(i, j)->text())
        y++;
    } // end for


	fitxersortidatxt += "my($filename) = $doc->oooGenerate(\"listadosxc.sxc\");\n";
	fitxersortidatxt += "\n";
	fitxersortidatxt += "exit;\n";


	QString cadena ="rm "+confpr->valor ( CONF_DIR_USER ) + "listadosxc.sxc";
	system ( cadena.toAscii() );
	cadena ="rm "+ archivod;
	system ( cadena.toAscii() );

	QFile file ( archivod );
	if ( file.open ( QIODevice::WriteOnly ) )  {
		QTextStream stream ( &file );
		stream.setCodec("UTF-8");
		stream << fitxersortidatxt;
		file.close();
	} // end if

	cadena= " cd "+confpr->valor ( CONF_DIR_USER ) +"; perl "+archivod;
	system ( cadena.toAscii() );
	cadena = "kspread "+confpr->valor ( CONF_DIR_USER ) + "listadosxc.sxc &";
	system ( cadena.toAscii() );

    _depura("END myplugsubformsxc::sacaSXC", 0);
}


int SubForm3_SubForm3_Post(SubForm3 *sub) {
   myplugsubformsxc *subformsxc = new myplugsubformsxc(sub);
   sub->QObject::connect(sub, SIGNAL(pintaMenu(QMenu *)), subformsxc, SLOT(s_pintaMenu(QMenu *)));
   sub->QObject::connect(sub, SIGNAL(trataMenu(QAction *)), subformsxc, SLOT(s_trataMenu(QAction *)));
   return 0;
}
