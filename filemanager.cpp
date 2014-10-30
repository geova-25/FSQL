#include "filemanager.h"

FileManager :: FileManager( const char* Directory)
{
    directory = Directory;
}
void FileManager :: generate_binaryFile(){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    ofstream fe(FileNameBin); //Creamos un archivo bin nuevo para una tabla nueva si no existe
    fe.close();
}

void FileManager :: initHeader(){

    header_buffer = calloc(1,sizeOfHeader);

    nameOfFile = (char*)header_buffer;
    sizeOfFile = (int*)(header_buffer + TABLESIZE);
    numberOfRegisters  = (int*)(header_buffer + 34);
    numberOfFreeRegisters  = (int*)(header_buffer + 38);
    ptrOfFirstRegister  = (int*)(header_buffer + 42);
    ptrToLastRegister  = (int*)(header_buffer + 46);
    ptrToFirstRegisterFree  = (int*)(header_buffer + 50);
    sizeOfRegister  = (int*)(header_buffer + 54);
    numberOfColumns  = (int*)(header_buffer + 58 );

    *nameOfFile =  ' n' ;
    *sizeOfFile = sizeOfHeader;
    *numberOfRegisters = 0;
    *numberOfFreeRegisters = 0 ;
    *ptrOfFirstRegister = nullPosition;
    *ptrToLastRegister = nullPosition;
    *ptrToFirstRegisterFree = nullPosition;
    *sizeOfRegister = 0;
    *numberOfColumns = 0;
}

void FileManager :: saveHeader(){

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
     if (fs){
         int temp = fs.tellp();
         fs.seekp (0, ios::beg);
         fs.write(reinterpret_cast<const char*>(header_buffer),sizeOfHeader);
         fs.seekp(temp, ios::beg);
         fs.close();
     }
     else cout<<"archivo no existe"<<endl;
}

void FileManager :: loadHeader(const char * name_of_file){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(name_of_file) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        int temp = fsr.tellg();
        fsr.seekg(0,ios::beg);
        fsr.read((char*)header_buffer, sizeOfHeader);

        nameOfFile = (char*)(header_buffer) ;
        sizeOfFile =(int*)(header_buffer+ TABLESIZE);
        numberOfRegisters = (int*)(header_buffer+34);
        numberOfFreeRegisters = (int*)(header_buffer+38);
        ptrOfFirstRegister = (int*)(header_buffer+42);
        ptrToLastRegister = (int*)(header_buffer+46);
        ptrToFirstRegisterFree = (int*)(header_buffer+50);
        sizeOfRegister = (int*)(header_buffer+54);
        numberOfColumns = (int*)(header_buffer+58);


        fsr.seekg(temp,ios::beg);
    }
    else{
        cout<<"Error 001 : El archivo seleccionado no existe"<<endl;    }

   fsr.close();
}

void FileManager :: closeFile(){
    free(fileBuffer);
}

void FileManager :: saveFile(){
    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
     if (fs){
         int temp = fs.tellp();
         fs.seekp (sizeOfHeader, ios::beg);
         fs.write(reinterpret_cast<const char*>(fileBuffer),*sizeOfFile - sizeOfHeader);
         fs.seekp(temp, ios::beg);
         fs.close();
     }
     else cout<<"archivo no existe"<<endl;

}


