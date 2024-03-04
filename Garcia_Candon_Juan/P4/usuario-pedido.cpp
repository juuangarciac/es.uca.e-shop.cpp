#include "usuario-pedido.hpp"

//----------------------------------------------------------Usuario Pedido----------------------------------------------------------------
//Cabecera: void Usuario_Pedido::asocia(const Usuario& U, const Pedido& P)
//Precondicion:
//Postcondicion: Enlazamos un Pedido a un Usuario
void Usuario_Pedido::asocia(const Usuario& usuario, const Pedido& pedido){
    //Declaramos los tipos necesarios para poder realizar la comprobacion
        Usuario_Pedido::Pedidos aux_pedidos; 
        aux_pedidos.insert(const_cast<Pedido*>(&pedido));
        std::pair <Usuario*, Pedidos> asociacion_up;
        asociacion_up.first = const_cast<Usuario*>(&usuario); asociacion_up.second = aux_pedidos;

    // Comprobamos si ya existe una clase de asociacion entre Usuario U y Pedido P
    if(enlace_UP.insert(asociacion_up).second == false){
        //Existe una instancia de la clase Asociacion de Usuario
        enlace_UP.at(asociacion_up.first).insert(const_cast<Pedido*>(&pedido));
    }else{
        //Insertamos el nuevo usuario en la clase de asociacion
        enlace_UP.insert(asociacion_up);
    }
}

//Cabecera: void Usuario_Pedido::asocia(const Pedido& P, const Usuario& U)
//Precondicion:
//Postcondicion: Enlazamos un usuario a un pedido
void Usuario_Pedido::asocia(const Pedido& pedido, const Usuario& usuario){
    std::pair<Pedido*, Usuario*> asociacion_pu;
    asociacion_pu.first = const_cast<Pedido*>(&pedido); asociacion_pu.second = const_cast<Usuario*>(&usuario);
    // Realizamos directamente la insercción, porque Num_Pedido es clave primaria de la clase Pedido
    // Es decir no pueden existir dos pedidos con el mismo Num_Pedido
    enlace_PU.insert(asociacion_pu);
}
