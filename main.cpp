#include <iostream>
#include "nodoarbolb.h"
#include "nodoarbolb.cpp"
#include <cstdlib> // malloc() & free()
using namespace std;

NodoArbolB<int>*nodoArbolRaiz = new NodoArbolB<int>();
NodoArbolB<int>* lista[6];
bool explote = false;

void quicksort (NodoArbolB<int>* arreglo, int L, int R){
    int i,j,pivot;
    i = L;
    j = R;    
    pivot = arreglo->getEspecifica((L+R)/2);
    do{
        while(arreglo->getEspecifica(i) < pivot){
            i++;
        }
        while(arreglo->getEspecifica(j) > pivot){
            j--;

        }

        if(i <=j){
            int aux = arreglo->getEspecifica(i);
            arreglo->setEspecifica(i,arreglo->getEspecifica(j));
            arreglo->setEspecifica(j,aux);
            i++;
            j--;
        }
    }
    while(i <= j);
    if (L<j){
        quicksort(arreglo,L,j);
    }
    if (i<R){
        quicksort(arreglo,i,R);
    }

}

bool estaVacia(){
    return  nodoArbolRaiz->estaVacia();
}


void imprimaArbolB(NodoArbolB<int>* impresa){
    //NodoArbolB<int>* n2 = (NodoArbolB<int>*)impresa->get_primeraClave()->getHijosIzq();
    //NodoArbolB<int>* n1 = (NodoArbolB<int>*)impresa->get_primeraClave()->getHijosDer();


    cout << "Raiz: " << endl;
    impresa->imprimir();
    //cout << "Izquierda: " << endl;
    //n2->imprimir();
    //cout << "Derecha: " << endl;
    //n1->imprimir();
    int i=0;
    int valor;
    for(Clave<int>* auxHijo = impresa->get_primeraClave(); auxHijo != NULL; auxHijo = auxHijo->get_siguiente()){
        valor = auxHijo->get_elemento();
        cout<<"-----------------------------------------"<<endl;
        cout<<"la clave es: "<<valor<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"El hijo izquierdo es"<<endl;
        NodoArbolB<int>* hIzq = (NodoArbolB<int>*) auxHijo->getHijosIzq();
        hIzq->imprimir();
        cout<<"-----------------------------------------"<<endl;
        cout<<"El hijo derecho es:"<<endl;
        NodoArbolB<int>* hDer = (NodoArbolB<int>*) auxHijo->getHijosDer();
        hDer->imprimir();
        //nodoArbolRaiz->get_primeraClave()=nodoArbolRaiz->get_primeraClave()->get_siguiente();
    }
}

void ingresarNuevo(int numeNuevo){
    for(Clave<int>* auxClaveNodoRaiz = nodoArbolRaiz->get_primeraClave(); auxClaveNodoRaiz != NULL;
        auxClaveNodoRaiz = auxClaveNodoRaiz->get_siguiente()){
        NodoArbolB<int>* hijoIzquieroDeLaClave = (NodoArbolB<int>*)auxClaveNodoRaiz->getHijosIzq();
        NodoArbolB<int>* hijoDerechoDeLaClave = (NodoArbolB<int>*)auxClaveNodoRaiz->getHijosDer();
        if(auxClaveNodoRaiz->get_elemento() > numeNuevo){
            hijoIzquieroDeLaClave->agregarAlFinal(numeNuevo);
            quicksort(hijoIzquieroDeLaClave, 0 ,hijoIzquieroDeLaClave->getSize()-1);
            break;
        }
        else if(auxClaveNodoRaiz->get_siguiente() != NULL){
            if(auxClaveNodoRaiz->get_elemento() < numeNuevo && auxClaveNodoRaiz->get_siguiente()->get_elemento()
                >=  numeNuevo ){
                hijoDerechoDeLaClave->agregarAlFinal(numeNuevo);
                quicksort(hijoDerechoDeLaClave, 0 ,hijoDerechoDeLaClave->getSize()-1);
                break;
            }
        }
        else{
            hijoDerechoDeLaClave->agregarAlFinal(numeNuevo);
            quicksort(hijoDerechoDeLaClave,0,hijoDerechoDeLaClave->getSize()-1);
            break;
        }
    }
}

