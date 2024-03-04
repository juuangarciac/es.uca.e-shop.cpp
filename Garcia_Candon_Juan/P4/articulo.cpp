#include "articulo.hpp"
using namespace std;

// Constructores de las subclases

ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio, size_t existencia):
  Articulo(autores, referencia, t, fecha, precio), n_ejemplares(existencia){}

LibroDigital::LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio, const Fecha& exp):
  Articulo(autores, referencia, t, fecha, precio), exp_(exp){}

Libro::Libro(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha,double precio, size_t n_paginas, size_t existencia):
  ArticuloAlmacenable(autores, referencia, t, fecha, precio, existencia), paginas(n_paginas){}

Cederron::Cederron(const Autores& autores, const Cadena& referencia, const Cadena& t, const Fecha& fecha, double precio,size_t tam, size_t existencia):
  ArticuloAlmacenable(autores, referencia, t, fecha, precio, existencia), tamanno_(tam){}


// Declaracion del metodo virtual puro de las subclases

void LibroDigital::impresion_especifica(ostream& os) const{
  os << " A la venta hasta " << this->f_expir() << ".";
}

void Libro::impresion_especifica(ostream& os) const{
  os << this->n_pag() << "pags., " << this->stock() << "unidades" ;
}

void Cederron::impresion_especifica(ostream &os) const{
  os << tam() << "tamaño, " << stock() << "unidades";
}

// Destructor de la clase Articulo
Articulo::~Articulo(){
  stock_ = 0;
  precio_ = 0;
  fecha_publi.~Fecha();
  cod_ref.~Cadena();
  titulo_.~Cadena();
  autores_.clear();
}
  

//cabecera: std::ostream& operator <<(std::ostream& os, const Fecha& A);
//precondicion:
//postcondicion:
std::ostream& operator <<(std::ostream& os, const Articulo& A){

  std::locale::global(std::locale("") );
  os << "[" << A.referencia() << "] \"";
  os << A.titulo() << "\", de ";

  auto it = A.autores().begin();
  os << (*it)->apellidos();
  while(++it != A.autores().end()){
    os << ", " << (*it)->apellidos();
  }
  os << ". " << A.f_publi().anno() << ". " << fixed << setprecision(2) << A.precio() << " €\n\t";
  A.impresion_especifica(os);
    return os;
}



//------------------------------------------------------Main----------------------------------------------------------------
