#include <string>
#include <QMessageBox>
#include "whatsprog_novaconversa.h"
#include "ui_whatsprog_novaconversa.h"
#include "whatsprog_dados_cliente.h"

extern WhatsProgDadosCliente DC;

WhatsProgNovaConversa::WhatsProgNovaConversa(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WhatsProgNovaConversa)
{
  ui->setupUi(this);
}

WhatsProgNovaConversa::~WhatsProgNovaConversa()
{
  delete ui;
}

void WhatsProgNovaConversa::on_buttonBox_accepted()
{
  // Falta fazer:
  // Recupera e testa nome da nova conversa
  // Insere nova conversa na base de dados
  // Faz a conversa recem inserida (a ultima) ser a conversa ativa
  // Sinaliza que houve alteracao na janelas: Conversas e Mensagens

  QString NomeConversa = ui->lineEditConversa->text();

  if(!NomeConversa.isEmpty()){
      DC.insertConversa(NomeConversa.toStdString());
  }

  emit signAtualizaConversas();
  emit signAtualizaMensagens();
}