void acomodarHijos(NodoArbolB<int>* clave,int ind){
    NodoArbolB<int>* n2 = (NodoArbolB<int>*)clave->get_primeraClave()->getHijosIzq();
    NodoArbolB<int>* n4 = (NodoArbolB<int>*)clave->get_primeraClave()->getHijosDer();
    for(int x = 0; x != clave->getSize(); x++){
        if(x < ind){
            n2->agregarAlFinal(clave->getEspecifica(x));
            clave->get_primeraClave()->setHijosIzq(n2);
        }
        if(x > ind){
            n4->agregarAlFinal(clave->getEspecifica(x));
            clave->get_primeraClave()->setHijosDer(n4);
        }
    }
}

void dividaRaiz(){

    cout << "Clave ordenada: " << endl;
    nodoArbolRaiz->imprimir();
    NodoArbolB<int>* hijosIzq = (NodoArbolB<int>*) malloc(sizeof(NodoArbolB<int>));
    NodoArbolB<int>* hijosDer = (NodoArbolB<int>*) malloc(sizeof(NodoArbolB<int>));
    nodoArbolRaiz->get_primeraClave()->setHijosDer(hijosDer);
    nodoArbolRaiz->get_primeraClave()->setHijosIzq(hijosIzq);

    int valorMitad =  nodoArbolRaiz->getEspecifica( nodoArbolRaiz->getSize()/2);
    acomodarHijos( nodoArbolRaiz, nodoArbolRaiz->getSize()/2);
    Clave<int>* aux = nodoArbolRaiz->get_primeraClave();
    nodoArbolRaiz->vaciar();
    nodoArbolRaiz->agregarAlFinal(valorMitad);
    nodoArbolRaiz->get_primeraClave()->setHijosDer(aux->getHijosDer());
    nodoArbolRaiz->get_primeraClave()->setHijosIzq(aux->getHijosIzq());

    cout<<"hola1"<<endl;
    imprimaArbolB( nodoArbolRaiz);
    cout << "-------------------------------------o------------------------------------------" << endl;
}

void guardarHijosEnLista(NodoArbolB<int>* nodo){
    NodoArbolB<int>* listaDeValoresDeHijos = (NodoArbolB<int>*)malloc(sizeof(NodoArbolB<int>));
    for(Clave<int>* nueva = nodo->get_primeraClave(); nueva != NULL; nueva = nueva->get_siguiente()){
        if(nueva == nodo->get_primeraClave()){
            NodoArbolB<int>* izq = (NodoArbolB<int>*)nueva->getHijosIzq();
            for(Clave<int>* claveHijo = izq->get_primeraClave(); claveHijo != NULL;
                claveHijo = claveHijo->get_siguiente()){

            }
        }
    }
}


void burbuja(NodoArbolB<int>*arreglo){
    int temp;
    for(Clave<int>* auxHijo1 = arreglo->get_primeraClave()->get_siguiente();
        auxHijo1 != NULL; auxHijo1 = auxHijo1->get_siguiente()){
        for(Clave<int>* auxHijo2 = arreglo->get_primeraClave();
            auxHijo2 != arreglo->get_ultimaClave(); auxHijo2 = auxHijo2->get_siguiente()){
            if (auxHijo2->get_elemento() > auxHijo2->get_siguiente()->get_elemento()){
                temp = auxHijo2->get_elemento();
                auxHijo2->set_elemento(auxHijo2->get_siguiente()->get_elemento());
                auxHijo2->get_siguiente()->set_elemento(temp);
            }
        }
    }
}

