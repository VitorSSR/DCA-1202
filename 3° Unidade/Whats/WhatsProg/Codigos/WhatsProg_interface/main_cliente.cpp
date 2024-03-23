#include <QApplication>
#include "whatsprog_main.h"

#include "mysocket.h"
#include "whatsprog_dados_cliente.h"

/// A variavel global que contem todas as msgs de todas as conversas
/// Falta fazer

/// A variavel global do socket do cliente, a ser utilizado por todas as threads
WhatsProgDadosCliente DC;
tcp_mysocket sock;


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  WhatsProgMain w;

  w.show();
  int result = a.exec();

  return result;
}
