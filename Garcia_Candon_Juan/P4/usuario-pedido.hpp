
#ifndef _USUARIO_PEDIDO_
#define _USUARIO_PEDIDO_

#include <iostream>
#include <map>
#include <set>

#include "usuario.hpp"
#include "pedido.hpp"

class Pedido;
class Usuario;


// Representa la asociacion bidirecional uno-a-varios entre las clases Usuario y Pedido
class Usuario_Pedido{
    private:
    //Tipos de la clase
        typedef std::set<Pedido*> Pedidos;

        typedef std::map <Usuario*, Pedidos> Usuario_Pedidos;
        typedef std::map<Pedido*, Usuario*> Pedido_Usuario;

    // Parametros de la clase
        Usuario_Pedidos enlace_UP; 
        Pedido_Usuario enlace_PU;

    public: 
    // Operaciones de la clase
        void asocia(const Usuario& usuario, const Pedido& pedido);
        void asocia(const Pedido& pedido, const Usuario& usuario);
    
    // Observadoras
        const Pedidos& pedidos(Usuario& usuario)const{return enlace_UP.at(&usuario);};
        const Usuario& cliente(Pedido& pedido)const{return *enlace_PU.at(&pedido);};
};

#endif
