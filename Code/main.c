#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structclient.h"
#include "vehicle_structure.h"
#include "structure1.h"
#include "engjell.h"
#include "kristi.h"
#include "indrit.h"

int main()
{
    CL *head = NULL;
    CL *newCL;
    resvV *head2 = NULL;
    struct reservation *head1 = NULL, *head3 = NULL, *tail = NULL, *newReservation = NULL;
    struct Vehicle *vhead;
    vhead = NULL;
    char username[20];
    char password[20];
    int menu;
    int isAdminLoggedIn = 0;

    printf("Welcome to the Vehicle Management System!\n");

    while (1) {
        printf("Please select your role (1 for Admin, 2 for User, or 0 to exit): ");
        int role;
        scanf("%d", &role);

        if (role == 0) {
            printf("Exiting the program.\n");
            return 0;
        } else if (role == 1) {
            printf("Admin login successful!\n");
            isAdminLoggedIn = 1;
            break;
        } else if (role == 2) {
            printf("User login successful!\n");
            break;
        } else {
            printf("Invalid input! Please try again.\n");
        }
    }

    if (isAdminLoggedIn) {
        while (1) {
            printf("\
>-----------------------------------------<\n\
|                  MENU                   |\n\
>-----------------------------------------<\n\
| Option |            Description          |\n\
>-----------------------------------------<\n\
|   1    | Display all vehicle information |\n\
|   2    | Display available vehicles      |\n\
|        |         currently               |\n\
|   3    | Display vehicles available      |\n\
|        | after x days                    |\n\
|   4    | Create a new reservation        |\n\
|   5    | Add a new vehicle               |\n\
|   6    | Search for a vehicle using      |\n\
|        | the license plate number        |\n\
|   7    | Sort and display vehicles       |\n\
|        | according to daily rental price |\n\
|   8    | Display top 3 most reserved     |\n\
|        | vehicles                        |\n\
|   9    | Display all reservations        |\n\
|  10    | Remove a vehicle                |\n\
|  11    | Cancel a reservation            |\n\
|  12    | Display clients with more than  |\n\
|        | 3 rented vehicles               |\n\
|  13    | Save reservations with total    |\n\
|        | cost exceeding 2500$ to a new file|\n\
|  14    | Modify vehicle information      |\n\
|        | using plate number              |\n\
|   0    | Exit the menu                   |\n\
>-----------------------------------------<\n");
            printf("| Please choose an option:               |\n");
            printf(">-----------------------------------------<\n\n");
            scanf("%d", &menu);

            switch (menu) {
                case 1:{
                    vhead = readingListFromFile();
                    displayAllInfo(vhead);
                    break;
                }
                case 2:{
                    available_vehicles(&head2);
                    break;
                }
                case 3:{
                    reservt1(&head2);
                    break;
                }
                case 4:{
                    addclint(&head, &newCL);
                    addReservation(&tail, &head1);
                    pricingReservation(&vhead);
                    break;
                }
                case 5:{
                    addVehicle(&vhead);
                    break;
                }
                case 6:{
                    vhead = readingListFromFile();
                    searchV(vhead);
                    break;
                }
                case 7:{
                    vhead = readingListFromFile();
                    sortingVehicles(&vhead);
                    putIntoFile(&vhead);
                    displayAllInfo(vhead);
                    break;
                }
                case 8:{
                    printf("Top 3 most reserved vehicles are: \n");
                    morecars();
                    break;
                }
                case 9:{
                    displayReservation(head1);
                    break;
                }
                case 10:{
                    vhead = readingListFromFile();
                    removeVehicle(&vhead);
                    putIntoFile(&vhead);
                    break;
                }
                case 11:{
                    head3 = readingListFromResFile();
                    deletereservation(&head3);
                    putIntoResFile(head3);
                    break;
                }
                case 12:{
                    printf("The clients who have rented a vehicle more than 3 times are: \n");
                    max1();
                    break;
                }
                case 13:{
                    overX();
                    break;
                }
                case 14:{
                    vhead = readingListFromFile();
                    modifyVehicleInfo(&vhead);
                    putIntoFile(&vhead);
                    break;
                }
                case 0:
                    printf("Admin: You have exited the menu.\n");
                    return 0;
                default:
                    printf("Admin: Invalid input! Please select another option :)\n");
                    break;
            }
        }
    } else {
        while (1) {
            printf("\
>-----------------------------------------<\n\
|                  MENU                   |\n\
>-----------------------------------------<\n\
| Option |            Description          |\n\
>-----------------------------------------<\n\
|   1    | Display all vehicle information |\n\
|   2    | Display available vehicles      |\n\
|        |         currently               |\n\
|   3    | Display vehicles available      |\n\
|        | after x days                    |\n\
|   4    | Create a new reservation        |\n\
|   5    | Search for a vehicle using      |\n\
|        | the license plate number        |\n\
|   6    | Sort and display vehicles       |\n\
|        | according to daily rental price |\n\
|   7    | Display top 3 most reserved     |\n\
|        | vehicles                        |\n\
|   8    | Display all reservations        |\n\
|   9    | Cancel a reservation            |\n\
|   0    | Exit the menu                   |\n\
>-----------------------------------------<\n");
            printf("| Please choose an option:               |\n");
            printf(">-----------------------------------------<\n\n");
            scanf("%d", &menu);

            switch (menu) {
                case 1:{
                    vhead = readingListFromFile();
                    displayAllInfo(vhead);
                    break;
                }
                case 2:{
                    available_vehicles(&head2);
                    break;
                }
                case 3:{
                    reservt1(&head2);
                    break;
                }
                case 4:{
                    addclint(&head, &newCL);
                    addReservation(&tail, &head1);
                    pricingReservation(&vhead);
                    break;
                }
                case 5:{
                    vhead = readingListFromFile();
                    searchV(vhead);
                    break;
                }
                case 6:{
                    vhead = readingListFromFile();
                    sortingVehicles(&vhead);
                    putIntoFile(&vhead);
                    displayAllInfo(vhead);
                    break;
                }
                case 7:{
                    printf("Top 3 most reserved vehicles are: \n");
                    morecars();
                    break;
                }
                case 8:{
                    displayReservation(head1);
                    break;
                }
                case 9:{
                    head3 = readingListFromResFile();
                    deletereservation(&head3);
                    putIntoResFile(head3);
                    break;
                }
                case 0:
                    printf("User: You have exited the menu.\n");
                    return 0;
                default:
                    printf("User: Invalid input! Please select another option :)\n");
                    break;
            }
        }
    }
    return 0;
}
