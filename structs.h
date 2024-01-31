#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_NAME 30
#define MAX_ACRONYM 5

typedef enum {
    Printer, Computer, PC, Monitor, Router, Switch, TV, Projector, Access, Mouse, Accessory, Other,
} Category ;

typedef enum {
    Operational, Maintenance, Not_Operational, Recycling,  
} Status;

typedef enum {
    UPDATE, TECHNICAL, REPLACEMENT,
            
} MaintanenceType;


typedef struct {
    int month;
    int day;
    int year;
} Date;

typedef struct {
    int numberMovement;
    Date date;
    MaintanenceType maintanence;
    char notes[MAX_NAME];
    
} Maintanence;


typedef struct {
    int id;
    char designation[MAX_NAME];
    Category category;
    Date dateOfAcquisition;
    Status status;
    int userCode;
    int isFree;
    Maintanence *maintanenceHitory; 
    int maintanenceCtr;
    
} Hardware;

typedef enum {
    INACTIVE, ACTIVE,
            
} UserStatus;


typedef struct {
    int userCode;
    char acronym[5];
    char name[MAX_NAME];
    char role[MAX_NAME];
    UserStatus status;
    Hardware hardware;
    int haveEquipment;
   
} User;


typedef struct {
    int userCtr;
    User *userPtr;
    
    int hardwareCtr;
    Hardware *hardwarePtr;
   
   
} DataBase ;



#endif /* STRUCTS_H */

