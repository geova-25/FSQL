#include "fsql_manager.h"

FSQL_Manager::FSQL_Manager()
{
}

int FSQL_Manager :: createTable(const char* filename, Schema<const char*, const char*,const char*>*  args  ){


    file_manager->initHeader();
    file_manager->initSchema();
    file_manager->setNameOfFile(filename);
    file_manager->setNumberOfColumns(args->getLength());

    Nodo<const char*,const char*,const char*>* temp;
    temp = args->get_primerNodo();
    args->get_ultimoNodo()->set_siguiente(NULL);
    int tamanio_registro = 4;

    for(int x=0 ; x<(args->getLength());x++){

        if ((temp->get_elemento2() == "string" || temp->get_elemento2() == "String")){
            file_manager->addStringToSchema(temp->get_elemento1() , atoi(temp->get_elemento3()));
            tamanio_registro +=  atoi(temp->get_elemento3());
        }
        else if ((temp->get_elemento2() == "int" || temp->get_elemento2() == "Int")){
            file_manager->addIntToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  atoi(temp->get_elemento3());
        }
        else if ((temp->get_elemento2() == "float" || temp->get_elemento2() == "Float")){
            file_manager->addFloatToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  atoi(temp->get_elemento3());
        }

        temp = temp->get_siguiente();
    }

    file_manager->setSizeOfRegister(tamanio_registro);

;
    file_manager->saveSchema();
    file_manager->saveHeader();



    return 0;
}

int FSQL_Manager :: insertInto(const char* filename, VectorRelacional<const char*, const char*>*  campos  ){

    file_manager->initHeader();
    file_manager->loadHeader(filename);

    file_manager->initSchema();
    file_manager->loadSchema();

    Register* new_reg = new Register(file_manager , directorioDe_fsql);
    new_reg->initRegister(filename);
    new_reg->fill_Register(campos);
    new_reg->setDirty(true);




    register_manager.addRegisterToMap(new_reg);

    file_manager->addNewRegister(new_reg->getBuffer());

    file_manager->saveHeader();
    file_manager->printHeader();




     return 0;
}


int FSQL_Manager:: logic(){
    // ---------------------------------------------------------Create table

    Schema<const char*, const char*,const char*>  args;
    args.agregarAlFinal("Nombre","string","20");
    args.agregarAlFinal("cedula","int","10");
    args.agregarAlFinal("direccion","string","10");
    args.agregarAlFinal("edad","float","10");
    args.agregarAlFinal("id","int","10");

    createTable("prueb" , &args);




    //---------------------------------------------------------insert into

    VectorRelacional<const char* , const char*> args2;

    args2.agregarAlFinal("Nombre","Sebastian");
    args2.agregarAlFinal("id" , "22");


    insertInto("prueb" , &args2);



file_manager->openFile();



    return 0;

}

