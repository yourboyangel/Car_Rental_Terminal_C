#ifndef OTHER_VEHICLE_OPERATIONS_H_INCLUDED
#define OTHER_VEHICLE_OPERATIONS_H_INCLUDED
void addVehicle(struct Vehicle **vhead){
    struct Vehicle *newVehicle,*curr;
    curr=*vhead;
    newVehicle=(struct Vehicle *)malloc(sizeof(struct Vehicle));    //getting data for the new vehicle
    printf("Enter the data about the new vehicle you want to add: \n");
    printf("Plate number: ");
    scanf("%s",newVehicle->plate_num);
    printf("Year: ");
    scanf("%d",&newVehicle->year);
    printf("Model: ");
    scanf("%s",newVehicle->model);
    printf("Fuel type: ");
    scanf("%s",newVehicle->fuel_type);
    printf("Consumption(liters per km): ");
    scanf("%d",&newVehicle->consumption);
    printf("Seats: ");
    scanf("%d",&newVehicle->seats);
    printf("Daily price($): ");
    scanf("%f",&newVehicle->price);
    printf("\n");
    newVehicle->next=NULL;

    if(*vhead==NULL){
        *vhead=newVehicle;
    }
    else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=newVehicle;
    }

    FILE *fp;
    fp=fopen("vehicle.txt","a");
    if(fp==NULL){
        printf("Error in opening file vehicle!\n");
        return;
    }

    //storing the data in file pointer
    fprintf(fp, "%s\n", newVehicle->plate_num);
    fprintf(fp, "%d\n", newVehicle->year);
    fprintf(fp, "%s\n", newVehicle->model);
    fprintf(fp, "%s\n", newVehicle->fuel_type);
    fprintf(fp, "%d\n", newVehicle->consumption);
    fprintf(fp, "%d\n", newVehicle->seats);
    fprintf(fp, "%.2f\n", newVehicle->price);
    fprintf(fp, "\n");

    fclose(fp);
}

struct Vehicle *readingListFromFile() {
    FILE *fv = fopen("vehicle.txt", "r");
    if (fv == NULL) {
        printf("Could not open file vehicle.\n");
        return NULL;
    }

    struct Vehicle *head = NULL;
    struct Vehicle *curr = NULL;
    struct Vehicle *newVehicle = NULL;

    while ((newVehicle = (struct Vehicle *)malloc(sizeof(struct Vehicle))) != NULL) {
        if (fscanf(fv, "%s\n%d\n%s\n%s\n%d\n%d\n%f\n\n",
                   newVehicle->plate_num,
                   &newVehicle->year,
                   newVehicle->model,
                   newVehicle->fuel_type,
                   &newVehicle->consumption,
                   &newVehicle->seats,
                   &newVehicle->price) == 7) {

            newVehicle->next = NULL;

            if (head == NULL) {
                head = newVehicle;
                curr = head;
            } else {
                curr->next = newVehicle;
                curr = curr->next;
            }
        } else {
            free(newVehicle);
            break;
        }
    }

    fclose(fv);
    return head;
}

void putIntoFile(struct Vehicle **vhead)
{
    FILE *fp=NULL;
    fp=fopen("vehicle.txt","w");
    if(fp==NULL)
    {
        printf("Could not open file vehicle!");
        return;
    }

    struct Vehicle *curr;
    curr=*vhead;

    while(curr!=NULL)
    {
        fprintf(fp,"%s\n%d\n%s\n%s\n%d\n%d\n%f\n\n",curr->plate_num,curr->year,curr->model,curr->fuel_type,curr->consumption,curr->seats,curr->price);
        curr=curr->next;
    }
    fclose(fp);
}

void displayAllInfo(struct Vehicle *vhead)
{
    struct Vehicle *curr;
    curr=vhead;

    if(vhead==NULL)
    {
        printf("There are no vehicles to display!");
        return;
    }
    else
    {
        while(curr!=NULL)
        {
            printf("Plate number: %s\n", curr->plate_num);
            printf("Year: %d\n", curr->year);
            printf("Model: %s\n", curr->model);
            printf("Fuel type: %s\n", curr->fuel_type);
            printf("Consumption(liters per km): %d\n", curr->consumption);
            printf("Seats: %d\n", curr->seats);
            printf("Price($): %.2f\n", curr->price);
            printf("\n");
            curr=curr->next;
        }
    }
}

void searchV(struct Vehicle *vhead){
    //searching plate number
    struct Vehicle *curr;
    curr=vhead;
    char searching[30];
    printf("Enter the license plate number: ");
    scanf("%s",searching);
    printf("\n");

    if(vhead==NULL){
        printf("There are no vehicles to search for!\n");
        return;
    }
    else{
        while(curr!=NULL){
            if(strcmp(searching,curr->plate_num)==0){
                printf("Plate number: %s\n", curr->plate_num);
                printf("Year: %d\n", curr->year);
                printf("Model: %s\n", curr->model);
                printf("Fuel type: %s\n", curr->fuel_type);
                printf("Consumption(liters per km): %d\n", curr->consumption);
                printf("Seats: %d\n", curr->seats);
                printf("Price($): %.2f\n", curr->price);
                printf("\n");
                break;
            }
            curr=curr->next;
        }
        if(curr==NULL){
            printf("Could not find vehicle.\n");
        }
    }
}

