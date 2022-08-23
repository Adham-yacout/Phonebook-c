#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char last[100];
    char name[100];
    date DOB;
    char address[100];
    char number[30];
    char email[60];
} person;

person p[200];
int count=0;




void load()
{
    FILE *f;
    f=fopen("phonebook.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%[^,],",p[count].last);
        fscanf(f,"%[^,],",p[count].name);
        fscanf(f,"%d-%d-%d,",&p[count].DOB.day,&p[count].DOB.month,&p[count].DOB.year);
        fscanf(f,"%[^,],",p[count].address);
        fscanf(f,"%[^,],",p[count].number);
        fscanf(f,"%s\n",p[count].email);
        count++;

    }
    fclose(f);
}
int numcheck(char x[100])
{

    int i;
    int counter=0;
    for(i=0; i<strlen(x); i++)
    {
        if(isdigit(x[i])==0)
        {
            counter++;
        }
    }

    if (counter==0)
    {
        return 1;
    }
    else
    {
        printf("number is invalid please enter a valid number \n");
        return 0;

    }
}
int checkmail(char x[])
{
    int counter=0;
    int counter2=0;
    int i,j;
    int tmp1,tmp2;
    int k=0;
    for(i=0 ; i<strlen(x) ; i++)
    {
        if(x[i]=='@')
        {
            counter++;
            tmp1=i;
            break;
        }
    }
    i=strlen(x);
    if(counter==1)
    {
        for(j=0; j<tmp1 ; j++)
        {
            if(!(x[j]=='_' || x[j]=='.' || isalpha(x[j]) || isdigit(x[j])))
            {
                k=-1;

                break;
            }
        }
    }
    if(k==0)
    {
        for(i; i>tmp1 ; i--)
        {
            if(x[i]=='.')
            {
                tmp2=i;
                counter2++;
                break;
            }
        }
    }
    if(counter2==1)
    {
        i--;
        for(i; i<tmp2 && i>tmp1; i--)
        {
            if(!(isalpha(x[i])))
            {
                k=-1;

                break;
            }
            else
            {
                k=1;
            }
        }
    }
    if(k==1)
    {
        if(x[tmp2+4]!='\0'||(strlen(x)-tmp2)<4)
        {
            k=-1;


        }

    }

    if(k!=1)
    {
        printf("invalid email\n");
    }
    return k;
}
int phrasecheck(char x[])
{
    int notletters=0, i;
    for (i = 0; x[i] != '\0'; i++)
    {
        if (isalpha(x[i]) == 0 && x[i]!=' ')
        {
            notletters++ ;

        }
    }
    if (notletters>0)
    {
        printf("invalid name,please enter a name with only characters\n");
        return 1;
    }
    else
        return 0 ;
}

void SearchLastName()
{


    int i,j=0;
    int search=1;
    while(search)
    {
        int z;
        char x[20];
        int f=0;
        do
        {
            printf("enter the last name of the person you want to search for\n");
            scanf("%s",x);
            z=phrasecheck(x);
        }
        while(z);

        for (i=0; i<count; i++)
        {
            if(strcasecmp(x,p[i].last)==0)
            {
                f=1;
                j=i;
            }
        }
        if(f==1)
        {
            printf("Person's First Name is: ");
            printf("%s\n", p[j].name);
            printf("Person's address is: ");
            printf("%s\n", p[j].address);
            printf("person's E-mail is: ");
            printf("%s\n", p[j].email);
            printf("person's date of birth is: ");
             printf("%d-%d-%d\n", p[j].DOB.day,p[j].DOB.month,p[j].DOB.year);
            printf("person's Phone number is: ");
            printf("%s\n", p[j].number);
            search=0;
            break;
        }
        int k;
        printf("could not find %s,if you want to search again press 1 if you do not press 0\n",x);
        do
        {
            scanf("%d",&k);
             if(k!=0&&k!=1){printf("invalid input please enter o or 1\n");}

        }
        while(k!=0 && k!=1);
        if(k==0)
        {
            search=0;
            break;
        }
    }
}


