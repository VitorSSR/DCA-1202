#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->line_cd_barra_nome->setText("");
    ui->line_cd_barra_preco->setText("");
    ui->line_cd_barra_num_faixas->setText("");
}


void IncluirCD::on_botoes_cd_accepted()
{
    QString nome = ui-> line_cd_barra_nome-> text();
    QString preco = ui-> line_cd_barra_preco-> text();
    QString numfaixas = ui-> line_cd_barra_num_faixas-> text();

    emit signIncluirCD(nome,preco,numfaixas);
}

