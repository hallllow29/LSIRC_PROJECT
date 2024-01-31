#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "manageUsers.h"
#include "input.h"
#include "string.h" 
#include "hardware.h"

DataBase *manageUsers(DataBase *dataBase) {
    int option = 0;

    do {
        puts("[1] Add User");
        puts("[2] List Users");
        puts("[3] Remove User");
        puts("[4] Edit user");
        puts("[9] BACK\n");
        puts("[0] EXIT");
        scanf("%d", &option);
        cleanInputBuffer();

        switch (option) {
            case 1:
                userAdd(dataBase);
                break;
            case 2:
                listUser(dataBase);
                break;
            case 3:
                removeUser(dataBase);
                break;
            case 4:
                editUser(dataBase);
                break;
            case 9:
                break;

                if (option == 9) {
                    option = 0;
                }

        }
    } while (option != 0);

    return dataBase;
}

DataBase *userAdd(DataBase *userList) {
    userList = newUserList(userList, userList->userCtr + 1);

    int index = userList->userCtr;

    userList->userPtr[index].userCode = index;

    puts("----------------------------------------------------------------------");
    puts("\t\t\t\tUSER ADD\t\t\t");
    readString(userList->userPtr[index].name, MAX_NAME, "Name: ");
    readString(userList->userPtr[index].acronym, MAX_ACRONYM, "Acronym: ");
    readString(userList->userPtr[index].role, MAX_NAME, "Role: ");

    chooseHardware(userList, index);


    userList->userPtr[index].status = 1;

    userList->userCtr++;

    return userList;
}

DataBase *newUserList(DataBase *userList, int newSize) {
    if (!userList) {
        puts("User list is NULL");
        return NULL;
    }

    User *newPtr = realloc(userList->userPtr, newSize * sizeof (User));

    if (!newPtr) {
        puts("Failed to allocate memory");
        return NULL;
    }

    userList->userPtr = newPtr;

    for (int i = userList->userCtr; i < newSize; ++i) {
        memset(&userList->userPtr[i], 0, sizeof (User));
    }

    return userList;
}

void listUser(DataBase *userList) {
    int i;

    for (i = 1; i < userList->userCtr; i++) {
        printf("ID: %d\n", userList->userPtr[i].userCode);
        printf("Name: %s\n", userList->userPtr[i].name);
        printf("Acronym: %s\n", userList->userPtr[i].acronym);
        printf("Role: %s\n", userList->userPtr[i].role);
        printf("Status :%s\n", printUserStatus(userList->userPtr[i].status));
        puts("------------------------------------------------------------------");
    }
}

DataBase *removeUser(DataBase *userList) {
    int index;
    int i;

    puts("-----------REMOVE MENU-------------");

    listUser(userList);

    puts("Select the index of the user do you want to remove: ");
    scanf("%d", &index);

    if (userList->userPtr[index].haveEquipment == 1) {
        puts("You cant remove a user with equipment associated!");
        return userList;
    }

    strcpy(userList->userPtr[index].name, "");
    strcpy(userList->userPtr[index].role, "");
    strcpy(userList->userPtr[index].acronym, "");

    userList->userPtr[index].userCode = 0;

    for (i = index; i < userList->userCtr - 1; i++) {
        userList->userPtr[i] = userList->userPtr[i + 1];
        userList->userPtr[i].userCode -= 1;
    }

    userList->userCtr--;

    return userList;

}

DataBase *chooseHardware(DataBase *dataBase, int index) {
    int hardwareIndex;
    int available = 0;

    available = printHardwareListForUser(dataBase);

    if (available == 1) {

        do {
            puts("Choose the index of the hardware you want to associate to the user: ");
            puts("If you don't want to associate enter -1:  ");
            scanf("%d", &hardwareIndex);

            if (dataBase->hardwarePtr[hardwareIndex].status == 3) {
                puts("You can't choose this hardware because is for recycling");

            }

        } while (dataBase->hardwarePtr[hardwareIndex].status == 3);


        if (hardwareIndex == -1) {
            puts("No equipment associated!");
            return dataBase;
        }



        dataBase->userPtr[index].hardware = dataBase->hardwarePtr[hardwareIndex];
        dataBase->hardwarePtr[hardwareIndex].userCode = index;
        dataBase->hardwarePtr[hardwareIndex].isFree = 0;
        dataBase->userPtr[index].haveEquipment = 1;
        dataBase->userPtr[index].status = 1;

    } else {
        puts("There is no available equipment please contact the admin!");
        dataBase->userPtr[index].haveEquipment = 0;
        dataBase->userPtr[index].status = 0;
    }

    return dataBase;

}

const char* printUserStatus(UserStatus status) {
    switch (status) {
        case INACTIVE:
            return "Inactive";
        case ACTIVE:
            return "Active";

    }
}

DataBase *editUser(DataBase *userList) {
    int index;
    int option;

    if (userList->userCtr == 1) {
        puts("There is no users on the list");
        return userList;
    }

    listUser(userList);

    index = getInt(1, userList->hardwareCtr, "Choose the index of the user you want to edit:");

    do {
        printf("[1] Edit Name: \t\t\t%s\n", userList->userPtr[index].name);
        printf("[2] Edit Acronym: \t\t\t%s\n", userList->userPtr[index].acronym);
        printf("[3] Edit Role: \t\t\t%s\n", userList->userPtr[index].role);
        printf("[4] Edit Status: \t\t\t%s\n", printUserStatus(userList->userPtr[index].status));
        puts("[0] BACK");
        option = getInt(0, 4, "Choose what you want to edit: \n");

        switch (option) {
            case 1:
                readString(userList->userPtr[index].name, MAX_NAME, "New Name: ");
                break;
            case 2:
                readString(userList->userPtr[index].acronym, MAX_NAME, "New Acronym: ");
                break;
            case 3:
                readString(userList->userPtr[index].role, MAX_NAME, "New Role: ");
                break;
            case 4:
                userList->userPtr[index].status = getInt(0, 1, "New status [0]Inactive\n[1] Active: ");
                break;
            case 0:
                break;
            default:
                puts("Choose a valid option if you want o exit the menu press 0!");

        }
    } while (option != 0);
}

DataBase *usersSaveToFile(DataBase *userList, char *filename) {
    int i;

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&userList->userCtr, sizeof (int), 1, fp);

    for (i = 0; i < userList->userCtr; i++) {
        fwrite(&userList->userPtr[i], sizeof (User), 1, fp);
    }

    fclose(fp);
    return userList;
}

DataBase *userLoadToFile(DataBase *userList, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return userList;
    }

    fread(&userList->userCtr, sizeof (int), 1, fp);

    if (userList->userCtr > 0) {
        userList->userPtr = (User *) calloc(userList->userCtr, sizeof (User));
        for (int i = 0; i < userList->userCtr; i++) {
            fread(&userList->userPtr[i], sizeof (User), 1, fp);
        }
    }

    fclose(fp);
    return userList;
}
