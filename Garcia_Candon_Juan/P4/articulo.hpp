
#ifndef _CLASE_ART_
#define _CLASE_ART_

#include "cadena.hpp"
#include "fecha.hpp"

#include <iomanip>
#include <iostream>
#include<set>

using namespace std;

class Autor{
public:
  Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& dir): nombre_(nombre), apellidos_(apellido), dir_(dir){}

  const Cadena& nombre()const{return nombre_;}
  const Cadena& apellidos()const{return apellidos_;}
  const Cadena& direccion()const{return dir_;}

  ~Autor(){nombre_.~Cadena(); apellidos_.~Cadena(); dir_.~Cadena();}
private:
  Cadena nombre_, apellidos_, dir_;
};


class Articulo{
    public:
  typedef std::set<Autor*> Autores; // Relacion con la clase Autor
  
    //Constructores
  Articulo(Autores autores,Cadena cod, Cadena ti, Fecha fe, float pre, int st = 0): autores_(autores),cod_ref(cod), titulo_(ti), fecha_publi(fe), precio_(pre), stock_(st){
        if(autores.empty()){
	  throw Articulo::Autores_vacios();
        }
  }
    //Observadoras
        Cadena referencia() const {return cod_ref;} 
        Cadena titulo() const {return titulo_;}
        Fecha f_publi() const {return fecha_publi;}
        
        float precio() const {return precio_;}
        int stock() const {return stock_;}
        virtual void impresion_especifica(ostream& os) const = 0;

    //Modificadoras
        float& precio(){return precio_;}
        int& stock(){return stock_;}
        
    //Operadores
        friend std::ostream& operator <<(std::ostream& os, const Articulo& A);

   // Relacion con la clase Autor
        class Autores_vacios{};
        const Autores& autores() const{return autores_;}


    // Destructor
        ~Articulo();
    private:
        Autores autores_;
        const Cadena cod_ref, titulo_;
        const Fecha fecha_publi;
        float precio_;
        int stock_;
};

class ArticuloAlmacenable: public Articulo{
public:
  ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio, size_t existencia = 0);
  size_t stock()const{return n_ejemplares;}
  size_t& stock(){return n_ejemplares;}
private:
  size_t n_ejemplares;
};


class LibroDigital: public Articulo{
public: 
  LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio, const Fecha& exp);
  const Fecha& f_expir() const {return exp_;}
  void impresion_especifica(ostream& os) const;
private:
  const Fecha exp_;
};

class Libro: public ArticuloAlmacenable{
public:
  Libro(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio, size_t n_paginas, size_t existencia = 0);
  size_t n_pag() const {return paginas;}
  void impresion_especifica(ostream& os) const;
private:
  const size_t paginas;
};


class Cederron: public ArticuloAlmacenable{
public:
  Cederron(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio ,size_t tam, size_t existencia = 0);
  size_t tam() const {return tamanno_;}
  void impresion_especifica(ostream& os) const;
private:
  const size_t tamanno_;
};


#endif
/* Apuntes

En la programacion orientada a objetos, una funcion virtual o metodo virtual es una funcion cuyo comportamiento, al ser declarado virtual, es determinado por la definicion de una funcion con la misma cabecera en alguna de sus subclases

Para crear una clase abstracta, declare al menos una funcion virtual pura
*/
