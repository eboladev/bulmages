#include <QWidget>
#include <QProcess>
#include <QDockWidget>
#include <QX11EmbedContainer>
#include <QMainWindow>
#include "abrevs.h"
#include "funcaux.h"
#include "trabajadores.h"
#include "empresatpv.h"
#include "tickets.h"



Abrevs::Abrevs ( EmpresaBase *emp, QWidget *parent ) : BLWidget ( emp, parent )
{
    setupUi ( this );

    /// Vamos a probar con un docwindow.
    m_doc2 = new QDockWidget ( "Teclado", g_main );
    m_doc2->setFeatures ( QDockWidget::AllDockWidgetFeatures );
    g_main->addDockWidget ( Qt::TopDockWidgetArea, m_doc2 );
    m_doc2->hide();
/// **** PRUEBAS DE EMBEBIDO

    m_proc = new QProcess();

    /*
        m_proc->start("xvkbd");
        if (!m_proc->waitForStarted())
            return;
        QString winId = "";
        while (winId == "") winId = windowID("xvkbd - Virtual Keyboard");
    */


    /*
            m_proc->start("klavier");
            if (!m_proc->waitForStarted())
                return;
            QString winId = "";
            while (winId == "") winId = windowID("klavier");
    */


    m_proc->start ( "matchbox-keyboard -xid es" );
    if ( !m_proc->waitForStarted() )
        return;
    m_proc->waitForReadyRead();
    QString winId = "";
    winId = m_proc->readAllStandardOutput();


    QX11EmbedContainer *container = new QX11EmbedContainer ( m_doc2 );
    container->embedClient ( winId.toInt() );
    m_doc2->setWidget ( container );
}


Abrevs::~Abrevs()
{
    m_proc->kill();
    delete m_proc;
    delete m_doc2;
}

void Abrevs::on_mui_teclado_clicked()
{

    if ( m_doc2->isVisible() ) {
        m_doc2->hide();
    } else {
        m_doc2->show();
// g_main->topDock()->setHeight(400);
    }// end if
}

void Abrevs::on_mui_usuario_clicked()
{

    /// Vamos a probar con un docwindow.
    /*
        QDockWidget *doc2 = new QDockWidget("Trabajadores", g_main);
        doc2->setFeatures(QDockWidget::AllDockWidgetFeatures);
        g_main->addDockWidget(Qt::TopDockWidgetArea, doc2);
        doc2->show();
    */
/// **** PRUEBAS DE EMBEBIDO

    Trabajadores * trab = new Trabajadores ( empresaBase(), 0 );

//    doc2->setWidget(trab);
    trab->exec();
//    trab->setWindowModality(Qt::WindowModal);
}

void Abrevs::on_mui_aparcar_clicked()
{
    EmpresaTPV * emp = ( EmpresaTPV * ) empresaBase();
    // El nombre del ticket no puede estar vacio.
    if ( emp->valorInput() == "" ) {
        mensajeAviso ( tr ( "Asigne un nombre al ticket antes de aparcarlo." ) );
        return;
    } // end if


    if ( emp->ticketActual() ->listaLineas() ->count() == 0 ) {
        mensajeAviso ( tr ( "El ticket esta vacio. No se puede aparcar." ) );
        return;
    } // end if


    /// Miramos que no haya ningun ticket abierto con el nombre usado
    Ticket *ticket;
    for ( int i = 0; i < emp->listaTickets() ->size(); ++i ) {
        ticket = emp->listaTickets() ->at ( i );
        if ( emp->valorInput() == ticket->DBvalue ( "nomticket" ) ) {
            mensajeAviso ( tr ( "Ya existe un ticket aparcado con el mismo nombre." ) );
            return;
        }// end if
    }// end for

    emp->ticketActual() ->setDBvalue ( "nomticket", emp->valorInput() );
    Ticket *tick = emp->newTicket();
    /// Ponemos al trabajador creado el trabajador del ticket actual.
    tick->setDBvalue ( "idtrabajador", emp->ticketActual() ->DBvalue ( "idtrabajador" ) );
    emp->setTicketActual ( tick );
    emp->listaTickets() ->append ( tick );
    /// Borra el valor del Input.
    emp->pulsaTecla ( Qt::Key_C, "C" );
    tick->pintar();
}

void Abrevs::on_mui_recuperar_clicked()
{

    Tickets * trab = new Tickets ( empresaBase(), 0 );
    trab->exec();
}


void Abrevs::on_mui_cliente_clicked()
{
    EmpresaTPV * emp = ( EmpresaTPV * ) empresaBase();

    if ( emp->valorInput() == "" ) return;
    QString query = "SELECT * FROM cliente WHERE codcliente = '" + emp->valorInput() + "'";
    cursor2 *cur = emp->cargacursor ( query );
    if ( !cur->eof() ) {
        emp->ticketActual() ->setDBvalue ( "idcliente", cur->valor ( "idcliente" ) );
    } else {
        emp->ticketActual() ->setDBvalue ( "idcliente", confpr->valor ( CONF_IDCLIENTE_DEFECTO ) );
    } // end if
    delete cur;
    emp->ticketActual() ->pintar();
    emp->setValorInput ( "" );
    emp->pulsaTecla ( 0, "" );
}
