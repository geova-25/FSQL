#include "filemanager.h"

FileManager :: FileManager( const char* Directory)
{
    directory = Directory;
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
    ofstream fe(FileNameBin); //Creamos un archivo bin nuevo para una tabla nueva si no existe
    fe.close();
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
        cout<<"no hay archivo"<<endl;    }

   fsr.close();
}

void FileManager :: openFile(){
    fileBuffer = calloc(1,126);

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(getNameOfFile()) + std::string(extBin);
    const char * FileNameBin = result.c_str();
    fstream fsr(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fsr){
        int temp = fsr.tellg();
        fsr.seekg(0 ,ios::end);
        cout<<fsr.tellg()<<endl;
        fsr.read((char*)fileBuffer, 64);


        cout<<"ddddd"<<*(int*)(fileBuffer)<<endl;
         cout<<"ddddd"<<FileNameBin<<endl;
          cout<<"ddddd"<<sizeOfHeader<<endl;
           cout<<"ddddd"<<getSizeOfFile()<<endl;
            cout<<"ddddd"<<getSizeOfFile()-sizeOfHeader<<endl;

        fsr.seekg(temp,ios::beg);
    }
    else{
        cout<<"no hay archivo"<<endl;    }

   fsr.close();
}


void FileManager :: addNewRegister(void* register_buffer ){

    const char* extBin = ".bin";
    std::string result = std::string(directory) +std::string(nameOfFile) + std::string(extBin);
    const char * FileNameBin = result.c_str();

    fstream fs(FileNameBin, std::ios::out | std::ios::in | std::ios::binary );
    if(fs){
        if(getSizeOfFile() == sizeOfHeader){//si el archivo esta vacio

            int temp = fs.tellp();
            fs.seekp (0, ios::end);
            cout<<fs.tellp()<<" dfs "<<endl;
            fs.write(reinterpret_cast<const char*>(register_buffer),getSizeOfRegister());


            setNumberOfRegisters(1);
            setPtrOfFirstRegister(sizeOfHeader);
            setPtrToLastRegister(sizeOfHeader);

            fs.seekp (0, ios::end);
            setSizeOfFile(fs.tellp());

            fs.seekp(temp,ios::end);

        }
        else{
            int temp = fs.tellp();
            fs.seekp (0, ios::end);
            int* ptr_anterior = (int*)register_buffer;
            *ptr_anterior = getPtrToLastRegister();    //tomo el ultimo reg y antes de guardar lo pongo como anterior
            fs.write(reinterpret_cast<const char*>(register_buffer),getSizeOfRegister());

            setNumberOfRegisters(getNumberOfRegisters() + 1);
            setPtrOfFirstRegister(sizeOfHeader );
            setPtrToLastRegister(getPtrToLastRegister() + getSizeOfRegister());

            fs.seekp (0, ios::end);
            setSizeOfFile(fs.tellp());
            fs.seekp(temp,ios::end);



        }


    }
    else cout<<"no se puede añadir registro porque archivo no existe"<<endl;




   fs.close();
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
       Schema<string, int, int> sch_copy;
       for(int x = 0 ; !fe.eof() && (x< *numberOfColumns)  ; x++) {
          fe >> cadena1;
          fe >> cadena2;
          fe >> cadena3;
          temps = std::string(cadena1);
          temp2 = atoi(cadena2);
          temp3 = atoi(cadena3);
        sch_copy.agregarAlFinal(temps,temp2,temp3);
       }
     Nodo<string,int,int>* temp;
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

       Nodo<const char*,int,int>* temp;
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
   Schema<const char *, int, int > FileManager :: getSchema(){
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