int* FileManager :: where(Vector3d<const char*,const char*,const char*>* condiciones , VectorRelacional<const char*,int>*op_logic){
    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo

    int* accepted_rows = new int[*numberOfRegisters];
    //por cada registro
    for(int num_row = 0; num_row < *numberOfRegisters ; num_row++){
        temp_register = (fileBuffer + (*sizeOfRegister*num_row)) ;//buffer temporal para recorrer de registro en registro
        bool* bools = new bool[condiciones->getLength()];

        Nodo3d<const char*,const char*,const char*>* nodo_temp;
        nodo_temp = condiciones->get_primerNodo();
        condiciones->get_ultimoNodo()->set_siguiente(NULL);

        for(int r=0 ; r< condiciones->getLength() ; r++){
           // cout<<"condicion :"<<r<<endl;
            //cout<<cumpleCondicion(nodo_temp->get_elemento1(),nodo_temp->get_elemento2(),nodo_temp->get_elemento3(),temp_register)<<endl;
            bools[r] = cumpleCondicion(nodo_temp->get_elemento1(),nodo_temp->get_elemento2(),nodo_temp->get_elemento3(),temp_register);

            nodo_temp = nodo_temp->get_siguiente();
        }
        bool final_bool;

        if(condiciones->getLength() > 1){
            //ciclo para determinar si un registro cumple condiciones

            NodoRelacional<const char*,int>* _temp;
            _temp = op_logic->get_primerNodo();
            op_logic->get_ultimoNodo()->set_siguiente(NULL);

             bool primera_vez=true;
            for(int f=0 ; f< op_logic->getLength() ; f++){

                if(compare_strings(_temp->get_elemento1(),"AND") && primera_vez){
                    final_bool = bools[f] && bools[f+1];
                    primera_vez=false;
                }
                if(compare_strings(_temp->get_elemento1(),"OR")&& primera_vez){
                    final_bool = bools[f] || bools[f+1];
                    primera_vez=false;
                }
                if(compare_strings(_temp->get_elemento1(),"AND") && !primera_vez){
                    final_bool = final_bool && bools[f+1];

                }
                if(compare_strings(_temp->get_elemento1(),"OR")&& !primera_vez){
                    final_bool = final_bool || bools[f+1];

                }
                _temp = _temp->get_siguiente();
            }//termna cilco de verificar cond*/


        }
        else{
            final_bool = bools[0];
        }


        if(final_bool){//si cumple las condiciones que retorne el numero de fila
           // cout<<"cumplio para columna : " <<num_row<<endl;
            accepted_rows[num_row] = num_row;
        }
        else{accepted_rows[num_row] =-1;}

    }
    return accepted_rows;

}
bool FileManager :: cumpleCondicion(const char* columna,const char* operador , const char* campo,void* temp_register){
        int desplazamiento =   4;     //se cuentan los 4 bytes del puntero al anterior
        Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
        temp_sch = schema.get_primerNodo();
        schema.get_ultimoNodo()->set_siguiente(NULL);
        for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
            if(compare_strings(columna,temp_sch->get_elemento1())){//para saber cual es la columna

                if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato comparar
                   // cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                    char* temp_char = (char*)(temp_register + desplazamiento);
                    std::string result = std::string(temp_char);
                    const char* temp_const= result.c_str();
                    if(compare_strings(temp_const,campo)){
                      //  cout<<"iguales "<<temp_char<<"  "  << campo<<endl;
                        return true;
                    }
                }
                else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato comparar

                    if(*(int*)(temp_register + desplazamiento) == atoi(campo)){
                        //cout<<"iguales "<<*(int*)(temp_register + desplazamiento)   <<"  "<< campo<<endl;
                        return true;
                    }
                }
                else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato comparar

                    if(*(float*)(temp_register + desplazamiento) == atof(campo)){
                      //  cout<<"iguales "<<*(float*)(temp_register + desplazamiento)   <<" "<< campo<<endl;
                        return true;
                    }


                }
            }
            if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}
            if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
            if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
            temp_sch = temp_sch->get_siguiente();
   }
        return false;

}

