#include "fecha.hpp"
//-------------------------------------------------------------------------------------------FUNCIONES AUXILIARES----------------------------------------------------------------------------------------------

void ValidarFecha(int d, int m, int a){
    //Año valido
    if(a >= Fecha::AnnoMinimo && a <= Fecha::AnnoMaximo){
        //Mes valido
        if(m >= 1 && m <= 12){
            //Dia valido
            if(d >= 0 && d <= 31){
                //Año Bisiesto
	      if(((a % 4 == 0) && (a % 100 != 0)) ||(a % 400 == 0)){
                    switch(m){
                        case 2:
                            if(d > 29)
                                throw Fecha::Invalida("No existe dicho dia en el mes introducido");
                            break;
                        case 4:
                        case 6:
                        case 8:
                        case 10:
                        case 12:
                            if(d > 30)
                                throw Fecha::Invalida("No existe dicho dia en el mes introducido");
                            break;
                    }
                }else{
                 //Año No Bisiesto
                     switch(m){
                        case 2:
                            if(d > 28)
                                throw Fecha::Invalida("No existe dicho dia en el mes introducido");
                            break;
                        case 4:
                        case 6:
                        case 8:
                        case 10:
                        case 12:
                            if(d > 30)
                                throw Fecha::Invalida("No existe dicho dia en el mes introducido");
                            break;
                    }
                }  
            }else{
                throw Fecha::Invalida("Dia Fuera de Rango");
            }
        }else{
            throw Fecha::Invalida("Mes Fuera de Rango");
        }
    }else{
        throw Fecha::Invalida("Anno Fuera de Rango");
    }
}

// resp == 0 -> FALSE && resp != 0 -> TRUE
int UltimoDiaMes(int m, int a){
    int resp = 0;
    //Año Bisiesto
    if((a % 4 == 0 && a % 100 != 0) ||(a % 400 == 0)){
        switch(m){
            //Meses Pares
            case 2:resp = 29; break;                      
            case 4:
            case 6:
            case 8:
            case 10:
            case 12:resp = 30; break;
            //Meses Impares
            case 1:
            case 3:
            case 5:
            case 7:
            case 9:
            case 11: resp = 31;break; 
            }
    }else{
    //Año No Bisiesto
        switch(m){
            //Meses Pares
            case 2: resp = 28;break;  
            case 4:
            case 6:
            case 8:
            case 10:
            case 12: resp = 30;break;
            //Meses Impares
            case 1:
            case 3:
            case 5:
            case 7:
            case 9:
            case 11: resp = 31;break;   
        }
    }  
return resp;
}


const char* Dia(int d, int m, int a){
    int regular[]={0,3,3,6,1,4,6,2,5,0,3,5};
    int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6};
    int result1,result2,result3,result4,result5;

    //Es bisiesto
    if((a%4==0) && !(a%100==0))
    {
        m=bisiesto[m-1];
    }
    else if (a%400==0)
    {
        m=bisiesto[m-1];
    }
    else
    {
        m=regular[m-1];
    }

    result1=(a-1)%7;
    result2=(a-1)/4;
    result3=(3*(((a-1)/100)+1))/4;
    result4=(result2-result3)%7;
    result5=d%7;
    d=(result1+result4+m+result5)%7;

    const char* resp = new char[20];
    switch(d){
    case 0:
        resp = "Domingo ";break;
    case 1:
        resp = "Lunes ";break;
    case 2:
        resp = "Martes ";break;
    case 3:
        resp = "Miercoles ";break;
    case 4:
        resp = "Jueves ";break;
    case 5:
        resp = "Viernes ";break;
    case 6:
        resp = "Sabado ";break;
    }  
  return resp;
}


