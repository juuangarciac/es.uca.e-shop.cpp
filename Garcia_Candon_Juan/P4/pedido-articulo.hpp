
#ifndef _PEDIDO_ARTICULO_
#define _PEDIDO_ARTICULO_

#include <iostream>
#include <map>
#include <set>
#include <iomanip>

#include "articulo.hpp"
#include "pedido.hpp"

//---------------------------------------------------------------------CLASE LineaPedido-------------------------------------------------------------------------------------

//Representa la clase de asociacion, que almacena los datos de la asociacion Pedido-Articulo
class LineaPedido{
    public:
        //Constructores
            explicit LineaPedido(double precio, unsigned cantidad = 1):precio_venta_(precio), cantidad_(cantidad){};
            void operator =(int precio) = delete;
            LineaPedido(int precio) = delete;

        //Observadoras
            double precio_venta()const{return precio_venta_;}
            unsigned cantidad()const{return cantidad_;}

        //Operadores de la clase
        friend std::ostream& operator <<(std::ostream& os, const LineaPedido& A);

    private:
        double precio_venta_;
        unsigned cantidad_;
};

//----------------------------------------------------------------------CLASE PEDIDO_ARTICULO--------------------------------------------------------------------------------

// binary_function es una clase para crear objetos de funcion con dos argumentos

// Un objeto de funcion o functor, es cualquier tipo que implementa el operator()
// Este operador se conoce como el operador de llamada o a veces el operador de aplicacion
// La biblioteca estándar de C++ usa objetos de funcion principalmente como criterios
//de ordenacion para los contenedores y en algoritmos

// Ordenamos los objetos de una clase, por su clave primaria
//Este objeto de función devuelve true si el primer parámetro es menor que el segundo parámetro.

//Representa la asociación bidireccional varios-a-varios con atributos de enlace entre Pedido y Articulo.

class Pedido;
class Articulo;
class LineaPedido;

class Pedido_Articulo{
    public:
    // Tipos de la clase
            class OrdenaArticulos: public std::binary_function <Articulo*, Articulo*, bool>
            {
	    public:
	      bool operator()(Articulo* a1, Articulo* a2) const;
            };

            class OrdenaPedidos: public std::binary_function <Pedido*, Pedido*, bool>
            {
	    public:
	      bool operator()(Pedido* p1, Pedido* p2) const;
            };

            //asoicacion entre Pedido y Articulo
            typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
            typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> asociacion_PA;

            //asoicacion entre articulo y pedido
            typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
            typedef std::map<Articulo*, Pedidos, OrdenaArticulos> asociacion_AP;
    
    // Creacion de enlaces
        // Pedido -> Articulo
        void pedir(Pedido& ped, Articulo& art, double precio, int cantidad);
        void pedir(Articulo& art, Pedido& ped, double precio, int cantidad);
    
    // Observadoras
        ItemsPedido* detalle(Pedido& ped);
        Pedidos *ventas(Articulo& art);
        std::ostream& mostrarDetallePedidos(std::ostream& o); //ventas agrupadas por pedidos
        std::ostream& mostrarVentasArticulos(std::ostream& o); // ventas agrupadas por articulos

    // Operadores de la clase
        friend std::ostream& operator <<(std::ostream& os, const ItemsPedido& A);
        friend std::ostream& operator <<(std::ostream& os, const Pedidos& A);
        
    private:
        asociacion_AP AP;
        asociacion_PA PA;
};


#endif