void FileManager :: printSelect(const char* columna ,int num_fila){
    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo
    for(int num_row = 0; num_row < *numberOfRegisters ; num_row++){
        if(num_row == num_fila){
            temp_register = (fileBuffer + (*sizeOfRegister*num_row)) ;//buffer temporal para recorrer de registro en registro
            int desplazamiento =   4;     //se cuentan los 4 bytes del puntero al anterior
            Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
            temp_sch = schema.get_primerNodo();
            schema.get_ultimoNodo()->set_siguiente(NULL);

            for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
                if(compare_strings(columna,temp_sch->get_elemento1())){//para saber cual es la columna
                    if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                    }
                    else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                    }
                    else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato guardar
                        cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                    }
                }
                if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}
                if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                temp_sch = temp_sch->get_siguiente();
            }
        }
    }

}
void FileManager :: setCampo(const char* columna , const char* campo,int num_fila){

    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo

    for(int num_row = 0; num_row < *numberOfRegisters ; num_row++){
        if(num_row == num_fila){
            temp_register = (fileBuffer + (*sizeOfRegister*num_row)) ;//buffer temporal para recorrer de registro en registro

            int desplazamiento =   4;     //se cuentan los 4 bytes del puntero al anterior
            Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
            temp_sch = schema.get_primerNodo();
            schema.get_ultimoNodo()->set_siguiente(NULL);

            for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){  //se recorre el schema
                if(compare_strings(columna,temp_sch->get_elemento1())){//para saber cual es la columna

                    if( temp_sch->get_elemento2() == STRING_ID){ //saber que tipo de dato guardar
                       // cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                        char* temp_char = (char*)(temp_register + desplazamiento);
                        int b;
                        for(b = 0 ; campo[b] != '\0'; b++){
                            *(temp_char + b) = campo[b];
                        }
                        temp_char[b] = '\0';

                    }
                    else if( temp_sch->get_elemento2() == INT_ID){ //saber que tipo de dato guardar

                       // cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                        *(int*)(temp_register + desplazamiento)=atoi(campo);


                    }
                    else if( temp_sch->get_elemento2() == FLOAT_ID){ //saber que tipo de dato guardar
                        //cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                        *(float*)(temp_register + desplazamiento)=atof(campo);


                    }
                }
                if(temp_sch->get_elemento2() == STRING_ID){ desplazamiento += temp_sch->get_elemento3();}
                if(temp_sch->get_elemento2() == INT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                if(temp_sch->get_elemento2() == FLOAT_ID){desplazamiento += BYTES_4;}// obtengo el lugar exacto donde se debe guardar los datos
                temp_sch = temp_sch->get_siguiente();
            }
        }
    }

}
void FileManager :: openFile(){
    fileBuffer = (char*)calloc(1,getSizeOfFile()-sizeOfHeader);



    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(getNameOfFile()) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        int temp = fsr.tellg();
        fsr.seekg(sizeOfHeader,ios::beg);
        fsr.read((char*)fileBuffer,getSizeOfFile()-sizeOfHeader );

        fsr.seekg(temp,ios::beg);
    }
    else{
        cout<<"no hay archivo"<<endl;    }

   fsr.close();
}

void FileManager :: printFile(){

   char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo

   cout<<"____________________________select * From  "<<nameOfFile << "______________________________"<<endl;
   //schema.imprimirFirstRow();

   for(int num_row = 0; num_row < *numberOfRegisters ; num_row++){
       temp_register = (fileBuffer + (*sizeOfRegister*num_row)) ;//buffer temporal para recorrer de registro en registro
       cout<<"_____________________________row : "<<num_row << "______________________________"<<endl;
       int desplazamiento =   4;     //se cuentan los 4 bytes del puntero al anterior
       Nodo3d<const char* ,  int , int >* temp_sch; //nodo temp del schema
       temp_sch = schema.get_primerNodo();
       schema.get_ultimoNodo()->set_siguiente(NULL);
       cout<<"puntero al anterior : "<<*(int*)(temp_register)<<endl;
       for(int i =0 ; schema.getLength() && (temp_sch != NULL) ; i++){

               if(temp_sch->get_elemento2() == STRING_ID){ //obtengo el tipo de dato

                   cout<<temp_sch->get_elemento1()<<" : "<<(char*)(temp_register + desplazamiento)<<endl;
                   desplazamiento += temp_sch->get_elemento3();// obtengo el lugar exacto donde se debe guardar los datos

               }
                else if(temp_sch->get_elemento2() == INT_ID){ //obtengo el tipo de dato

                   cout<<temp_sch->get_elemento1()<<" : "<<*(int*)(temp_register + desplazamiento)<<endl;
                   desplazamiento += BYTES_4;// obtengo el lugar exacto donde se debe guardar los datos

               }
                else if(temp_sch->get_elemento2() == FLOAT_ID){ //obtengo el tipo de dato
                   cout<<temp_sch->get_elemento1()<<" : "<<*(float*)(temp_register + desplazamiento)<<endl;
                     desplazamiento += BYTES_4;// obtengo el lugar exacto donde se debe guardar los datos

               }
           temp_sch = temp_sch->get_siguiente();
       }
   }
   cout<<"__________________________end of Table : "<<nameOfFile << "______________________________"<<endl;
}
void FileManager :: delete_row(int num_fila){

    char* temp_register = (char*)calloc(1,*sizeOfRegister); //registro temporal para recorrer el archivo

    cout<<"____________________________delete row : "<<num_fila << "______________________________"<<endl;

    for(int num_row = 0; num_row < *numberOfRegisters ; num_row++){
        temp_register = (fileBuffer + (*sizeOfRegister*num_row)) ;//buffer temporal para recorrer de registro en registro
        if(num_fila == num_row){
            cout<<"puntero al anterior : "<<*(int*)(temp_register)<<endl;
        }
     }

}

