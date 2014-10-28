#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "schema.h"
#include "vectorrelacional.h"

using namespace std;


class FileManager
{

    void * header_buffer = NULL;
    void * fileBuffer = NULL;

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

    Schema<const char *, int, int > schema;

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

    void initSchema();
    void loadSchema();
    void saveSchema();
    Schema<const char *, int, int > getSchema();
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


};

#endif // FILEMANAGER_H
