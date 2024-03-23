#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::clear()
{
    ui->line_livros_barra_nome->setText("");
    ui->line_livros_barra_preco->setText("");
    ui->line_livros_barra_autor->setText("");
}


void IncluirLivro::on_botoes_livro_accepted()
{
    QString nome = ui-> line_livros_barra_nome-> text();
    QString preco = ui-> line_livros_barra_preco-> text();
    QString autor = ui-> line_livros_barra_autor-> text();

    emit signIncluirLivro(nome,preco,autor);
}
