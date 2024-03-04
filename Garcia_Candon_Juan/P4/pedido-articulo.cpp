#include "pedido-articulo.hpp"

//---------------------------------------------------------------------------------------------CLASE ORDENA-ARTICULOS y ORDENA-PEDIDOS--------------------------------------------

bool Pedido_Articulo::OrdenaArticulos::operator()(Articulo* a1, Articulo* a2) const { return a1->referencia() < a2->referencia();} 

bool Pedido_Articulo::OrdenaPedidos::operator()(Pedido* p1, Pedido* p2) const {return p1->numero() < p2->numero();}

/*----------------------------------------------------------------------------------------------CLASE PEDIDO ARTICULO--------------------------------------------------------------*/

//Cabecera: void Pedido_Articulo::pedir(const Pedido& ped, const const Articulo& art, double precio, int cantidad)
//Precondicion:
//Postcondicion:
void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, int cantidad){
  
  LineaPedido LP(precio, cantidad);
  
  PA[&ped].insert(std::make_pair(&art, LP));
  AP[&art].insert(std::make_pair(&ped, LP));
}

//Cabecera: void Pedido_Articulo::pedir(const Articulo& art, const Pedido& ped, double precio, int cantidad)
//Precondicion:
//Postcondicion:
void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, int cantidad){
    pedir(ped, art, precio, cantidad);
}

//Cabecera: Pedido_Articulo::ItemsPedido* Pedido_Articulo::detalle(const Pedido& ped) const
//Precondicion:
//Postcondicion:
Pedido_Articulo::ItemsPedido* Pedido_Articulo::detalle(Pedido& ped){
  return &PA.find(&ped)->second;
}

//Cabecera: Pedido_Articulo::Pedidos* Pedido_Articulo::ventas(const Articulo& art) const
//Precondicion:
//Postcondicion:
Pedido_Articulo::Pedidos* Pedido_Articulo::ventas(Articulo& art){
    return &AP.find(&art)->second;
}

//Cabecera: void Pedido_Articulo::mostrarDetallePedidos() const
//Precondicion:
//Postcondicion:
 std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& o){
  float total = 0;
  for(auto i = PA.begin(); i != PA.end(); i++){
    o << "Num.Pedido: " << i->first->numero() << "        " << "Cliente: " << i->first->tarjeta().titular()->nombre() << "     Fecha: " << i->first->fecha();
    total += i->first->importe();
  }  
  o << "TOTAL: " << total;
  return o;
}

//Cabecera: void Pedido_Articulo::mostrarDetalleVentas() const
//Precondicion:
//Postcondicion:
 std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& o){
  for(auto i = AP.begin(); i != AP.end(); i++){
    o << "Ventas de: " <<  "[" << i->first->referencia() << "]" << i->first->titulo() << std::endl;
  }
  return o;
}


// Sobrecarga de Operadores de flujo
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& A){
  // Imprimira los detalles del pedido, mostrara el importe total y ejemplares del pedido
  os << " PVP    Cantidad                 Artículo" << std::endl;
  os << "=========================================================================================" << std::endl;
  float total = 0;
  for(auto i = A.begin(); i != A.end(); i++){
    os << i->second.precio_venta() << "   " << i->second.cantidad() << "      " << "[" << i->first->referencia() << "]" << i->first->titulo() << std::endl;
    total += i->second.precio_venta() * i->second.cantidad();
  }
  os << "=========================================================================================";
  os << "Total: " << total;
  return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& A){
  int num_pedidos = 0;
  for(auto i = A.begin(); i != A.end(); i++){
    num_pedidos++;
  }

  os << "[" << "Pedidos : " << num_pedidos <<  "]" << std::endl;
  os << "================================================================" << std::endl;
  os  << "PVP   Cantidad                            Fecha de Venta " << std::endl;
  float total = 0;
  for(auto i = A.begin() ; i != A.end(); i++){
    os << i->second.precio_venta()  << "   " <<  i->second.cantidad() << "              " << i->first->fecha() << std::endl;
    total += i->second.precio_venta() * i->second.cantidad();
  }
  os << "=================================================================" << std::endl;
  os << "Total: " << total;
  return os;
}
