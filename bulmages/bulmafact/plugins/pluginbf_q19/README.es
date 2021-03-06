#######
#Plugins
#######
#README.es
#20080501

Nombre: Remesas bancarias

Biblioteca: libpluginbf_q19.so

Descripción: <H1>Remesas Bancarias</H1>
<P>Agrega un botón de generacion de remesas bancarias al listado de facturas. Funciona en conjuncion con el plugin de impresionesmultiples y al seleccionar varias facturas o cobros y darle a este botón genera el archivo q19 para poder pasarlo al banco. El codigo de referencia y devolución los genera como el id de bd con una F añadida al final para las facturas (para no duplicar código si un cobro y una factura tienen el mismo id, luego no sabríamos cuál nos  ha devuelto el banco. ver https://lists.berlios.de/pipermail/bulmages-main/2009-February/000935.html</P>
<P>Bulamfact marca automáticamente  los recibos que se incluyen en una remesa bancaria  como efectivos (desmarca la casilla "previsión de cobro") para facilitar la gestión de cuáles hay que enviar al banco y cuáles estan ya enviados. Es responsabilidad del usuario que el fichero generado llegue al banco y sea procesado o en caso contrario restablecer los cobros como previsiones, modificarlos, y/o lo que corresponda.</P>
<B>Author:</B>Tomeu Borrás (tborras@conetxia.com)<BR>
<HR>

ParmBD: 

ArchivoSQLpatch: 

ArchivoSQLdeins: 

Dependencias: libpluginbf_multiimprimir.so; libpluginbf_banco.so

Incompatibles:

Categorias: Facturacion avanzada; Experimentales; Asociaciones de padres de alumnos;Distribución; Supermercados;Distribución Alimentaria;Servicios Generales;Alquileres;

Orden: 900

Comentarios: 
