#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "hardware.h"
#include "manageUsers.h"
#include "input.h"
#include <string.h>
#include "main.h"

DataBase *manageHardware(DataBase *dataBase) {
    int option = 0;

    do {
        puts("[1] List Hardware Equipment");
        puts("[2] Add Hardware");
        puts("[3] Hardware Maintenance");
        puts("[4] Check Maintenance History");
        puts("[5] Search for equipment");
        puts("[6] Edit Equipment Status");
        puts("[7] Remove Equipment");
        puts("[8] List Free Equipments");
        puts("[9] List Equipments for recycling");
        puts("[0] BACK\n");
        scanf("%d", &option);
        cleanInputBuffer();

        switch (option) {
            case 1:
                printHardwareList(dataBase);
                break;
            case 2:
                addHardware(dataBase);
                break;
            case 3:
                hardwareMaintanence(dataBase);
                break;
            case 4:
                checkMaintanenceHistory(dataBase);
                break;
            case 5:
                searchHardware(dataBase);
                break;
            case 6:
                editHardwareStatus(dataBase);
                break;
            case 7:
                removeHardware(dataBase);
                break;
            case 8:
                freeEquipments(dataBase);
                break;
            case 9:
                checkEquipmentForRecycling(dataBase);
                break;
            case 0:
                break;
       
        }

    } while (option != 0);


}

DataBase *addHardware(DataBase *hardwareList) {
    hardwareList = newHardwareList(hardwareList, hardwareList->hardwareCtr + 1);

    int index = hardwareList->hardwareCtr;

    puts("---------------ADD HARDWARE MENU-------------------");

    chooseCategory(hardwareList, index);

    hardwareList->hardwarePtr[index].id = index;
    readString(hardwareList->hardwarePtr[index].designation, MAX_NAME, "Designation: ");

    hardwareList->hardwarePtr[index].dateOfAcquisition.day = getInt(1, 31, "Day: ");
    hardwareList->hardwarePtr[index].dateOfAcquisition.month = getInt(1, 12, "Month: ");
    hardwareList->hardwarePtr[index].dateOfAcquisition.year = getInt(2010, 2024, "Day: ");
    hardwareList->hardwarePtr[index].status = 0;
    hardwareList->hardwarePtr[index].isFree = 1;
    hardwareList->hardwarePtr[index].userCode = 0;

    hardwareList->hardwareCtr++;

    return hardwareList;

}

DataBase *newHardwareList(DataBase *hardwareList, int newSize) {
    if (!hardwareList) {
        puts("User list is NULL");
        return NULL;
    }

    User *newPtr = realloc(hardwareList->hardwarePtr, newSize * sizeof (User));
    if (!newPtr) {
        puts("Failed to allocate memory");
        return NULL;
    }

    hardwareList->hardwarePtr = newPtr;

    for (int i = hardwareList->hardwareCtr; i < newSize; ++i) {
        memset(&hardwareList->hardwarePtr[i], 0, sizeof (Hardware));
    }

    return hardwareList;
}

DataBase *chooseCategory(DataBase *hardwareList, int index) {
    int option;

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

    hardwareList->hardwarePtr[index].category = option;

    return hardwareList;


}

void getHardwareData(Hardware hardwareList) {
    printf("ID: %d\n", hardwareList.id);
    printf("User Code: %d\n", hardwareList.userCode);
    printf("Designation: %s\n", hardwareList.designation);
    printf("Category: %s\n", printCategory(hardwareList.category));
    printf("Date: %d/%d/%d\n", hardwareList.dateOfAcquisition.day, hardwareList.dateOfAcquisition.month, hardwareList.dateOfAcquisition.year);
    printf("Status : %s\n", printStatus(hardwareList.status));
}

void printHardwareList(DataBase *hardwareList) {
    int i;

    if (hardwareList->hardwareCtr == 1) {
        puts("There is no equipment on the list!");
        return;
    }

    for (i = 1; i < hardwareList->hardwareCtr; i++) {
        getHardwareData(hardwareList->hardwarePtr[i]);

    }
}