void FileManager :: addNewRegister(void* register_buffer ){

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fs){
        if(getSizeOfFile() == sizeOfHeader){//si el archivo esta vacio 
            setPtrOfFirstRegister(sizeOfHeader);
            setPtrToLastRegister(sizeOfHeader);
        }
        else{
            int* ptr_anterior = (int*)register_buffer;
            *ptr_anterior = getPtrToLastRegister();    //tomo el ultimo reg y antes de guardar lo pongo como anterior
            setPtrToLastRegister(getPtrToLastRegister() + getSizeOfRegister() ); //actualizo puntero al ultimo registro
        }

        int temp = fs.tellp();
        fs.seekp (0, ios::end);

        fs.write(reinterpret_cast<const char*>(register_buffer),getSizeOfRegister());

        setNumberOfRegisters(getNumberOfRegisters() + 1);

        fs.seekp (0, ios::end);
        setSizeOfFile(fs.tellp());
        fs.seekp(temp,ios::end);


    }
    else cout<<"Error 002 :No se puede añadir registro porque archivo no existe"<<endl;



   fs.close();
   free(register_buffer); //libero el espacio que soliticte para el buffer
 }


char* FileManager :: getNameOfFile(){    return nameOfFile;}
int FileManager :: getSizeOfFile(){    return *sizeOfFile;}
int FileManager :: getNumberOfRegisters(){    return *numberOfRegisters;}
int FileManager :: getNumberOfFreeRegisters(){    return *numberOfFreeRegisters;}
int FileManager :: getPtrOfFirstRegister(){    return *ptrOfFirstRegister;}
int FileManager :: getPtrToLastRegister(){    return *ptrToLastRegister;}
int FileManager :: getPtrToFirstRegisterFree(){    return *ptrToFirstRegisterFree;}
int FileManager :: getSizeOfRegister(){    return *sizeOfRegister;}
int FileManager :: getNumberOfColumns(){    return *numberOfColumns;}

void FileManager :: setNameOfFile(const char* name_of_file){
    int i;
    for(i = 0; (name_of_file[i] != '\0') && i < TABLESIZE ; i++){  //obtenemos el nombre del archivo
           *(nameOfFile+i) = name_of_file[i];
       }

    *(nameOfFile+i) = '\0' ;

}
void FileManager :: setSizeOfFile( int size_of_file){    *sizeOfFile = size_of_file;}
void FileManager :: setNumberOfRegisters(int number_of_registers){    *numberOfRegisters = number_of_registers;}
void FileManager :: setNumberOfFreeRegisters(int number_of_free_registers){    *numberOfFreeRegisters = number_of_free_registers;}
void FileManager :: setPtrOfFirstRegister(int ptr_to_first_register){    *ptrOfFirstRegister=ptr_to_first_register;}
void FileManager :: setPtrToLastRegister(int ptr_to_last_register){    *ptrToLastRegister = ptr_to_last_register;}
void FileManager :: setPtrToFirstRegisterFree(int ptr_to_first_register_free){    *ptrToFirstRegisterFree=ptr_to_first_register_free;}
void FileManager :: setSizeOfRegister(int size_of_register){    *sizeOfRegister = size_of_register;}
void FileManager :: setNumberOfColumns(int number_of_columns){    *numberOfColumns = number_of_columns;}



