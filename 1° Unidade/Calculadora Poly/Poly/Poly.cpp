#include "Poly.h"
#include <cmath>
#include <fstream>
#include <string>



//Construtor default
Poly::Poly() : grau(-1) , a(nullptr){
}

//Construtor específico

Poly::Poly(int g) : grau(g), a(nullptr) {
     if (g == 0) {
        a = new double[1];
        a[0] = 0.0;
    }
    else if (g > 0) {
        a = new double[g + 1];
        for (int i = 0; i <= g; i++) {
            a[i] = 0.0;
        }
        a[g] = 1.0;
    }
    else {
        grau = -1;
    }
}

//Construtor por cópia

Poly::Poly(const Poly &copy_poly) : grau(copy_poly.grau), a(nullptr) {
    if (grau >= 0) {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; i++) {
            a[i] = copy_poly.a[i];
        }
    }
}


//Construtor por movimento

Poly::Poly(Poly &&copy_poly) : grau(copy_poly.grau), a(copy_poly.a) {
    copy_poly.grau = -1;
    copy_poly.a = nullptr;
}


//Operador de sobrecarga por cópia

Poly& Poly::operator=(const Poly &copy_poly) {
    if (this != &copy_poly) {
        delete[] a;
        grau = copy_poly.grau;
        if (grau >= 0) {
            a = new double[grau + 1];
            for (int i = 0; i <= grau; i++) {
                a[i] = copy_poly.a[i];
            }
        } else {
            a = nullptr;
        }
    }
    return *this;
}


//Operador de sobrecarga por movimento

Poly& Poly::operator=(Poly&& copy_poly) {

    delete[] a;

    grau = -1;
    a = nullptr;

    swap(grau, copy_poly.grau);
    swap(a, copy_poly.a);

    return *this;
}


//Método de consulta do grau

int Poly::getGrau() const {
    return grau;
}

//Método de consulta do coeficiente

double Poly::getCoef(int i) const {
    if (i < 0 || i > grau) {
        return 0.0;
    }
    return a[i];
}

//Método de alteração do coeficiente

void Poly::setCoef(int i, double novo_coef) {
    if (i < 0 || i > grau) {
        cerr << "Erro: O indice usado e invalido." << endl;
        return;
    }
    else if (novo_coef == 0 && i == grau && grau > 0) {
        cerr << "Erro: O coeficiente de maior grau nao pode ser nulo, exceto para polinomios de grau 0." << endl;
        return;
    }
    a[i] = novo_coef;
}

double Poly::operator[](int i) const {
    return getCoef(i);                //Sobrecarga do Operador []
}

//Método para redefinição do grau e coeficiente usando a função "recriar"

void Poly::recriar(int novo_grau){
    *this = Poly(novo_grau);
}


//Sobrecarregando o "operator==" com um booleano
bool Poly::operator==(const Poly& other) const {

    // Verificando se os graus são iguais
    if (grau == other.grau) {
        return true;
    }

    // Verificando se os coeficientes são diferentes
    for (int i = 0; i <= grau; i++) {
        if (a[i] != other.a[i]) {
            return false;
        }
    }

    // Se os polinômios forem diferentes
    return false;
}

bool Poly::operator!=(const Poly& other) const {
    return !(*this == other);
}

//Método de consulta empty

bool Poly::empty() const {
    return grau < 0;
}

//Método de consulta de grau zero e coeficiente nulo

bool Poly::isZero() const {
    return grau == 0 && a[0] == 0.0;
}

//Método do getValor, para saber o valor do polinômio para um dado valor de x;

double Poly::getValor(double x) const {
    if (empty()) {
        return 0.0;
    }

    double resposta = 0.0;
    double potencia_x = 1.0; //1.0 pois inicia-se em x^0. Em todo caso será 1.0

    for (int i = 0; i <= grau; i++) {
        resposta += a[i] * potencia_x;  //Percorrendo os coeficientes do polinômio, calcular as potências de x e mostrar o cálculo preciso do valor do polinômio
        potencia_x *= x;
    }

    return resposta;
}

double Poly::operator()(double x) const {
        return getValor(x);                 //Sobrecarga do Operador ()
}

ostream& operator<<(ostream& ostream, const Poly& other) {
    int grau = other.getGrau();

    if (grau < 0) {
        // Polinômio vazio, não imprime nada
        return ostream;
    }

    if (grau < 0 || other.isZero()) {
        //Imprimirá 0 quando for polinômio vazio ou nulo
        ostream << "0";
        return ostream;
    }

    for (int i = grau; i >= 0; i--) {
        double coeficiente = other.getCoef(i);

        if (coeficiente != 0.0) {
            if (i == grau) {
                // Coeficiente de maior grau -> não precisa de sinal de adição
                if (coeficiente < 0.0) {
                    ostream << "-";
                }
            } else {
                // Sinal de adição se não for o coeficiente de maior grau
                if (coeficiente < 0.0) {
                    ostream << " - ";
                } else {
                    ostream << " + ";
                }
            }

            double abs_coeficiente = abs(coeficiente);

            if (abs_coeficiente != 1.0 || i == 0) {
                ostream << abs_coeficiente;
            }

            // Imprime 'x'
            if (i != 0) {
                if (abs(other.a[i]) !=1.0){
                    ostream << "*";
                }
                ostream << "x";
                if (i > 1) {
                    ostream << "^" << i;
                }
            }
        }
    }

    return ostream;
}


