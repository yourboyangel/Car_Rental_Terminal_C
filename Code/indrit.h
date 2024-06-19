#ifndef INDRIT_H_INCLUDED
#define INDRIT_H_INCLUDED

void addReservation(struct reservation **tail, struct reservation **head1)
{
    struct reservation *newReservation, *curr;
    curr=*head1;
    newReservation = (struct reservation *)malloc(sizeof(struct reservation));
    printf("\nEnter new reservation data (RESERVATION ID,DATE,CLIENTID)\n");
    scanf("%d %s %d", &newReservation->reservationID, newReservation->date, &newReservation->clientId);
    newReservation->next = NULL;


    if(*head1==NULL)
    {
        *head1=newReservation;
    }
    else
    {
        while(curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=newReservation;
    }


    FILE *fn=NULL;
    fn=fopen("allreservations.txt","a");
    if(fn==NULL)
    {
        printf("Could not open file reservation!");
        return;
    }

    fprintf(fn,"%d %s %d ", newReservation->reservationID, newReservation->date, newReservation->clientId);


    fclose(fn);
}
void pricingReservation(struct Vehicle **vhead)
{

    FILE *rf = fopen("allreservations.txt", "a");
    if(rf == NULL)
    {
        printf("File not opened");
        return;
    }

    struct reservation *newReservation;
    struct Vehicle *newVehicle = *vhead;
    newReservation = (struct reservation *)malloc(sizeof(struct reservation));

    if(newReservation == NULL)
    {
        printf("\nMemory allocation did not work\n");
        fclose(rf);
        return;
    }

    FILE *vehicleData = fopen("vehicle.txt", "r");
    if(vehicleData == NULL)
    {
        printf("Vehicle data not found!!!\n");
        fclose(rf);
        free(newReservation);
        return;
    }

    char vehicleModel[50];
    printf("Enter the model of the vehicle (Please make sure that it is on the list): \n");
    scanf("%s", vehicleModel);

    struct Vehicle *chosenVehicle = NULL;
    struct Vehicle *currVehicle = (struct Vehicle *)malloc(sizeof(struct Vehicle));

    while(fscanf(vehicleData,"%s %d %s %s %d %d %f", currVehicle->plate_num, &currVehicle->year, currVehicle->model, currVehicle->fuel_type, &currVehicle->consumption, &currVehicle->seats, &currVehicle->price) == 7)
    {
        if (strcmp(currVehicle->model, vehicleModel)==0)
        {
            chosenVehicle = currVehicle;
            break;
        }
    }

    fclose(vehicleData);

    if(chosenVehicle == NULL)
    {
        printf("This vehicle model does not exist");
        fclose(rf);
        free(newReservation);
        return;
    }

    printf("\nEnter the data for the new reservation: (AMOUNT OF DAYS)\n");
    scanf("%d", &newReservation->clientDays);

    printf("\nChoose a pricing option\n");

    printf("\n1. Fixed Price\n");

    printf("\n2. Discount based on the number of days\n");

    int choice;
    scanf("%d", &choice);


    if (choice == 1)
    {
        newReservation->totalPrice = chosenVehicle->price * newReservation->clientDays;
    }
    else if (choice == 2)
    {
        if (newReservation->clientDays >= 7 && newReservation->clientDays< 14)
        {
            newReservation->totalPrice = chosenVehicle->price * newReservation->clientDays * 0.9;
        }
        else if (newReservation->clientDays >= 14 && newReservation->clientDays < 30)
        {
            newReservation->totalPrice = chosenVehicle->price * newReservation->clientDays * 0.85;
        }
        else if (newReservation->clientDays >= 30)
        {
            newReservation->totalPrice = chosenVehicle->price * newReservation->clientDays * 0.8;
        }
        else
        {
            newReservation->totalPrice = chosenVehicle->price * newReservation->clientDays;
        }
    }
    else
    {
        printf("\nInvalid choice selected.\n");
        newReservation->totalPrice = 0.0;
    }


    printf("\nThe price for this reservation is %f!\n", newReservation->totalPrice);
    printf("\nReservation added successfully,Have a nice day!\n");

    fprintf(rf," %s %s %.2f %d\n",currVehicle->plate_num,currVehicle->model, newReservation->totalPrice,newReservation->clientDays);
    fclose(rf);

    free(newReservation);

}

void overX()
{
    FILE *overXData = fopen("allreservations.txt", "r");
    FILE *vehicleDataX = fopen("vehicle.txt", "r");
    FILE *finish = fopen("higherThanX.txt", "a");
    if(overXData == NULL)
    {
        printf("Over X data not found!!!");
        return;
    }
    struct reservation *currReservation = (struct reservation *)malloc(sizeof(struct reservation));
    struct Vehicle *currVehicle = (struct Vehicle *)malloc(sizeof(struct Vehicle));
    if(currReservation == NULL)
    {
        printf("nMemory allocation failed!!!\n");
        fclose(overXData);
        fclose(finish);
        return;
    }

    while(fscanf(overXData,"%d %s %d %s %s %f %d\n", &currReservation->reservationID, currReservation->date, &currReservation->clientId, &currVehicle->plate_num, &currVehicle->model, &currReservation->totalPrice, &currReservation->clientDays) == 7)
    {
        if (currReservation->totalPrice>2500)
        {
            fprintf(finish,"%d %s %d %s %s %f %d\n", currReservation->reservationID, currReservation->date, currReservation->clientId, currVehicle->plate_num, currVehicle->model, currReservation->totalPrice, currReservation->clientDays);
            printf("Reservation over 2500$ added to file!\n");
        }
    }

    fclose(overXData);
    fclose(finish);
    fclose(vehicleDataX);
    free(currReservation);
}

struct reservation  *readingListFromResFile()
{
    FILE *fr = fopen("allreservations.txt", "r");
    if (fr == NULL)
    {
        printf("Could not open file vehicle.\n");
        return NULL;
    }

    struct reservation *head = NULL;
    struct reservation *curr = NULL;
    struct reservation *newReservation = NULL;


    while ((newReservation = (struct reservation *)malloc(sizeof(struct reservation))) != NULL)
    {
        curr= newReservation;
        if (fscanf(fr, "%d %s %d %s %s %f %d\n",
                   &curr->reservationID,
                   curr->date,
                   &curr->clientId,
                   curr->vehicle.plate_num,
                   curr->vehicle.model,
                   &curr->totalPrice,
                   &curr->clientDays) == 7)
        {

            newReservation->next = NULL;

            if (head == NULL)
            {
                head = newReservation;

            }
            else
            {
                curr = head;
                while(curr->next != NULL)
                {
                    curr = curr->next;
                }
                curr->next = newReservation;
            }
        }
        else
        {
            free(newReservation);
            break;
        }
    }

    fclose(fr);
    return head;
}


void deletereservation(struct reservation** head3)
{
    if (*head3 == NULL)
    {
        printf("There are no reservations!\n");
        return;
    }

    int reservationID2;
    printf("Enter the reservation ID of the reservation you would like to delete from the list:\n");
    scanf("%d", &reservationID2);

    struct reservation* curr = *head3;
    struct reservation* prev = NULL;

    while (curr != NULL)
    {
        if (curr->reservationID == reservationID2)
        {
            if (prev == NULL)
            {
                *head3 = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }

            printf("The reservation with ID %d was deleted successfully!\n", reservationID2);
            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("The reservation with ID %d was not found!\n", reservationID2);
}



void putIntoResFile(struct reservation* head3)
{
    FILE *fp=NULL;
    fp=fopen("allreservations.txt","w");
    if(fp==NULL)
    {
        printf("Could not open file vehicle!");
        return;
    }

    struct reservation* curr;
    curr=head3;

    while(curr!=NULL)
    {
        fprintf(fp,"%d %s %d %s %s %f %d\n",curr->reservationID,curr->date,curr->clientId,curr->vehicle.plate_num,curr->vehicle.model,curr->totalPrice,curr->clientDays);
        curr=curr->next;
    }
    fclose(fp);
    return;
}

void displayReservation(struct reservation *head1)
{
    struct reservation *curr;
    FILE *fp = fopen("allreservations.txt", "a+");

    if (fp == NULL)
    {
        printf("Cannot open file 'allreservations.txt'!");
        return;
    }

    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }
    fclose(fp);
}



#endif // INDRIT_H_INCLUDED
