

#ifndef VECTORRELACIONAL_H_
#define VECTORRELACIONAL_H_

#include "nodorelacional.h"




#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>



template <class T , class H> class VectorRelacional {
public:


    VectorRelacional()
    {
        this->primerNodo = NULL;
        this->ultimoNodo = NULL;

    }
     /**
      * @brief destructor de ListaEnlazada
      * @param
      * @return
      */

    void imprimir()
    {
        if(estaVacia()){
            cout<<"No hay elementos a imprimir"<<endl;
        }
        else{
            NodoRelacional<T,H>* temporal = NULL;
            temporal = this->primerNodo;
            cout << "[";
            while(temporal != NULL)
            {
                if (temporal != this->ultimoNodo){
                        cout << temporal->get_elemento1()<<"  -  "<<temporal->get_elemento2()<< " , ";
                }
                else{
                    cout << temporal->get_elemento1()<<"   -  "<<temporal->get_elemento2()<<" ]"<<endl;
                }

                temporal = temporal->get_siguiente();

            }

        }
    }

    void  eliminarDelFrente()
    {
        if(estaVacia())
        {
            cout << "La lista se encuentra vacia" << endl;
        }
        else
        {
            this->primerNodo = this->primerNodo->get_siguiente();
        }
        length -=1;
    }
    void eliminarDelFinal()
    {
        NodoRelacional<T,H> *tempo = this->primerNodo;
        if(estaVacia())
        {
            cout << "NO HAY ELEMENTOS EN LA LISTA" << endl;
        }
        else
        {
            while(tempo->get_siguiente() != this->ultimoNodo)
            {
                tempo = tempo->get_siguiente();
            }
            this->ultimoNodo = tempo;
            this->ultimoNodo->set_siguiente(NULL);
        }
        length -= 1;
    }

    void agregarAlFinal(T ele1,H ele2)
    {
        NodoRelacional<T,H>* temp = new NodoRelacional<T,H>(ele1, ele2);
        if (estaVacia())
        {
            this->primerNodo = this->ultimoNodo = temp;
        }
        else
        {
            this->ultimoNodo->set_siguiente(temp);
            this->ultimoNodo = temp;
            this->ultimoNodo->set_siguiente(NULL);
        }
        length += 1;

    }

    void vaciar()
    {
        int x;
        while(this->primerNodo != this->ultimoNodo)
        {
            eliminarDelFinal();
        }
        this->primerNodo = this->ultimoNodo = NULL;
        length = 0;
    }
    bool estaVacia()
    {
        return this->primerNodo == NULL;
    }
    int getLength(){
        return length;
    }

    NodoRelacional<T,H>* get_primerNodo(){
        return this->primerNodo;
    }
    NodoRelacional<T,H>* get_ultimoNodo(){
        return this->ultimoNodo;
    }
protected:

    NodoRelacional<T,H>* primerNodo;
    NodoRelacional<T,H>* ultimoNodo;
    int length=0;
};


#endif // VECTORRELACIONAL_H
