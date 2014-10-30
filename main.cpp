#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "fsql_manager.h"

using namespace std;



int main()
{

    FSQL_Manager  fsql_Manager;

    fsql_Manager.logic();













/*
    //---------------------------parametros que ocupamos obtener automaticamente
    int Ncolumnas = 6; //ejemplo
    const char** vector_columns_name = new const char*[Ncolumnas] ;
    const char** vector_data_tipe = new const char*[Ncolumnas];
    int* vector_columnsSize = new int[Ncolumnas];

    vector_columns_name[0] = "PtrAnterior";
    vector_data_tipe[0]= "int";
    vector_columnsSize[0] = 4;
    vector_columns_name[1] = "PtrSiguiente";
    vector_data_tipe[1]= "int";
    vector_columnsSize[1] = 4;


    vector_columns_name[2] = "ID";
    vector_data_tipe[2]= "int";
    vector_columnsSize[2] = 4;
    vector_columns_name[3] = "Apellidos";
    vector_data_tipe[3] = "string";
    vector_columnsSize[3] = 30;
    vector_columns_name[4] = "Salario";
    vector_data_tipe[4] = "int";
    vector_columnsSize[4] = 4;
    vector_columns_name[5] = "direccion";
    vector_data_tipe[5] = "string";
    vector_columnsSize[5] = 30;
      //-----------------------........................................................//

    //------------------------------create table------------------------------------

    //-------------------------------Insert into---------------------------------------



    MetadataReader reader(directorioDe_fsql);

    cout <<reader.readFileName("7databla")<<endl;

    cout  << *reader.readSizeOfFile("7databla") << endl;

     cout  << *reader.readNumOfRegisters("7databla") << endl;

      cout  << *reader.readNumOfFreeRegisters("7databla") << endl;

       cout  << *reader.readPointerToFirstRegister("7databla") << endl;

       cout  << *reader.readPointerToFistFree("7databla") << endl;

        cout  << *reader.readPointerToLastRegister("7databla") << endl;

         cout  << *reader.readSizeOfRegister("7databla") << endl;

          cout  << *reader.readNumberOfColumns("7databla") << endl;


    SchemaReader* sch = new SchemaReader("7databla",directorioDe_fsql);
    sch->print();

    */


    return 0;
}

