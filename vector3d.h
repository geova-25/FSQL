#ifndef VECTORRELACIONAL_H_
#define VECTOR_H_

#include "nodo3d.h"




#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>



template <class T , class H , class J> class Vector3d {
public:


    Vector3d()
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
            Nodo3d<T,H,J>* temporal = NULL;
            temporal = this->primerNodo;
            cout << "[";
            while(temporal != NULL)
            {
                if (temporal != this->ultimoNodo){
                        cout << temporal->get_elemento1()<<"  -  "<<temporal->get_elemento2()<<" -  "<<temporal->get_elemento3()<<" , ";
                }
                else{
                    cout << temporal->get_elemento1()<<"   -  "<<temporal->get_elemento2()<<" -  "<<temporal->get_elemento3()<<" ]"<<endl;
                }

                temporal = temporal->get_siguiente();

            }

        }
    }
    void imprimirFirstRow()
    {
        int tamanio_chars = sumatoria_de_elementos3();
        for(int n =0 ; n< tamanio_chars;n++){
            cout<<"_";
        }
        cout<<endl;

        if(estaVacia()){
            cout<<"No hay elementos a imprimir"<<endl;
        }
        else{
            Nodo3d<T,H,J>* temporal = NULL;
            temporal = this->primerNodo;
            cout << "|";
            while(temporal != NULL)
            {
                if (temporal != this->ultimoNodo){
                        cout << temporal->get_elemento1();
                        for(int b=0 ;b<(temporal->get_elemento3()-get_tamanio(temporal->get_elemento1())-1); b++){
                            cout<<" ";
                        }
                        cout<<"|";
                }
                else{
                    cout << temporal->get_elemento1();
                    for(int b=0 ;b<(temporal->get_elemento3()-get_tamanio(temporal->get_elemento1())-1); b++){
                        cout<<" ";
                    }
                    cout<<"|"<<endl;
                }

                temporal = temporal->get_siguiente();

            }

        }
        for(int n =0 ; n< tamanio_chars;n++){
            cout<<"_";
        }
        cout<<endl;
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
        Nodo3d<T,H,J> *tempo = this->primerNodo;
        if(estaVacia())
        {
            cout << "NO HAY ELEMENTOS EN LA LISTA" << endl;
        }
        else if(length == 1){
            primerNodo = NULL;
            ultimoNodo = primerNodo;
            length = 0;
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

    void agregarAlFinal(T ele1,H ele2, J ele3)
    {
        Nodo3d<T,H,J>* temp = new Nodo3d<T,H,J>(ele1, ele2, ele3 );
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

    Nodo3d<T,H,J>* get_primerNodo(){
        return this->primerNodo;
    }
    Nodo3d<T,H,J>* get_ultimoNodo(){
        return this->ultimoNodo;
    }
    int sumatoria_de_elementos3(){
        if(estaVacia()){
            cout<<"No hay elementos a imprimir"<<endl;
        }
        else{
            Nodo3d<T,H,J>* temporal = NULL;
            temporal = this->primerNodo;
           this->ultimoNodo->set_siguiente(NULL);
            int suma=0;
            while(temporal != NULL) {
                suma+= temporal->get_elemento3();

                temporal = temporal->get_siguiente();


            }
             return suma;

        }

    }
private:


    Nodo3d<T,H,J>* primerNodo;
    Nodo3d<T,H,J>* ultimoNodo;
    int length=0;

    int get_tamanio(const char* string){
        int tam;
        for(tam = 0; string[tam] !='\0'  ; tam++){
        }
        return tam;
    }

};

#endif /* LISTAENLAZADA_H_ */
