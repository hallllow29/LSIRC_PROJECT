#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "hardware.h"
#include "manageUsers.h"
#include "input.h"
#include "main.h"
#include "manageUsers.h"

int main() {
    int option;

    DataBase *dataBase = calloc(1, sizeof (DataBase));

    dataBase = initLoadDataBase(dataBase);

    do {
        puts("[1] Manage Hardware");
        puts("[2] Manage Users\n");
        puts("[0] EXIT");
        scanf("%d", &option);
        cleanInputBuffer();


        switch (option) {
            case 1:
                manageHardware(dataBase);
                break;
            case 2:
                manageUsers(dataBase);
                break;
            case 0:
                puts("EXITING THE PROGRAM");
                saveData_FreeMemory(dataBase);
                break;
        }

    } while (option != 0);

    
    
    return 0;

}

DataBase *initLoadDataBase(DataBase *dataBase) {
    dataBase->hardwarePtr = NULL;
    dataBase->userPtr = NULL;
    dataBase->hardwareCtr = 1;
    dataBase->userCtr = 1;

    dataBase = hardwareLoadToFile(dataBase, FILE_NAME);
    dataBase = userLoadToFile(dataBase, USER_FILE);

    return dataBase;

}

void saveData_FreeMemory(DataBase *dataBase) {
    puts("Saving data.....");
    sleep(1);
    dataBase = hardwareSaveToFile(dataBase, FILE_NAME);
    dataBase = usersSaveToFile(dataBase, USER_FILE);
    free(dataBase->hardwarePtr);
    free(dataBase->userPtr);
    free(dataBase);
}