void FileManager :: addStringToSchema(const char* columna , int offset){
    schema.agregarAlFinal(columna,STRING_ID,offset);

}
void FileManager :: addIntToSchema(const char* columna,int offset){
    schema.agregarAlFinal(columna,INT_ID,offset);

}
void FileManager :: addFloatToSchema(const char* columna,int offset){
    schema.agregarAlFinal(columna, FLOAT_ID, offset);

}

void FileManager :: loadSchema(){
    const char* extTxt = ".txt";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extTxt);
    const char * schemaName = result.c_str();
    ifstream fe(schemaName);
       char cadena1[100];
       char cadena2[100];
       char cadena3[100];
       std::string temps;
       int temp2;
       int temp3;
       Vector3d<string, int, int> sch_copy;
       for(int x = 0 ; !fe.eof() && (x< *numberOfColumns)  ; x++) {
          fe >> cadena1;
          fe >> cadena2;
          fe >> cadena3;
          temps = std::string(cadena1);
          temp2 = atoi(cadena2);
          temp3 = atoi(cadena3);
        sch_copy.agregarAlFinal(temps,temp2,temp3);
       }
     Nodo3d<string,int,int>* temp;
     temp = sch_copy.get_primerNodo();
     sch_copy.get_ultimoNodo()->set_siguiente(NULL);
     for(int g = 0; g < sch_copy.getLength(); g++){
         const char* temp_c;
         temp_c = temp->get_elemento1().c_str();
         schema.agregarAlFinal(temp_c,temp->get_elemento2(),temp->get_elemento3());
         temp = temp->get_siguiente();
     }
       fe.close();
}
void FileManager :: saveSchema(){

    const char* extTxt = ".txt";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extTxt);
    const char * schemaName = result.c_str();
    // Crea un fichero de salida

       ofstream fe(schemaName);

       Nodo3d<const char*,int,int>* temp;
       temp = schema.get_primerNodo();
       schema.get_ultimoNodo()->set_siguiente(NULL);
       for(int x=0 ; x<(schema.getLength());x++){
           fe << temp->get_elemento1() <<endl;
           fe << temp->get_elemento2() <<endl;
           fe << temp->get_elemento3() <<endl;

           temp = temp->get_siguiente();

       }
       fe.close();
}
void FileManager :: initSchema(){
    schema.vaciar();
}
   Vector3d<const char *, int, int > FileManager :: getSchema(){
     return schema;
 }
void FileManager :: printHeader(){
    cout << "---------------------Header------------------------------------"<< endl;
      cout << "nombre de tabla : "<< getNameOfFile() << endl;
      cout << "tamaño archivo : "<< getSizeOfFile() << endl;
      cout << "num reg : "<< getNumberOfRegisters() << endl;
      cout << "num libres : "<< getNumberOfFreeRegisters() << endl;
      cout << "primer reg : "<< getPtrOfFirstRegister() << endl;
      cout << "primer libre : "<< getPtrToFirstRegisterFree() << endl;
      cout << "ultimo reg : "<< getPtrToLastRegister() << endl;
      cout << "tamañoRegistro : "<< getSizeOfRegister() << endl;
      cout << "num de columnas : "<< getNumberOfColumns() << endl;
       cout << "---------------------end-of-Header------------------------------------"<< endl;
}

bool FileManager :: compare_strings(const char* str1 , const char* str2){
    int tamanio1;
    int tamanio2;
    for(tamanio1=0 ; (str1[tamanio1] != '\0') ; tamanio1++){ }
    for(tamanio2=0 ; (str2[tamanio2] != '\0') ; tamanio2++){ }
    if(tamanio1 != tamanio2){ return false;}
    for(int x=0 ; (str1[x] != '\0') &&  (str2[x] != '\0') ; x++){
        if(str1[x] != str2[x]){
            return false;
        }
    }
    return true;
}