int printHardwareListForUser(DataBase *hardwareList) {
    int i;
    int multiple = 0;

    for (i = 1; i < hardwareList->hardwareCtr; i++) {
        if (hardwareList->hardwarePtr[i].status != 3 && hardwareList->hardwarePtr[i].isFree == 1) {
            getHardwareData(hardwareList->hardwarePtr[i]);
            multiple++;
        }
    }
    if (multiple == 0) {
        puts("The list is empty! Ask the admin to check if there is equipment available on the storage");
        return -1;
    }

    return 1;

}

const char* printCategory(Category category) {

    switch (category) {
        case Printer:
            return "Printer";
        case Computer:
            return "Computer";
        case PC:
            return "PC";
        case Monitor:
            return "Monitor";
        case Router:
            return "Router";
        case Switch:
            return "Switch";
        case TV:
            return "TV";
        case Projector:
            return "Projector";
        case Access:
            return "Access Control";
        case Mouse:
            return "Mouse";
        case Accessory:
            return "Accessory";
        case Other:
            return "Other";
        default:
            return "Unknown Type!";
    }
}

const char* printStatus(Status status) {
    switch (status) {
        case Operational:
            return "Operational";
        case Maintenance:
            return "Maintenance";
        case Not_Operational:
            return "Not Operational";
        case Recycling:
            return "Recycling";

    }
}

int listFreeEquipments(DataBase *hardwareList) {
    int i;
    int multiple = 0;

    for (i = 1; i < hardwareList->hardwareCtr; i++) {
        if (hardwareList->hardwarePtr[i].isFree == 1) {
            printf("ID: %d\n", hardwareList->hardwarePtr[i].id);
            printf("Designation: %s\n", hardwareList->hardwarePtr[i].designation);
            printf("Category: %s\n", printCategory(hardwareList->hardwarePtr[i].category));
            printf("Date: %d/%d/%d\n,", hardwareList->hardwarePtr[i].dateOfAcquisition.day, hardwareList->hardwarePtr[i].dateOfAcquisition.month, hardwareList->hardwarePtr[i].dateOfAcquisition.year);
            printf("Status : %s\n", printStatus(hardwareList->hardwarePtr[i].status));
            multiple++;
        }

        if (multiple == 0) {
            puts("There is no available hardware on the list please add a new one!");
            return -1;
        }
    }

    return 1;
}

DataBase *hardwareMaintanence(DataBase *maintanenceList) {
    int option;

    do {
        puts("[1] Software Update");
        puts("[2] Technical Maintenance");
        puts("[3] Component Replacement");
        puts("[9] BACK\n");
        puts("[0] EXIT");
        scanf("%d", &option);

        switch (option) {
            case 1:
                maintenanceEquipment(maintanenceList, option);
                break;
            case 2:
                maintenanceEquipment(maintanenceList, option);
                break;
            case 3:
                maintenanceEquipment(maintanenceList, option);
                break;
            case 9:
                break;
            default:
                puts("Please enter a valid option if you want to exit press 0 or 9 to back");
                break;
            case 0:
                break;

                if (option == 9) {
                    option = 0;
                }

        }
    } while (option != 0);
}

DataBase *maintenanceEquipment(DataBase *maintanenceList, int option) {
    int index;

    puts("-------------------------SOFTWARE UPDATE------------------------------");

    printHardwareList(maintanenceList);

    index = getInt(1, maintanenceList->hardwareCtr, "Choose the index of the equipment you want to update: ");
    int size = maintanenceList->hardwarePtr[index].maintanenceCtr;


    if (maintanenceList->hardwarePtr[index].maintanenceHitory == NULL) {
        maintanenceList->hardwarePtr[index].maintanenceHitory = malloc(1 * sizeof (Maintanence));
        maintanenceList->hardwarePtr[index].maintanenceCtr = 0;
    } else {
        maintanenceList->hardwarePtr[index].maintanenceHitory = realloc(maintanenceList->hardwarePtr[index].maintanenceHitory, size * sizeof (Maintenance));
    }

    maintanenceList->hardwarePtr[index].maintanenceHitory[size].date.day = getInt(1, 31, "Day: ");
    maintanenceList->hardwarePtr[index].maintanenceHitory[size].date.month = getInt(1, 31, "Month: ");
    maintanenceList->hardwarePtr[index].maintanenceHitory[size].date.year = getInt(2010, 2024, "Year: ");

    if (option == 1) {
        maintanenceList->hardwarePtr[index].maintanenceHitory[size].maintanence = UPDATE;
        readString(maintanenceList->hardwarePtr[index].maintanenceHitory[size].notes, MAX_NAME, "Notes: ");
    } else if (option == 2) {
        maintanenceList->hardwarePtr[index].maintanenceHitory[size].maintanence = TECHNICAL;
        readString(maintanenceList->hardwarePtr[index].maintanenceHitory[size].notes, MAX_NAME, "Notes: ");
    } else if (option == 3) {
        maintanenceList->hardwarePtr[index].maintanenceHitory[size].maintanence = REPLACEMENT;
        readString(maintanenceList->hardwarePtr[index].maintanenceHitory[size].notes, MAX_NAME, "Notes: ");
    }


    maintanenceList->hardwarePtr[index].maintanenceHitory[size].numberMovement++;
    maintanenceList->hardwarePtr[index].maintanenceCtr++;

    return maintanenceList;

}

