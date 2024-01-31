#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "hardware.h"
#include "manageUsers.h"
#include "input.h"
#include <string.h>

DataBase *searchHardware(DataBase *hardwareList) {
    int option;

    do {
        puts("[1] Search by category");
        puts("[2] Search by Status");
        scanf("%d", &option);

        switch (option) {
            case 1:
                searchByCategory(hardwareList);
                break;
            case 2:
                searchByStatus(hardwareList);
                break;
        }
    } while (option != 0);

    return hardwareList;
}

void searchByCategory(DataBase *hardwareList) {
    int option = 0;

    puts("Choose the category you want to search: ");

    puts("[0] Printer");
    puts("[1] Computer");
    puts("[2] PC");
    puts("[3] Monitor");
    puts("[4] Router");
    puts("[5] Switch");
    puts("[6] TV");
    puts("[7] Projector");
    puts("[8] Access");
    puts("[9] Mouse");
    puts("[10] Accessory");
    puts("[11] Other");

    scanf("%d", &option);
    cleanInputBuffer();

    switch (option) {
        case 0:
            printEquipmentData(hardwareList, option);
            break;
        case 1:
            printEquipmentData(hardwareList, option);
            break;
        case 2:
            printEquipmentData(hardwareList, option);
            break;
        case 3:
            printEquipmentData(hardwareList, option);
            break;
        case 4:
            printEquipmentData(hardwareList, option);
            break;
        case 5:
            printEquipmentData(hardwareList, option);
            break;
        case 6:
            printEquipmentData(hardwareList, option);
            break;
        case 7:
            printEquipmentData(hardwareList, option);
            break;
        case 8:
            printEquipmentData(hardwareList, option);
            break;
        case 9:
            printEquipmentData(hardwareList, option);
            break;
        case 10:
            printEquipmentData(hardwareList, option);
            break;
        case 11:
            printEquipmentData(hardwareList, option);
            break;
    }
}

void printEquipmentData(DataBase *hardwareList, int option) {
    int i;

    switch (option) {
        case 0:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 0) {
                    getHardwareData(hardwareList->hardwarePtr[i]);
                }
            }
            break;
        case 1:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 1) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 2:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 2) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 3:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 3) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 4:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 4) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 5:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 5) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 6:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 6) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 7:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 7) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 8:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 8) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 9:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 9) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 10:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 10) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 11:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 11) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;

    }



}

void searchByStatus(DataBase *hardwareList) {
    int option = 0;
    int i = 0;

    puts("[0] OP");
    puts("[1] INOP");
    puts("[2] Maintenance");
    puts("[3] Recycling");
    scanf("%d", &option);
    cleanInputBuffer();

    switch (option) {
        case 0:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].status == 0) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 1:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 1) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 2:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 2) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;
        case 3:
            for (i = 1; i < hardwareList->hardwareCtr; i++) {
                if (hardwareList->hardwarePtr[i].category == 2) {
                    getHardwareData((hardwareList->hardwarePtr[i]));
                }
            }
            break;


    }

}


