#include "fsql_manager.h"

FSQL_Manager::FSQL_Manager()
{
}

bool FSQL_Manager :: createTable(const char* filename, Vector3d<const char*, const char*,const char*>*  args  ){


    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->setNameOfFile(filename);//es necesario crear un archivo con un nombre
    file_manager->generate_binaryFile();
    file_manager->setNumberOfColumns(args->getLength());

    //contador para tamaño de registro empieza en 4 porque los 4 bytes primeros representan ptr al anterior registro
    int tamanio_registro = 4;


    Nodo3d<const char*,const char*,const char*>* temp;
    temp = args->get_primerNodo();
    args->get_ultimoNodo()->set_siguiente(NULL);

    //agregamos los parametros de create table para armar un schema en memoria
    for(int x=0 ; x<(args->getLength());x++){

        if (file_manager->compare_strings(temp->get_elemento2(),"string")
                ||file_manager->compare_strings( temp->get_elemento2(),"String")){
            //agrego string al schema con tamaño en caracteres
            file_manager->addStringToSchema(temp->get_elemento1() , atoi(temp->get_elemento3()));
            tamanio_registro +=  atoi(temp->get_elemento3());
        }
        else if (file_manager->compare_strings(temp->get_elemento2(), "int")
                 || file_manager->compare_strings(temp->get_elemento2(),"Int")){
            //agrego int al schema con tamaño en caracteres
            file_manager->addIntToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  file_manager->BYTES_4;                         //4 bytes de tamaño por el momento
        }
        else if (file_manager->compare_strings(temp->get_elemento2(),"float")
                 || file_manager->compare_strings(temp->get_elemento2(),"Float")){
              //agrego int al schema con su tamaño en caracteres
            file_manager->addFloatToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  file_manager->BYTES_4;  //guardo por ahora solo 4 bytes
        }

        temp = temp->get_siguiente();
    }


    file_manager->setSizeOfRegister(tamanio_registro); //actualizo tamaño del registro en bytes


    file_manager->saveSchema();//se guarda el schema en disco
    file_manager->saveHeader();//se guarda el header en disco



    return true;
}

bool FSQL_Manager :: insertInto(const char* filename, VectorRelacional<const char*, const char*>*  campos  ){

    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro

    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria



//creamos el registro
    Register* new_reg = new Register(file_manager , directorioDe_fsql);
    new_reg->initRegister(filename);
    new_reg->fill_Register(campos);//lleno el registro en memoria
    new_reg->setDirty(true);

    register_manager.addRegisterToMap(new_reg); //agrego al mapa de registros en memoria

    file_manager->addNewRegister(new_reg->getBuffer());

    file_manager->saveHeader();//salvo el header antes de agregar un registro
  // file_manager->printHeader();

     return true;
}

bool FSQL_Manager :: update(const char* filename, Vector3d<const char*, const char*,const char*>* condiciones
                            , VectorRelacional<const char*,int>* operadores_logicos,VectorRelacional<const char*,const char*>* sets){
    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria
    file_manager->openFile();

    if(condiciones->getLength() > 0){
        int* accepted_rows = file_manager->where(condiciones,operadores_logicos);


        for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
            if(accepted_rows[i] != -1){
                NodoRelacional<const char*,const char*>* temp_ = sets->get_primerNodo();
                sets->get_ultimoNodo()->set_siguiente(NULL);
                while(temp_!= NULL){
                    file_manager->setCampo(temp_->get_elemento1(),temp_->get_elemento2(),accepted_rows[i]);
                    temp_=temp_->get_siguiente();
                }
            }
           // cout<<accepted_rows[i]<<endl;
        }

    }



    file_manager->saveFile();
    file_manager->closeFile();
    return true;

}

bool FSQL_Manager :: Select(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                            , VectorRelacional<const char*,int>* columnas, VectorRelacional<const char*,int>* operadores_logicos ){
     cout<<"-------------------------Select From "<<file_manager->getNameOfFile()<<" --------------------------------"<<endl;
    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria
    file_manager->openFile();

    if(condiciones->getLength() > 0){
        int* accepted_rows = file_manager->where(condiciones,operadores_logicos);

        for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
            if(accepted_rows[i] != -1){
                NodoRelacional<const char*,int>* temp_ = columnas->get_primerNodo();
                columnas->get_ultimoNodo()->set_siguiente(NULL);
                while(temp_!= NULL){
                    cout<<"-------------------------Row "<<accepted_rows[i]<<" --------------------------------"<<endl;
                    file_manager->printSelect(temp_->get_elemento1(),accepted_rows[i] );
                    temp_=temp_->get_siguiente();
                }
            }
           // cout<<accepted_rows[i]<<endl;
        }

    }

  //  file_manager->saveFile();
    file_manager->closeFile();
    return true;

}
bool FSQL_Manager :: Select_asterisco(const char* filename){
     file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
     file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
     file_manager->initSchema();//se vacia el schema en memoria
     file_manager->loadSchema();//cargo el header a memoria
     file_manager->openFile();

     file_manager->printFile();

     file_manager->closeFile();
 }