void sortingVehicles(struct Vehicle **vhead)
{
    char temp_pnum[30];
    int temp_year;
    char temp_model[30];
    char temp_fuel[30];
    int temp_consumption;
    int temp_seats;
    float temp_price;

    struct Vehicle *curr,*after;
    curr=*vhead;
    if(*vhead==NULL)
    {
        printf("There are no vehicles!");
        return;
    }
    while(curr!=NULL)
    {
        after=curr->next;
        while(after!=NULL)
        {
            if(after->price<=curr->price)
            {
                strcpy(temp_pnum,after->plate_num);
                strcpy(after->plate_num,curr->plate_num);
                strcpy(curr->plate_num,temp_pnum);

                temp_year=after->year;
                after->year=curr->year;
                curr->year=temp_year;

                strcpy(temp_model,after->model);
                strcpy(after->model,curr->model);
                strcpy(curr->model,temp_model);

                strcpy(temp_fuel,after->fuel_type);
                strcpy(after->fuel_type,curr->fuel_type);
                strcpy(curr->fuel_type,temp_fuel);

                temp_consumption=after->consumption;
                after->consumption=curr->consumption;
                curr->consumption=temp_consumption;

                temp_seats=after->seats;
                after->seats=curr->seats;
                curr->seats=temp_seats;

                temp_price=after->price;
                after->price=curr->price;
                curr->price=temp_price;
            }
            after=after->next;
        }
        curr=curr->next;
    }
}

void removeVehicle(struct Vehicle **vhead)
{
    if(*vhead==NULL)
    {
        printf("There are no vehicles!\n");
        return;
    }
    char plate_num_del[30];
    printf("Enter the license plate number of the vehicle you would like to delete from the list:\n");
    scanf("%s",plate_num_del);

    struct Vehicle *curr, *prev;
    curr=*vhead;
    prev=NULL;

    while(curr!=NULL)
    {
        if(strcmp(plate_num_del,curr->plate_num)==0)
        {
            if(prev==NULL)
            {
                *vhead=curr->next;
            }
            else
            {
                prev->next=curr->next;
            }
            printf("The vehicle with license plate number %s was deleted successfully!\n",plate_num_del);
            return;
        }
        prev=curr;
        curr=curr->next;
    }
    printf("The vehicle with license plate number %s was not found!\n", plate_num_del);
    free(curr);
}

void modifyVehicleInfo(struct Vehicle **vhead)
{
    struct Vehicle *curr;
    curr=*vhead;
    char searching[30];
    printf("Enter the license plate number: ");
    scanf("%s",searching);
    printf("\n");
    int modify;

    if(vhead==NULL)
    {
        printf("There are no vehicles to search for!\n");
        return;
    }
    else
    {
        while(curr!=NULL)
        {
            if(strcmp(searching,curr->plate_num)==0)
            {
                printf("Which information do you want to modify? Select one of the following options:\n\
                       1-Year\n\
                       2-Model\n\
                       3-Fuel Type\n\
                       4-Consumption\n\
                       5-Seats\n\
                       6-Daily Price\n");
                scanf("%d",&modify);
                switch(modify)
                {
                case 1:
                {
                    int myear;
                    printf("Enter the new year: \n");
                    scanf("%d",&myear);
                    curr->year=myear;
                    break;
                }
                case 2:
                {
                    char mmodel[30];
                    printf("Enter the new model: \n");
                    scanf("%s",mmodel);
                    strcpy(curr->model,mmodel);
                    break;
                }
                case 3:
                {
                    char mfuel[30];
                    printf("Enter the new fuel type: \n");
                    scanf("%s",mfuel);
                    strcpy(curr->fuel_type,mfuel);
                    break;
                }
                case 4:
                {
                    int mcons;
                    printf("Enter the new consumption in liters per km: \n");
                    scanf("%d",&mcons);
                    curr->consumption=mcons;
                    break;
                }
                case 5:
                {
                    int mseats;
                    printf("Enter the new number of seats: \n");
                    scanf("%d",&mseats);
                    curr->seats=mseats;
                    break;
                }
                case 6:
                {
                    float mprice;
                    printf("Enter the new price: \n");
                    scanf("%f",&mprice);
                    curr->price=mprice;
                    break;
                }
                default:
                {
                    printf("Invalid option selected! Please try again from the MENU!\n");
                    break;
                }
                }
                break;

            }
            curr=curr->next;
        }
        if(curr==NULL)
        {
            printf("Could not find vehicle.\n");
        }
    }
}
#endif // OTHER_VEHICLE_OPERATIONS_H_INCLUDED
