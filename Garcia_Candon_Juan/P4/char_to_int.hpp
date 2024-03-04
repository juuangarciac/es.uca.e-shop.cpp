#include <iostream>

#ifndef _CHAR_TO_INT_
#define _CHAR_TO_INT_
//Cabecera: char_to_int(int v_ascii)
//Precondicion: Dado un valor entero, de la tabla ascii
//Postcondicion: Devuelve el valor entero asociado a dicha posicion
int char_to_int(int v_ascii){
    switch (v_ascii)
    {
        case 48: return 0; break;
        case 49: return 1; break;
        case 50: return 2; break;
        case 51: return 3; break;
        case 52: return 4; break;
        case 53: return 5; break;
        case 54: return 6; break;
        case 55: return 7; break;
        case 56: return 8; break;
        case 57: return 9; break;
        default: return false; break;
    }
}

#endif