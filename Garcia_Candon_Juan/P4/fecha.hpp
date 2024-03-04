
#ifndef _Fecha_H_
#define _Fecha_H_

#include <ctime>
#include <iostream>
#include <string.h>
#include <stdlib.h>


class Fecha{
    public:
     //SUBCLASE INVALIDA
        class Invalida{
            public:
                Invalida(const char* f):excepcion(new char[50]){strcpy(excepcion, f);}
                const char* por_que() const{return excepcion;}
            private:
                char* excepcion;
        };

    //PARAMETROS DE LA CLASE
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;

    //CONSTRUCTORES
        //Apartado a), b), c) y d) -> Constructor Parametrizado, Por defecto
        Fecha(int d = 0, int m = 0, int a = 0);
        //Apartado f) -> Constructor de Conversion
        Fecha(const char* f);

    //OPERADOR DE ASIGNACION
        Fecha& operator =(const Fecha& B);
        
    //OPERADORES DE LA CLASE
        Fecha& operator ++();
        Fecha& operator ++(int);

        Fecha& operator --();
        Fecha& operator --(int);

        Fecha& operator +=(int n);
        Fecha& operator -=(int n);

        friend  Fecha operator +(const Fecha& A, int n);
        friend  Fecha operator -(const Fecha& A, int n);

        friend bool operator ==(const Fecha& A, const Fecha& B);
        friend bool operator != (const Fecha& A, const Fecha& B);

        friend bool operator <(const Fecha& A, const Fecha& B);
        friend bool operator <=(const Fecha& A, const Fecha& B);

        friend bool operator >(const Fecha& A, const Fecha& B);
        friend bool operator >=(const Fecha& A, const Fecha& B); 

    //OBSERVADORAS
        int dia()const{return d;}
        int mes()const{return m;}
        int anno()const{return a;}
    
    //CONVERSOR
        const char* cadena() const;
        friend std::ostream& operator <<(std::ostream& os, const Fecha& A);
        friend std::istream& operator >>(std::istream& is, Fecha& A);

    //DESTRUCTOR
        ~Fecha(){d = 0; m = 0; a = 0;}
    private:
        int d, m, a;

        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
};

//Cabecera:void ValidarFecha(int d,int m,int a);
//Precondicion: Recibe una Fecha
//Postcondicion: Devuelve si esta es válida o No
void ValidarFecha(int d, int m, int a);

//Cabecera:int UltimoDiaMes(int d, int m);
//Precondicion: recibe un dia y un mes validos
//Postcondicion: Devuelve si el dia es el ultimo dia del mes o no
int UltimoDiaMes(int m, int a);


//Cabecera:const char* Dia(int d, int m, int a);
//Precondicion:recibe una fecha
//Postcondicion: devuelve el valor cadena del dia
const char* Dia(int d, int m, int a);


//Cabecera:const char* Mes(int m);
//Precondicion:recibe una fecha
//Postcondicion: devuelve el valor cadena del mes
const char* Mes(int m);

#endif
































/* APUNTES DE LA PRACTICA:
    No se pueden referenciar objetos constantes.

 Las referencias son variables que contienen una dirección de memoria, igual que los punteros 
 (es decir cualquier cambio realizado en dicha direccion de memoria se vera reflejado en la variable que contiene su direccion de memoria). 
 Pero a diferencia de los punteros, 
 las referencias no pueden ser inicializadas a un valor arbitrario y, más importante, se referencian y dereferencian automáticamente: 
 no es necesario usar los operadores unarios * ó &.

 Es decir, la referencia nos permite pasar un objeto por referencia pero mantener la ilusión de que lo estamos pasando por valor.

 "a" -> es un const char
 'a' -> es char

 Para llamar al constructor por defecto, EL QUE NO TIENE PARAMETROS, no hace falta poner el parantesis a la derecha (Nos dara error)

 El mensaje de la excepcion se lanza cuando se captura

 Las conversiones del tipo de nuestra clase a otro cualquiera, se pueden hacer mediante:
    Constructores de Converion
    Funciones de Conversion En este caso devuelve el atributo del objeto que sea del tipo al que queremos realizar la conversion

Añadir la palabra reservada const al final de la declaracion de las funciones MODIFICADORAS.

----------------------------------------------CONVERSION CHAR* A STRING
char *c;
string s="1234";
c=s.c_str();
En el código anterior, el último contenido al que apunta c es basura, porque el objeto s se destruye, su contenido se procesa y el compilador informará un error. El código correcto es el siguiente:

std::string f = (CalcularDiaSemana(d, m, a) + " " + std::to_string(d) + " de " + std::to_string(m) + " de " + std::to_string(a));
//Debemos indicarle el tamaño a la variable char* ya que si no 
char* resp = new char [f.size() + 1];
strcpy(resp, f.c_str());
*/

/* Dudas:
    ¿En caso de poder implementar un constructor tanto fuera como dentro del fichero de la clase, donde es mas recomendable realizar la implemtacion del mismo? Es mejor practica 
    definirla fuera de la clase, ya que es lo mismo hacerlo inline fuera y dentro de la clase. De esta manera cuando el usuario vaya a usar el .h no tiene por que saber nada de la implementacion 
    de los metodos de la clase. <<Si es inline podemos hacerlo pero es mas recomendable fuera>>

        Fecha(const Fecha& f): dia(f.dia), mes(f.mes), anio(f.anio){};
        Fecha(const Fecha& f):{ dia = (f.dia); mes = (f.mes); anio = (f.anio)}; ?  Si la lista de inicializadores es mejor, ya que de la otra forma cuando llamamos al contructor los parametros se inicializan con basura
        y despues le asignamos valores, sin embargo con la lista de inicilizadores inicializamos los parametros de esta con los valores que queremos.
    
    ¿Las funciones auxiliares son recomendables declararlas en la parte privada de la clase? Si, no hace falta que el usuario conozca la parte privada

    No entiendo muy bien el uso de excepciones, estar atento en la clase
    Que diferencia hay entre controlar las excepciones usando, clausulas if y try

    No entiendo por que, en el operador suma no recibe el objeto implicito que realiza la llamada y en los operadores postfijos y prefijos si -> El operador suma y resta tambien recibe 
    El puntero implicito del objeto que hace la llamada. Lo que no entiendo muy bien como.

    ¿Cuando necesito hacer funciones auxiliares que trabajen sobre los parametros privados de una clase, es mejor hacer friend y asi pasar el objeto
    como const Fecha& o hacerlas trabajar sobre los parametros del * this? Yo creo que si, por que alguien que no tenga mucha idea (me incluyo) puede realizar cambios sin darse cuenta dentro de los 
    parametros del objeto sin darse cuenta y liarla un poco parda

    ¿Cuando haces la conversion de un objeto a otro tipo, realmente lo que estas haciendo es cambiando el tipo de los parametros de la clase ?
    */

