#include "register.h"

Register::Register(FileManager* file_manager , const char * Directory )
{

   directory = Directory;
   fileManager = file_manager;

}
void Register :: initRegister(const char * file_name ){


    fileName = file_name;
    size_of_register = fileManager->getSizeOfRegister();

    Buffer = calloc(1,size_of_register );

    ptr_al_anterior = (int*)Buffer;  // coloco el puntero al inicio del registro
    *ptr_al_anterior = NULL_POINTER;



}

void Register :: fill_Register(VectorRelacional<const char* ,  const char *>* campos){
    NodoRelacional<const char* ,  const char *>* temp;
    temp = campos->get_primerNodo();
    campos->get_ultimoNodo()->set_siguiente(NULL);

    for(int x = 0 ;  x < campos->getLength() && temp != NULL ; x++){



        int desplazamiento = 4;     //se cuentan los 4 bytes del puntero al anterior
        Nodo<const char* ,  int , int >* temp_sch; //nodo temp del schema
        temp_sch = fileManager->getSchema().get_primerNodo();
        fileManager->getSchema().get_ultimoNodo()->set_siguiente(NULL);

        for(int i =0 ; (i < fileManager->getSchema().getLength()) && (temp_sch != NULL) ; i++){


            if (*temp->get_elemento1() == *temp_sch->get_elemento1()){// si el nombre de la columna es el mismo

                if(temp_sch->get_elemento2() == fileManager->STRING_ID){ //obtengo el tipo de dato

                    //
                    char* temp_char = (char*)(Buffer + desplazamiento);


                    const char* temp_const_c;
                    temp_const_c = temp->get_elemento2(); // obtengo el const char del arreglo que entra que quiero guardar
                    int b;
                    for(b = 0 ; temp_const_c[b] != '\0'; b++){
                        *(temp_char + b) = temp_const_c[b];
                    }

                    temp_char[b] = '\0';

                 //   cout<<"se guardo: " << temp_char << "  en el desplzamiento: " << desplazamiento <<endl;
                    break;
                    //



                }
                else if(temp_sch->get_elemento2() == fileManager->INT_ID){ //obtengo el tipo de dato

                    int* temp_int = (int*)(Buffer+desplazamiento);

                    *temp_int = atoi(temp->get_elemento2()); //obtengo el entero que quiero guardar

                    //  cout<<"se guardo: " << *temp_int << "  en el desplzamiento: " << desplazamiento <<endl;
                     break;

                }
                else if(temp_sch->get_elemento2() == fileManager->FLOAT_ID){ //obtengo el tipo de dato
                    float* temp_float = (float*)(Buffer + desplazamiento);

                    *temp_float = atof(temp->get_elemento2()); //obtengo el float que quiero guardar
                    //cout<<"se guardo: " << *temp_float << "  en el desplzamiento: " << desplazamiento <<endl;
                    break;
                }
            }
            desplazamiento += temp_sch->get_elemento3();// obtengo el lugar exacto donde se debe guardar los datos

            temp_sch = temp_sch->get_siguiente();
        }

        temp = temp->get_siguiente();
    }




}


bool Register :: isDirty(){
    return dirty;
}
void Register :: setDirty(bool dirt){
    dirty = dirt;
}

void  Register :: saveString(const char* string , const char* nombre_columna,int desplazamiento){


}

void Register :: saveInt(int Int , const char* nombre_columna,int desplazamiento){

}

void Register :: saveFloat(float Float , const char* nombre_columna,int desplazamiento){

}

void Register :: setID(int id){
    regID = id;
}

int Register :: getID(){
    return regID;
}
int Register :: getPtr_al_anterior(){
    return *ptr_al_anterior;
}
void Register :: setPtr_al_anterior(int ptr_anterior){
    *ptr_al_anterior = ptr_anterior;
}
 int Register :: getSizeOfRegister(){
    return size_of_register;
}

 void* Register :: getBuffer(){
     return Buffer;
 }



