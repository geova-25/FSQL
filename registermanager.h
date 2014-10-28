#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include "register.h"
class RegisterManager
{
private:
    VectorRelacional<int, Register*> map;
public:
    RegisterManager();
    void addRegisterToMap(Register*);
};

#endif // REGISTERMANAGER_H