//Sobrecarga do operador >>
istream& operator>>(istream& istream, Poly& other) {
    // Verificando se o polinômio está vazio
    if (other.empty()) {
        cerr << "Erro: O polinomio esta vazio. Nao e possivel inserir coeficientes nesse estado" << endl;
        return istream;
    }

    for (int i = other.getGrau(); i >= 0; i--) {
        cout << "x^" << i << ": ";
        double coeficiente;

        // Lê o coeficiente dado através da entrada
        if (!(istream >> coeficiente)) {
            cerr << "Erro: Falha ao ler coeficiente." << endl;
            return istream;
        }

        // Verifica se o coeficiente de maior grau não é nulo (exceto para grau 0)
        if (i == other.getGrau() && coeficiente == 0.0 && other.getGrau() != 0) {
            cerr << "Erro: O coeficiente de maior grau nao pode ser nulo, a menos que se trate de grau 0" << endl;
            i++; // Releitura do coeficiente
            continue;
        }

        // Define o coeficiente do polinômio
        other.setCoef(i, coeficiente);
    }

    return istream;
}

//Método "salvar"

bool Poly::salvar(const string& nome_file) const {
    ofstream file(nome_file);

    if (!file.is_open()) {
        cerr << "Erro: Falha ao abrir o arquivo para escrita." << endl;
        return false;
    }

    int grau = getGrau();

    file << "POLY " << grau << endl;

    for (int i = 0; i <= grau; i++) {
        file << a[i];
        if (grau >= 0) {
            file << " ";
        } else {
            file << endl;
        }
    }

    file.close();
    return true;
}

//Método de leitura

bool Poly::ler(const string& nome_file) {
    ifstream file(nome_file);

    if (!file.is_open()) {
        return false;
    }

    string palavra_reservada;
    file >> palavra_reservada;

    if (!(file.good()) || (palavra_reservada != "POLY")) {
        file.close();
        return false; // Arquivo não começa com a palavra reservada POLY
    }

    int grau_lido;

    if (!(file.good()) || !(file >> grau_lido)) {
        file.close();
        return false; // Grau inválido
    }

    Poly prov(grau_lido); // Polinômio temporário com o grau lido

    if (grau_lido >= 0) {
        for (int i = 0; i <= grau_lido; i++) {
            double coeficiente;
            if (!(file >> coeficiente)) {
                file.close();
                return false;
            }else{
            prov.a[i] = coeficiente;
            }
        }
    }

    // Verifica se o coeficiente de maior grau não é nulo (exceto para grau 0)
    if (!(file.good()) || (grau_lido > 0 && prov.getCoef(grau_lido) == 0.0)) {
        file.close();
        return false;
    }

    // Transfere para *this se todas as regras acima passarem
    *this = prov;

    file.close();
    return true;
}


// Operador - (unário)
Poly Poly::operator-() const {
    Poly resposta(*this); // Cria uma cópia do polinômio original

    for (int i = 0; i <= resposta.getGrau(); i++) {
        resposta.setCoef(i, -resposta.getCoef(i)); // Inverte o sinal dos coeficientes
    }

    return resposta;
}


//Operador + Binário
Poly Poly::operator+(const Poly& other) const {

    if (empty()) {
        return other;
    }
    if (other.empty()) {
        return *this;
    }

    int maior_grau = max(getGrau(), other.getGrau());

    Poly resposta(maior_grau);

    for (int i = 0; i <= maior_grau; i++) {

        double coeficiente = 0.0;

        if (i<=getGrau()){
            coeficiente += a[i];
        }

        if(i<=other.grau){
                coeficiente+=other.a[i];
        }

        resposta.a[i] = coeficiente;

    }

    resposta.reduzir();

    return resposta;
}

// Operador - (binário)
Poly Poly::operator-(const Poly& other) const {
    return *this + (-other);
}



// Método para reduzir o grau do polinômio

void Poly::reduzir() {
    while (grau > 0 && a[grau] == 0.0) {
        grau--;
    }
    if (grau >= 0) {
        double* novos_coeficientes = new double[grau + 1];
        for (int i = 0; i <= grau; i++) {
            novos_coeficientes[i] = a[i];
        }
        delete[] a; // Liberar a memória antiga
        a = novos_coeficientes;
    } else {
        delete[] a; // Se o grau for -1, não há coeficientes, então liberamos a memória.
        a = nullptr;
    }
}

Poly Poly::operator*(const Poly& other) const {
    if (empty() || other.empty()) { // polinômio vazio
      return Poly();
    }
    if (isZero() || other.isZero()) { // polinômio nulo
      Poly produto(0);

      return produto;
    }

    int grau_max = grau + other.grau;
    Poly produto(grau_max);

    for (int i = 0; i <= grau_max; i++) {
      double coef = 0.0;
      for (int j = 0; j <= i; j++) {
        if (j <= grau && i - j <= other.grau) {
          coef += a[j] * other.a[i - j];
        }
      }
      produto.setCoef(i, coef);
    }

    return produto;
}


//Destrutor

Poly::~Poly() {
    delete[] a;
}

