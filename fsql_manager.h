#ifndef FSQL_MANAGER_H
#define FSQL_MANAGER_H



#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "register.h"
#include "filemanager.h"
#include "registermanager.h"








using namespace std;

class FSQL_Manager
{
public:
    FSQL_Manager();

    int logic();
    int createTable(const char* filename, Schema<const char*, const char*,const char*>*  );
    int insertInto(const char* filename, VectorRelacional<const char*, const char*>*  args  ) ;

private:
    const char* directorioDe_fsql = "/home/sebastian/Escritorio/BaseDeDatos/";

    FileManager* file_manager = new FileManager(directorioDe_fsql);
    RegisterManager register_manager;




};

#endif // FSQL_MANAGER_H