void checkMaintanenceHistory(DataBase *maintanenceList) {
    int index = 0;
    int i = 0;

    printHardwareList(maintanenceList);

    index = getInt(1, maintanenceList->hardwareCtr, "Choose the hardware that you want to check the maintenance history: ");

    if (maintanenceList->hardwarePtr[index].maintanenceCtr == 0) {
        puts("The hardware don't have any maintenance!");
        return;
    }

    for (i = 0; i < maintanenceList->hardwarePtr[index].maintanenceCtr; i++) {
        printf("Number of movements: %d\n", maintanenceList->hardwarePtr[index].maintanenceHitory[i].numberMovement);
        printf("Date: %d-%d-%d\n", maintanenceList->hardwarePtr[index].maintanenceHitory[i].date.day, maintanenceList->hardwarePtr[index].maintanenceHitory[i].date.month, maintanenceList->hardwarePtr[index].maintanenceHitory[i].date.year);
        printf("Notes: %s\n", maintanenceList->hardwarePtr[index].maintanenceHitory[i].notes);
        printf("Maintenance type: %s\n", printMaintanenceType(maintanenceList->hardwarePtr[index].maintanenceHitory[i].maintanence));
        puts("----------------------------------------------------------------------------------------------------------------");

    }

}

const char* printMaintanenceType(MaintanenceType type) {
    switch (type) {
        case UPDATE:
            return "Software Update";
        case TECHNICAL:
            return "Technical Maintenance";
        case REPLACEMENT:
            return "Component Replacement";
    }
}

DataBase *editHardwareStatus(DataBase *hardwareList) {
    int index;
    int option;

    printHardwareList(hardwareList);

    puts("Choose the id of the equipment you want to edit: ");
    scanf("%d", &index);
    cleanInputBuffer();

    puts("Choose a status for the equipment: ");
    puts("[1] OP");
    puts("[2] Maintenance");
    puts("[3] INOP");
    puts("[4] Recycling\n");
    puts("[0] Exit");
    scanf("%d", &option);

    cleanInputBuffer();

    switch (option) {
        case 1:
            hardwareList->hardwarePtr[index].status = 0;
            break;
        case 2:
            hardwareList->hardwarePtr[index].status = 1;
            break;
        case 3:
            hardwareList->hardwarePtr[index].status = 2;
            break;
        case 4:
            hardwareList->hardwarePtr[index].status = 3;
            break;
        default:
            puts("Choose a valid option!");
        case 0:
            break;

    }

    return hardwareList;

}

DataBase *removeHardware(DataBase *hardwareList) {
    int i;
    int index;

    if (hardwareList->hardwareCtr == 1) {
        puts("There is no equipment on the list!");
        return hardwareList;
    }


    printHardwareList(hardwareList);

    puts("Choose the id of the equipment you want to remove: ");
    scanf("%d", &index);

    if (hardwareList->hardwarePtr[index].status == 3) {
        hardwareList->hardwarePtr[index].id = 0;
        strcpy(hardwareList->hardwarePtr[index].designation, "");
        hardwareList->hardwarePtr[index].dateOfAcquisition.day = 0;
        hardwareList->hardwarePtr[index].dateOfAcquisition.month = 0;
        hardwareList->hardwarePtr[index].dateOfAcquisition.year = 0;
        hardwareList->hardwarePtr[index].isFree = 0;
        hardwareList->hardwarePtr[index].maintanenceCtr = 0;
        hardwareList->hardwarePtr[index].maintanenceHitory = NULL;
        hardwareList->hardwarePtr[index].status = 0;
        hardwareList->hardwarePtr[index].userCode = 0;

        for (i = index; i < hardwareList->hardwareCtr - 1; i++) {
            hardwareList->hardwarePtr[i] = hardwareList->hardwarePtr[i + 1];
            hardwareList->hardwarePtr[i].id -= 1;
        }

        hardwareList->hardwareCtr--;


    } else {
        puts("You only can remove equipment with recycling status! ");

    }

    return hardwareList;
}