bool FSQL_Manager :: DeleteFrom(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                                , VectorRelacional<const char*,int>* operadores_logicos){
    cout<<"-------------------------Delete From "<<file_manager->getNameOfFile()<<" --------------------------------"<<endl;
   file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
   file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
   file_manager->initSchema();//se vacia el schema en memoria
   file_manager->loadSchema();//cargo el header a memoria
   file_manager->openFile();

   if(condiciones->getLength() > 0){
       int* delete_rows = file_manager->where(condiciones,operadores_logicos);

       for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
           if(delete_rows[i] != -1){
               file_manager->delete_row(delete_rows[i]);
           }
       }

   }

   file_manager->saveFile();
   file_manager->closeFile();
   return true;
}

int FSQL_Manager:: logic(){
    // ---------------------------------------------------------Create table

    Vector3d<const char*, const char*,const char*>  args;
    args.agregarAlFinal("Nombre","string","20");
    args.agregarAlFinal("cedula","int","20");
     args.agregarAlFinal("institucion","string","20");
    args.agregarAlFinal("direccion","string","10");
    args.agregarAlFinal("edad","float","4");
    args.agregarAlFinal("id","int","6");

    createTable("prueb" , &args);




    //---------------------------------------------------------insert into

    VectorRelacional<const char* , const char*> args2;
    VectorRelacional<const char* , const char*> args1;
     VectorRelacional<const char* , const char*> args3;
    args2.agregarAlFinal("id" , "22");
    args2.agregarAlFinal("Nombre","Sebastian");
    args2.agregarAlFinal("cedula","345");
    args2.agregarAlFinal("direccion" , "sanjose");
    args2.agregarAlFinal("edad" , "19");

    args1.agregarAlFinal("id" , "02");
    args1.agregarAlFinal("Nombre","jose");
    args1.agregarAlFinal("cedula","22345");
    args1.agregarAlFinal("direccion" , "heredia");
    args1.agregarAlFinal("edad" , "27");

    args3.agregarAlFinal("edad" , "37");
    args3.agregarAlFinal("id" , "02");
    args3.agregarAlFinal("Nombre","daniel");
    args3.agregarAlFinal("cedula","1111");
    args3.agregarAlFinal("direccion" , "cartago");




  insertInto("prueb" , &args1);
  insertInto("prueb" , &args2);
  insertInto("prueb" , &args1);

//--------------------------------------update-------------------------------------
  Vector3d<const char* , const char*, const char*> condiciones;
  VectorRelacional<const char*,int> operadores_logic;
  VectorRelacional<const char*,const char*> sets;

  //set
  sets.agregarAlFinal("edad","98");
  sets.agregarAlFinal("institucion","OOJ");

  //where
  condiciones.agregarAlFinal("Nombre","=","jose");
  operadores_logic.agregarAlFinal("OR",1);
  condiciones.agregarAlFinal("cedula","=","22345");
   operadores_logic.agregarAlFinal("AND",1);
  condiciones.agregarAlFinal("direccion","=","heredia");



  update("prueb",&condiciones,&operadores_logic, &sets );
 //---------------------------------------select From-------------------------------------------
  Vector3d<const char* , const char*, const char*> condiciones2;
  VectorRelacional<const char*,int> operadores_logic2;
  VectorRelacional<const char*,int> columnas2;

  //select
  columnas2.agregarAlFinal("edad",0);
  columnas2.agregarAlFinal("institucion",0);

  //where
 // condiciones2.agregarAlFinal("Nombre","=","Sebastian");
  //operadores_logic2.agregarAlFinal("OR",1);
  //condiciones2.agregarAlFinal("cedula","=","345");
   //operadores_logic2.agregarAlFinal("AND",1);
  condiciones2.agregarAlFinal("direccion","=","heredia");

  Select("prueb",&condiciones2,&columnas2,&operadores_logic2);

  //------------------------------------Select asterisco----------------------------------

  Select_asterisco("prueb");

//--------------------------------------------delete from--------------------------------
  Vector3d<const char* , const char*, const char*> condiciones3;
  VectorRelacional<const char*,int> operadores_logic3;

  condiciones3.agregarAlFinal("institucion","=", "OOJ");

  DeleteFrom("prueb",&condiciones3,&operadores_logic);


  //----------------------------------------------prints------------------------------

  /*file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
  file_manager->loadHeader("prueb");//cargo el header del aqrchivo que quiero agregar registro
  file_manager->initSchema();//se vacia el schema en memoria
  file_manager->loadSchema();//cargo el header a memoria
  file_manager->openFile();

  file_manager->printHeader();
  file_manager->printFile();*/




    return 0;

}