NodoArbolB<int>** guardar_Nodos(NodoArbolB<int>* nodo){
    //NodoArbolB<int>** lista = new NodoArbolB<int>*;
    int i=2;
    for(Clave<int>* auxHijo = nodo->get_primeraClave(); auxHijo != NULL; auxHijo = auxHijo->get_siguiente()){
        NodoArbolB<int>* hIzq = (NodoArbolB<int>*) auxHijo->getHijosIzq();
        NodoArbolB<int>* hDer = (NodoArbolB<int>*) auxHijo->getHijosDer();
        if (auxHijo==nodo->get_primeraClave()){
            lista[0]=hIzq;
            lista[1]=hDer;
        }
        else {
           lista[i]=hDer;
           i++;
        }
    }
    return lista;
}

void verificarDesbordeDeNodos(){
    if(nodoArbolRaiz->getNumeroDeClaves() == 5){
        cout << "Se desbordo la raiz :O" << endl;
    }
    else{
        NodoArbolB<int>* auxHijosDer;
        NodoArbolB<int>* auxHijosIzq;
        for(Clave<int>* auxClaveNodoRaiz = nodoArbolRaiz->get_primeraClave(); auxClaveNodoRaiz != NULL;
            auxClaveNodoRaiz = auxClaveNodoRaiz->get_siguiente()){
            auxHijosDer = (NodoArbolB<int>*) auxClaveNodoRaiz->getHijosDer();
            auxHijosIzq = (NodoArbolB<int>*) auxClaveNodoRaiz->getHijosIzq();
            if(auxHijosDer->getNumeroDeClaves() == 6){
                cout<<"\n"<<"\n"<<"\n"<<endl;
                cout << "Se desbordo el hijo derecho" << endl;
                NodoArbolB<int>* temp1 = nodoArbolRaiz;
                NodoArbolB<int>* temp2;
                //temp1->get_primeraClave()->setHijosIzq(auxHijosIzq);
                //temp1->get_primeraClave()->setHijosDer(auxHijosDer);
                nodoArbolRaiz = auxHijosDer;
                dividaRaiz();
                temp2=nodoArbolRaiz;
                int valor = nodoArbolRaiz->get_primeraClave()->get_elemento();
                //temp2->get_primeraClave()->setHijosIzq(nodoArbolRaiz->get_primeraClave()->getHijosIzq());
                //temp2->get_primeraClave()->setHijosDer(nodoArbolRaiz->get_primeraClave()->getHijosDer());
                nodoArbolRaiz=temp1;
                nodoArbolRaiz->agregarAlFinal(valor);
                burbuja(nodoArbolRaiz);
                for(Clave<int>* auxHijo = nodoArbolRaiz->get_primeraClave(); auxHijo != NULL;
                    auxHijo = auxHijo->get_siguiente()){
                    cout<<"holaDer1"<<endl;
                    if(auxHijo->get_elemento()==valor){
                        auxHijo->setHijosIzq(temp2->get_primeraClave()->getHijosIzq());
                        auxHijo->setHijosDer(temp2->get_primeraClave()->getHijosDer());
                        if(auxHijo->get_anterior()!=NULL){
                            auxHijo->get_anterior()->setHijosDer(temp2->get_primeraClave()->getHijosIzq());
                        }
                        if(auxHijo->get_siguiente()!=NULL){
                            auxHijo->get_siguiente()->setHijosIzq(temp2->get_primeraClave()->getHijosDer());
                            auxHijo->get_siguiente()->setHijosDer(auxHijosIzq);
                            //puede que esta ultima linea sea (^):
                            //auxHijo->get_siguiente()->setHijosDer(temp1->get_ultimaClave()->getHijosDer());
                        }

                        //break;

                    }
                    else{
                        int i=0;
                        cout<<"holaDer2"<<endl;
                        for(Clave<int>* auxHijo = nodoArbolRaiz->get_primeraClave(); auxHijo != NULL;
                            auxHijo = auxHijo->get_siguiente()){

                            if(auxHijo==nodoArbolRaiz->get_primeraClave()){
                                //auxHijo->setHijosIzq(lista[i]);
                                //auxHijo->setHijosDer(lista[i]);
                            }
                            else{
                                if(auxHijo->get_siguiente()!=NULL){
                                    auxHijo->get_siguiente()->setHijosIzq(auxHijo->getHijosDer());
                                }
                                else{
                                    auxHijo->setHijosDer(lista[i]);
                                }
                            }
                             i++;
                        }
                    }

                }
                cout<<"holaDer3"<<endl;
            }
            if(auxHijosIzq->getNumeroDeClaves() == 6){
                cout<<"\n"<<"\n"<<"\n"<<endl;
                cout << "Se desbordo el hijo izquierdo" << endl;
                NodoArbolB<int>* temp1 = nodoArbolRaiz;
                NodoArbolB<int>* temp2;
                //temp1->get_primeraClave()->setHijosIzq(auxHijosIzq);
                //temp1->get_primeraClave()->setHijosDer(auxHijosDer);
                nodoArbolRaiz = auxHijosIzq;
                dividaRaiz();
                temp2=nodoArbolRaiz;
                int valor = nodoArbolRaiz->get_primeraClave()->get_elemento();
                //temp2->get_primeraClave()->setHijosIzq(nodoArbolRaiz->get_primeraClave()->getHijosIzq());
                //temp2->get_primeraClave()->setHijosDer(nodoArbolRaiz->get_primeraClave()->getHijosDer());
                nodoArbolRaiz=temp1;
                guardar_Nodos(nodoArbolRaiz);
                nodoArbolRaiz->agregarAlFinal(valor);

                burbuja(nodoArbolRaiz);
                for(Clave<int>* auxHijo = nodoArbolRaiz->get_primeraClave(); auxHijo != NULL;
                    auxHijo = auxHijo->get_siguiente()){
                    cout<<"holaIZq1"<<endl;
                    if(auxHijo->get_elemento()==valor){
                        auxHijo->setHijosIzq(temp2->get_primeraClave()->getHijosIzq());
                        auxHijo->setHijosDer(temp2->get_primeraClave()->getHijosDer());
                        if(auxHijo->get_anterior()!=NULL){
                            auxHijo->get_anterior()->setHijosDer(temp2->get_primeraClave()->getHijosIzq());
                        }
                        if(auxHijo->get_siguiente()!=NULL){
                            cout<<"entro"<<endl;

                            auxHijo->get_siguiente()->setHijosIzq(temp2->get_primeraClave()->getHijosDer());
                            auxHijo->get_siguiente()->setHijosDer(auxHijosDer);
                        }
                        //break;
                    }
                    else{
                        int i=0;
                        cout<<"holaIzq2"<<endl;
                        for(Clave<int>* auxHijo = nodoArbolRaiz->get_primeraClave(); auxHijo != NULL;
                            auxHijo = auxHijo->get_siguiente()){

                            if(auxHijo==nodoArbolRaiz->get_primeraClave()){
                                //auxHijo->setHijosIzq(lista[i]);
                                //auxHijo->setHijosDer(lista[i]);
                            }
                            else{
                                if(auxHijo->get_siguiente()!=NULL){
                                    auxHijo->get_siguiente()->setHijosIzq(auxHijo->getHijosDer());
                                }
                                else{
                                    auxHijo->setHijosDer(lista[i]);
                                }
                            }
                             i++;
                        }
                    }
                }
                cout<<"holaIzq3"<<endl;
            }
        }
    }
}

