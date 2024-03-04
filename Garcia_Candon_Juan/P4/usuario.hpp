#ifndef _USUARIO_
#define _USUARIO_

#include <iostream>
#include <string.h>
#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
#include <strstream>
#include <random>
#include <utility>


class Tarjeta;
class Articulo;
class Numero;

//---------------------------------------------------------------------------------------CLASE CLAVE--------------------------------------------------------------------------------------------------------
class Clave{
    public:
    // Atributos de la clase
     enum Razon{CORTA, ERROR_CRYPT}_;

    //Constructor
        Clave(const char* contrasena);

    //Observadoras
        const Cadena clave() const {return contrasena_;}

    //Funciones miembro de la clase
        bool verifica(const char* contrasena);

    //Control de Excepciones
        class Incorrecta{
            public:
	  Incorrecta(Razon r): r_(r){}
                Razon razon(){return r_;}
            private:
                Razon r_;
        };

    //Destructor
  ~Clave(){contrasena_.~Cadena();}
    private:
        Cadena contrasena_;
    
    //Factorizamos la funcion encriptar
    const char* encriptar(const char* cadena);
};


//----------------------------------------------------------------------------------------CLASE USUARIO----------------------------------------------------------------------------------------
class Usuario{
    public:
    //Tipos de la clase
        typedef std::map <Numero, Tarjeta*> Tarjetas;
        typedef std::unordered_map <Articulo*, unsigned int> Articulos;

    //Constructores
        Usuario(Cadena identificador, Cadena nombre, Cadena apellidos, Cadena dir, Clave contrasena);

    //Control de Excepciones
        class Id_duplicado{
            public:
                Id_duplicado(Cadena idd): idd_(idd){}
                const Cadena idd(){return idd_;}
            private:
                Cadena idd_;
        };

    //Observadoras
        const Cadena id()const{return identificador_;}
        const Cadena nombre()const{return nombre_;}
        const Cadena apellidos()const{return apellidos_;}
        const Cadena direccion()const{return dir_;}
        const Tarjetas tarjetas()const{return tarjetas_pago;}
        const Articulos compra()const{return carrito;}
        
    
    //Operadores
        friend std::ostream& operator <<(std::ostream& os, const Usuario& A);
        friend std::ostream& operator <<(std::ostream& os, const Articulos& compra);

    //Relaciones
        //Asociacion clase tarjeta
        void es_titular_de(const Tarjeta& tarjeta); //Añadimos una tarjeta
        void no_es_titular_de(const Tarjeta& tarjeta);//Eliminamos una tarjeta

        //Asociacion clase Articulo
        void compra(Articulo& art, int cantidad = 1);
        const int n_articulos() const;
    
    //Destructor
        ~Usuario(); //Debemos desasociar al usuario de las tarjetas que posee

    //Restricciones
        Usuario(const Usuario& A) = delete;
        void operator =(const Usuario& A) = delete;
    
    // Sobrecarga Operadores de flujo
        friend std::ostream& operator <<(std::ostream& os, const Usuario& A);

    private:
        const Cadena identificador_, nombre_, apellidos_, dir_;
        Clave contrasena_;
        Tarjetas tarjetas_pago; //1 a varios
        Articulos carrito;      //1 a varios

        static std::unordered_set<Cadena> id_Usuarios; 
};

// Funciones externas

void mostrar_carro(std::ostream& o, const Usuario& U);


#endif
