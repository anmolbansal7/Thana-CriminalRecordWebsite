/*Criminal Record Database using a dynamic - single linked list
Date : 03/02/2020
*/

/*----------------------------------------------------------------------------*/
/* Define libraries to be included */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
/*----------------------------------------------------------------------------*/
/* Define Functions*/

void addNewcriminal(void);
void listAll(void);
void deletecriminal(void);
void modifycriminal(void);
int findcriminal(void);
int prompt(void);
int findnum (int);
/*----------------------------------------------------------------------------*/
/* Define Structures*/

typedef struct criminal {
    int number;             /*unique account number*/
    int d,m,y;
    char name[20];
    /*contains name*/
    char fatherName[20];     /*contains fathers name*/
    char motherName[20];     /*contains mothers  name*/
    char address[30];
    int height;
    int weight;
    char gender[10];
    char phone[15];    /*contains phone number*/
    char crime[20];           /*contains crime */
    struct criminal *next; /*next is used to navigate through structures.*/
    } Criminal;
Criminal *firstc,*currentc,*newc; /*pointers*/
/* firstc is used to point to first record in list
currentc points to current record in list
newc contains address of new structure/node
*/
int cnum = 0; /*gives unique account numbers*/

char crimes[15][20] = {
                            "Theft",
                            "Robbery",
                            "Abduction",
                            "Murder",
                            "Larceny",
                            "Arson",
                            "Burglary",
                            "Motor Vehicle Theft",
                            "Aggravated Assault",
                            "Embezzlement",
                            "Espionage",
                            "Forgery",
                            "Slander",
                            "Trafficking",
                            "Vandalism"
                        };

char genders[3][15] = {
                        "Male",
                        "Female",
                        "Transgender"
                    };
