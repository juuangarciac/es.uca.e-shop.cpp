
#ifndef _PEDIDO_
#define _PEDIDO_

#include <iostream>
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{
    public:
    //Constructores
        Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& Actual = Fecha());
    
    // Control de excepciones
        class Vacio{
            // Excepcion lanzada cuando el carrito no tiene ningun articulo
            public:
                Vacio(Usuario* u): usuario_(u){};
                const Usuario& usuario(){return *usuario_;}
            private:
                const Usuario* usuario_;
        };
    
        class Impostor{
            public:
                // Excepcion lanzada cuando el usuario != titular de la tarjeta
                Impostor(Usuario* u): usuario_(u){};
                const Usuario& usuario(){return *usuario_;}
            private:
                const Usuario* usuario_;
        };

        class SinStock{
                // En el carrito hay articulos fuera de stock
            public:
                SinStock(Articulo* a): articulo_(a){}
                const Articulo& articulo(){return *articulo_;}
            private:
                const Articulo* articulo_;

        };

        // metodos observadores
        const int numero() const{return num_pedido;}
        const Tarjeta& tarjeta() const{return *tarjeta_pago;}
        Fecha fecha()const{return fecha_venta;}
        double importe()const{return importe_;}
        static int n_total_pedidos(){return num_pedidos;}


    private:
        const int num_pedido;
        const Tarjeta* tarjeta_pago;
        Fecha fecha_venta;
        double importe_;
        static int num_pedidos;

  // Usaremos un ordered_
};

// Operadores Externos de la clase
std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif
