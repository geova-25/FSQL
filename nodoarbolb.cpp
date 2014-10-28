#include "nodoarbolb.h"

#include "clave.h"

#include<iostream>


using namespace std;

/**
 * @brief Constructor de NodoArbolB
 * @param
 * @return
 */

template <class T>
 NodoArbolB<T> :: NodoArbolB()
{
    this->counter = 0;
    this->counterIndice = 0;
    this->primerNodo = NULL;
    this->ultimoNodo = NULL;
}

template <class T>
 void NodoArbolB<T> :: inicializar()
{
    this->primerNodo = NULL;
    this->ultimoNodo = NULL;

}
 /**
  * @brief destructor de NodoArbolB
  * @param
  * @return
  */


template <class T>
void NodoArbolB<T> :: setEspecifica(int indice, T ingresado){
     NodoArbolB<T>* ltemp = new NodoArbolB<T>();
     int x = 0;
     for(Clave<T>* n = this->primerNodo; n != NULL; n = n->get_siguiente()){
         if(n->getIndice() == indice){
             ltemp->agregarAlFinal(ingresado);
             x++;
         }
         else{
             ltemp->agregarAlFinal(this->getEspecifica(x));
             x++;
         }
     }
     this->primerNodo = ltemp->get_primeraClave();
     this->ultimoNodo = ltemp->get_ultimaClave();
 }


template <class T>
NodoArbolB<T> ::~NodoArbolB() {
    // TODO Auto-generated destructor stub
}


/**
 * @brief imprime la ListaEnlazada
 * @param
 * @return
 */

template <class T>
 T NodoArbolB<T> :: getEspecifica(int indice){
     for(Clave<T>* n = primerNodo; n != NULL; n = n->get_siguiente()){
         if(n->getIndice() == indice){
             return n->get_elemento();
         }
     }
}

template <class T>
void NodoArbolB<T> :: imprimir()
{
    if(estaVacia()){
        cout<<"No hay elementos a imprimir"<<endl;
    }
    else{        
        Clave<T>* temporal = NULL;
        temporal = this->primerNodo;        
        cout << "[";
        while(temporal != NULL)
        {
            if (temporal != ultimoNodo){
                cout << temporal->get_elemento() <<" , ";
            }
            else{
                cout << temporal->get_elemento() << "]"<<endl;
            }

            temporal = temporal->get_siguiente();
        }        
    }
}

/**
 * @brief Retorna true si la ListaEnlazada esta vacia
 * @param
 * @return bool
 */
template <class T>
bool NodoArbolB<T> :: estaVacia()
{
    return this->primerNodo == NULL;
}

/**
 * @brief agrega al final de la lista un nodo
 * @param T num
 * @return void
 */
template <class T>
void  NodoArbolB<T> :: agregarAlFinal(T num)
{
    counter ++;
    Clave<T>* temp = new Clave<T>(num);    
    temp->setIndice(counterIndice);
    counterIndice++;
    if (estaVacia())
    {                
        this->primerNodo = this->ultimoNodo = temp;        
    }
    else
    {
        this->ultimoNodo->set_siguiente(temp);
        temp->set_anterior(ultimoNodo);
        this->ultimoNodo = temp;
        this->ultimoNodo->set_siguiente(NULL);
    }


}

/**
 * @brief elimina el ultimo nodo de la ListaEnlazada
 * @param
 * @return void
 */
template <class T>
void  NodoArbolB<T> :: eliminarDelFinal()
{
    Clave<T> *tempo = this->primerNodo;
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
}

/**
 * @param Elimina el primer nodo de la ListaEnlazada
 * @return void
 */
template <class T>
void  NodoArbolB<T> :: eliminarDelFrente()
{
    if(estaVacia())
    {
        cout << "La lista se encuentra vacia" << endl;
    }
    else
    {
        this->primerNodo = this->primerNodo->get_siguiente();
        this->primerNodo->set_anterior(NULL);
    }
}
/**
 * @brief Vacia la ListaEnlazada
 * @param
 * @return void
 */
template <class T>
void   NodoArbolB<T> :: vaciar()
{
    while(this->primerNodo != this->ultimoNodo)
    {
        eliminarDelFinal();
    }
    this->primerNodo = this->ultimoNodo = NULL;
    this->counter = 0;
    this->counterIndice = 0;
}
/**
 * @brief obtiene el primer nodo de la ListaEnlazada
 * @param
 * @return Nodo<T>* primeroNodo
 */
template <class T>
Clave<T>*  NodoArbolB<T> ::get_primeraClave(){
    return this->primerNodo;
}

template <class T>
Clave<T>*  NodoArbolB<T> ::get_ultimaClave(){
    return this->ultimoNodo;
}

template <class T>
int NodoArbolB<T> :: getSize(){
    return this->counter;
}

template <class T>
int NodoArbolB<T> :: getNumeroDeClaves(){
    return this->counter;
}


