

#ifndef _Tarjeta_
#define _Tarjeta_

#include <iostream>
#include <unordered_set>
#include <cctype>
#include <iomanip>
#include <algorithm>

#include "cadena.hpp"
#include "usuario.hpp"
#include "char_to_int.hpp"
#include "fecha.hpp"

/*------------------------------------------------------------------CLASE NUMERO-------------------------------------*/
class Numero{
    public:
    //Clases amigas
        friend class Tarjeta;
        
    //Constructor
        Numero(Cadena numero);

        enum Razon{LONGITUD, DIGITOS, NO_VALIDO};

    //Controlar excepciones
        class Incorrecto{
            public:
	  Incorrecto(Razon error): error_(error){}
                const Razon razon() const{return error_;}
            private:
                Razon error_;
        };

    //Operadores de la clase
        operator const char*()const {return numero_.c_str();}

    //Destructor
        ~Numero(){numero_.~Cadena();} 
    private:
       Cadena numero_;
  
       struct EsDigito: std::unary_function<char, bool>{
           bool operator()(char c)const{return isdigit(c);}
       };
};

// custom hash 
namespace std{
  template<>
  struct hash<Numero>{
    size_t operator()(const Numero& n) const{
      hash<string> hs;
      const char* p = n;
      string s(p);
      size_t res = hs(s);
      return res;
    }
  };
}


class Usuario;
/*-----------------------------------------------------------------CLASE TARJETA--------------------------------------------------*/
class Tarjeta{
    public:
    //Clases Amigas
   
    //Definicion de atributos + Constructores de la clase
        enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
        Tarjeta(const Numero& num, const Usuario& ti, const Fecha& f);

        Tarjeta(const Tarjeta& A) = delete;
        void operator =(const Tarjeta& A) = delete;

    //Control de Excepciones
        struct Caducada{
            public:
	        Caducada(const Fecha f): f_caducada(f){}
                const Fecha cuando()const{return f_caducada;}
            private:
                const Fecha f_caducada;
        };

        struct Num_duplicado{
            public:
                Num_duplicado(Numero num): num_(num){}
                const Numero num(){return num_;}
            private:
                Numero num_;
        };

       struct Desactivada{
            public:
	         Desactivada(const Tarjeta* t):tar(t){}
	         const Tarjeta& por_que(){return *tar;}
            private:
                 const Tarjeta* tar;
       };
    
    //Funciones Observadoras de la clase
        const Numero numero() const{return num_tarjeta;}
        const Usuario* titular() const{return titular_;}
        const Fecha caducidad() const{return caducidad_;}
        const bool activa() const{return activa_;}
        const Tipo tipo() const;
    
    //Funciones modificadoras de la clase
        bool activa(bool estado){activa_ = estado; return activa_;}
        void anular_titular(){titular_ = NULL; activa_ = false;}
    
    //Operadores
        friend std::ostream& operator <<(std::ostream& os, const Tarjeta& A);
        friend bool operator <(const Tarjeta& A, const Tarjeta& B);

    //Destructor
        ~Tarjeta(); //Debemos desasociar al Usuario de la Tarjeta
        
    private:
        const Numero num_tarjeta;
        const Usuario* titular_;
        const Fecha caducidad_;
        bool activa_;    //Siempre activa
  
        static std::unordered_set<Numero> id_tarjetas;
};

#endif
