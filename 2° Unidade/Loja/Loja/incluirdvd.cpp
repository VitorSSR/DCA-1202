#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}


void IncluirDVD::clear()
{
    ui->line_dvd_barra_nome->setText("");
    ui->line_dvd_barra_preco->setText("");
    ui->line_dvd_barra_duracao->setText("");
}


void IncluirDVD::on_botoes_dvd_accepted()
{
    QString nome = ui-> line_dvd_barra_nome-> text();
    QString preco = ui-> line_dvd_barra_preco-> text();
    QString duracao = ui-> line_dvd_barra_duracao-> text();

    emit signIncluirDVD(nome,preco,duracao);
}

