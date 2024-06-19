#ifndef KRISTI_H_INCLUDED
#define KRISTI_H_INCLUDED
#define MAX_PLATE_NUMBERS 1000


void addclint(CL **head, CL **newCL) {
    *newCL = (CL*)malloc(sizeof(CL));
    printf("Enter your information please (NAME, SURNAME, ID(3 NO), PASSPORT-ID, STATE, PHONE-NUMBER): ");
    scanf("%s %s %d %s %s %d", (*newCL)->name, (*newCL)->surname, &(*newCL)->ID, (*newCL)->PASSID, (*newCL)->State, &(*newCL)->PHnumber);
    (*newCL)->next = NULL;

    if (*head == NULL) {
        *head = *newCL;
    } else {
        CL* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *newCL;
    }

    FILE* fp2 = fopen("f10.txt", "a");
    if (fp2 == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(fp2, "%s %s %d %s %s %d\n", (*newCL)->name, (*newCL)->surname, (*newCL)->ID, (*newCL)->PASSID, (*newCL)->State, (*newCL)->PHnumber);
    fclose(fp2);
}

void max1()
{


    FILE* fp = fopen("f10.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");  // Check if the file opens or not
        return;
    }

    int idCount[1000] = {0}; // Assuming IDs range from 0 to 999
    char name[100], surname[100], pass[100], state[100];
    int fileID, phnumber;

    while (fscanf(fp, "%s %s %d %s %s %d", name, surname, &fileID, pass, state, &phnumber) != EOF)
    {
        idCount[fileID]++; // By incrementing the count for each fileID encountered in the file, you can track the number of occurrences of each fileID.
    }

    fclose(fp);


    fp = fopen("f10.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }


    while (fscanf(fp, "%s %s %d %s %s %d", name, surname, &fileID, pass, state, &phnumber) != EOF)
    {
        if (idCount[fileID] >= 3)  // Print the IDs that appear more than 3 times
        {
            printf("ID: %d\n", fileID);
            printf("Name: %s\n", name);
            printf("Surname: %s\n", surname);
            printf("PASS ID: %s\n", pass);
            printf("STATE: %s\n", state);
            printf("PHONE NUMBER: 0%d\n", phnumber);
            printf("\n");

            // Reset the count for the printed ID to avoid duplicate printing
            idCount[fileID] = 0;
        }
    }

    fclose(fp);

}


void morecars()
{
    FILE* fp = fopen("allreservations.txt", "r");  // Open the file for reading
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char plate_num[100];
    char unique_plate_numbers[MAX_PLATE_NUMBERS][100];  // Array to store unique plate numbers
    int countMap[MAX_PLATE_NUMBERS] = {0};  // Array to store the count of each plate number
    int num_unique_plate_numbers = 0;  // Counter for the number of unique plate numbers
    int ID, ID2;
    char data[100], name[100];
    float price;
    int days;

    // Loop through the file and count the occurrences of each plate number
    while (fscanf(fp, "%d %s %d %s %s %f %d", &ID, data, &ID2, plate_num, name, &price,&days) != EOF)
    {
        int index = -1;
        for (int i = 0; i < num_unique_plate_numbers; i++)
        {
            if (strcmp(plate_num, unique_plate_numbers[i]) == 0)
            {
                index = i;
                break;
            }
        }
        if (index == -1)    // If the plate number is not found in the unique_plate_numbers array
        {
            strcpy(unique_plate_numbers[num_unique_plate_numbers], plate_num);  // Add it to the array
            index = num_unique_plate_numbers;
            num_unique_plate_numbers++;
        }
        countMap[index]++;  // Increment the count for the plate number
    }

    fclose(fp);  // Close the file

    // Sort the unique plate numbers based on their count in descending order
    for (int i = 0; i < num_unique_plate_numbers - 1; i++)
    {
        for (int j = i + 1; j < num_unique_plate_numbers; j++)
        {
            if (countMap[i] < countMap[j])
            {
                int tempCount = countMap[i];
                countMap[i] = countMap[j];
                countMap[j] = tempCount;

                char tempPlate[100];
                strcpy(tempPlate, unique_plate_numbers[i]);
                strcpy(unique_plate_numbers[i], unique_plate_numbers[j]);
                strcpy(unique_plate_numbers[j], tempPlate);
            }
        }
    }

    // Print the top three most reserved cars
    printf("Top three most reserved vehicles:\n");
    for (int i = 0; i < 3 && i < num_unique_plate_numbers; i++)
    {
        printf("Vehicle #%d\n", i + 1);
        printf("Plate Number: %s\n", unique_plate_numbers[i]);
        printf("Reservation Count: %d\n", countMap[i]);
        printf("\n");
    }
}


typedef struct albV1
{
    char plate_num[30];
    int year;
    char model[30];
    char fuel_type[30];
    int consumption;
    int seats;
    float price;

    struct albV1 *next;
} albV;



void available_vehicles(resvV** head1)
{
    albV* head = NULL;
    albV* newvechl;

    resvV* newresvechl;

    char plate_num1[30];
    int year1;
    char model1[30];
    char fuel_type1[30];
    int consumption1;
    int seats1;
    float price1;

    FILE* fp = fopen("vehicle.txt", "r");

    if (fp == NULL)
    {
        printf("The file does not open");
        return;
    }

    while (fscanf(fp, "%s %d %s %s %d %d %f", plate_num1, &year1, model1, fuel_type1, &consumption1, &seats1, &price1) != EOF)
    {
        newvechl = (albV*)malloc(sizeof(albV));
        strcpy(newvechl->plate_num, plate_num1);
        newvechl->year = year1;
        strcpy(newvechl->model, model1);
        strcpy(newvechl->fuel_type, fuel_type1);
        newvechl->consumption = consumption1;
        newvechl->seats = seats1;
        newvechl->price = price1;
        newvechl->next = NULL;

        if (head == NULL)
        {
            head = newvechl;
        }
        else
        {
            albV* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newvechl;
        }
    }

    fclose(fp);

    FILE* fp2 = fopen("allreservations.txt", "r");

    if (fp2 == NULL)
    {
        printf("The file does not open");
        return;
    }

    int ID, ID2;
    char data[100], name[200];
    float price;
    int day;
    int cnt;

    while (fscanf(fp2, "%d %s %d %s %s %f %d", &ID, data, &ID2, plate_num1, name, &price,&day) != EOF)
    {
        albV* temp = head;
        albV* prev = NULL;

        while (temp != NULL)
        {
            if (strcmp(temp->plate_num, plate_num1) == 0)
            {

                newresvechl = (resvV*)malloc(sizeof(resvV));
                strcpy(newresvechl->plate_num, plate_num1);
                strcpy(newresvechl->model, name);
                newresvechl->days = day;
                newresvechl->next = NULL;

                if (*head1 == NULL)
                {
                    *head1 = newresvechl;
                }
                else
                {
                    resvV* temp1 = *head1;
                    while (temp1->next != NULL)
                    {
                        temp1 = temp1->next;
                    }
                    temp1->next = newresvechl;
                }
                // Delete the node
                if (prev == NULL)
                {
                    // If the matched node is the head, update the head pointer
                    head = temp->next;
                    free(temp);
                    temp = head;
                }
                else
                {
                    prev->next = temp->next;
                    free(temp);
                    temp = prev->next;
                }

            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }

    fclose(fp2);

    albV* curr = head;

    while (curr != NULL)
    {
        printf("Model: %s  Plate_Number: %s\n", curr->model, curr->plate_num);
        curr = curr->next;
    }

    FILE* fp3 = fopen("currently_available_cars.txt", "w");

    if (fp3 == NULL)
    {
        printf("The file does not open");
        return;
    }

    curr = head;
    while (curr != NULL)
    {
        fprintf(fp3, "Model: %s\n", curr->model);
        fprintf(fp3, "Plate Number: %s\n", curr->plate_num);
        fprintf(fp3, "\n");
        curr = curr->next;
    }

    fclose(fp3);
}

void reservt1(resvV** head1)
{
    albV* head = NULL;
    albV* newvechl;

    resvV* newresvechl;
    * head1 = NULL;

    char plate_num1[30];
    int year1;
    char model1[30];
    char fuel_type1[30];
    int consumption1;
    int seats1;
    float price1;

    FILE* fp = fopen("vehicle.txt", "r");

    if (fp == NULL)
    {
        printf("The file does not open");
        return;
    }

    while (fscanf(fp, "%s %d %s %s %d %d %f", plate_num1, &year1, model1, fuel_type1, &consumption1, &seats1, &price1) != EOF)
    {
        newvechl = (albV*)malloc(sizeof(albV));
        strcpy(newvechl->plate_num, plate_num1);
        newvechl->year = year1;
        strcpy(newvechl->model, model1);
        strcpy(newvechl->fuel_type, fuel_type1);
        newvechl->consumption = consumption1;
        newvechl->seats = seats1;
        newvechl->price = price1;
        newvechl->next = NULL;

        if (head == NULL)
        {
            head = newvechl;
        }
        else
        {
            albV* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newvechl;
        }
    }

    fclose(fp);

    FILE* fp2 = fopen("allreservations.txt", "r");

    if (fp2 == NULL)
    {
        printf("The file does not open");
        return;
    }

    int ID, ID2;
    char data[100], name[200];
    float price;
    int day;

    while (fscanf(fp2, "%d %s %d %s %s %f %d", &ID, data, &ID2, plate_num1, name, &price, &day) != EOF)
    {
        albV* temp = head;
        albV* prev = NULL;

        while (temp != NULL)
        {
            if (strcmp(temp->plate_num, plate_num1) == 0)
            {
                newresvechl = (resvV*)malloc(sizeof(resvV));
                strcpy(newresvechl->plate_num, plate_num1);
                strcpy(newresvechl->model, name);
                newresvechl->days = day;
                newresvechl->next = NULL;

                if (*head1 == NULL)
                {
                    *head1 = newresvechl;
                }
                else
                {
                    resvV* temp1 = *head1;
                    while (temp1->next != NULL)
                    {
                        temp1 = temp1->next;
                    }
                    temp1->next = newresvechl;
                }

                if (prev == NULL)
                {
                    head = temp->next;
                    free(temp);
                    temp = head;
                }
                else
                {
                    prev->next = temp->next;
                    free(temp);
                    temp = prev->next;
                }
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }

    fclose(fp2);

    FILE* fp4 = fopen("f2.txt", "w");

    if (fp4 == NULL)
    {
        printf("The file does not open");
        return;
    }

    resvV* curr_resv = *head1;

    while (curr_resv != NULL)
    {
        fprintf(fp4, "Reserved Car:\n");
        fprintf(fp4, "Model: %s\n", curr_resv->model);
        fprintf(fp4, "Plate Number: %s\n", curr_resv->plate_num);
        fprintf(fp4, "Days Reserved: %d\n", curr_resv->days);
        fprintf(fp4, "\n");
        curr_resv = curr_resv->next;
    }

    fclose(fp4);

    curr_resv = *head1;

    while (curr_resv != NULL)
    {
        printf("Reserved Car:\n");
        printf("Model: %s\n", curr_resv->model);
        printf("Plate Number: %s\n", curr_resv->plate_num);
        printf("Days Reserved: %d\n", curr_resv->days);
        printf("\n");
        curr_resv = curr_resv->next;
    }
}

#endif // KRISTI_H_INCLUDED
