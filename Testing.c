#include <stdio.h>
#include <stdlib.h>
#include  <math.h>
#include <string.h>

const double epsilon = 0.0001;


struct Activity{
    char name[35];
    double price;
    char startDate[13];
    char endDate[13];
    int counter[5][30];
    int passAge;
    int rAge;
}activityList[20];

static int activityListCounter;

struct Attendee{
    int id;
    char name[20];
    int age;
    char date[10];
    char state;
    char Address[7];
    struct Activity ActivityZone;
    int numOfCompanion;
    double activityFee;
    double totalFees;
    double balance;
    struct Attendee* next;
};

struct Companion{
    int id;
    char name[20];
    int age;
    char gender;
    char Address[7];
    struct Companion* next;
};

void editActivity(int );

int main(){
    FILE* activFile;
    activFile = fopen("Activities.txt","r");

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
    activityListCounter = i;

    editActivity(i);

    printf("-------------------- \nWELCOME TO \nRiyadh Season 2021 \nImagine, MORE!! \n--------------------\n");
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
        activityListCounter++;
    }
}
