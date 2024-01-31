#ifndef SEARCHHARDWARE_H
#define SEARCHHARDWARE_H
#include "structs.h"

void printEquipmentData(DataBase hardwareList, int option);
void searchByCategory(DataBase hardwareList);

DataBase *searchHardware(DataBase *hardwareList);

void searchByStatus(DataBase *hardwareList);


#endif /* SEARCHHARDWARE_H */

