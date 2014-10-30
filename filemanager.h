#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "vector3d.h"
#include "vectorrelacional.h"

using namespace std;


class FileManager
{

    void * header_buffer = NULL;
    char * fileBuffer =NULL;


    char* nameOfFile = NULL;
    int* sizeOfFile = NULL;
    int* numberOfRegisters = NULL;
    int* numberOfFreeRegisters = NULL;
    int* ptrOfFirstRegister = NULL;
    int* ptrToLastRegister = NULL;
    int* ptrToFirstRegisterFree = NULL;
    int* sizeOfRegister = NULL;
    int* numberOfColumns = NULL;


    const char* directory;

    Vector3d<const char *, int, int > schema;

public:
    const int INT_ID = 999;
    const int FLOAT_ID = 888;
    const int STRING_ID = 777;
    const int BYTES_4 = 4;
    const int TABLESIZE = 30;

    const int sizeOfHeader = 62;
    const int nullPosition = -1;

    FileManager(  const char* Directory);
    void initHeader();
    void loadHeader(const char * name_of_file);
    void saveHeader();
    void printHeader();
    void openFile();
    void addNewRegister(void*);
    int* where(Vector3d<const char*,const char*,const char*>* , VectorRelacional<const char*,int>*);
    bool cumpleCondicion(const char* ,const char* operador, const char*,void* temp_register);
    void printFile();
    void closeFile();
    void saveFile();
    void setCampo(const char* columna , const char* campo,int num_row);
    void printSelect(const char* columna ,int num_row);
    void delete_row(int);

    void initSchema();
    void loadSchema();
    void saveSchema();
    void generate_binaryFile();
    Vector3d<const char *, int, int > getSchema();
    void addStringToSchema(const char*, int);
    void addIntToSchema(const char*,int);
    void addFloatToSchema(const char*,int);


    char* getNameOfFile();
    int getSizeOfFile();
    int getNumberOfRegisters();
    int getNumberOfFreeRegisters();
    int getPtrOfFirstRegister();
    int getPtrToLastRegister();
    int getPtrToFirstRegisterFree();
    int getSizeOfRegister();
    int getNumberOfColumns();

    void setNameOfFile(const char*);
    void setSizeOfFile( int);
    void setNumberOfRegisters(int);
    void setNumberOfFreeRegisters(int);
    void setPtrOfFirstRegister(int);
    void setPtrToLastRegister(int);
    void setPtrToFirstRegisterFree(int);
    void setSizeOfRegister(int);
    void setNumberOfColumns(int);

    bool compare_strings(const char* str1 , const char* str2);


};

#endif // FILEMANAGER_H
