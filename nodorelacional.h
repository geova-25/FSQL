#ifndef NODORELACIONAL_H_
#define NODORELACIONAL_H_



#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>
using std::string;


template <class T , class H> class NodoRelacional {
public:
    NodoRelacional()
   {
       this->elemento ;
       this->elemento2;

       this->siguiente_elemento = NULL;

   }

   NodoRelacional(T ele , H ele2)
    {
        this->elemento = ele;
        this->elemento2 = ele2;

        this->siguiente_elemento = NULL;
    }
    void set_elementos(T nume, H ele2 )
    {
        this->elemento = nume;
        this->elemento2 = ele2;

        return;
    }
    T get_elemento1()
    {
        return this->elemento;
    }
    H get_elemento2()
    {
        return this->elemento2;
    }


    void set_siguiente(NodoRelacional *punt)
    {
        this->siguiente_elemento = punt;
        return;
    }
    NodoRelacional<T,H>* get_siguiente()
    {
        return this->siguiente_elemento;
    }
protected:
    T elemento;
    H elemento2;


    NodoRelacional<T,H>* siguiente_elemento;
    //Nodo * anterior_elemento;
};

#endif /* NODO_H_ */
