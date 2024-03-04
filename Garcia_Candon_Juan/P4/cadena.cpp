#include "cadena.hpp"

//-------------------------------------------------Auxiliares
int ValorAlfabetico(const char c){return c - '0';}

//-------------------------------------------------Constructores--------------------------------------------------------------------------
Cadena::Cadena(){
    tam_ = 0;
    s_ = NULL;
}

//Al crear la cadena con memoria dinámica, el caracter NULL se coloca al final del espacio reservado por new, no al final de los caracteres que tenemos almacenados dentro del vector
Cadena::Cadena(unsigned t, const char c):s_(new char[t]), tam_(t)
{
    //0 hasta tam-1
    for(int i = 0; i < tam_; i++){
        s_[i] = c;
    }
    s_[tam_] = '\0';
}


Cadena::Cadena(const char* c): s_(new char[strlen(c) + 1]), tam_(strlen(c)){
    //Reservamos memoria
    strcpy(s_, c);
    s_[length()] = '\0';
}

//--------------------------------------------------Operadores de Conversion------------------------------------------------------------
const char* Cadena::c_str()const {
  return const_cast<char*>(s_);
}

std::ostream& operator <<(std::ostream& os, const Cadena& A){
    os << A.s_;
    return os;
}

std::istream& operator >>(std::istream& is, Cadena& A){
   char* cad = new char[32];
   is >> cad;

   A.s_ = cad;
   A.tam_ = strlen(A.s_);

   return is;
};

//------------------------------------------------Operadores de la clase-----------------------------------------------------------------
Cadena& Cadena::operator =(Cadena&& A){
    
    if(*this != A){
        strcpy(s_, A.s_);
        tam_ = A.tam_;

        A.s_ = nullptr;
        A.tam_ = 0;
    }
    return *this;
}

Cadena& Cadena::operator =(const Cadena& A){
    //Liberamos la memoria de nuestra cadena
    delete[] s_;

    //Reservamos de nuevo memoria con el tamaño de A.tam_
    s_ = new char[A.tam_];

    //Asignamos los valores
    s_ = strcpy(s_, A.s_);
    tam_ = A.tam_;
    return *this;
}


Cadena& Cadena::operator =(char* c){
  Cadena A(c);
  *this = A;
  return *this;
}

Cadena& Cadena::operator +=(const Cadena& B){
    //Almacenamos el valor de s_
    char* aux = new char[tam_];
    aux = strcpy(aux, s_);

    //Le damos a s_ su nuevo tamaño
    delete[] s_;
    tam_ = tam_ + B.tam_;
    s_ = new char[tam_];

    //Asignamos el nuevo valor
    s_ = strcat(strcpy(s_, aux), B.s_);

    delete[] aux;
    return *this;
}


Cadena operator+(const Cadena& A, const Cadena& B){
    Cadena aux(A);
    aux += B;
    return aux;
}

//--------------------------------------------------------------------Metodos Observadores---------------------------------------------
//strcmp: devuelve 0 si son iguales (valor booleano es 1 si es true) y 1 si son diferentes (valor booleano 0 si es false)

bool operator ==(const Cadena& A, const Cadena& B){
    return !strcmp(A.s_, B.s_) && A.tam_ == B.tam_;}

bool operator !=(const Cadena& A, const Cadena& B){
    return !strcmp(A.s_, B.s_) && A.tam_ && B.tam_;
}


//Debemos tener en cuenta que contra mas grande sea el numero, mas lejos del principio esta, por lo tanto el mas grande es el que tiene el número mas pequeño
//Solo compararmos el primer caracter ya que:
//  Si son cadenas de un solo tipo de elemento tipo 'XX', el primero es igual que el segundo
//  Si son de diferentes caracteres 'Hey', nos guiaremos por el valor del primer valor, ya que es el que nos indicara si la cadena se encuentra antes o no en el sistema de orden alfabetico
bool operator >(const Cadena& A, const Cadena& B){
    if(ValorAlfabetico(A.s_[0]) < ValorAlfabetico(B.s_[0])){
        return true;
    }else{
        return false;
    }     
}

bool operator >=(const Cadena& A, const Cadena& B){
    if(ValorAlfabetico(A.s_[0]) <= ValorAlfabetico(B.s_[0])){
        return true;
    }else{
        return false;
    }     
}


bool operator <(const Cadena& A, const Cadena& B){
    if(ValorAlfabetico(A.s_[0]) > ValorAlfabetico(B.s_[0])){
        return true;
    }else{
        return false;
    }     
}

bool operator <=(const Cadena& A, const Cadena& B){
    if(ValorAlfabetico(A.s_[0]) >= ValorAlfabetico(B.s_[0])){
        return true;
    }else{
        return false;
    }     
}


const char Cadena::at(int pos)const{
    if(pos >= 0 && pos < tam_){
        return s_[pos];
    }else{
        throw std::out_of_range ("Fuera de Rango");
    }
}

char& Cadena::at(int pos){
    if(pos >= 0 && pos < tam_){
        return s_[pos];
    }else{
        throw std::out_of_range ("Fuera de Rango");
    }
}


 Cadena Cadena::substr(int indice, int t)const{
     if(indice + t >= 0 && indice + t < tam_){
        char* aux = new char[tam_];
        strncpy(aux, s_ + indice, t);
        return const_cast<char*>(aux);
    }else{
       throw std::out_of_range ("Fuera de Rango"); // Si se lanza la excepcion no se continua la ejecucion de la funcion
    }
 }
//---------------------------------------------------MAIN---------------------------------------------------------------------------------
