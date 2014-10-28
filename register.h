#ifndef REGISTER_H
#define REGISTER_H

#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "filemanager.h"

using namespace std;


class Register
{
public:
    Register(FileManager* file_manager , const char * Directory );

    void initRegister(const char * file_name );
    void fill_Register(VectorRelacional<const char* ,  const char *>* campos);


    bool isDirty();
    void setDirty(bool);
    void setID(int);
    int getID();
    int getPtr_al_anterior();
    void setPtr_al_anterior(int);
    int getSizeOfRegister();
    void* getBuffer();

private :

    void saveString(const char* string , const char* nombre_columna,int desplazamiento);
    void saveInt(int Int , const char* nombre_columna,int desplazamiento);
    void saveFloat(float Float , const char* nombre_columna,int desplazamiento);

    int regID;

    const char* directory;

    const char* fileName;

    int size_of_register;

    bool dirty = false;

    void* Buffer = NULL;

    int* ptr_al_anterior = NULL;

    FileManager* fileManager;

    const int NULL_POINTER = -1;







};

#endif // REGISTER_H
