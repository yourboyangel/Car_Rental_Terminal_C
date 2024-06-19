#ifndef STRUCTCLIENT_H_INCLUDED
#define STRUCTCLIENT_H_INCLUDED



typedef struct clint
{
    char name[20];
    char surname[20];
    int ID;
    char PASSID[20];
    char State[20];
    int PHnumber;



    struct clint *next;



}CL;
typedef struct resvV1
{
    char plate_num[30];

    char model[30];
    int days;


    struct resvV1 *next;
} resvV;























#endif
