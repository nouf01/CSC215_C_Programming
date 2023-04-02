#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const double epsilon = 0.0001;
int countR , countV ;

struct Activity{
    char name[35];
    double price;
    char startDate[13];
    char endDate[13];
    int counter[6][31];
    int passAge;
    int rAge;
}activityList[20];

static int activityListCounter;

struct Companion{
    int id;
    char name[20];
    int age;
    char gender;
    char Address[7];
    struct Companion* next;
};

struct Attendee{
    int id;
    char name[20];
    int age;
    char date[10];
    char* state;
    char Address[7];
    struct Activity* ActivityZone;
    int numOfCompanion;
    struct Companion* compList;
    double activityFee;
    double totalFees;
    double balance;
    struct Attendee* next;
};



void addNewAttendee(struct Attendee** ,struct Attendee**);
int checkLimit(struct Activity** , char* , int);
void testList(struct Attendee** );
void addNewCompanion(struct Attendee* );
void editRecord(struct Attendee **head);
void editActivity(int index);
void deleteCompanions(struct Companion *head, struct Companion *prev, struct Companion *last);
void showattendeereport ();
void showattendee(struct Attendee** rList , struct Attendee** vList);
void printAttendees(struct Attendee *Array , char ch);
void testByDate(struct Attendee** , char*);
void writeattendee (char* , struct Attendee *);
void deleterecord(struct Attendee** rList,struct Attendee** vList, int id);
void printList(struct Attendee** rList,struct Attendee** vList);

