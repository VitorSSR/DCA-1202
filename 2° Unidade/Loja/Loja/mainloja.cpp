#include "mainloja.h"
#include "./ui_mainloja.h"

#include "loja.h"
#include "loja.cpp"

#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <string>



MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)

    , X()
    , inclLivro(new IncluirLivro(this))
    , inclCD(new IncluirCD(this))
    , inclDVD(new IncluirDVD(this))
    , total_itens(new QLabel("0",this))

{
    ui->setupUi(this);

    connect(inclLivro,SIGNAL(signIncluirLivro(QString,QString,QString)),this,SLOT(slotIncluirLivro(QString,QString,QString)));
    connect(inclCD,SIGNAL(signIncluirCD(QString,QString,QString)),this,SLOT(slotIncluirCD(QString,QString,QString)));
    connect(inclDVD,SIGNAL(signIncluirDVD(QString,QString,QString)),this,SLOT(slotIncluirDVD(QString,QString,QString)));

    //Cor dos titulos das listas
    ui->LIVROS->setStyleSheet("background-color: lightgray;");
    ui->CDS->setStyleSheet("background-color: lightgray;");
    ui->DVDS->setStyleSheet("background-color: lightgray;");


    //Cor do cabeçalho das listas
    ui->LIVROS_TABLE->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");
    ui->CDS_TABLE->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");
    ui->DVDS_TABLE->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");


    //Ajuste da Table dos Livros
    ui->LIVROS_TABLE->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->LIVROS_TABLE->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->LIVROS_TABLE->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    //Ajuste da Table dos CDS
    ui->CDS_TABLE->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->CDS_TABLE->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->CDS_TABLE->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    //Ajuste da Table dos DVDS
    ui->DVDS_TABLE->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->DVDS_TABLE->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->DVDS_TABLE->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);


    //Fixando o texto dos cabeçalhos
    ui->LIVROS_TABLE->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "AUTOR");
    ui->CDS_TABLE->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "NÚMERO DE FAIXAS");
    ui->DVDS_TABLE->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "DURAÇÃO");


    statusBar()->insertWidget(0,new QLabel("Total de Itens: "));
    statusBar()->addWidget(total_itens);
}

MainLoja::~MainLoja()
{
    delete ui;
}



void MainLoja:: exibir_lista_livros(){

    ui->LIVROS_TABLE->clearContents();

    int total_livros = X.getNumLivro();

    ui->LIVROS_TABLE->setRowCount(total_livros);


    for (int i = 0; i < total_livros; i++) {

        Livro livro = X.getLivro(i);
        QLabel* label_nome_livros = new QLabel(livro.getNome().c_str());
        QLabel* label_preco_livros = new QLabel(QString::number(livro.getPreco(), 'f', 2));
        QLabel* label_autor_livros = new QLabel(livro.getAutor().c_str());

        label_nome_livros->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label_preco_livros->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        label_autor_livros->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        ui->LIVROS_TABLE->setCellWidget(i, 0, label_nome_livros);
        ui->LIVROS_TABLE->setCellWidget(i, 1, label_preco_livros);
        ui->LIVROS_TABLE->setCellWidget(i, 2, label_autor_livros);
    }
}

void MainLoja::on_LIVROS_TABLE_cellDoubleClicked(int row)
{
    if (row >= 0 && row < X.getNumLivro())
    {
        X.excluirLivro(row);

        exibir_lista_livros();
        exibir_total();
    }
}


void MainLoja:: exibir_lista_CDS(){

    ui->CDS_TABLE->clearContents();

    int total_CDS = X.getNumCD();

    ui->CDS_TABLE->setRowCount(total_CDS);

    for (int i = 0; i < total_CDS; i++) {

        CD cd = X.getCD(i);
        QLabel* label_nome_CDS = new QLabel(cd.getNome().c_str());
        QLabel* label_preco_CDS = new QLabel(QString::number(cd.getPreco(), 'f', 2));
        QLabel* label_numero_faixas = new QLabel(QString::number(cd.getNumFaixas()));

        label_nome_CDS->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label_preco_CDS->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        label_numero_faixas->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        ui->CDS_TABLE->setCellWidget(i, 0, label_nome_CDS);
        ui->CDS_TABLE->setCellWidget(i, 1, label_preco_CDS);
        ui->CDS_TABLE->setCellWidget(i, 2, label_numero_faixas);
    }
}


void MainLoja::on_CDS_TABLE_cellDoubleClicked(int row)
{
    if (row >= 0 && row < X.getNumCD())
    {
        X.excluirCD(row);

        exibir_lista_CDS();
        exibir_total();
    }
}



