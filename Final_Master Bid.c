#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>


//GLOBAL VARIABLES
int item_num,counter,user_n;

//STRUCTURE DECLARATION
struct user
{
char name[50];
char password[50];
};

struct items
{
char item_name[20];
char item_lable[6];
float item_cost;
int bid_num;
char highest_bid[10];
float ini_cost;
char file_name[30];
};

//FUNCTION PROTOTYPE
void printlist(struct items item[]);
int signin(struct user bidder[], struct items item[]);
void bid(struct items item[], struct user bidder[], int a);
void create_files(struct items item[]);

int main()
{
printf("\t\t\t\t\t\t MASTER BID");

// Entering the initial items by the seller
printf("\nITEM SETUP");
printf("\n\nHow many items to be bitted(Maximum 10): ");
scanf("%d",&item_num);

while(item_num<0 || item_num>10)
{
	printf("Maximum number of items should be 10\tPlease re-enter the no. of items: ");
	scanf("%d",&item_num);
}

struct items item[item_num];

char test_label[6];

int i,j,k,l;

FILE *fptr = fopen("ITEMS.txt","a");
if(fptr==NULL){
printf("FILE DOES NOT EXITS");
exit(1);
}//CHECK LATER!!

for( i = 0; i< item_num; i++)
{
	
fflush(stdin);
printf("\nEnter Item %d name: ", i+1);
gets(item[i].item_name);
int empty;
empty=strcmp(item[i].item_name,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter item %d name: ",i+1);
	gets(item[i].item_name);
	empty=strcmp(item[i].item_name,"");
}

//Creating the file name for item in .txt format
strcpy(item[i].file_name,item[i].item_name);
strcat(item[i].file_name,".txt");

printf("Enter Item Label: ");
gets(test_label);
empty=strcmp(test_label,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter item %d label: ",i+1);
	gets(test_label);
	empty=strcmp(test_label,"");
}

j=0;
int label_f=0;	
while(j<item_num)
{	while((strcmp(test_label,item[j].item_lable))==0)
	{
	printf("Lable already exists.\tPlease enter another lable: ");
	gets(test_label);
	label_f=1;
	}
if(label_f==0)
	{
		j++;
	}
else if(label_f==1)
	{
		j=0;
		label_f=0;
	}
}

strcpy(item[i].item_lable,test_label);	
	
printf("Enter the initial cost in PKR: ");
scanf("%f",&item[i].item_cost);
while(item[i].item_cost<0)
{
	printf("Please enter the correct item cost in PKR: ");
	scanf("%f",&item[i].item_cost);
}
item[i].ini_cost = item[i].item_cost;
item[i].bid_num=0;

fprintf(fptr,"%d.NAME: %s\tLABEL: %s\tINITIAL PRICE: %.2f\n",i+1,item[i].item_name,item[i].item_lable,item[i].item_cost);
}

fclose(fptr);

create_files(item);

for(l=0;l<4;l++)
{
	printf("\n");
}
printf("=========================================================\n");

fptr = fopen("USER DETAIL.txt","a");
if(fptr==NULL){
printf("FILE DOES NOT EXITS");
exit(1);
}

//setting up users
printf("\nBIDDER SETUP\n");
printf("\nEnter total number of bidders: ");
scanf("%d",&user_n);
struct user bidder[user_n];

char test_name[50];
char test_pass[50];

for(j=0;j<user_n;j++)
{
fflush(stdin);
printf("\nEnter %d Username: ",j+1);
gets(test_name);
int empty=strcmp(test_name,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter username: ",i+1);
	gets(test_name);
	empty=strcmp(test_name,"");
}
int c=0,name_f=0;

while(c<user_n)
{	while((strcmp(test_name,bidder[c].name))==0)
	{
	printf("Username already exists.\tPlease enter another Username: ");
	gets(test_name);
	name_f=1;
	}
if(name_f==0)
	{
		c++;
	}
else if(name_f==1)
	{
		c=0;
		name_f=0;
	}
}
	
strcpy(bidder[j].name,test_name);


fflush(stdin);
printf("Enter %d User Password: ",j+1);
gets(bidder[j].password);
empty=strcmp(bidder[j].password,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter password: ",i+1);
	gets(bidder[j].password);
	empty=strcmp(bidder[j].password,"");
}

fprintf(fptr,"%d. USERNAME: %s\tPASSWORD: %s\n",j+1,bidder[j].name,bidder[j].password);
}

fclose(fptr);

printf("\n=========================================================\n");

// Printing item list
printf("\nITEM LIST :\n");
printlist(item);

// Commencing the bidding process

int activate=0;
printf("\nDo you want to start the bidding process? 1. YES\t0. NO ");
scanf("%d",&activate);

if(activate == 1)
{
//Setting a termination password for the timer
char termination_pass[20];
printf("Enter a termination password for the timer: ");
fflush(stdin);
gets(termination_pass);

//Setting up the timer
float time = (clock()/CLOCKS_PER_SEC)/60;

float ini_time =  time;
//Asking for how many minutes have elapsed since the program wou ld run
printf("Enter the alloted time for bidding in minutes: ");
float minutes;
scanf("%f",&minutes);

while (minutes<2)
{
printf("Time alloted should be greater than 1 minute\t Enter alloted time: ");
scanf("%f",&minutes);
}

printf("\n=========================================================\n");
printf("\nBIDDING HAS STARTED\nPROCESS TIME: %.2f minutes",minutes);
printf("\n=========================================================\n");


while(time<=(ini_time+minutes))
{

time = (clock()/CLOCKS_PER_SEC)/60;

float time_remain = minutes-(time-ini_time);

//Checking for timer's end

if(time_remain>=1)
{
printf("\nTIME REMAINING: %.2f mins\n", time_remain);
}
else if(time_remain==0)
{
break;
}
printf("\n=========================================================\n");

//Checking if user wants to bid
printf("\nDoes the user whishes to bid?\t1.Yes 0.N0: ");
int consent,found;
scanf("%d",&consent);

//If the condition is true
if(consent==1)
{
//User sign-in
int found=signin(bidder,item);
switch(found)
	{
	case 0:
		printf("\nUser Information is not correct!");
		break;
	case 1:
		printf("\nThank you for bidding!\n");
		break;
	}
}
//If user does not wishes to bid anymore
else if(consent==0)
{
//Check for termination
char termination_check[20];
printf("Enter the termination password: ");
fflush(stdin);
gets(termination_check);

	if((strcmp(termination_check,termination_pass))==0)
	{
		printf("\nTHE PROCESS HAS BEEN TERMINATED\n");
		break;
	}	
	else
	{
		printf("\nPassword is Incorrect\n");
	}
}

printf("\n\nITEM LIST :\n============================================\n");
printlist(item);

}// time while scope terminator
}//activate if scope terminator

printf("\n\nTHE BIDDING PROCESS HAS ENDED\n\n\t\t\t\tFINAL OUTCOME\n\n");
int a;
float total_charity=0;

//PRINTING FINAL OUTCOME
for(a=0; a<item_num; a++)
{
printf("\n%d. %s\t",a+1,item[a].item_lable);
printf("%s\t",item[a].item_name);
printf("Price: %.1f\t\t",item[a].item_cost);

//IF NO ITEM IS BIDED ON EVEN ONCE
if(item[a].item_cost==item[a].ini_cost)
{
printf("Buyer: NONE\t");
}
else
{
printf("Buyer: %s\t",item[a].highest_bid);
}

//CALULATION TOTAL AND CHARITY FROM EACH ITEM
float charity;
if(item[a].item_cost==item[a].ini_cost)
{
charity=0;
printf("Charity Ammount: %.2f PKR\n",charity);
}
else
{
charity=(item[a].item_cost)*0.1;
printf("Charity Ammount: %.2f PKR\n",charity);
}

fptr = fopen("Charity.txt","a");
fprintf(fptr,"%d. %s\t Price: %.2f\t Charity: %.2f PKR\n",a+1,item[a].item_name,item[a].item_cost,charity);
fclose(fptr);

total_charity += charity; 

}


printf("\n=========================================================\n");
printf("Total Charity: %.2f PKR",total_charity);
printf("\n=========================================================\n");
printf("\n\t\t\t\t\t\tTHANK YOU FOR USING MASTER BID");
}


