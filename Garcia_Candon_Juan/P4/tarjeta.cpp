#include "tarjeta.hpp"

/*--------------------------------------------------------------------------------clase Numero--------------------------------------------------------------*/
//Cabecera: bool VerificarTarjeta(const char *numero) 
//Precondicion:
//Postcondicion:
bool VerificarTarjeta(Cadena numero) {
    const Cadena n = numero;
    int digito;
    bool par = false;
    int res = 0;

    for(auto i = 0; i < numero.length(); i++){
        digito = char_to_int(n[i]);
        res += digito;
        if(par){
            res +=digito;
            if(digito > 4) res -= 9;
        }
	par = !(par);
    }
    return !(res % 10);
}

//Cabecera: bool operator <(const Numero& A, const Numero& B)
//Precondicion:
//Postcondicion:
Numero::Numero(Cadena numero):
    numero_(numero)
{
  // remove_if reorganiza el contenedor, de tal manera que todos los elementos que devuelvan true en el predicado, o funcion lambda se almacenen dentro del rango n - numero.end()
  auto n = std::remove_if(numero_.begin(), numero_.end(), [](char c){return isspace(c);});
  
  char* aux = new char[sizeof(numero)];
  int j = 0;
  for(auto i = numero.begin(); i != n; i++){
    aux[j] = numero[j];
    j++;
  }
  Cadena A(aux);
  numero_ = A;
  
  // Comprobamos que todos los caracteres sean digitos
  std::unary_negate<EsDigito>not_EsDigito((EsDigito()));
  n = std::find_if(numero_.begin(), numero_.end(), not_EsDigito);
	if(n != numero_.end())
	  throw(Incorrecto(Razon::DIGITOS));

	// Comprobamos la longitud
	if(numero_.length() <=  13 && numero_.length() >= 19)
	  throw(Incorrecto(Razon::LONGITUD));
	// Comprobamos la validez
	
	if(!luhn(numero_))
	  throw(Incorrecto(Razon::NO_VALIDO));
}

/*--------------------------------------------------------------------------------TARJETA-----------------------------------------------------------*/
//Declaracion del elemento estatico de la clase
std::unordered_set<Numero> Tarjeta::id_tarjetas;

//Cabecera: Tarjeta::Tarjeta(const Numero& num, const Usuario* ti, const Fecha f)
//Precondicion:
//Postcondicion:
Tarjeta::Tarjeta(const Numero& num, const Usuario& ti, const Fecha& f):
  num_tarjeta(num), titular_(&ti), caducidad_(f)
{
    //Comprobamos si ya existe una tarjeta con dicho numero
    if(id_tarjetas.insert(num).second == false){ //PAIR: <Numero, bool>
        //Existe una tarjeta con dicho numero
        throw Num_duplicado(num);
    }else{
        //Comprobamos que la fecha es valida
        Fecha actual;
        if(f < actual){
            throw Fecha::Invalida("La fecha es menor a la actual");
        }else{
            //Registramos la tarjeta 
            activa_ = true;
                //Le asociamos la tarjeta a su usuario titular
               const_cast<Usuario*>(titular_)->es_titular_de(*this);

            //La añadimos al unordered_set
            id_tarjetas.insert(num_tarjeta);
        }
    }
}

//Cabecera: const Tarjeta::Tipo tipo()
//Precondicion:
//Postcondicion:
const Tarjeta::Tipo Tarjeta::tipo() const{
    Cadena num = num_tarjeta.numero_;
    num = num.substr(0, 2);

    if((num[0] == '3' && num[1] == '4') || (num[0] == '3'&& num[1]== '7')){
        return Tipo::AmericanExpress;
    }else if(num[0] == '3'){
        return Tipo::JCB;
    }else if(num[0] == '4'){
        return Tipo::VISA;
    }else if(num[0] == '5'){
        return Tipo::Mastercard;
    }else if(num[0] == '6'){
        return Tipo::Maestro;
    }else{
        return Tipo::Otro;
    }
}

//Cabecera: bool operator <(const Tarjeta& A, const Tarjeta& B)
//Precondicion:
//Postcondicion:
bool operator <(const Tarjeta& A, const Tarjeta& B){
    return(strcmp(A.num_tarjeta, B.num_tarjeta) < 0);
}

//Cabecera: std::ostream& operator <<(std::ostream& os, const Tarjeta& A)
//Precondicion:
//Postcondicion:
std::ostream& operator <<(std::ostream& os, const Tarjeta& A){
    os << A.tipo() << "\n" << A.num_tarjeta << "\n"
            << A.titular() << "\n" << "Caduca: " << A.caducidad() << "\n";
    return os;
}

//Cabecera: Tarjeta::~Tarjeta()
//Precondicion:
//Postcondicion:
Tarjeta::~Tarjeta(){
    //Preparamos el objeto tarjeta para ser destruido
    //Deberemos desacoiar el Usuario de dicha tarjeta
    if(titular_ != NULL){
        const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
        anular_titular();
        id_tarjetas.erase(num_tarjeta); 
    }
}
