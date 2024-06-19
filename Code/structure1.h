#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct reservation
{
    int reservationID;
    char date[20];
    int clientId;
    int clientDays;
    float totalPrice;
    struct Vehicle vehicle;

    struct reservation *next;
};

#endif // STRUCT_H_INCLUDED