const char* Mes(int m){
    const char* resp = new char[20];
    switch (m)
    {
        case  1 : resp = "Enero";
                  break;
        case  2 : resp = "Febrero";
                  break;
        case  3 : resp = "Marzo";
                  break;
        case  4 : resp = "Abril";
                  break;
        case  5 : resp = "Mayo";
                  break;
        case  6 : resp = "Junio";
                  break;
        case  7 : resp = "Julio";
                  break;
        case  8 : resp = "Agosto";
                  break;
        case  9 : resp = "Septiembre";
                  break;
        case 10 : resp = "Octubre";
                  break;
        case 11 : resp = "Noviembre";
                  break;
        case 12 : resp = "Diciembre";
                  break;
        default : printf( "\n   ERROR: Mes incorrecto." );
    }
    return resp;
}
//--------------------------------------------------------------------------------------------CONSTRUCTORES----------------------------------------------------------------------------------------------------
Fecha::Fecha(int dia, int mes, int anno){
    try{
        if(dia == 0){
            d = tiempo_descompuesto->tm_mday;
        }
        if(mes == 0){
           m = tiempo_descompuesto->tm_mon + 1;
        }
        if(anno == 0){
            a = tiempo_descompuesto->tm_year + 1900;
        }

        ValidarFecha(dia, mes, anno);
        d = dia;
        m = mes;
        a = anno;
    }catch(Fecha::Invalida e){
        e.por_que();
    }
    
}


Fecha::Fecha(const char* f){
    int aux_dia, aux_mes, aux_anno;
    sscanf(f, "%d/%d/%d", &aux_dia, &aux_mes, &aux_anno);

    try{
        if(aux_dia == 0){
            aux_dia = tiempo_descompuesto->tm_mday;
        }
        if(aux_mes == 0){
           aux_mes = tiempo_descompuesto->tm_mon + 1;
        }
        if(aux_anno == 0){
            aux_anno = tiempo_descompuesto->tm_year + 1900;
        }

        ValidarFecha(aux_dia, aux_mes, aux_anno);
        d = aux_dia;
        m = aux_mes;
        a = aux_anno;
    }catch(Fecha::Invalida e){
        e.por_que();
    }
}

//---------------------------------------------------------------------------------Operador de Asignacion--------------------------------------------------------------------------------
Fecha& Fecha::operator=(const Fecha& B){
    //No se comprueba que haya autosignacion ya que no se trabaja con direcciones de memoria en esta clase
    d = B.d;
    m = B.m;
    a = B.a;
    return *this;
}
//---------------------------------------------------------------------------------Operadores de Conversion-------------------------------------------------------------------------------
const char* Fecha::cadena()const{
    char* cad = new char[30];
    
    strcpy(cad, Dia(d, m, a));
    strcat(cad, " ");

    /*Concatenar Dia int */
 
    char* dia = new char[(((sizeof d) * sizeof(char)) + 2)/3 + 2];
    sprintf(dia, "%d", d);
    strcat(cad, dia);

    strcat(cad, " de ");
    strcat(cad, Mes(m));
    strcat(cad, " de ");

    /*Concatenar Año*/
     char* anno = new char[(((sizeof a) * sizeof(char)) + 2)/3 + 2];
    sprintf(anno, "%d", a);
    strcat(cad, anno);


    return cad;
}


std::ostream& operator <<(std::ostream& os, const Fecha& A){
    os << Dia(A.d, A.m, A.a) << " " << A.d << " de " << Mes(A.m) << " de " << A.a;
    return os;
}


