#include <iostream>
#include <string.h>
#include <iterator>


#ifndef POO_P0_EJ2_
#define POO_P0_EJ2_

class Cadena
{
    public:
    //Constructores
        Cadena(); //Constructor por defecto
        Cadena(unsigned t ,const char c = ' '); //Constructor Parametrizado (Tambien sirve como Constructor de Conversion de Entero a Cadena)
        Cadena(const char* c);//Constructor de conversion de const char* a Cadena
        Cadena(const Cadena& A):s_(new char[A.tam_]), tam_(A.tam_){strcpy(s_, A.s_);};//Constructor por copia
        Cadena(Cadena&& cad):s_(cad.s_), tam_(cad.tam_){cad.s_ = nullptr; cad.tam_ = 0;}//Constructor Movimiento

    //Operadores de la clase
        friend std::ostream& operator <<(std::ostream& os, const Cadena& A);
        friend std::istream& operator >>(std::istream& is, Cadena& A);

        Cadena& operator =(const Cadena& A);
        Cadena& operator =(Cadena&& A);
        //Cadena& operator = (const char* c); ¿Si tenemos constructor de conversion, hace falta?
        
        Cadena& operator +=(const Cadena& B);
        friend Cadena operator +(const Cadena& A, const Cadena& B);

        friend bool operator ==(const Cadena& A, const Cadena& B);

        friend bool operator !=(const Cadena& A, const Cadena& B);

        friend bool operator >(const Cadena& A, const Cadena& B);
        friend bool operator >=(const Cadena& A, const Cadena& B);


        friend bool operator <(const Cadena& A, const Cadena& B);
        friend bool operator <=(const Cadena& A, const Cadena& B);

        const char operator [](int pos)const{return s_[pos];}
        char& operator [](int pos){return s_[pos];}
  
        const char at(int pos)const;
        char& at(int post);

    //Observadoras
        int length()const{return tam_;};
        Cadena substr(int indice, int t)const;
        const char* c_str()const;
    
    
    // Iteradores
        // Iterator es un patrón de diseño de comportamiento que permite el recorrido secuencial por una estructura de datos compleja sin exponer sus detalles internos
        // Gracias al patrón Iterator, los clientes pueden recorrer elementos de colecciones diferentes de un modo similar, utilizando una única interfaz iteradora.
        typedef char* iterator;
        typedef const char* const_iterator;

        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

            // Iterator
        // Devuelve un puntero al primer elemento de nuestro contenedor (cadena de caracteres)
        iterator begin(){return s_;}
        const_iterator begin() const {return const_iterator(s_);}
        const_iterator cbegin()const {return const_iterator(s_);}

        // Devuelve un puntero al carácter terminador \0.
        iterator end(){return s_ + tam_;}
        const_iterator end() const {return const_iterator(s_ + tam_);}
        const_iterator cend() const {return const_iterator(s_ + tam_);}

            // Reverse_Iterator
        // Iterator para recorrer inversamente un contenedor. Devuelve un puntero al carácter terminador \0.
        reverse_iterator rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}

        // Iterator para recorrer inversamente un contenedor. Devuelve un puntero al primer elemento del contendor.
        reverse_iterator rend(){return reverse_iterator(begin());}
        const_reverse_iterator rend() const{return const_reverse_iterator(begin());}
        const_reverse_iterator crend() const{return const_reverse_iterator(begin());}

    //Destructor
        ~Cadena(){delete[] s_; tam_ = 0;};

    private:
        char* s_;
        int tam_;
};


//Apuntes
/*
    Se puede reservar memoria para un puntero en la lista inicializadora, de hecho debemos hacerlo, por que no podemos reasignar memoria con el operador new
    Por lo que nuestro puntero sera siempre del mismo tamaño, y encima el que le de el compilador
*/


#endif

