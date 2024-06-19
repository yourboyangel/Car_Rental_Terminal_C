#ifndef VEHICLE_STRUCTURE_H_INCLUDED
#define VEHICLE_STRUCTURE_H_INCLUDED
struct Vehicle{
    char plate_num[30];
    int year;
    char model[30];
    char fuel_type[30];
    int consumption;
    int seats;
    float price;

    struct Vehicle *next;
};



#endif // VEHICLE_STRUCTURE_H_INCLUDED
