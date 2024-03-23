#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <istream>

using namespace std;

class Poly {
private:

    int grau;    // Grau do polin�mio
    double* a;   // Coeficientes

public:

    //Construtores
    Poly();  //Default

    explicit Poly(int g); //Espec�fico

    Poly(const Poly &copy_poly); //Construtor por c�pia

    Poly(Poly &&copy_poly);   //Construtor por movimento


    //Operadores de sobrecarga

    Poly& operator=(const Poly &copy_poly); //Sobrecarga por c�pia

    Poly& operator=(Poly &&copy_poly);  //Sobrecarga por movimento

    double operator[](int i) const;

    bool operator==(const Poly& p) const; //Sobrecarga do Operador ==

    bool operator!=(const Poly& p) const; //Sobrecarga do Operador !=

    double operator()(double x) const;

    friend ostream& operator<<(ostream& ostream, const Poly& p); //Sobrecarga do Operador <<

    friend istream& operator>>(istream& istream, Poly& p); // Sobrecarga do Operador >>

    Poly operator-() const; // Sobrecarga do Operador - (un�rio)

    Poly operator+(const Poly& p) const; // Sobrecarga do Operador + (bin�rio)

    Poly operator-(const Poly& p) const; // Sobrecarga do Operador - (bin�rio)

    Poly operator*(const Poly& other) const; //Sobrecarga do Operador *


    //M�todos

    int getGrau() const; //Consulta dos par�metros

    double getCoef(int i) const;  //Consulta dos coeficientes

    void setCoef(int i, double novo_coef); //Altera��o dos coeficientes

    void recriar(int novo_g); //Redefini��o do grau e coeficientes

    bool empty() const;  // M�todo de consulta para saber se o polin�mio est� vazio

    bool isZero() const; //M�todo de consulta para grau 0 e coeficiente nulo

    double getValor(double x) const; //M�todo de consulta do valor do polin�mio para um dado valor de X

    bool salvar(const string& nome_file) const; //M�todo salvar

    bool ler(const string& nome_file);  //M�todo de leitura do polin�mio

    void reduzir(); //M�todo para reduzir grau



    //Destrutor
    ~Poly();

};


#endif





