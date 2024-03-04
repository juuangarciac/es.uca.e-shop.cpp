#include "usuario.hpp"

//-----------------------------------------------------------------------------------------------------------CLASE CLAVE---------------------------------------------------------------------------------------
//Cabecera: char* Clave::encriptar(char* cadena)
//Precondicion:
//Postcondicion:
const char* Clave::encriptar(const char* cadena){
     //Pasamos a codificar la cadena
    static char caracteres[65]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/."};
    static std::random_device gen;
    static std::uniform_int_distribution<std::size_t> dist(0, 63);

    int a{};
    char sal[3]{};
    int i{0};

    while(i < 2){
        a = dist(gen);
        sal[i] = caracteres[a];
        i++;
    }

    char* ret = crypt(cadena, sal); 
    return ret;
}


//Cabecera: Clave::Clave(char* contraseña)
//Precondicion:
//Postcondicion:
Clave::Clave(const char* contraseña){
   if(strlen(contraseña) < 5){
     throw Clave::Incorrecta(Clave::Razon::CORTA);
   }

   contrasena_ = encriptar(contraseña);
}

//Cabecera: bool Clave::verifica(char* Cadena)
//Precondicion:
//Postcondicion:
bool Clave::verifica(const char* Cadena){
    return contrasena_ == encriptar(Cadena);
}

//------------------------------------------------------------------------------------------------ CLASE USUARIO ----------------------------------------------------------------------------------------------
//Cabecera:std:: std::unordered_set<Cadena> Usuario::id_Usuarios; 
std::unordered_set<Cadena> Usuario::id_Usuarios; 

//Cabecera: Usuario(Cadena identificador, Cadena nombre, Cadena apellidos, Cadena dir, Clave contraseña)
//Precondicion:
//Postcondicion:
Usuario::Usuario(Cadena identificador, Cadena nombre, Cadena apellidos, Cadena dir, Clave contrasena):
  identificador_(identificador), nombre_(nombre), apellidos_(apellidos), dir_(dir), contrasena_(contrasena)
{
    //Comprobamos si el usuario es repetido
    if(id_Usuarios.insert(identificador).second == false){
        //El usuario es repetido
        throw Id_duplicado(identificador);
    }else{
        //Insertamos el id en el unordened_Set
        id_Usuarios.insert(identificador);
    }
}


// Relacion de Asociacion entre Usuario_Tarjeta

//Cabecera: void Usuario::_es_titular_de(Tarjeta& tarjeta)
//Precondicion:
//Postcondicion:
void Usuario::es_titular_de(const Tarjeta& tarjeta){
    //Si la tarjeta no existe en <<tarjetas_pago>>
    //  la insertamos
    std::pair <Numero, Tarjeta*> new_tarjeta = std::make_pair(tarjeta.numero(), const_cast<Tarjeta*>(&tarjeta));;

    if(tarjetas_pago.insert(new_tarjeta).second == false){
        //La tarjeta existe
        throw Tarjeta::Num_duplicado(tarjeta.numero());
    }else{
        //Registramos la Tarjeta
        if(tarjeta.titular() == this)
        tarjetas_pago.insert(new_tarjeta);
            //Ojo en la clase tarjeta deberemos de asociar la tarjeta a dicho usuario
    }
}

//Cabecera: void Usuario::no_es_titular_de(Tarjeta& tarjeta)
//Precondicion:
//Postcondicion:
void Usuario::no_es_titular_de(const Tarjeta& tarjeta){
    // Debemos comprobar que la tarjeta existe
    // y que dicha tarjeta tiene asociado como titular el usuario actual
    Numero new_tarjeta = tarjeta.numero();
        tarjetas_pago.erase(new_tarjeta);
}


//Relacion de Asociacion: Usuario_Compra

//Cabecera: void Usuario::compra(Articulo& art, int cantidad = 1);
//Precondicion:
//Postcondicion:
void Usuario::compra(Articulo& art, int cantidad){
    //Comprobamos la cantidad
    // para saber si el usuario quiere eliminar o añadir al carrito
    if(cantidad == 0){
        //Eliminamos el articulo del carrito
        carrito.erase(const_cast<Articulo*>(&art));
    }else{
        // Comprobamos si dicho articulo ya esta en el carrito
        std::pair <Articulo*, int > new_articulo;
        new_articulo.first = const_cast<Articulo*>(&art); new_articulo.second = cantidad;
        if(carrito.insert(new_articulo).second == false){
            //El articulo ya esta en la cesta, por lo que actualizamos la cantidad
            carrito.at(new_articulo.first) += new_articulo.second;
        }else{
            // El articulo no esta registrado en la cesta, por lo que lo insertamos
            carrito.insert(new_articulo);
        }
    }
}

//Cabecera: int Usuario::n_articulos()
//Precondicion:
//Postcondicion: devuelve el numero de articulos del carrito
const int Usuario::n_articulos()const{
    return carrito.size();
}

//Cabecera: std::ostream& operator <<(std::ostream& os, const Usuario& A)
//Precondicion:
//Postcondicion: devuelve el numero de articulos del carrito
std::ostream& operator <<(std::ostream& os, const Usuario& A){
    os << A.identificador_ << " [" << A.contrasena_.clave() << "] " << A.nombre_ << " " << A.apellidos_ << "\n"
            << A.dir_ << "\n"
            << "Tarjetas: " << "\n ";

    const Usuario::Tarjetas Tarjetas_A = A.tarjetas();
    for(Usuario::Tarjetas::const_iterator i = Tarjetas_A.begin(); i != Tarjetas_A.end(); i++){
       os << i->second;
    }
    return os;
}


//Cabecera: void mostrar_carro(const Usuario& U, const Articulo& carro)
//Precondicion:
//Postcondicion: 
void mostrar_carro(std::ostream& o, const Usuario& U){
  o << "Carrito de compra de " << U.id() << " [Articulos: " << U.n_articulos() << "] " << "\n"
    << "Cant. " << "Articulo" << "\n";
    o << "======================================================================================" << " \n";
    const Usuario::Articulos Articulos_U = U.compra();
    //Bucle para Imprimir los articulos del carrito
    for(Usuario::Articulos::const_iterator i = Articulos_U.begin(); i != Articulos_U.end(); i++){
        std::cout << i->second << " " << "[" << i->first->referencia() << "] "  << "'" << i->first->titulo() << "' "<< i->first->f_publi() << ", " <<  i->first->precio() << " \n" ;
    }
}


//Cabecera: ~Usuario()
//Precondicion:
//Postcondicion: 
Usuario::~Usuario(){
    contrasena_.~Clave();
    //Vaciamos todos los diccionarios
        //Desasociamos las tarjetas del usuario
        for(Usuario::Tarjetas::const_iterator i = tarjetas_pago.begin(); i != tarjetas_pago.end(); i++){
            tarjetas_pago.erase(i->first);
                i->second->anular_titular(); //anular_titular()
        }
        //Vaciamos el carro de la compra
        for(Usuario::Articulos::const_iterator i = carrito.begin(); i != carrito.end(); i++){
            carrito.erase(i->first);
        }
    //Eliminamos el identificador_ de id_Usuarios
    id_Usuarios.erase(identificador_);
}
//---------------------------------------------------------------MAIN------------------------------------------------------------------

//---------------------------------------------------------------------------Apuntes de la P2---------------------------------------------------------

//const_iterator Describe un objeto que puede actuar como un iterador constante de la secuencia controlada.
int main()
{
    Clave c("Juan");
    std::cout << c.verifica("Juan");
    return 0;
}