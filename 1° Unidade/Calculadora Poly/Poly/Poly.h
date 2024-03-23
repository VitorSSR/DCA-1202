#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <istream>

using namespace std;

class Poly {
private:

    int grau;    // Grau do polinômio
    double* a;   // Coeficientes

public:

    //Construtores
    Poly();  //Default

    explicit Poly(int g); //Específico

    Poly(const Poly &copy_poly); //Construtor por cópia

    Poly(Poly &&copy_poly);   //Construtor por movimento


    //Operadores de sobrecarga

    Poly& operator=(const Poly &copy_poly); //Sobrecarga por cópia

    Poly& operator=(Poly &&copy_poly);  //Sobrecarga por movimento

    double operator[](int i) const;

    bool operator==(const Poly& p) const; //Sobrecarga do Operador ==

    bool operator!=(const Poly& p) const; //Sobrecarga do Operador !=

    double operator()(double x) const;

    friend ostream& operator<<(ostream& ostream, const Poly& p); //Sobrecarga do Operador <<

    friend istream& operator>>(istream& istream, Poly& p); // Sobrecarga do Operador >>

    Poly operator-() const; // Sobrecarga do Operador - (unário)

    Poly operator+(const Poly& p) const; // Sobrecarga do Operador + (binário)

    Poly operator-(const Poly& p) const; // Sobrecarga do Operador - (binário)

    Poly operator*(const Poly& other) const; //Sobrecarga do Operador *


    //Métodos

    int getGrau() const; //Consulta dos parâmetros

    double getCoef(int i) const;  //Consulta dos coeficientes

    void setCoef(int i, double novo_coef); //Alteração dos coeficientes

    void recriar(int novo_g); //Redefinição do grau e coeficientes

    bool empty() const;  // Método de consulta para saber se o polinômio está vazio

    bool isZero() const; //Método de consulta para grau 0 e coeficiente nulo

    double getValor(double x) const; //Método de consulta do valor do polinômio para um dado valor de X

    bool salvar(const string& nome_file) const; //Método salvar

    bool ler(const string& nome_file);  //Método de leitura do polinômio

    void reduzir(); //Método para reduzir grau



    //Destrutor
    ~Poly();

};


#endif