//MY FUNTIONS:

//FUNTION TO PRINT LIST
void printlist(struct items item[])
{
//printf("\n=========================================================\n");
int a;
for(a=0; a<item_num; a++)
{
printf("\n%d. %s\t",a+1,item[a].item_lable);
printf("%s\t",item[a].item_name);
printf("Price: %.1f\t",item[a].item_cost);
printf("No. of bids: %d\n",item[a].bid_num);
}
printf("\n=========================================================\n\n");
}


//FUNCTION OF BIDDING PROCESS
void bid(struct items item[], struct user bidder[], int a)
{
char bid_lable[6];
//CHECKING FOR ITEM LABLE
fflush(stdin);
printf("\nEnter the item label you want to bid on: ");
gets(bid_lable);
int empty;
empty=strcmp(bid_lable,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter correct item lable: ");
	gets(bid_lable);
	empty=strcmp(bid_lable,"");
}

int b;
float bid_value;
int label_found = 0;
FILE *fptr3;

for(b=0;b<item_num;b++)
{	
	//IF LABEL IS FOUND THEN BIDDING PRICE IS ASKED
	if((strcmp(item[b].item_lable,bid_lable))==0)
	{
	printf("\nEnter your bid in PKR: ");
	scanf("%f",&bid_value);
	while(bid_value<0)
    {
	    printf("Please enter the correct bid value in PKR: ");
	    scanf("%f",&bid_value);
    } 
	    while(bid_value<=item[b].item_cost)
	    {
	    printf("\nThe bid you entered is less than the reserved price.");
	    printf("\n\nEnter higher bid: ");
	    scanf("%f",&bid_value);
		}
	
	item[b].item_cost=bid_value;
	
	//INCREMENT IN NUMBER OF BIDS
	item[b].bid_num++;
	
	//STORING THE NAME OF THE BIDDER
	strcpy(item[b].highest_bid,bidder[a].name);
	label_found=1;
	
	//Storing the these details in the item file
	fptr3 = fopen(item[b].file_name,"a");
	fprintf(fptr3,"BIDDER NAME: %s\tITEM COST: %.2f\n",bidder[a].name, item[b].item_cost);
	fclose(fptr3);
	
	break;
	}
}
//IF THE LABLE IS NOT FOUND
if(label_found==0)
{
printf("LABEL DOES NOT EXISTS");
}
}




