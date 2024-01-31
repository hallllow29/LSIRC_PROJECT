#ifndef MANAGEUSERS_H
#define MANAGEUSERS_H
#include "structs.h"

#define USER_FILE "users.bin"

DataBase *manageUsers(DataBase *dataBase);

DataBase *newUserList(DataBase *userList, int size);

DataBase *userAdd(DataBase *userList);

void listUser(DataBase *userList);

DataBase *removeUser(DataBase *userList);

int associateUser(DataBase *dataBase, int userIndex, int hardwareIndex);

DataBase *chooseHardware(DataBase *dataBase, int index);

const char* printUserStatus(UserStatus status);

DataBase *editUser(DataBase *userList);

DataBase *userLoadToFile(DataBase *userList, char *filename);

DataBase *usersSaveToFile(DataBase *userList, char *filename);

#endif /* MANAGEUSERS_H */