void modify()
{
    int y,f;
    char z;
    int i=0,j=0;
    int mod=1;
    while(mod)
    {
        person s;
        int h=0;
        do
        {
            printf("enter the last name of the person you want to modify\n");
            scanf("%s",s.last);
            h=phrasecheck(s.last);
        }
        while(h);
        for(i=0; i<count; i++)
        {
            if(strcasecmp(s.last,p[i].last)==0)
            {
                f=1;
                j=i;
            }
        }

        if(f==1)
        {
            printf("enter the new date of birth of %s %s \n",p[j].name,p[j].last);
            scanf("%d%d%d",&p[j].DOB.day,&p[j].DOB.month,&p[j].DOB.year);
            printf("enter the new address of %s %s \n",p[j].name,p[j].last);
            getchar();
            gets(p[j].address);
            do
            {
                printf("enter the new number of %s %s \n",p[j].name,p[j].last);
                scanf("%s",p[j].number);
                y=numcheck(p[j].number);
            }
            while(!y);
            do
            {
                printf("enter the new email of %s %s \n",p[j].name,p[j].last);
                scanf("%s",p[j].email);
                z=checkmail(p[j].email);
            }
            while(z!=1);

            mod=0;
            break;
        }
        int x;
        printf("could not find %s,if you want to search again press 1, if you do not press 0\n",s.last);
        do
        {
            scanf("%d",&x);
            if(x!=0&&x!=1){printf("invalid input please enter o or 1\n");}
        }
        while(x!=0 && x!=1);
        if(x==0)
        {
            mod=0;
            break;
        }
    }
}


void add()
{
    int y,f;
    char z;
    printf("enter data for the person yo want to add\n");
    printf("enter last name:\n");
    do
    {
        scanf("%s",p[count].last);
        f=phrasecheck(p[count].last);
    }
    while(f);
    do
    {
        printf("enter first name:\n");
        getchar();
        gets(p[count].name);
        f=phrasecheck(p[count].name);
    }
    while(f);
    do
    {
        printf("enter day  of birth:\n\n day should be between[1-31]\n");
        scanf("%d",&p[count].DOB.day);
    }
    while(p[count].DOB.day>31);
    do
    {
        printf("enter month  of birth:\n\n month should be between[1-12]\n");
        scanf("%d",&p[count].DOB.month);
    }
    while(p[count].DOB.month>12);

    do
    {
        printf("enter year of birth:\n\n year should be between[1900-2021]\n");
        scanf("%d",&p[count].DOB.year);

    }
    while(p[count].DOB.year>2021||p[count].DOB.year<1900);
    printf("enter the address\n");
    getchar();
    gets(p[count].address);
    do
    {
        printf("enter the number:\nthe phone number should contain numbers only\n");
        scanf("%s",p[count].number);
        y=numcheck(p[count].number);
    }
    while(!y);
    do
    {
        printf("please enter his email address in the format ahmed@gmail.com\n");
        getchar();
        gets(p[count].email);
        z=checkmail(p[count].email);
    }
    while(z!=1);
    count++;
    int x;
    printf("if you want to add another name press 1, if you do not press 0\n");
        do
        {
            scanf("%d",&x);
            if(x!=0&&x!=1){printf("invalid input please enter o or 1\n");}
        }
        while(x!=0 && x!=1);
        if (x==1)
        {
            add();
        }
        if(x==0)
        {
            return 0;}
}

void sortByLname()
{
    int i,j;
    person temp;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(strcasecmp(p[i].last,p[j].last)>0)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}
void sortByDOB()
{
    int i,j;
    person temp;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(p[i].DOB.year>p[j].DOB.year)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;

            }
        }
    }
    for(i=0; i<count; i++)
    {

        for(j=i+1; j<count; j++)
        {
            if((p[i].DOB.year>p[j].DOB.year || p[i].DOB.year==p[j].DOB.year) && p[i].DOB.month>p[j].DOB.month)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if((p[i].DOB.year>p[j].DOB.year || p[i].DOB.year==p[j].DOB.year) && (p[i].DOB.month>p[j].DOB.month || p[i].DOB.month==p[j].DOB.month) && p[i].DOB.day>p[j].DOB.day)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }



}
void print()
{
    int x;
    printf("if you want to print the phoneBook sorted by date of birth press 1,\n if you want to print the phoneBook sorted by last name press 2\n");
    scanf("%d",&x);
    if(x==1)
        sortByDOB();
    else if(x==2)
        sortByLname();
    else
        printf("invalid selection,the phoneBook will be printed unsorted\n");
    int i;
    for(i=0; i<count; i++)
    {

        printf("%s,%s,%d-%d-%d,%s,%d,%s\n",p[i].last,p[i].name, p[i].DOB.day, p[i].DOB.month, p[i].DOB.year, p[i].address,p[i].number,p[i].email);
    }
}