void orderByCategory(DataBase *hardwareList) {
    int i;
    int j;

    for (i = 0; i < hardwareList->hardwareCtr; i++) {
        for (j = 0; j < hardwareList->hardwareCtr - i - 1; j++) {
            if (hardwareList->hardwarePtr[j].category > hardwareList->hardwarePtr[j + 1].category) {
                Hardware temp = hardwareList->hardwarePtr[j];
                hardwareList->hardwarePtr[j] = hardwareList->hardwarePtr[j + 1];
                hardwareList->hardwarePtr[j + 1] = temp;
            }
        }
    }
}

void freeEquipments(DataBase *hardwareList) {
    int i;

    if (hardwareList->hardwareCtr == 1) {
        puts("There is no equipment on the list!");
        return;
    }

    orderByCategory(hardwareList);

    for (i = 0; i < hardwareList->hardwareCtr; i++) {
        if (hardwareList->hardwarePtr[i].isFree == 1) {
            getHardwareData(hardwareList->hardwarePtr[i]);
        }
    }
}

void checkEquipmentForRecycling(DataBase *hardwareList) {
    int i;
    int multiple = 0;

    for (i = 1; i < hardwareList->hardwareCtr; i++) {
        if (hardwareList->hardwarePtr[i].status == 3) {
            getHardwareData(hardwareList->hardwarePtr[i]);
            multiple++;
        }
    }

    if (multiple == 0) {
        puts("There is no equipment for recycling at the moment!");
        return;
    }

}

DataBase *hardwareLoadToFile(DataBase *hardwareList, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        puts("Unable to open file");
        return hardwareList;
    }

    fread(&hardwareList->hardwareCtr, sizeof (int), 1, fp);
    if (hardwareList->hardwareCtr > 0) {
        if (hardwareList->hardwarePtr != NULL) {
            free(hardwareList->hardwarePtr);
        }

        hardwareList->hardwarePtr = calloc(hardwareList->hardwareCtr, sizeof (Hardware));
        for (int i = 0; i < hardwareList->hardwareCtr; i++) {
            fread(&hardwareList->hardwarePtr[i], sizeof (Hardware), 1, fp);
            if (hardwareList->hardwarePtr[i].maintanenceCtr != 0) {
                hardwareList->hardwarePtr[i].maintanenceHitory = alloc_COMMT_array(hardwareList->hardwarePtr[i].maintanenceCtr);
                fread(hardwareList->hardwarePtr[i].maintanenceHitory, sizeof (Maintenance),
                        hardwareList->hardwarePtr[i].maintanenceCtr, fp);
            }
        }
    }

    fclose(fp);
    return hardwareList;
}

Maintanence *alloc_COMMT_array(int size) {
    return calloc(size, sizeof (Maintenance));
}

DataBase *hardwareSaveToFile(DataBase *hardwareList, char *filename) {
    if (hardwareList == NULL) {
        return NULL;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return NULL;
    }

    fwrite(&hardwareList->hardwareCtr, sizeof (int), 1, fp);

    for (int i = 0; i < hardwareList->hardwareCtr; i++) {
        fwrite(&hardwareList->hardwarePtr[i], sizeof (Hardware), 1, fp);
        if (hardwareList->hardwarePtr[i].maintanenceCtr > 0 && hardwareList->hardwarePtr[i].maintanenceHitory != NULL) {
            fwrite(hardwareList->hardwarePtr[i].maintanenceHitory, sizeof (Maintenance), hardwareList->hardwarePtr[i].maintanenceCtr, fp);
        }
    }

    fclose(fp);
    return hardwareList;
}
