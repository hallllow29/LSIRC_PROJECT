#ifndef HARDWARE_H
#define HARDWARE_H
#include "structs.h"

#define FILE_NAME "hardware.bin"

DataBase *manageHardware(DataBase *dataBase);

DataBase *addHardware(DataBase *hardwareList);

DataBase *newHardwareList(DataBase *hardwareList, int newSize);

DataBase *chooseCategory(DataBase *hardwareList, int index);
    
const char* printCategory(Category category);

void printHardwareList(DataBase *hardwareList);

const char* printStatus(Status status);

int listFreeEquipments(DataBase *hardwareList);

DataBase *maintenanceEquipment(DataBase *maintanenceList, int option);

DataBase *hardwareMaintanence(DataBase *maintanenceList);

const char* printMaintanenceType(MaintanenceType type);

void checkMaintanenceHistory(DataBase *maintanenceList);

void getHardwareData(Hardware hardwareList);


DataBase *editHardwareStatus(DataBase *hardwareList);

DataBase *removeHardware(DataBase *hardwareList);

void orderByCategory(DataBase *hardwareList);

void freeEquipments(DataBase *hardwareList);

void checkEquipmentForRecycling(DataBase *hardwareList);

int printHardwareListForUser(DataBase *hardwareList);

Maintanence *alloc_COMMT_array(int size);

void printHardwareList(DataBase *hardwareList);

DataBase *hardwareSaveToFile(DataBase *hardwareList, char *filename);

DataBase *hardwareLoadToFile(DataBase *hardwareList, char *filename) ;


#endif /* HARDWARE_H */

