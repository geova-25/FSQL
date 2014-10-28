#ifndef CLAVE_H
#define CLAVE_H

#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "nodoarbolb.h"
using std::string;


template <class T> class Clave {
public:
    Clave();
    virtual ~Clave();
    Clave(T);
    void set_elemento(T);
    T get_elemento();
    void set_siguiente(Clave<T> *);
    Clave<T>* get_siguiente();
    void set_anterior(Clave<T> *);
    Clave<T>* get_anterior();

    void setIndice(int);
    int getIndice();
    void* getHijosIzq();
    void* getHijosDer();
    void setHijosIzq(void*);
    void setHijosDer(void*);
protected:
    void* hijosDer;
    void* hijosIzq;
    T elemento;
    int indice;
    Clave<T>* siguiente_elemento;
    Clave<T>* anterior_elemento;
};

#endif // CLAVE_H