int main(){

    FILE* activFile;
    activFile = fopen("Activities.txt","r");
    if (activFile == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    char empt[150];// to read empty spaces
    char header[150];
    fgets(header,149,activFile);
    fgets(empt,149,activFile);// empty Line
    int i =0;
    while(!feof(activFile)){
        fgets(activityList[i].name,32,activFile);
        char strPrice[30];
        fgets(strPrice,25,activFile);
        activityList[i].price = atoi(strPrice);
        fgets(activityList[i].startDate,11,activFile);
        fgets(empt,2,activFile);
        fgets(activityList[i].endDate,11,activFile);
        fgets(empt,16,activFile);
        char strPass[50];
        fgets(strPass,20,activFile);
        activityList[i].passAge = atoi(strPass);
        fgets(empt,2,activFile);
        char strRest[30];
        if(fgets(strRest,10,activFile) == NULL)
            activityList[i].rAge = 0;
        else
            activityList[i].rAge = atoi(strRest);
        i++;
    }
    //intilize counter to zeros
    for(int a=0; a<activityListCounter; a++){
        for(int m =0; m<6; m++){
            for(int d =1; d<31; d++){
                activityList[a].counter[m][d] = 0;
            }
        }
    }

    activityListCounter =i;

    MENU:printf("-------------------- \nWELCOME TO \nRiyadh Season 2021 \nImagine, MORE!! \n--------------------\n");
    printf("%s",header);
    for(int k=0; k<activityListCounter; k++){
        printf("%s\t",activityList[k].name);
        printf("%.2f\t\t",activityList[k].price);
        printf("%s-",activityList[k].startDate);
        printf("%s\t\t",activityList[k].endDate);
        if(activityList[k].passAge==0)
            printf("-\t\t\t\t");
        else
            printf("<%d\t\t\t\t",activityList[k].passAge);
        if(activityList[k].rAge==0)
            printf("-\t\t\t\t");
        else
            printf(">%d\t\t\t\t",activityList[k].rAge);
        printf("\n");
    }

    //Creating Attendees Linked List:
    struct Attendee* registered;
    struct Attendee* singleVisit;


    //show menu
    int input;
    do{
        printf("*******************************************\n");
        printf("Enter the corresponding no\n");
        printf("1.Add new attendee record\n");
        printf("2.Search or edit record\n");
        printf("3.Edit attendee\n");
        printf("4.Edit activity\n");
        printf("5.Show report\n");
        printf("6.Know the records of attendees\n");
        printf("7.Delete the records\n");
        printf("8.Exit from the program\n");
        scanf("%d",&input);

        switch(input){
            case 1:
                //call method addNewAttendee()
                addNewAttendee(&registered,&singleVisit);
                break;
            case 2:{
                //call method editrecord()
                editRecord(&registered);
                testList(&registered);
            }
                break;
            case 3:{
                //call method editrecord() //Same as previous case because editRecord() both search and edit.
                editRecord(&registered);
                testList(&registered);
            }
                break;
            case 4:{
                //call method editactivity()
                editActivity(activityListCounter);
                goto MENU; // to show the changes happened in the activityList[]
                break;
            }
            case 5:
                //call method showattendeereport()
                showattendeereport(&registered,&singleVisit);
                break;
            case 6:
                //call method showattendee():
                showattendee(&registered,&singleVisit);
                break;
            case 7:{
                //call method deleterecord():
                int theID;
                printf("\n Enter Attende ID: ");
                scanf("%d",&theID);
                deleterecord(&registered,&singleVisit,theID);
                break;
            }
            case 8:
                break;
        }

    }while(input != 8);

    showattendeereport(&registered,&singleVisit);
    printList(&registered,&singleVisit);
    return 0;
}

void addNewAttendee(struct Attendee** rList,struct Attendee** vList){
    //create new attendee
    struct Attendee* temp = (struct Attendee*) malloc(sizeof(struct Attendee));
    if(temp == NULL){
        return;
    }
    //read data
    char clean[20];
    char lName[20];
    printf("Enter Attendee ID:");
    scanf("%d",&temp->id);
    printf("\nEnter Attendee Name:");
    scanf("%s",temp->name);
    scanf("%s",lName);
    strcat(temp->name,lName);

    int intState;
    char state;
    printf("\nChoose state of attendee \n1: Registered Visitor \n2: Single Visitor\n");
    scanf("%d",&intState);
    if(intState == 1){
        temp->state = "R";
        printf("\nThe State is: %s",temp->state);
    }
    else if(intState == 2){
        temp->state = "V";
        printf("\nThe State is: %s",temp->state);
    }

    printf("\nEnter Attendee Age:");
    scanf("%d",&temp->age);


    printf("\nEnter the address of Attendee:");
    scanf("%s",temp->Address);
    //choose activity
    printf("\nChoose Activity no:\n");
    int s;
    for(s =0; s<activityListCounter; s++){
        printf("%d . %s \n",(s+1) , activityList[s].name);
    }
    int act;
    scanf("%d",&act);;
    temp->ActivityZone = &activityList[act - 1];
    temp->activityFee = temp->ActivityZone->price;
    printf("\nPrice for one Ticket is:%.2lf",temp->activityFee);
    //check foe seats
    printf("\nChoose date between (%s) and (%s):\n",temp->ActivityZone->startDate, temp->ActivityZone->endDate);
    scanf("%s",temp->date);

    if(checkLimit(&temp->ActivityZone, temp->date,1) == 0){
        printf("\nSorry Re Register Again:");
        return;
    }

    if(strcmp(temp->state,"R") == 0){
        printf("\nEnter number of companions:");
        scanf("%d",&temp->numOfCompanion);

        for(int i=0; i<temp->numOfCompanion; i++)
            addNewCompanion(temp);


        //calculate total fees
        temp->totalFees = temp->activityFee;
        struct Companion * currentComp = temp->compList;
        for(int k=0; k<temp->numOfCompanion; k++){
            if(currentComp == NULL)
                break;
            if(currentComp->age >= temp->ActivityZone->passAge){
                temp->totalFees = temp->totalFees + temp->activityFee;
            }
            currentComp = currentComp->next;
        }
    }//end register 'R'

    else if(strcmp(temp->state,"V") == 0){
        temp->totalFees = temp->activityFee;
        temp->numOfCompanion =0;
    }

    //charge balance:
    printf("\nYour total Total Fees: %.2lf",temp->totalFees);
    int wrong =1;
    do{
        double charge;
        printf("\nEnter the balance you want to charge:");
        scanf("%lf",&charge);
        if(temp->balance < 0)
           printf("Negative number not allowed!!");
        if(strcmp(temp->state,"V") == 0){
           if(fabs(charge - temp->activityFee)< epsilon){//double comparison not work with == so i use fabs()
                temp->balance = charge;
                wrong =0;
           }
            else
                 printf("Your charge should be equal to the Activity Fee!");
        }
        else if(strcmp(temp->state,"R") == 0){
            if(charge >= temp->totalFees){
               temp->balance = charge;
               wrong =0;
            }
            else
               printf("Your charge should be greater than or equal to the total fees");
        }
    }while(wrong == 1);

    //add to the linked list

    if(strcmp(temp->state,"V") == 0){
        if((*vList) == NULL){//list is still empty
            (*vList) = temp;
            printf("Attendee Added Successfully\n");
        }
        else{
            struct Attendee * current = (*vList);
            while (current->next != NULL)
                current = current->next;
            current->next = temp;
            printf("Attendee Added Successfully\n");
        }
        writeattendee("SingleVisit.txt",temp);
    }
    else if(strcmp(temp->state,"R") == 0){
        if((*rList) == NULL){//list is still empty
            (*rList) = temp;
            printf("Attendee Added Successfully\n");
        }
        else{
            struct Attendee* current = (*rList);
            while (current->next != NULL)
                current = current->next;
            current->next = temp;
            printf("Attendee Added Successfully\n");
        }
        writeattendee("Registered.txt",temp);
    }

    //test list content
    printf("\nChoose no. :\n");
    printf("1. Test Reigster Content\n");
    printf("2. Test Visitor Content\n");
    printf("3. Return to main\n");
    int cho;
    scanf("%d",&cho);
    if(cho == 1)
        testList(rList);
    else if(cho == 2)
        testList(vList);

}

int checkLimit(struct Activity** actv, char* date, int addOrSub){

    char* monthC = strchr(date,'/');
    monthC = monthC +1;
    char* dayC = strrchr(date,'/');
    dayC = dayC +1;

    int month = atoi(monthC);
    int day = atoi(dayC);

    if(addOrSub == 1){
        if(month >= 10){
            if((*actv)->counter[month-10][day] <= 49){
                (*actv)->counter[month-10][day] ++;
                printf("\nTotal Attendees in this Date: %d\n",(*actv)->counter[month-10][day]);
                return 1;
            }
            else{
                printf("No Available Seats on this date");
                return 0;
            }
        }
        else{
            if((*actv)->counter[month+2][day]  <= 49){
                (*actv)->counter[month+2][day] ++;
                printf("\nTotal Attendees in this Date: %d\n",(*actv)->counter[month+2][day]);
                return 1;
            }
            else{
                printf("No Available Seats on this date");
                return 0;
            }
        }
    }
    else if(addOrSub == 0){
        if(month >= 10){
            (*actv)->counter[month-10][day]--;
            printf("\nTotal Attendees in this Date: %d\n",(*actv)->counter[month-10][day]);
            return 1;
        }
        else{
            (*actv)->counter[month+2][day]--;
            printf("\nTotal Attendees in this Date: %d\n",(*actv)->counter[month+2][day]);
            return 1;
        }
    }
    else
        return 0;
}
void testList(struct Attendee** List){
        struct Attendee* crnt = (*List);
        printf("****%s List Content****",crnt->state);
        while((crnt)->next != NULL){
            printf("\nID: %d\n",(crnt)->id);
            printf("Name: %s\n",(crnt)->name);
            printf("Age: %d\n",(crnt)->age);
            printf("Address: %s\n",(crnt)->Address);
            printf("State: %s\n",(crnt)->state);
            printf("Activity Name %s\n",(crnt)->ActivityZone->name);
            printf("Activity Fee: %.2lf\n",(crnt)->activityFee);
            printf("Total Fees: %.2lf\n",(crnt)->totalFees);
            printf("Balance: %.2lf\n",(crnt)->balance);
            printf("Date: %s \n",(crnt)->date);
            if((crnt)->numOfCompanion > 0){
                printf("$$$ Companions $$$");
                struct Companion* comps = (crnt)->compList;
                for(int i=0; i<(crnt)->numOfCompanion; i++){
                    printf("\nID: %d\n",comps->id);
                    printf("Name: %s\n",comps->name);
                    printf("Age: %d\n",comps->age);
                    printf("Gender: %c\n",comps->gender);
                    printf("Address: %s\n",comps->Address);
                    comps = comps->next;
                }
            }
            (crnt) = (crnt)->next;
        }
        // for last node
        printf("\nID: %d\n",(crnt)->id);
        printf("Name: %s\n",(crnt)->name);
        printf("Age: %d\n",(crnt)->age);
        printf("Address: %s\n",(crnt)->Address);
        printf("State: %s\n",(crnt)->state);
        printf("Activity Name %s\n",(crnt)->ActivityZone->name);
        printf("Activity Fee: %.2lf\n",(crnt)->activityFee);
        printf("Total Fees: %.2lf\n",(crnt)->totalFees);
        printf("Balance: %.2lf\n",(crnt)->balance);
        printf("Date: %s \n",(crnt)->date);
        if((crnt)->numOfCompanion > 0){
            printf("$$$ Companions $$$");
            struct Companion* comps = (crnt)->compList;
            for(int i=0; i<(crnt)->numOfCompanion; i++){
                printf("\nID: %d\n",comps->id);
                printf("Name: %s\n",comps->name);
                printf("Age: %d\n",comps->age);
                printf("Gender: %c\n",comps->gender);
                printf("Address: %s\n",comps->Address);
                comps = comps->next;
            }
        }
}


void addNewCompanion(struct Attendee* temp){
    struct Companion* tempComp = (struct Companion*) malloc(sizeof(struct Companion));
    if(tempComp == NULL){
        return;
    }
    char lName[20];
    printf("\nEnter companion ID:\n");
    scanf("%d",&tempComp->id);
    printf("Enter companion Name:");
    scanf("%s",tempComp->name);
    scanf("%s",lName);
    strcat(tempComp->name,lName);
    printf("Enter companion Age:\n");
    scanf("%d",&tempComp->age);
    if(tempComp->age < temp->ActivityZone->rAge){
        printf("To enter this activity age should be >%d",temp->ActivityZone->rAge);
        return;
    }
    char x;//to clean
    scanf("%c",&x);
    printf("Enter companion Gender:\n");
    scanf("%c",&tempComp->gender);
    printf("Enter companion Address");
    scanf("%s",tempComp->Address);
    if( (temp->compList) == NULL){//first companion in the list
        temp->compList = tempComp;
        //increase counter
        if(checkLimit(&temp->ActivityZone, temp->date,1) == 0){
            printf("\nSorry Re Register Again:");
            return;
        }
    }
    else{
        struct Companion * currentComp = temp->compList;
        while (currentComp->next != NULL)
            currentComp = currentComp->next;
        currentComp->next = tempComp;
        //increase counter
        if(checkLimit(&temp->ActivityZone, temp->date,1) == 0){
            printf("\nSorry Re Register Again:");
            return;
        }
    }
}//end companion list

void editRecord(struct Attendee **head){ // added it to have a refrence to the head of the list
    int id, edit, check = 0, numComp;
    printf("Enter attendee's id: ");
    scanf("%d", &id);
    struct Attendee *tmp = *head;
    struct Companion *prev, *last;
    while (tmp != NULL){ // To search if the id exists
        if (tmp->id == id){
            check = 1;
            break;
        }
        tmp = tmp->next;
    }
    if (check == 0){
        printf("Attendee doesn't exist or is a single visitor\n");
        return;
    }
    struct Companion *headComp = tmp->compList;
    printf("Do you want to add or delete companions? (1: add) or (2: delete)");
    scanf("%d", &edit);
    if (edit == 1){
        printf("How many companions do you want to add?");
        scanf("%d", &numComp);
        for (int i = 0; i < numComp; i++){
            addNewCompanion(tmp);
            tmp->numOfCompanion++;
        }

        //calculate total fees
        tmp->totalFees = tmp->activityFee;
        struct Companion * currentComp = tmp->compList;
        for(int k=0; k<tmp->numOfCompanion; k++){
            if(currentComp == NULL)
                break;
            if(currentComp->age >= tmp->ActivityZone->passAge){
                tmp->totalFees = tmp->totalFees + tmp->activityFee;
            }
            currentComp = currentComp->next;
        }
        printf("\n Your Total Fees Now: %.2lf \n",tmp->totalFees);
        double charge;
        if (tmp->totalFees > tmp->balance){
            printf("The number of companions exceeded the balance, please change your balance\n");
            printf("\nEnter the balance you want to charge:");
            scanf("%lf",&charge);
            if(tmp->totalFees > charge){
                printf("\n The balance is not enough, The list of companions will not change");
                deleteCompanions(headComp, prev, last);
                for (int i = 0; i < numComp; i++){
                    deleteCompanions(headComp, prev, last);
                    tmp->numOfCompanion--;
                    checkLimit(&tmp->ActivityZone, tmp->date,0); // to decrement activity counter;
                }
                return;
            }
            else{
                tmp->balance = charge;
                printf("Balance updated successfully");
            }
        }

        printf("Companions added successfully! \n");
    }
    if (edit == 2){
        if (tmp->numOfCompanion == 0){ // In case there are no companions
            printf("You don't have any registered companions to delete. \n");
            return;
        }
        printf("How many companions do you want to delete? ");
        scanf("%d", &numComp);
        for (int i = 0; i < numComp; i++){
            deleteCompanions(headComp, prev, last);
            tmp->numOfCompanion--;
            checkLimit(&tmp->ActivityZone, tmp->date,0);// to decrement activity counter;
        }
        printf("Delete is done successfuly\n");
    }
}

void deleteCompanions(struct Companion *head, struct Companion *prev, struct Companion *last){
    if (head != NULL){
        if (head->next == NULL){ // In case ony one companion in list
            head = NULL;
            return;
        }
        else {
            prev = head;
            while (prev->next->next != NULL)
                prev = prev->next;
            last = prev->next;
            prev->next = NULL;
            free(last);
        }
    }
}

void editActivity(int index){ //The i in the main to know the index of the next activity
    int indexActivity;
    char x;
    int y;
    char clean[20];
    //choose activity
    printf("\nChoose Activity no: (The Activity you want to edit)\n");
    int s;
    for(s =0; s<index; s++){
        printf("%d . %s \n",(s+1) , activityList[s].name);
    }
    printf("%d . Add new Activity \n",s+1);
    int act;
    scanf("%d",&act);;
    int check = 0;

    if (act < s+1){
            check = 1;
            indexActivity = act -1;
    }

    if (check == 0){ // Activity doesn't exist so I have to ask user to add its info
        printf("The activity doesn't exist, so add its information as follows:\n");
        printf("Enter new activity name: \n");
        scanf("%s",activityList[index].name);
        scanf("%s",clean);
        strcat(activityList[index].name, clean);
        strcat(activityList[index].name, "\t\t");
        printf("Enter the price of the activity: ");
        scanf(" %lf", &activityList[index].price);
        printf("Enter the start date: ");
        scanf(" %s", activityList[index].startDate);
        printf("Enter the end date: ");
        scanf(" %s", activityList[index].endDate);
        printf("Enter the free pass age or 0 if there is no free pass: ");
        scanf(" %d", &activityList[index].passAge);
        printf("Enter the restricted age or 0 if there is no restricted age: ");
        scanf(" %d", &activityList[index].rAge);
        activityListCounter++;
    }

    if (check == 1){ // Activity exists and user can edit the price, start date, and end date only
        struct Activity* actv = &activityList[indexActivity];
        int temp;
        printf("You can only edit the price, start date, and end date \n");
        printf("Do you want to edit the price? (1: yes) or (0: no) ");
        scanf("%d", &temp);
        if (temp == 1){
            printf("Enter the new price of activity: ");
            scanf("%lf", & actv->price);
        }
        //scanf("%s",claen);
        printf("Do you want to edit the start date? (1: yes) or (0: no) ");
        scanf(" %d", &temp);
        if (temp == 1){
            printf("Enter the new start date: ");
            scanf("%s", actv->startDate);
        }
        printf("Do you want to edit the end date? (1: yes) or (0: no) ");
        scanf("%d", &temp);
        if (temp == 1){
            printf("Enter the new end date: ");
            scanf("%s", actv->endDate);
        }
    }
}

void showattendeereport (struct Attendee** rList,struct Attendee** vList){
    //total attendees’numbers for each activity
    printf("The total attendees’ numbers for each activity : \n");
    for(int a = 0 ; a<activityListCounter ; a++){
        int count = 0;
        for (int i = 0 ; i <6 ; i++){
            for(int j=1; j<31; j++){
                count +=  activityList[a].counter[i][j];
            }
        }
        printf("%s : %d \n",activityList[a].name,count);
    }

    //attendees’ numbers for each activity by date
    printf("Please Enter a Date using this format yyyy/mm/dd to show its attendees’ numbers in each Activity: ");
    char date1[10];
    scanf("%s",date1);//we have 150 days, and 10 activity, it's not effecient to list them all so we read the date from user
    char* monthC = strchr(date1,'/');
    monthC = monthC +1;
    char* dayC = strrchr(date1,'/');
    dayC = dayC +1;

    int m = atoi(monthC);
    int d = atoi(dayC);
    printf("The attendees’ numbers for each activity on %s : \n",date1);
        if(m >= 10 )
            m -= 10;
        else
            m += 2;
    for(int a = 0 ; a <activityListCounter ; a++)
        printf("%s : %d \n",activityList[a].name,activityList[a].counter[m][d]);

    /*total attendees’ numbers for each date
    we have 150 days, and 10 activity,
    it's not effecient to list them all so we will read the date from user*/
    printf("\nPlease Enter a Date using this format yyyy/mm/dd to show its attendees’ numbers in all Activities: ");
    scanf("%s",date1);
    monthC = strchr(date1,'/');
    monthC = monthC +1;
    dayC = strrchr(date1,'/');
    dayC = dayC +1;
    m = atoi(monthC);
    d = atoi(dayC);
    if(m >= 10 )
        m -= 10;
    else
        m += 2;
    int countDate =0;
    for(int a =0; a<activityListCounter; a++){
        countDate = countDate + activityList[a].counter[m][d];
    }
    m = atoi(monthC);
    d = atoi(dayC);
    if(m >= 10)
        printf("\n-- total attendees’ numbers for %s is : %d",date1,countDate);
    if(m < 10)
        printf("\n-- total attendees’ numbers for %s is : %d",date1,countDate);
    // total income coming from all activities by dates
    printf("\nPlease Enter a Date using this format yyyy/mm/dd to show its total income: ");
    scanf("%s",date1);
    monthC = strchr(date1,'/');
    monthC = monthC +1;
    dayC = strrchr(date1,'/');
    dayC = dayC +1;
    m = atoi(monthC);
    d = atoi(dayC);
    if(m >= 10 )
        m -= 10;
    else
        m += 2;
    double income =0.0;
    struct Attendee* crnt = (*vList);
    if(crnt != NULL){
    while((crnt)->next != NULL){
        if(strcmp(crnt->date,date1) == 0){
            income = income + crnt->totalFees;
        }
        crnt = crnt->next;
    }
    if(strcmp(crnt->date,date1) == 0){
        income = income + crnt->totalFees;
    }
    }
    //R list
    crnt = (*rList);
    if(crnt != NULL){
    while((crnt)->next != NULL){
        if(strcmp(crnt->date,date1) == 0){
            income = income + crnt->totalFees;
        }
        crnt = crnt->next;
    }
    if(strcmp(crnt->date,date1) == 0){
        income = income + crnt->totalFees;
    }
    }
    printf("\nThe total income coming from all activities on %s is:  %.2lf\n",date1, income);
}


void showattendee(struct Attendee** rList,struct Attendee** vList){
    int chois;
    struct Attendee *current;
    do{
        printf("\nEnter the corresponding no");
        printf("\n1.Records of attendees in alphabetical order");
        printf("\n2.Records of single visit attendees");
        printf("\n3.Records of registered attendees");
        printf("\n4.Records in particular date");
        printf("\n5.Return to main menu");
        scanf("%d",&chois);

        char date[10];
        switch(chois){

            case 1:{
            //to sort the registered attendees
                printf("** Records of registered attendees in alphabetical order : **");
                current = *rList;
                struct Attendee *rListsorted;
                //to coppy
                for (int i = 0; current!=NULL ; i++){
                    *(rListsorted+i) = *current;
                    current = current->next ;}

                for (int s = 0; s < countR ; s++) {
                    for (int i = 0 ; i < countR-s-1 ; i++ )
                    if (  strcmp((rListsorted+i)->name , (rListsorted+i+1)->name ) > 0  ){
                        struct Attendee temp = *(rListsorted+i);
                        *(rListsorted+i) = *(rListsorted+i+1);
                        *(rListsorted+i+1) = temp;}}
                    printAttendees(rListsorted,'R');
            //to sort the visited attendees
                printf("** Records of single visit attendees in alphabetical order : **");
                struct Attendee *vListsorted;
                current = *vList;
                for (int i = 0; current!=NULL ; i++){
                    *(vListsorted+i) = *current;
                    current = current->next ;}
                for (int s = 0; s < countV ; s++) {
                    for (int i = 0 ; i < countV-s-1 ; i++ )
                    if (  strcmp((vListsorted+i)->name , (vListsorted+i+1)->name ) > 0  ){
                        struct Attendee temp = *(vListsorted+i);
                        *(vListsorted+i) = *(vListsorted+i+1);
                        *(vListsorted+i+1) = temp;}
                    }printAttendees(vListsorted,'V');
                break;
            }
            case 2:{
                if(*vList != NULL)
                    testList(vList);
                break;
            }
            case 3:{
                if(*rList != NULL)
                    testList(rList);
                break;
            }

            case 4:{
                printf("Please Enter a Date using this format yyyy/mm/dd : ");
                scanf("%s",date);
                if(*vList != NULL && *rList != NULL){
                    testByDate(rList,date);
                    testByDate(vList,date);
                }
                break;
            }
            case 5:
                return;
        }//end switch
    }while(chois!=5);
    }//end the method

void printAttendees(struct Attendee *Array , char ch){

        switch(ch){
            case'R':
                printf("%-10s%-10s%-10s%-10s%-10s%-10s%-20s%-20s%-20s%-20s%-20s%-10s\n","id","name","age",
                            "date", "state", "Address", "activityZone", "numOfCompanion",
                            "listOfCompanion", "activityFee" ,"totalFees", "balance");

                for (int i = 0; i < countR ; i++) {
                 printf("%-10d%-10s%-10d%-10s%-10s%-10s%-20d",(Array+i)->id,(Array+i)->name
                        ,(Array+i)->age,(Array+i)->date,(Array+i)->state,(Array+i)->Address
                        ,(Array+i)->numOfCompanion);//,*(Array+i)->ActivityZone
                 //print the list Of Companion//
                 if((Array+i)->numOfCompanion == 0)//if there are NO Companion
                     printf("%-20s","{}");
                 if((Array+i)->numOfCompanion > 0){//if there are Companion
                 printf("{");
                    for (int j = 0; j < (Array+i)->numOfCompanion; j++) {
                       printf("{%d%s%d%c%s}\n",(Array+i)->compList->id,(Array+i)->compList->name
                            ,(Array+i)->compList->age,(Array+i)->compList->gender,(Array+i)->compList->Address);
                    }printf("}");}//end if
                printf("%-20lf%-20lf%-10lf\n", (Array+i)->activityFee ,(Array+i)->totalFees,(Array+i)->balance);

                }break;

            case'V':
                printf("%-10s%-10s%-10s%-10s%-10s%-10s%-20s%-20s%-20s%-10s\n","id","name","age",
                            "date", "state", "Address", "activityZone","activityFee" ,"totalFees", "balance");

                for (int i = 0; i < countR ; i++) {
                 printf("%-10d%-10s%-10d%-10s%-10s%-10s%-20lf%-20lf%-10lf\n",(Array+i)->id,(Array+i)->name
                        ,(Array+i)->age,(Array+i)->date,(Array+i)->state,(Array+i)->Address
                         , (Array+i)->activityFee ,(Array+i)->totalFees,(Array+i)->balance);

                }break;

        }//ens switch
}

void testByDate(struct Attendee** List , char* date){
        struct Attendee* crnt = (*List);
        printf("****%s List Content****",crnt->state);
        while((crnt)->next != NULL){
            if(strcmp(crnt->date,date) == 0){
            printf("\nID: %d\n",(crnt)->id);
            printf("Name: %s\n",(crnt)->name);
            printf("Age: %d\n",(crnt)->age);
            printf("Address: %s\n",(crnt)->Address);
            printf("State: %s\n",(crnt)->state);
            printf("Activity Name %s\n",(crnt)->ActivityZone->name);
            printf("Activity Fee: %.2lf\n",(crnt)->activityFee);
            printf("Total Fees: %.2lf\n",(crnt)->totalFees);
            printf("Balance: %.2lf\n",(crnt)->balance);
            printf("Date: %s \n",(crnt)->date);
            if((crnt)->numOfCompanion > 0){
                printf("$$$ Companions $$$");
                struct Companion* comps = (crnt)->compList;
                for(int i=0; i<(crnt)->numOfCompanion; i++){
                    printf("\nID: %d\n",comps->id);
                    printf("Name: %s\n",comps->name);
                    printf("Age: %d\n",comps->age);
                    printf("Gender: %c\n",comps->gender);
                    printf("Address: %s\n",comps->Address);
                    comps = comps->next;
                }
            }
            }
            (crnt) = (crnt)->next;
        }
        // for last node
        if(strcmp(crnt->date,date) == 0){
        printf("\nID: %d\n",(crnt)->id);
        printf("Name: %s\n",(crnt)->name);
        printf("Age: %d\n",(crnt)->age);
        printf("Address: %s\n",(crnt)->Address);
        printf("State: %s\n",(crnt)->state);
        printf("Activity Name %s\n",(crnt)->ActivityZone->name);
        printf("Activity Fee: %.2lf\n",(crnt)->activityFee);
        printf("Total Fees: %.2lf\n",(crnt)->totalFees);
        printf("Balance: %.2lf\n",(crnt)->balance);
        printf("Date: %s \n",(crnt)->date);
        if((crnt)->numOfCompanion > 0){
            printf("$$$ Companions $$$");
            struct Companion* comps = (crnt)->compList;
            for(int i=0; i<(crnt)->numOfCompanion; i++){
                printf("\nID: %d\n",comps->id);
                printf("Name: %s\n",comps->name);
                printf("Age: %d\n",comps->age);
                printf("Gender: %c\n",comps->gender);
                printf("Address: %s\n",comps->Address);
                comps = comps->next;
            }
        }
    }
}

void writeattendee (char* fileName, struct Attendee *newAttendee){
    FILE *fpo;
    fpo = fopen(fileName, "a");
    if (fpo == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    fseek(fpo, 0, SEEK_END);
    int len = ftell(fpo);
    if (len == 0)
    {
        if (strcmp(fileName,"SingleVisit.txt") == 0){
            fprintf(fpo,"SingleVisit\n");
            fprintf(fpo,"id\tname\tage\tAddress\tactivity zone\tactivity fee\tbalance\n");
        }
        else
        {
            fprintf(fpo,"Registered\n");
            fprintf(fpo,"id\tname\tage\tAddress\tactivity zone\tnum of companion\tactivity fee\tbalance\n");
        }
    }

    if (strcmp(fileName,"SingleVisit.txt") == 0)
    {
       fprintf(fpo,"%d\t%s\t%d\t%s\t%s\t%lf\t%lf\n",newAttendee->id, newAttendee->name,newAttendee->age,newAttendee->Address,newAttendee->ActivityZone->name,
                                               newAttendee->activityFee,newAttendee->balance - newAttendee->totalFees);
    }
    else
    {
        fprintf(fpo,"%d\t%s\t%d\t%s\t%s\t%d\t%lf\t%lf\n",newAttendee->id, newAttendee->name,newAttendee->age,newAttendee->Address,newAttendee->ActivityZone->name,
                                               newAttendee->numOfCompanion,newAttendee->activityFee, newAttendee->balance - newAttendee->totalFees);
    }

    fclose(fpo);
}

void deleterecord(struct Attendee** rList,struct Attendee** vList, int id){
    if (*vList != NULL){
        struct Attendee* head = (*vList);
        if ((head)->id == id){
            struct Attendee* temp = head;
            *vList = (*vList)->next;
            free(temp);
            printf("Deleted  successfully");
            checkLimit(&temp->ActivityZone, temp->date,0);// to decrement activity counter;
            return;
        }
        struct Attendee* crnt = (*head).next;
        struct Attendee* prev = head;
        while ((crnt) != NULL){
            if ((crnt)->id == id){
               checkLimit(&crnt->ActivityZone, crnt->date,0);// to decrement activity counter;
               prev->next = crnt->next;
               free(crnt);
               printf("Deleted  successfully");
               return;
            }
            prev = crnt;
            crnt = crnt->next;
        }
    }

    if (*rList != NULL){
       struct Attendee* rHead = (*rList);
       struct Attendee* rCrnt = rHead;
       int numOfActivity = 0;
       while (rCrnt != NULL){
          if (rCrnt->id == id){
             numOfActivity++;
          }
          rCrnt = rCrnt->next;
        }
    //if has one Activity
       if (numOfActivity == 1){
          if ((rHead)->id == id){
             struct Attendee* temp = rHead;
             *rList = (*rList)->next;
             free(temp);
             printf("Deleted  successfully Here");
             checkLimit(&temp->ActivityZone, temp->date,0);// to decrement activity counter;
             return;
            }
          rCrnt = rHead->next;
          struct Attendee* rPrev = rHead;
          while ((rCrnt) != NULL){
              if ((rCrnt)->id == id){
                  checkLimit(&rCrnt->ActivityZone, rCrnt->date,0);// to decrement activity counter;
                  rPrev->next = rCrnt->next;
                  free(rCrnt);
                  printf("Deleted  successfully");
                  return;
              }
              rPrev = rCrnt;
              rCrnt = rCrnt->next;
           }
        }
    //has mora than one Activity
        else{
            printf("\n You Register in more than one one Activity:");
            int *actv;
            int deletAll;
            rCrnt = rHead;
            int i =0;
            while (rCrnt != NULL){
                if (rCrnt->id == id){
                    printf("\n %s ", rCrnt->ActivityZone->name);
                }
                rCrnt = rCrnt->next;
            }

            printf("\nIf you want to delete all activities(enter 0) or single activity(enter 1): ");
            scanf("%d",&deletAll);
            if (deletAll == 0){
                rCrnt = rHead;
                struct Attendee* rPrev = rHead;
                 while ((rCrnt) != NULL){
                     if ((rCrnt)->id == id){
                         checkLimit(&rCrnt->ActivityZone, rCrnt->date,0);// to decrement activity counter;
                         rPrev->next = rCrnt->next;
                     }
                 rPrev = rCrnt;
                 rCrnt = rCrnt->next;
                }
             printf("Deleted  successfully");
             return;
            }

            //delete one Activity
            else{
                int choo;
                int index = 0;
                rCrnt = rHead;
                int i =0;
                while (rCrnt != NULL){
                    if (rCrnt->id == id){
                        printf("\n %s ", rCrnt->ActivityZone->name);
                        printf("Do You Want to delete this Activity? (1: Yes) (0: No)");
                        scanf("%d",&choo);
                        if(choo == 1){
                            for(int a =0; a< activityListCounter; a++){
                                if(strcpy(activityList[a].name,rCrnt->ActivityZone->name) == 0)
                                   index = a;
                            }
                        }
                    }
                    rCrnt = rCrnt->next;
                }

                rCrnt = rHead;
                struct Attendee* rPrev = rHead;
                while ((rCrnt) != NULL){
                    if ((rCrnt)->id == id && strcmp(rCrnt->ActivityZone->name, activityList[index].name) == 0){
                         checkLimit(&rCrnt->ActivityZone, rCrnt->date,0);// to decrement activity counter;
                         rPrev->next = rCrnt->next;
                         free(rCrnt);
                         printf("Deleted  successfully");
                         return;
                }
                rPrev = rCrnt;
                rCrnt = rCrnt->next;
          }
       }

    }
    }
    printf("id %d does not exist.",id);
}
void printList(struct Attendee** rList,struct Attendee** vList){
    //Linking the two linked Lists
    struct Attendee * current = (*vList);
    while (current->next != NULL)
                current = current->next;
    current->next = (*rList);
    current = (*vList);
printf("%-10s%-10s\t%-10s%-10s%-10s%-10s%-20s%-20s%-20s%-20s%-20s%-10s\n","id","name","age",
                            "date", "state", "Address", "activityZone", "numOfCompanion",
                            "listOfCompanion", "activityFee" ,"totalFees", "balance");
    //Note: to show remaining balance we substract the totalFee first so the balance after paying for tickts remains
    for(int a=0; a<activityListCounter; a++){
    while ( current != NULL)
    {
        int value = strcmp(current->ActivityZone->name, activityList[a].name);
        if ( value== 0)
        {
           if (strcmp(current->state,"V") == 0 || ((strcmp(current->state,"R") == 0) && current->numOfCompanion == 0))
           {
               printf("%d\t%s\t%d\t%s\t%s\t%s\t%s%s\t%s\t\t\t%lf\t%lf\t%lf\t\n",current->id,current->name,current->age,current->date,current->state,current->Address,current->ActivityZone->name,"0","{}",current->activityFee, current->totalFees,current->balance - current->totalFees);
           }
           if (strcmp(current->state,"R") == 0)
           {
               printf("%d\t%s%d\t%s\t%s\t%s\t%s\t%d\t",current->id,current->name,current->age,current->date,current->state,current->Address,current->ActivityZone->name,current->numOfCompanion);
               printf("{");
               for (int i = 0; i < current->numOfCompanion; i++)
               {
                    printf("{%d%s%d%c%s}\n",current->compList->id,current->compList->name,current->compList->age,current->compList->gender,current->compList->Address);
                    current->compList = current->compList->next;
               }
               printf("}");
               printf("\t%lf\t%lf\t%lf\n",current->activityFee, current->totalFees,  current->balance - current->totalFees);
           }

        }
        current = current->next;
       }
    }

}

