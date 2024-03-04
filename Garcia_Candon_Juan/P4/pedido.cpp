#include "pedido.hpp"

//-----------------------------------------------------------CLASE PEDIDO---------------------------------------------------------------------

int Pedido::num_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a,Usuario& usuario, const Tarjeta& tarjeta, const Fecha& Actual):
num_pedido(num_pedidos+1), tarjeta_pago(&tarjeta), fecha_venta(Actual), importe_(0){
    // Realizamos comprobaciones necesarias
  if(usuario.compra().empty())
    throw(Pedido::Vacio(&usuario));
  if(&usuario != tarjeta.titular())
    throw (Pedido::Impostor(&usuario));
  if(tarjeta.caducidad() < Actual)
    throw Tarjeta::Caducada(tarjeta.caducidad());
  if(!tarjeta.activa())
    throw Tarjeta::Desactivada(&tarjeta);
  
  // Pedido queda asociado al Usuario que ha realizado la compra
  u_p.asocia(usuario, *this);

  // Pedido queda asociado a los articulos
  Usuario::Articulos carro = usuario.compra();
  for(auto n = carro.begin(); n != carro.end(); n++){
    std::pair<Articulo*, unsigned int> par_pedido;
    par_pedido.first = n->first;
    par_pedido.second = n->second;

    Articulo* art = par_pedido.first;
    unsigned cant = par_pedido.second;

    if(cant > art->stock()){
      for(auto art_aux = carro.begin(); art_aux != carro.end(); art_aux++){
	usuario.compra(*art , 0);
      }
      throw(SinStock(art));
    }
    
    p_a.pedir(*this,*art, art->precio(), cant);
    p_a.pedir(*art, *this, art->precio(), cant);
    
    //Actualizamos el stock de los articulos pedidos
    art->stock() -= cant;

    //Vaciamos el carro del usuario
    usuario.compra(*art, 0);
  }
}

std::ostream& operator <<(std::ostream& os, const Pedido& p){
  os << "Num.Pedido: " << p.numero() << std::endl << "Fecha:        " << p.fecha() << std::endl << "Pagado con:   " << p.tarjeta() << std::endl << "Importe:      "<< p.importe() << std::endl;
  return os;
}