void MainLoja:: exibir_lista_DVDS(){

    ui->DVDS_TABLE->clearContents();

    int total_DVDS = X.getNumDVD();

    ui->DVDS_TABLE->setRowCount(total_DVDS);


    for (int i = 0; i < total_DVDS; i++) {

        DVD dvd = X.getDVD(i);
        QLabel* label_nome_DVDS = new QLabel(dvd.getNome().c_str());
        QLabel* label_preco_DVDS = new QLabel(QString::number(dvd.getPreco(), 'f', 2));
        QLabel* label_duracao_DVDS = new QLabel(QString::number(dvd.getDuracao()));

        label_nome_DVDS->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label_preco_DVDS->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        label_duracao_DVDS->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        ui->DVDS_TABLE->setCellWidget(i, 0, label_nome_DVDS);
        ui->DVDS_TABLE->setCellWidget(i, 1, label_preco_DVDS);
        ui->DVDS_TABLE->setCellWidget(i, 2, label_duracao_DVDS);
    }
}



void MainLoja::on_DVDS_TABLE_cellDoubleClicked(int row)
{
    if (row >= 0 && row < X.getNumCD())
    {
        X.excluirDVD(row);

        exibir_lista_DVDS();
        exibir_total();
    }
}

void MainLoja::on_actionIncluir_Livro_triggered()
{
    inclLivro->clear();
    inclLivro->show();
}

void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
}


void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
}


void MainLoja::on_actionLer_triggered()
{
    QString fileName = QFileDialog::
        getOpenFileName(this, "Ler estoque",QString(),"*.txt");

    std::string fileString = fileName.toStdString();

    if (!fileName.isEmpty())
    {
        if (!X.ler(fileString))
        {
            QMessageBox::critical(this,tr("Erro"), tr("Erro na leitura do arquivo."));
        }
    }
    exibir_lista_livros();
    exibir_lista_CDS();
    exibir_lista_DVDS();
    exibir_total();
}


void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar estoque", QString(), "*.txt");

    if (fileName.isEmpty()) // Verifica se o nome do arquivo não está vazio
    {
        return;
    }

    std::string fileString = fileName.toStdString();

    if (!X.salvar(fileString))
    {
        QMessageBox::critical(this, tr("Erro"), tr("Erro na escrita do arquivo."));
    }
}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void MainLoja:: slotIncluirLivro(QString nome, QString preco, QString autor){

    std:: string nomeString = nome.toStdString();
    std:: string autorString = autor.toStdString();

    int preco_centavos =round(preco.toFloat()*100);

    if( nomeString==""||preco_centavos<=0||autorString==""){
        QMessageBox::critical(this,"Livro Inválido\n" ,
                              "Não foi possível a inclusão do Livro = \n "
                              "Nome = "+ nome +"\n"
                              "Preço = "+ preco +"\n"
                              "Autor = "+ autor);
    }else{

    Livro novo_livro(nomeString,preco_centavos,autorString);
    X.incluirLivro(novo_livro);
    exibir_lista_livros();
    exibir_total();
    }
}


void MainLoja:: slotIncluirCD(QString nome, QString preco, QString numfaixas){

    std:: string nomeString = nome.toStdString();

    int preco_centavos =round(preco.toFloat()*100);
    int num_faixas = numfaixas.toInt();

    if( nomeString==""||preco_centavos<=0||num_faixas<=0){
    QMessageBox::critical(this,"CD Inválido\n ",
                          "Não foi possível a inclusão do CD =  \n"
                          "Nome = "+nome+"\n"
                          "Preço = "+preco+"\n"
                          "Nº de Faixas = "+numfaixas);
    }else{
    CD novo_cd(nomeString,preco_centavos,num_faixas);
    X.incluirCD(novo_cd);
    exibir_lista_CDS();
    exibir_total();
    }
}


void MainLoja:: slotIncluirDVD(QString nome, QString preco, QString duracao){

    std:: string nomeString = nome.toStdString();

    int preco_centavos =round(preco.toFloat()*100);
    int minutos = round(duracao.toInt());
    if( nomeString==""||preco_centavos<=0||minutos<=0){
    QMessageBox::critical(this,"DVD Inválido\n ",
                          "Não foi possível a inclusão do DVD = \n"
                          "Nome = "+nome+"\n"
                          "Preço = "+preco+"\n"
                          "Duração = "+duracao);
    }else{
    DVD novo_dvd(nomeString,preco_centavos,minutos);
    X.incluirDVD(novo_dvd);
    exibir_lista_DVDS();
    exibir_total();
    }
}

void MainLoja:: exibir_total(){
    total_itens->setText(QString::number(X.getNumLivro() + X.getNumCD() + X.getNumDVD()));
}




