#include "registermanager.h"

RegisterManager::RegisterManager()
{
}
void RegisterManager :: addRegisterToMap(Register* regist){
    map.agregarAlFinal(0,regist);

}