/*----------------------------------------------------------------------------*/
/* Main Function */
int main()
{

    FILE *datafile;
    char *filename = "criminaldata.dat";
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");

    if(datafile)
    {
	    firstc = (struct criminal *)malloc(sizeof(struct criminal));
	    currentc = firstc;
	    while(1) /*endless while loop. a NULL pointer in final node ends loop*/
     	    {
		    newc = (struct criminal *)malloc(sizeof(struct criminal));
		    fread(currentc,sizeof(struct criminal),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;       /* pointer referencing next node*/
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }

    do
    {
	fflush(stdin);
        puts("\nWelcome To The Criminal Database");/* print menu messages*/
        puts("-- -----------------------------");
        puts("1 - Add a new criminal record");
        puts("2 - Delete criminal record");
        puts("3 - List all criminals");
        puts("4 - Modify criminal record");
        puts("5 - Find a criminal by name");
        puts("-- -----------------------------");
        puts("Q - Save and quit\n");
        printf("\tYour choice:");
        ch = getchar();
	    ch = toupper(ch);
	    system("clear");
        switch(ch)
        {
            case '1':
                puts("Add a new criminal record\n");
	        fflush(stdin);
                addNewcriminal();
                break;
	    case '2':
		puts("Delete a criminal record\n");
		deletecriminal();
		break;
	    case '3':
		puts("Quick list all criminals\n");
		listAll();
		break;
	    case '4':
		puts("Modify a criminal record\n");
		modifycriminal();
		break;
	    case '5':
		puts("Find details of a criminal by name\n");
		findcriminal();
		break;
            case 'Q':
                puts("Save and quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');
/*
 * Save the records to disk
 */
    currentc = firstc;

    if(currentc == NULL)
	    return(0);		/*no data to write*/

    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }

    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct criminal),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);             /*closes data file*/
    return(0);
}
/*----------------------------------------------------------------------------*/
void addNewcriminal(void) /* add new criminal function*/
{
    newc = (struct criminal *)malloc(sizeof(struct criminal));
    /*allocates memory for new structure.*/
/*
 * Checks to see whether this is the first record in file
 * If so, then all pointers are initialized to this record,
 */
    if(firstc==NULL)
        firstc = currentc = newc;
/*
 * if not, end of structure list is obtained
 */
    else
    {
        currentc = firstc;

        while(currentc->next != NULL)currentc = currentc->next;

        currentc->next = newc;
        currentc = newc;
    }
/* update the structure */
    cnum++;
    printf("%27s: %5d\n","criminal number",cnum);
    currentc->number = cnum;    /*cnum is used to give unique account numbers*/

    printf("%27s: ","Enter criminal name");
    gets(currentc->name);
    fflush(stdin);
    printf("%27s: ","Enter Father's name");
    gets(currentc->fatherName);
    printf("%27s: ","Enter Mother's name");
    gets(currentc->motherName);
    printf("%27s: ","Enter date of birth in dd/mm/yyyy format");
    scanf("%d/%d/%d",&currentc->d,&currentc->m,&currentc->y);
    fflush(stdin);
    printf("%27s: ","Enter current address");
    gets(currentc->address);
    printf("%27s: ","Enter the weight in kg");
    scanf("%d",&currentc->weight);
    printf("%27s: ","Enter the height in cm");
    scanf("%d",&currentc->height);
    printf("%27s: \n","Select gender");

    int i,ch;
    for(i=0;i<3;i++)
    {
        printf("%d : %s\n",i+1,genders[i]);
    }
    scanf("%d",&ch);
    printf("\n");
    strcpy(currentc->gender,genders[ch-1]);

    printf("%27s: ","Enter criminal Phone number");
    scanf("%s",currentc->phone);
    printf("\n");

    printf("%27s: \n","Select crime from the list given below");

    for(i=0;i<15;i++)
    {
        printf("%d : %s\n",i+1,crimes[i]);
    }
    scanf("%d",&ch);
    strcpy(currentc->crime, crimes[ch-1]);

    printf("criminal added!");

    currentc->next = NULL;
}
/*----------------------------------------------------------------------------*/
void listAll(void) /* list all criminals function*/
{
    if(firstc==NULL)
        puts("There are no criminals to display!"); /*prints message*/

    else
    {
	    printf("%6s %-20s %-15s %-15s\n","Acct#","Name","DOB","Crime");
        puts("------ -------------------- ------------- -------------------");
                            /*prints table titles*/
        currentc=firstc;

        do
        {

                printf("%6d: %-20s %d/%d/%d%5s %-20s\n",\
                currentc->number,\
                currentc->name,\
                currentc->d,currentc->m,currentc->y,"",\
                currentc->crime);

        }

        while((currentc=currentc->next) != NULL);
    }
}
/*----------------------------------------------------------------------------*/
void deletecriminal(void)
{
    int record;
    struct criminal *previousa;
    if(firstc==NULL)
    {
        puts("There are no criminals to delete!");
	return;
    }

    listAll();		/* show all records*/
    printf("Enter criminal account number to delete: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL)
    {
        if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;
        free(currentc);
	    printf("criminal %d deleted!\n",record);
	    return;
	}

	else
	{
        previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("criminal %d not found!\n",record);
 }
/*----------------------------------------------------------------------------*/
void modifycriminal(void)
{
    int record, result;
    char s[20];
    if(firstc==NULL)
    {
        puts("There are no criminals to modify!");
	return;
    }

    listAll();
    printf("Enter criminal account number to modify or change: ");
    scanf("%d",&record);
    result = findnum(record);

    if( result >0 ){
	    printf("Criminal %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
        printf("Father's name: %s\n",currentc->fatherName);
	    if(prompt())
		    gets(currentc->fatherName);
        printf("Mother's name: %s\n",currentc->motherName);
	    if(prompt())
		    gets(currentc->motherName);
        printf("DOB: %d/%d/%d\n",currentc->d,currentc->m,currentc->y);
        if(prompt())
            scanf("%d/%d/%d",&currentc->d,&currentc->m,&currentc->y);
        printf("Address: %s\n",currentc->address);
	    if(prompt())
            gets(currentc->address);
        printf("Height: %d\n",currentc->height);
	    if(prompt())
            scanf("%d",&currentc->height);
        printf("weight: %d\n",currentc->weight);
	    if(prompt())
            scanf("%d",&currentc->weight);
	    printf("Phone: %s\n",currentc->phone);
	    if(prompt())
		    gets(currentc->phone);
	    printf("Crime: %s\n",currentc->crime);
	    printf("\n");
	    if(prompt())
        {
            int i,ch;
            for(i=0;i<15;i++) printf("%d : %s\n",i+1,crimes[i]);

            scanf("%d",&ch);
            strcpy(currentc->crime, crimes[ch-1]);

        }

	    return;
	}
    printf("criminal %d was not found!\n",record);
}
/*----------------------------------------------------------------------------*/
int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

        if(currentc->number == record)
	     {
           return 1;
         }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
/*----------------------------------------------------------------------------*/
int findcriminal(void)
{
     char buff[20];

     if(firstc==NULL)
	{
        puts("There are no criminals to find!");
	    return 1;
    }

    printf("Enter criminal name: ");
    fflush(stdin);
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
        if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%-6s:%d\n %-20s:%s\n %-20s:%s\n %-20s:%d/%d/%d\n %-20s:%d\n %-20s:%d\n %-20s:%s\n %-20s:%s\n %-20s:%s\n %-20s:%s\n %-20s:%s\n",\
          "Acct#",currentc->number,\
          "Name",currentc->name,\
          "Gender",currentc->gender,\
          "DOB",currentc->d,currentc->m,currentc->y,\
          "Height",currentc->height,\
          "Weight",currentc->weight,\
          "Father's name",currentc->fatherName,\
          "Mother's name",currentc->motherName,\
          "Address",currentc->address,\
          "Phone",currentc->phone,\
          "Crime",currentc->crime);
			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("criminal %s was not found!\n",buff);
          return 1;
}
/*----------------------------------------------------------------------------*/
int prompt(void)
{
	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
/*----------------------------------------------------------------------------*/
/* END OF PROGRAM */