//FUNCTION OF SIGNING IN
int signin(struct user bidder[], struct items item[])
{
int i,found;
char name[50];
char pass[50];
//CHECKING IF USER DETAILS ARE CORRECT
fflush(stdin);
printf("\n\nEnter Your Username: ");
gets(name);
int empty;
empty=strcmp(name,"");
while(empty==0)
{
	printf("Required section!");
	printf("\tPlease enter Username: ");
	gets(name);
	empty=strcmp(name,"");
}

//Signing in
for(i=0; i<user_n; i++)
{	//TEST
	int k = strcmp(name,bidder[i].name);
	if(k==0)
	{
	fflush(stdin);
	printf("Enter Your Password: ");
	gets(pass);
	int empty;
    empty=strcmp(pass,"");
    while(empty==0)
   {
	printf("Required section!");
	printf("\tPlease enter Password: ");
	gets(pass);
	empty=strcmp(pass,"");
   } 
	
		int l = strcmp(pass,bidder[i].password);
			if(l==0)
			{
			bid(item,bidder,i);
			found = 1;
			return found;
			break;
			}
			else
			{
			found = 0;
			continue;
			}
	}
	else
	{
		found = 0;
		continue;
	}
	
}
return found;
}

void create_files(struct items item[])
{
int i;
FILE *fptr2;

for(i=0;i<item_num;i++)
{
fptr2 = fopen(item[i].file_name,"w");
if(fptr2==NULL)
{
printf("FILE DOES NOT EXISTS");
continue;
}
fclose(fptr2);
}


}



