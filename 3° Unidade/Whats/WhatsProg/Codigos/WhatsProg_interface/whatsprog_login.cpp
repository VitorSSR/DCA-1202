#include "whatsprog_login.h"
#include "ui_whatsprog_login.h"

WhatsProgLogin::WhatsProgLogin(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WhatsProgLogin),
  novoUsuario(false)
{
  ui->setupUi(this);

  ui->lineEditSenhaUsuario->setEchoMode( QLineEdit::Password );
}

WhatsProgLogin::~WhatsProgLogin()
{
  delete ui;
}

void WhatsProgLogin::slotLogin(bool NovoUsuario)
{
  novoUsuario = NovoUsuario;
  if (novoUsuario) setWindowTitle("Usuario - Criar");
  else setWindowTitle("Usuario - Conectar");
  ui->lineEditIpServidor->clear();
  ui->lineEditNomeUsuario->clear();
  ui->lineEditSenhaUsuario->clear();
  show();
}

void WhatsProgLogin::on_buttonBox_accepted()
{
  // Falta fazer:
  QString IP = ui->lineEditIpServidor->text();
  QString login = ui->lineEditNomeUsuario->text();
  QString senha = ui->lineEditSenhaUsuario->text();

  bool novoUsuario;
  if(novoUsuario) emit signConectar(IP, login, senha, novoUsuario);
  else emit signConectar(IP, login, senha, novoUsuario=false);


  // Envia sinal com os dados recuperados dos lineEdit e limpa os campos dos lineEdit

  ui->lineEditIpServidor->clear();
  ui->lineEditNomeUsuario->clear();
  ui->lineEditSenhaUsuario->clear();

}