void ingresarDato(int num){
    if (explote){
        ingresarNuevo(num);
        verificarDesbordeDeNodos();
        cout<<"\n"<<"\n"<<"\n"<<endl;
        imprimaArbolB(nodoArbolRaiz);
        cout << "-------------------------------------o------------------------------------------" << endl;
    }
    else if (nodoArbolRaiz->getNumeroDeClaves() == 4 && !explote){
        explote = true;
        nodoArbolRaiz->agregarAlFinal(num);
        quicksort( nodoArbolRaiz, 0 ,  nodoArbolRaiz->getSize()-1);
        dividaRaiz();

    }
    else{
         nodoArbolRaiz->agregarAlFinal(num);
    }
}


int main(){
    /*ListaSimple* l1 = (ListaSimple*) malloc(sizeof(ListaSimple));
    l1->agregarAlFinal(100);
    l1->agregarAlFinal(99);
    l1->agregarAlFinal(100);
    l1->agregarAlFinal(12);
    l1->agregarAlFinal(10);
    quicksort(l1,0,l1->getSize() - 1);
    l1->imprimir();*/
    /*Nodos* nodo = l1->getEspecifica(3);
    l1->setEspecifica(0, nodo);
    l1->imprimir();
    l1->eliminarEspecifica(3);
    cout << "Despues de eliminar" << endl;
    l1->imprimir();
    free(l1);*/

    nodoArbolRaiz->inicializar();
    ingresarDato(76);
    ingresarDato(37);
    ingresarDato(70);
    ingresarDato(78);
    ingresarDato(87);
    ingresarDato(71);

    ingresarDato(107);
    ingresarDato(108);

    ingresarDato(77);
    ingresarDato(86);
    ingresarDato(0);
    ingresarDato(75);
    ingresarDato(90);
    ingresarDato(20);
    ingresarDato(74);
    ingresarDato(99);
    ingresarDato(73);
    ingresarDato(100);
    ingresarDato(102);
    ingresarDato(103);
    ingresarDato(104);

    ingresarDato(105);
    ingresarDato(106);


    /*NodoArbolB<int>* nodo1 = new NodoArbolB<int>();
    for(int x = 0; x != 10; x++){
        nodo1->agregarAlFinal(x);
    }
    nodo1->imprimir();
    Clave<int>* n = new Clave<int>();
    n->set_elemento(5);
    Clave<int>* n1 = new Clave<int>();
    n1->set_elemento(5);
    nodo1->setEspecifica(6,n);
    nodo1->setEspecifica(5,n);
    cout << nodo1->getEspecifica(3)<< endl;
    nodo1->imprimir();*/
    /*NodoArbolB<int>* n1 = new NodoArbolB<int>();
    NodoArbolB<int>* n2 = new NodoArbolB<int>();
    NodoArbolB<int>* n3 = new NodoArbolB<int>();
    NodoArbolB<int>* n4 = new NodoArbolB<int>();
    NodoArbolB<int>* n5 = new NodoArbolB<int>();
    for(int x = 10; x != 21; x++){
        n2->agregarAlFinal(x);
        n3->agregarAlFinal(x + 1);
        n4->agregarAlFinal(x + 2);
        n5->agregarAlFinal(x);
    }
    n1->inicializar();
    n1->ingresarHijosIzq(n2);
    n1->ingresarHijosIzq(n3);
    n1->ingresarHijosIzq(n4);
    n1->ingresarHijosIzq(n5);
    NodoArbolB<int>* n31 = (NodoArbolB<int>*)n1->getHijosIzq()->get_primeraClave()->get_elemento();
    NodoArbolB<int>* n32 = (NodoArbolB<int>*)n1->getHijosIzq()->get_primeraClave()->get_siguiente()->get_elemento();
    NodoArbolB<int>* n33 = (NodoArbolB<int>*)n1->getHijosIzq()->get_primeraClave()->get_siguiente()->get_siguiente()->get_elemento();
    n31->imprimir();
    n32->imprimir();
    n33->imprimir();*/
    /*NodoArbolB<int>* n31 = new NodoArbolB<int>();
    for(int x = 10; x != 20; x++){
        n31->agregarAlFinal(x);
    }
    n31->imprimir();
    n31->setEspecifica(9,3);
    n31->setEspecifica(3,4);
    n31->setEspecifica(5,6);
    n31->setEspecifica(0,9);
    n31->imprimir();*/
    /*Clave<int>* prueba = new Clave<int>();
    NodoArbolB<int>* arbolPrueba = new NodoArbolB<int>();
    for(int x = 0; x != 10; x++){
        arbolPrueba->agregarAlFinal(x);
    }
    arbolPrueba->agregarAlFinal(5);
    prueba->setHijosDer(arbolPrueba);
    NodoArbolB<int>* retornado = (NodoArbolB<int>*)prueba->getHijosDer();
    for(Clave<int>* ne = retornado->get_primeraClave(); ne != NULL; ne = ne->get_siguiente() ){
        cout << ne->get_elemento() << endl;
    }*/

    return 0;
}

