#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <QLabel>
#include "loja.h"

#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();


private slots:

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirCD(QString nome, QString preco, QString numfaixas);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);

    void exibir_lista_livros();

    void exibir_lista_CDS();

    void exibir_lista_DVDS();

    void exibir_total();

    void on_LIVROS_TABLE_cellDoubleClicked(int row);

    void on_CDS_TABLE_cellDoubleClicked(int row);

    void on_DVDS_TABLE_cellDoubleClicked(int row);

    void on_actionIncluir_Livro_triggered();

    void on_actionIncluir_CD_triggered();

    void on_actionIncluir_DVD_triggered();


private:
    Ui::MainLoja *ui;
    Loja X;
    IncluirLivro* inclLivro;
    IncluirCD* inclCD;
    IncluirDVD* inclDVD;
    QLabel* total_itens;
};






#endif // MAINLOJA_H