void delete()
{   char f[20];
    char l[20];
    int fc,lc;
    int s=1;
    int x,y,i,num,flag=0;
    while(s){
    printf("enter the last name and the first name for the person you want to delete him\n");
   label:
       do{printf("enter first name:");
    scanf("%s",&f);
    fc=phrasecheck(f);
       }while(fc);
       do{
    printf("enter last name:");
    scanf("%s",&l);
    lc=phrasecheck(l);}while(lc);
    for(i=0;i<count;i++)
    {
        x=strcasecmp(f,p[i].name);
        y=strcasecmp(l,p[i].last);
        if(x==0&&y==0)
        {
            num=i;
            flag++;
        }
    }
    if (flag!=0){
    for(i=num;i<count;i++)
    {
        p[i]=p[i+1];

     }
     count--;
     printf("deleted\n");
     s=0;
     }
     else
 {  int z;
     int g;
         printf("no matching name press 1 to enter another name to delete or enter 0 to exit function\n");
         do{
                scanf("%d",&g);
                if(g!=0&&g!=1){printf("invalid input please enter o or 1\n");}
                }
        while(g!=0&&g!=1);
         if(g==1){goto label;}
         else{ if(g==0) break;}
     }
    }
}

void save ()
{
    int i;

    FILE *f;
    f=fopen("phonebook.txt","w");
    for(i=0;i<count;i++)
    {

        fprintf(f,"%s,",p[i].name);
        fprintf(f,"%s,",p[i].last);
        fprintf(f,"%d-%d-%d,",p[i].DOB.day,p[i].DOB.month,p[i].DOB.year);
        fprintf(f,"%s,",p[i].address);
        fprintf(f,"%s,",p[i].number);
        fprintf(f,"%s\n",p[i].email);

    }
    printf("SAVED!");
    fclose(f);
    }

void quit ()
{
    char A[3];
    char a[3];
    int i;

    printf(" All the changes will be discarded!\n");
    printf(" Do you want to save ?\n");
    printf(" Yes or No\n");


int z;
         do{
       label2: scanf("%s",A);
        z=phrasecheck(A);
        }while(z);
        if(strcasecmp(A,"yes")==0)
        {
            save();
            exit(0);
        }
        else if(strcasecmp(A,"no")!=0&&strcasecmp(A,"yes")!=0)
        {
            printf("please enter either yes or no");
            goto label2;
        }
        else if(strcasecmp(A,"no")==0)
{
            printf("do you want to exit?\n");
           label: do{
            scanf("%s",a);
            i=phrasecheck(a);
            }while(i);
            if(strcasecmp(a,"yes")==0)
                exit(0);
            else if (strcasecmp(a,"no")==0)
            return 0;



         else{
                printf("please enter either yes or no");
            goto label;
         }
        }
}


int main()
{
    int x;

    printf("\t\twelcome to the phonebook\n-----------------------------------------------------------------------\n");
load();
    label2:{
        printf("-----------------------------------------------------------------------\n");
    printf("\t\tMENU\n-----------------------------------------------------------------------\n");
    printf("press 1:to add a new person\n");
    printf("press 2:to seacrh for a person\n");
    printf("press 3:to modify a person\n");
    printf("press 4:to print all data\n");
    printf("press 5:to delete a person\n");
    printf("press 6:to save a person \n");
    printf("press 7:to quit\n");
    printf("press 0:exit\n");
    printf("-----------------------------------------------------------------------\n");}

    scanf("%d",&x);
    int f=0;
    while(f==0)
    {
       label: switch(x)
        {
        case 1:
            add();
            goto label2;

        case 2:
            SearchLastName();
            goto label2;
        case 3:
            modify();
            goto label2;
        case 4:
            print();
            goto label2;
        case 5:
            delete();
            goto label2;
        case 6:
            save ();
            goto label2;
        case 7:
            quit ();
            goto label2;

        case 0:
           printf("thank you for using our phonebook\n-----------------------------------------------------------------------");
            f=1;
            break;

        default:
            printf("please enter a valid entry:");
            scanf("%d",&x);
            printf("\n");
            goto label;
        }
    }
    return 0;
}
