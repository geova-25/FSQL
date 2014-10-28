#ifndef NODO_H_
#define NODO_H_



#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>
using std::string;


template <class T , class H, class J > class Nodo {
public:
    Nodo()
   {
       this->elemento ;
       this->elemento2;
        this->elemento3;
       this->siguiente_elemento = NULL;

   }

    Nodo(T ele , H ele2, J ele3)
    {
        this->elemento = ele;
        this->elemento2 = ele2;
        this->elemento3 = ele3;
        this->siguiente_elemento = NULL;
    }
    void set_elementos(T nume, H ele2 , J ele3)
    {
        this->elemento = nume;
        this->elemento2 = ele2;
        this->elemento3 = ele3;
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
    J get_elemento3(){
        return elemento3;
    }

    void set_siguiente(Nodo *punt)
    {
        this->siguiente_elemento = punt;
        return;
    }
    Nodo<T,H,J>* get_siguiente()
    {
        return this->siguiente_elemento;
    }
protected:
    T elemento;
    H elemento2;
    J elemento3;

    Nodo<T,H,J>* siguiente_elemento;
    //Nodo * anterior_elemento;
};

#endif /* NODO_H_ */