std::istream& operator >>(std::istream& is, Fecha& A){
    char c;
    int dia, mes, anno;
    is >> dia >> c >> mes >> c >> anno;

    /*Controlamos el formato de la fecha*/
    try{
        ValidarFecha(dia, mes, anno);
        A.d = dia;
        A.m = mes;
        A.a = anno;
    }catch(Fecha::Invalida e){
        e.por_que();
    }
    
    return is;
}
//--------------------------------------------------------------------------------------Operadores de la Clase-------------------------------------------------------------------------
Fecha& Fecha::operator++(){
    if(d == UltimoDiaMes(m, a)){
        //Ultimo dia del mes
        if(m < 12){
            d = 1;
            m = m + 1;
        }else{
            //Ultimo dia del año
            d = 1;
            m = 1;
            if(a < Fecha::AnnoMaximo){
                a = a + 1;
            }else{
                throw Fecha::Invalida("El año se sale del rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        d = d + 1;
    }
    return *this;
}

Fecha& Fecha::operator++(int){
    if( d == UltimoDiaMes(m, a)){
        //Ultimo dia del mes
        if(m < 12){
            d = 1;
            m = m + 1;
        }else{
            //Ultimo dia del año
            d = 1;
            m = 1;
            if(a < Fecha::AnnoMaximo){
                a = a + 1;
            }else{
                throw Fecha::Invalida("El año se sale del rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        d = d + 1;
    }
    return *this;
}


Fecha& Fecha::operator--(){
      if(d == 1){
        //Primer dia del mes
        if(m > 1){
            m = m - 1;
            d = UltimoDiaMes(m, a);
        }else{
            //Primer dia del Primer Mes
            d = 31;
            m = 12;
            if(a > Fecha::AnnoMinimo){
                a = a-1;
            }else{
                throw Invalida("El año se sale de rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        d = d - 1;
    }
      return *this;
}

Fecha& Fecha::operator--(int){
      if(d == 1){
        //Primer dia del mes
        if(m > 1){
            m = m - 1;
            d = UltimoDiaMes(m, a);
        }else{
            //Primer dia del Primer Mes
            d = 31;
            m = 12;
            if(a > Fecha::AnnoMinimo){
                a = a-1;
            }else{
                throw Invalida("El año se sale de rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        d = d - 1;
    }
      return *this;
}


Fecha operator +(const Fecha& B, int n){
     Fecha A(B);
  
     if(A.d + n >= UltimoDiaMes(A.m, A.a)){
        //Ultimo dia del mes
        if(A.m < 12){
            A.d =  (A.d + n) - UltimoDiaMes(A.m, A.a);
            A.m = A.m + 1;
        }else{
            //Ultimo dia del año
            A.d = (A.d + n) - UltimoDiaMes(A.m, A.a);;
            A.m = 1;
            if(A.a < Fecha::AnnoMaximo){
                A.a = A.a + 1;
            }else{
                throw Fecha::Invalida("El año se sale del rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        A.d = A.d + n;
    }
     return A;
}

Fecha operator -(const Fecha& B, int n){
     Fecha A(B);
  
     if(A.d - n <= 1){
        //Ultimo dia del mes
        if(A.m > 1){
            A.d = UltimoDiaMes(A.m, A.a) - (n - A.d);
            A.m = A.m - 1;
        }else{
            //Ultimo dia del año
            A.d = UltimoDiaMes(A.m, A.a) - (n - A.d);
            A.m = 1;
            if(A.a > Fecha::AnnoMinimo){
                A.a = A.a - 1;
            }else{
                throw Fecha::Invalida("El año se sale del rango");
            }
        }
    }else{
        //Un dia cualquiera que no sea el ultimo del mes
        A.d = A.d - n;
    }
     return A;
}

Fecha& Fecha::operator +=(int n){
  *this = *this + n;
  return *this;
}

Fecha& Fecha::operator -=(int n){
  *this = *this - n;
  return *this;
}
  
bool operator ==(const Fecha& A, const Fecha& B){
    return (A.d == B.d) && (A.m == B.m) && (A.a == B.a);
}

bool operator <(const Fecha& A, const Fecha& B){
    bool ret;
    if(A.a == B.a){
        if(A.m == B.m){
            ret = A.d < B.d;
        }else{
            ret = A.m < B.m;
        }
    }else{
        ret = A.a < B.a;
    }
    return ret;
}

bool operator !=(const Fecha& A, const Fecha& B){
  return !(A == B);
}


bool operator <=(const Fecha& A, const Fecha& B){
  return A < B || A == B;
}



bool operator >(const Fecha& A, const Fecha& B){
     bool ret;
    if(A.a == B.a){
        if(A.m == B.m){
            ret = A.d > B.d;
        }else{
            ret = A.m > B.m;
        }
    }else{
        ret = A.a > B.a;
    }
    return ret;
}

bool operator >=(const Fecha& A, const Fecha& B){
  return A > B || A == B;
}
//----------------------------------------------------------------------------------------MAIN-----------------------------------------------------------------------------------------------------------------
