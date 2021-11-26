#define _CRT_SECURE_NO_WARNINGS
#define MAXSTRING 256
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

const char* returnword(char* line, int n);

enum MyEnum { /*Welcome Menu*/ LOGIN = 1, REGISTRATION = 2, EXIT = 3,
	/*Manger Menu*/ CATALOG = 1, ORDERS = 2, PRINTALL = 3, CHANGEMANAGERPASS = 4, DISCONNECT = 5,
	/*Client Menu*/ CART = 2, DISCONNECTC = 4,
	/*Manager Catalog*/ ADD = 1, UPDATE = 2, DELETE = 3, RETURN = 4
};

char* ChangeChar(char* s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			s[i] = '_';
		}
		i++;
	}
	return s;
}

void delay(int number_of_seconds)
{

	// Converting time into milli_seconds

	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time

	clock_t start_time = clock();

	// looping till required time is not achieved

	while (clock() < start_time + milli_seconds) {}
	system("cls");

}

int ChangePasswordManager()
{
	FILE* fp;
	char password[MAXSTRING] = "\0";
	printf("Enter the password you want to apply: ");
	scanf("%s", password);
	getchar();
	fp = fopen("ManagerPassword.txt", "w");
	fprintf(fp, "%s", password);
	fclose(fp);
	printf("Password Changed!... Clearing....\n");
	delay(2);
	return 1;
}

char* GetPasswordManager()
{
	char password[MAXSTRING] = "\0";
	FILE* fp;
	fp = fopen("ManagerPassword.txt", "r");
	fgets(password, MAXSTRING, fp);
	fclose(fp);
	return password;
}

char Registration(char* USER)
{
	printf("Proceeding to registration page...\n");
	delay(2);
	char choose = ' ';
	int count = 0;
	char password[MAXSTRING];
	char presetpass[MAXSTRING];
	strcpy(presetpass, GetPasswordManager());
	int x = 0;
	while (!x)
	{
		printf("Welcome to registration section.\n");
		printf("Are you manager or a client?\n");
		printf("Please enter M for manager or C for client: ");
		scanf("%c", &choose);
		getchar();
		count = 0;
		while (count < 3 && choose == 'M')
		{
			printf("Please confirm manager password to proceed: ");
			scanf("%s", password);
			if (strcmp(password, presetpass) == 0)
			{
				printf("Excellent! proceeding...\n");
				x = 1;
				break;
			}
			else
			{
				x = 0;
				count++;
			}
			if (count == 3)
			{
				printf("After %d attempts, You failed to enter the manager password\nClearing in 3 seconds...", count);
				delay(3);
			}
			getchar();
		}
		if (choose == 'C')
			x = 1;
		if (!x && count < 3)
			printf("You must enter the right character!\n");
	}
	x = 0;
	printf("Moving to registration..");
	delay(2);
	char username[MAXSTRING];
	while (!x)
	{
		username[0] = '\0';
		password[0] = '\0';
		printf("Enter Username and Password.\n");
		printf("Reminder-\nUsername must contain only letters and numbers.\n");
		printf("Password must contain at least 1 capital, 1 small letter and numbers\n");
		printf("Username: ");
		scanf("%s", username);
		printf("Password: ");
		scanf("%s", password);
		x = checkUserNotExist(username) && CheckUserName(username) && CheckPassword(password);
		if (!x)
		{
			printf("Username is exist or password is incorrect!, Try Again..\nClearing in 3 seconds...");
			delay(3);
		}
	}
	x = SendUserAndPass(username, password, choose);
	delay(1);
	if (x)
	{
		printf("Registration has been successfully completed!\n");
		strcpy(USER, username);
	}
	else
		printf("Registration has failed... try again later!\n");
	printf("Moving....\n");
	delay(3);
	return choose;
}

int Reg(char choose)
{
	int ok = 0;
	char username[MAXSTRING];
	char password[MAXSTRING];
	while (!ok)
	{
		username[0] = '\0';
		password[0] = '\0';
		printf("Enter Username and Password.\n");
		printf("Reminder-\nUsername must contain only letters and numbers.\n");
		printf("Password must contain at least 1 capital, 1 small letter and numbers\n");
		printf("Username: ");
		scanf("%s", username);
		printf("Password: ");
		scanf("%s", password);
		ok = checkUserNotExist(username) && CheckUserName(username) && CheckPassword(password);
		if (!ok)
		{
			printf("Username is exist or password is incorrect!, Try Again..\nClearing in 2 sec...");
			delay(2);
		}
	}
	ok = SendUserAndPass(username, password, choose);

	return ok;
}

int SendUserAndPass(char* username, char* password, char* choose)
{
	FILE* fpointer;
	fpointer = fopen("RegisteredUsers.txt", "a");
	int written = fprintf(fpointer, "%s %s.%c.\n", username, password, choose);
	int closed = fclose(fpointer);
	return written;
}

int CheckUserName(char* username)
{
	for (int i = 0; i < strlen(username); i++)
	{
		if (!('a' <= username[i] && username[i] <= 'z' || 'A' <= username[i] && username[i] <= 'Z' || '0' <= username[i] && username[i] <= '9'))
			return 0;
	}
	return 1;
}


int CheckPassword(char* password)
{
	int capital = 0;
	int small = 0;
	int digit = 0;
	for (int i = 0; i < strlen(password); i++) // going through the array
	{
		if ('A' <= password[i] && password[i] <= 'Z') // checking if any char is between A-Z
			capital = 1;
		if ('a' <= password[i] && password[i] <= 'z') // checking if any char is between a-z
			small = 1;
		if ('0' <= password[i] && password[i] <= '9') // checking if any char is between 0-9
			digit = 1;

	}
	return small && digit && capital;
}

int PrintWelcome()
{
	int choose = 0;
	while (choose != 1 && choose != 2 && choose != 3)
	{
		printf("Welcome To SCE SuperMarket!\n");
		printf("Please choose one of the following:\n");
		printf("1) Login\n");
		printf("2) Register\n");
		printf("3) Exit\n");
		printf("Your choice: ");
		scanf("%d", &choose);
		getchar();
		if (choose != 1 && choose != 2 && choose != 3)
		{
			printf("Your choice is invalid!\n");
			printf("Clearing in 3 sec..\n");
			delay(3);
		}
	}
	printf("Moving....\n");
	delay(2);
	return choose;
}

int PrintClientMenu(char* username)
{
	int choose = 0;
	printf("Hello %s!\n", username);
	while (choose != 1 && choose != 2 && choose != 3 && choose != 4)
	{
		printf("Please choose one of the following:\n");
		printf("1) Catalog\n");
		printf("2) Shopping cart\n");
		printf("3) Print all store products\n");
		printf("4) Log out\n");
		printf("Your choice: ");
		scanf("%d", &choose);
		getchar();
		if (choose != 1 && choose != 2 && choose != 3 && choose != 4)
		{
			printf("Your choice is invalid!\n");
			printf("Clearing in 3 sec..\n");
			delay(3);
		}
	}
	return choose;
}

int PrintManagerMenu(char* username)
{
	int choose = 0;
	printf("Hello %s!\n", username);
	while (choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5)
	{
		printf("Please choose one of the following:\n");
		printf("1) Catalog management\n");
		printf("2) Order management\n");
		printf("3) Print all store products\n");
		printf("4) Change the manager password\n");
		printf("5) Log out\n");
		printf("Your choice: ");
		scanf("%d", &choose);
		getchar();
		if (choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5)
		{
			printf("Your choice is invalid!\n");
			printf("Clearing in 3 sec..\n");
			delay(3);
		}
	}
	return choose;
}

void Print_Shopping_Cart_Menu()
{
	printf("Please choose one of the following options below:\n");
	printf("1) Edit shopping cart\n");
	printf("2) Erase shopping cart\n");
	printf("3) Print shopping cart\n");
	printf("4) Purchase shopping cart\n");
}

char** New_Shopping_Cart()
{
	char** List = (int**)malloc(0);
	if (List == NULL)
	{
		printf("Memory alocation failed!");
		return 1;
	}
	return List;
}

char** Add_New_Item_To_Shopping_Cart(char** List, int* Current_Size_list, char Product_Details[])
{
	char** NewList = (char**)malloc(((*Current_Size_list) + 1) * (sizeof(char[MAXSTRING])));
	if (NewList == NULL)
	{
		printf("Memory alocation failed!");
		return 1;
	}

	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		NewList[i] = (char*)malloc((sizeof(char[MAXSTRING])));
		strcpy(NewList[i], List[i]);
	}
	NewList[i] = (char*)malloc((sizeof(char[MAXSTRING])));
	strcpy(NewList[i], Product_Details);
	(*Current_Size_list)++;

	return NewList;
}

char** Remove_Item_From_Shopping_Cart(char** List, int* Current_Size_list, char Product_Details[])
{
	int check;
	char** NewList = (char**)malloc((*Current_Size_list + 1) * (sizeof(char[MAXSTRING])));
	if (NewList == NULL)
	{
		printf("Memory alocation failed!");
		return 1;
	}
	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		if (strcmp(List[i], Product_Details) != 0)
		{
			NewList[i] = (char*)malloc((sizeof(char[MAXSTRING])));
			strcpy(NewList[i], List[i]);
		}
		else
		{
			(*Current_Size_list)--;
			break;
		}

	}
	int j;
	for (j = i; j < *Current_Size_list; j++)
	{
		NewList[j] = (char*)malloc((sizeof(char[MAXSTRING])));
		strcpy(NewList[j], List[j + 1]);
	}
	return NewList;
}

char** Change_Quantity_Of_A_Product(char** List, int* Current_Size_list, char Product_Details[], char* New_Quantity)
{
	if (atoi(New_Quantity) == 0)
	{
		return Remove_Item_From_Shopping_Cart(List, Current_Size_list, Product_Details);
	}
	char** NewList = (char**)malloc((*Current_Size_list) * (sizeof(char[MAXSTRING])));
	if (NewList == NULL)
	{
		printf("Memory alocation failed!");
		return 1;
	}

	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		if (strcmp(List[i], Product_Details) == 0)
		{
			NewList[i] = (char*)malloc((sizeof(char[MAXSTRING])));
			int j = 0;
			int counter = 0;
			while (counter < 4)
			{
				if (List[i][j] == ' ')
				{
					counter++;
				}
				NewList[i][j] = List[i][j];
				j++;
			}
			int k;
			for (k = 0; k < strlen(New_Quantity) + 1; k++)
			{
				NewList[i][j] = New_Quantity[k];
				j++;
			}
			NewList[i][j] = '\0';
		}
		else
		{
			NewList[i] = (char*)malloc((sizeof(char[MAXSTRING])));
			strcpy(NewList[i], List[i]);

		}
	}
	return NewList;
}

void Print_Shopping_Cart_Items(char** List, int* Current_Size_list)
{
	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		printf("%s\n", List[i]);
	}
}

void Delete_Shopping_Cart(char** List, int* Current_Size_list)
{
	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		free(List[i]);
	}
	free(List);
	*Current_Size_list = 0;
}

void Shopping_Cart_To_File(char** List, int* Current_Size_list, char Full_Name[], char* ID, char Adress[], int* Shopping_Cart_Serial, int Day, int Month, char* User)
{
	FILE* open;
	char newS[MAXSTRING] = "\0";
	(*Shopping_Cart_Serial)++;
	sprintf(newS, "%d", (*Shopping_Cart_Serial));
	strcat(newS, ".txt");
	open = fopen(newS, "w");
	fprintf(open, "%s\n", User);
	fprintf(open, "%s %s %s\n", Full_Name, ID, Adress);
	fprintf(open, "%d %d\n", Day, Month);
	for (int i = 0; i < *Current_Size_list; i++)
	{
		fprintf(open, "%s\n", List[i]);
	}
	fclose(open);
}

int Count_For_Deliveries_At_The_Same_Day(int* Amount_of_Deliveries, int Day_Number, int Month_Number)
{
	FILE* out;
	char Day[3] = "\0";
	char Month[3] = "\0";
	char DayToCompare[3] = "\0";
	char MonthToCompare[3] = "\0";
	char Serial[30] = "\0";
	char Text[MAXSTRING] = "\0";
	int count = 0;
	sprintf(Day, "%d", Day_Number);
	sprintf(Month, "%d", Month_Number);
	for (int i = 1; i < (*Amount_of_Deliveries) + 1; i++)
	{
		sprintf(Serial, "%d", i);
		strcat(Serial, ".txt");
		out = fopen(Serial, "r");
		if (out == NULL)
			continue;
		fgets(Text, MAXSTRING, out);
		fgets(Text, MAXSTRING, out);
		int j = 0;
		while (Text[j] != ' ')
		{
			DayToCompare[j] = Text[j];
			j++;
		}
		j++;
		int k = 0;
		while (Text[j] != '\n')
		{
			MonthToCompare[k] = Text[j];
			j++;
			k++;
		}

		if (!strcmp(DayToCompare, Day) && !strcmp(MonthToCompare, Month))
			count++;
		fclose(out);
	}
	return count;
}

int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

char* Choosing_Date_For_Delivery(int* AmountofDeliveries)
{
	int choice = 1;
	int Agreed = 1;
	int Day_Of_The_Month = -1;
	struct tm* ClientChoice;
	struct tm* Current;
	time_t t;
	t = time(NULL);
	Current = localtime(&t);
	printf("The deliveries will be delivered between 08:00 to 23:00. The delivery crew will contact the client 30 minutes before they will arrive.\n");
	while (Agreed == 1)
	{
		ClientChoice = localtime(&t);
		ClientChoice->tm_hour = 8;
		ClientChoice->tm_min = 0;
		ClientChoice->tm_sec = 0;
		printf("Please choose a day of the month for your delivery (1-31): \n");
		scanf("%d", &Day_Of_The_Month);
		getchar();
		if (Day_Of_The_Month > 0 && Day_Of_The_Month < 32)
		{
			if (Current->tm_mday >= Day_Of_The_Month)
			{
				ClientChoice->tm_mon = (ClientChoice->tm_mon + 1) % 12;
				if (ClientChoice->tm_mon == 0)
					ClientChoice->tm_year = ClientChoice->tm_year + 1;
				ClientChoice->tm_wday = dayofweek(Day_Of_The_Month, (ClientChoice->tm_mon + 1), ClientChoice->tm_year + 1900);
			}
			else
			{
				ClientChoice->tm_wday = (ClientChoice->tm_wday + Day_Of_The_Month - ClientChoice->tm_mday) % 7;
				ClientChoice->tm_mday = Day_Of_The_Month;
			}
			if (ClientChoice->tm_wday == 6)
			{
				printf("Saturday is not a delivery day, please choose again.\n");
				continue;
			}
			ClientChoice->tm_mday = Day_Of_The_Month;
			if (Count_For_Deliveries_At_The_Same_Day(AmountofDeliveries, ClientChoice->tm_mday, (ClientChoice->tm_mon + 1)) == 15)
			{
				printf("This day is full please choose another one\n");
				continue;
			}
			printf("Your chosen date is: %s\n", asctime(ClientChoice));
			printf("ATTENTION!! The deliveries will be delivered between 08:00 to 23:00. The delivery crew will contact the client 30 minutes before they will arrive.\n");
			printf("Would you like to book this date? (1-No, 2-Yes)\n");
			scanf("%d", &choice);
			getchar();
			if (choice == 2)
			{
				Agreed = 0;
				return (ClientChoice);
			}

		}
		else
			printf("Wrong option, please try again\n");

	}

}

void Shopping_Cart_Purchase(char** List, int* Current_Size_list, char Shopping_Cart_Serial[], int* AmountofDeliveries, char* User)
{
	char Full_Name[31] = "-1";
	char ID[20] = " ";
	char Adrress[51] = "-1";
	int Approval = -1;
	char HouseNumber[31] = " ";
	char AppartmentNumber[31] = " ";
	char Credit_Card_Number[20] = " ";
	char Credit_Card_Date_Year[20] = " ";
	char Credit_Card_Date_Month[20] = "  ";
	char Credit_Card_CVV[20] = " ";
	struct tm* T;
	time_t t;
	t = time(NULL);
	T = localtime(&t);
	if ((*Current_Size_list) == 0)
	{
		printf("You can not buy an empty shopping cart\n");
		return;
	}

	printf("Hello, please enter your details as as asked below:\n");

	while (Approval != 2)
	{
		while (atoi(Full_Name) != 0)
		{
			printf("Full name: ");
			gets(Full_Name);
			if (atoi(Full_Name) != 0)
			{
				printf("Please enter your name (letters only)\n");
				strcpy(Full_Name, "-1");
				continue;
			}

			for (int i = 0; i < strlen(Full_Name); i++)
			{
				if ((isalpha(Full_Name[i]) == 0 && Full_Name[i] != ' '))
				{
					strcpy(Full_Name, "-1");
					printf("Please enter your name (letters only)\n");
					break;
				}
			}


		}

		while (atoi(ID) == 0)
		{
			printf("ID:  ");
			gets(ID);
			if (strlen(ID) != 9)
			{
				strcpy(ID, " ");
				printf("ID needs to be 9 numbers long!\n");
			}
			if (atoi(ID) == 0)
			{
				printf("Please enter your ID (Numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(ID); i++)
			{
				if (isdigit(ID[i]) == 0)
				{
					strcpy(ID, " ");
					printf("Please enter your ID (numbers only)\n");
					break;
				}
			}

		}
		printf("Adress-  \n");
		while (atoi(Adrress) != 0)
		{
			printf("Street name:  ");
			gets(Adrress);
			if (atoi(Adrress) != 0 || strlen(Adrress) <= 1)
			{
				printf("Please enter your adress (letters only)\n");
				strcpy(Adrress, "-1");
				continue;
			}
			for (int i = 0; i < strlen(Adrress); i++)
			{
				if ((isalpha(Adrress[i]) == 0 && Adrress[i] != ' '))
				{
					strcpy(Adrress, "-1");
					printf("Please enter your adress (letters only)\n");
					break;
				}
			}
		}
		while (atoi(HouseNumber) == 0 && atoi(HouseNumber) <= 0)
		{
			printf("House number: ");
			gets(HouseNumber);
			if (atoi(HouseNumber) == 0 && atoi(HouseNumber) <= 0)
			{
				printf("Please enter your house number (numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(HouseNumber); i++)
			{
				if (isdigit(HouseNumber[i]) == 0)
				{
					strcpy(HouseNumber, " ");
					printf("Please enter your house number (numbers only)\n");
					break;
				}
			}
		}
		while ((atoi(AppartmentNumber) == 0) && (atoi(AppartmentNumber) <= 0))
		{
			printf("Apartment number: ");
			gets(AppartmentNumber);
			if (atoi(AppartmentNumber) == 0 && atoi(AppartmentNumber) <= 0)
			{
				printf("Please enter your apartment number (numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(AppartmentNumber); i++)
			{
				if (isdigit(AppartmentNumber[i]) == 0)
				{
					strcpy(AppartmentNumber, " ");
					printf("Please enter your apartment number (numbers only)\n");
					break;
				}
			}
		}


		while (atoi(Credit_Card_Number) == 0)
		{
			printf("Credit Card Number:  ");
			gets(Credit_Card_Number);
			if (strlen(Credit_Card_Number) != 16)
			{
				strcpy(Credit_Card_Number, " ");
				printf("Credit Card Number needs to be 16 numbers long!\n");
			}
			if (atoi(Credit_Card_Number) == 0)
			{
				printf("Please enter your Credit Card Number (Numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(Credit_Card_Number); i++)
			{
				if (isdigit(Credit_Card_Number[i]) == 0)
				{
					strcpy(Credit_Card_Number, " ");
					printf("Please enter your Credit Card Number (numbers only)\n");
					break;
				}
			}

		}

		while ((atoi(Credit_Card_Date_Month) == 0) && (atoi(Credit_Card_Date_Year) == 0))
		{
			printf("Credit Card Expire Date:  \n");
			printf("Month(MM): ");
			gets(Credit_Card_Date_Month);
			printf("Year(YYYY): ");
			gets(Credit_Card_Date_Year);
			if (strlen(Credit_Card_Date_Month) != 2 || strlen(Credit_Card_Date_Year) != 4)
			{
				strcpy(Credit_Card_Date_Month, " ");
				strcpy(Credit_Card_Date_Year, " ");
				printf("Credit Card Expire Date needs to be 2 numbers long for the month and 4 for the year \n");
				continue;
			}
			if ((atoi(Credit_Card_Date_Year) - (T->tm_year + 1900) > 10 && atoi(Credit_Card_Date_Year) - T->tm_year + 1900 >= 0) || (atoi(Credit_Card_Date_Month) <= T->tm_mon + 1 && atoi(Credit_Card_Date_Year) - (T->tm_year + 1900) == 0) || atoi(Credit_Card_Date_Month) > 12 || T->tm_year + 1900 > atoi(Credit_Card_Date_Year))
			{
				strcpy(Credit_Card_Date_Month, " ");
				strcpy(Credit_Card_Date_Year, " ");
				printf("Credit Card Expire Date needs to be 2 numbers long for the month and 4 for the year \n");
				continue;
			}
			if (atoi(Credit_Card_Date_Month) == 0 && atoi(Credit_Card_Date_Year) == 0)
			{
				printf("Please enter your Credit Card Expire Date (Numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(Credit_Card_Date_Month); i++)
			{
				if (isdigit(Credit_Card_Date_Month[i]) == 0)
				{
					strcpy(Credit_Card_Date_Month, " ");
					strcpy(Credit_Card_Date_Year, " ");
					printf("Please enter your Credit Card Expire Date (numbers only)\n");
					break;
				}
			}
			for (int i = 0; i < strlen(Credit_Card_Date_Year); i++)
			{
				if (isdigit(Credit_Card_Date_Year[i]) == 0)
				{
					strcpy(Credit_Card_Date_Month, " ");
					strcpy(Credit_Card_Date_Year, " ");
					printf("Please enter your Credit Card Expire Date (numbers only)\n");
					break;
				}
			}

		}

		while (atoi(Credit_Card_CVV) == 0)
		{
			printf("Credit Card CVV:  ");
			gets(Credit_Card_CVV);
			if (strlen(Credit_Card_CVV) != 3)
			{
				strcpy(Credit_Card_CVV, " ");
				printf("Credit Card CVV needs to be 3 numbers long!\n");
				continue;
			}
			if (atoi(Credit_Card_CVV) == 0)
			{
				printf("Please enter your Credit Card CVV (Numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(Credit_Card_CVV); i++)
			{
				if (isdigit(Credit_Card_CVV[i]) == 0)
				{
					strcpy(Credit_Card_CVV, " ");
					printf("Please enter your Credit Card CVV (numbers only)\n");
					break;
				}
			}

		}

		printf("\n\n");
		printf("Full Name:  ");
		puts(Full_Name);
		printf("ID: ");
		puts(ID);
		printf("Adress: %s, %s/%s \n", Adrress, HouseNumber, AppartmentNumber);
		printf("Are you sure those are your details? (1 - No, 2 - Yes)\n");
		scanf("%d", &Approval);
		getchar();
		if (Approval != 2)
		{
			strcpy(Full_Name, "-1");
			strcpy(ID, " ");
			strcpy(Adrress, "-1");
			strcpy(HouseNumber, " ");
			strcpy(AppartmentNumber, " ");
			strcpy(Credit_Card_Number, " ");
			strcpy(Credit_Card_Date_Year, " ");
			strcpy(Credit_Card_Date_Month, " ");
			strcpy(Credit_Card_CVV, " ");
			printf("Please enter your details again\n");
		}
	}
	strcat(Adrress, ", ");
	strcat(Adrress, HouseNumber);
	strcat(Adrress, "/");
	strcat(Adrress, AppartmentNumber);
	struct tm* Clients_Ship_Day = Choosing_Date_For_Delivery(AmountofDeliveries);
	Shopping_Cart_To_File(List, Current_Size_list, Full_Name, ID, Adrress, Shopping_Cart_Serial, Clients_Ship_Day->tm_mday, Clients_Ship_Day->tm_mon + 1, User);
	printf("Thank you! Have a good day!!");
}

void Shopping_Cart(char** List, int* Number_Of_Products, int* Number_Of_Total_Carts, int* Updadated_Serial, char* User)
{
	enum MyEnum { EDIT = 1, ERASE = 2, PRINT = 3, PURCHASE = 4, GOBACK = 5 };
	char Choice[MAXSTRING] = " ";
	char SerialChoice[MAXSTRING] = " ";
	char NewQuantity[MAXSTRING] = " ";
	char ProductDetails[MAXSTRING] = " ";
	char Serial[MAXSTRING] = " ";
	while (atoi(Choice) != 5)
	{
		printf("Please choose one of the following options below:\n");
		printf("1) Edit shopping cart\n");
		printf("2) Erase shopping cart\n");
		printf("3) Print shopping cart\n");
		printf("4) Purchase shopping cart\n");
		printf("5) Return to the prevoius menu\n");
		gets(Choice);
		switch (atoi(Choice))
		{
		case EDIT:
			Print_Shopping_Cart_Items(List, Number_Of_Products);
			while (strcmp(ProductDetails, " ") == 0)
			{
				printf("Please choose a product by entering it's serial number: ");
				gets(SerialChoice);
				for (int i = 0; i < *Number_Of_Products; i++)
				{
					int j = 0;
					while (List[i][j] != ' ')
						j++;
					int k = 0;
					j++;
					while (List[i][j] != ' ')
					{
						Serial[k] = List[i][j];
						j++;
						k++;
					}
					if (strcmp(Serial, SerialChoice) != 0)
						strcpy(ProductDetails, " ");
					else
					{
						strcpy(ProductDetails, List[i]);
						break;
					}
				}
				if (strcmp(ProductDetails, " ") == 0)
					printf("Product does not exist, Try again!\n");
			}
			while (atoi(NewQuantity) == 0 && strcmp(NewQuantity, "0") != 0)
			{
				printf("You can only change the quantity of the product, Please enter the new quantity (Choose 0 to remove it from the shoppingcart):");
				gets(NewQuantity);
				if (atoi(NewQuantity) == 0 && strcmp(NewQuantity, "0") != 0)
					printf("Please choose numbers only!\n");
			}
			List = Change_Quantity_Of_A_Product(List, Number_Of_Products, ProductDetails, NewQuantity);
			strcpy(ProductDetails, " ");
			strcpy(NewQuantity, " ");
			break;

		case ERASE:
			Delete_Shopping_Cart(List, Number_Of_Products);
			break;
		case PRINT:
			Print_Shopping_Cart_Items(List, Number_Of_Products);
			break;
		case PURCHASE:
			Shopping_Cart_Purchase(List, Number_Of_Products, Updadated_Serial, Number_Of_Total_Carts, User);
			strcpy(Choice, "5");
			break;
		case GOBACK:
			printf("Returning to the previous manu\n");
			break;
		default:
			printf("Wrong number! Please try again\n");
			break;
		}
	}

}

char** printcategory()
{
	int i = 0, j = 1, count, tablecounter = 0;
	char** categorylist = (char**)malloc(sizeof(char*) * MAXSTRING);
	if (categorylist == NULL)
	{
		printf("Memory Allocation Failed.\n");
		return 0;
	}
	for (int i = 0; i < MAXSTRING; i++)
	{
		categorylist[i] = (char*)malloc(MAXSTRING);
		if (categorylist[i] == NULL)
		{
			printf("Memory Allocation Failed.\n");
			return 0;
		}
	}
	categorylist[0][0] = '\0';
	FILE* category;
	category = fopen("categories.txt", "r");
	char line[150], categoi[20];
	printf("please choose one catagory from the list below: \n");
	while (!feof(category))
	{
		fgets(line, 150, category);
		while (line[i] != ' ')
		{
			categoi[i] = line[i];
			i++;
		}
		categoi[i] = '\0';
		if (categorylist[0][0] == '\0')
		{
			strcpy(categorylist[0], categoi);
			tablecounter++;
		}
		else
		{
			count = 0;
			for (int k = 0; k < tablecounter; k++)
			{
				if (strcmp(categoi, categorylist[k]) == 0)
				{
					count++;
				}
			}
			if (count == 0)
			{
				strcpy(categorylist[j], categoi);
				j++;
				tablecounter++;
			}
		}
		i = 0;
	}
	for (i = 0; i < tablecounter; i++)
	{
		printf("%d. %s \n", i + 1, categorylist[i]);
	}
	fclose(category);
	return categorylist;
}

void addProduct(char* category, int* serial)//הוספת מוצר לסוף 
{
	FILE* productlist;
	char product[MAXSTRING], serialnum[MAXSTRING], newproduct[MAXSTRING], temp[MAXSTRING];
	/*
	productlist = fopen("categories.txt", "r");
	while (!feof(productlist))
	{
		fgets(product, 150, productlist);
		strcpy(serialnum, returnword(product, 1));
	}
	fclose(productlist);
	int serial = atoi(serialnum);
	*/
	(*serial)++;
	sprintf(serialnum, "%d", *serial);
	strcpy(newproduct, category);
	strcat(newproduct, " ");
	strcat(newproduct, serialnum);
	strcat(newproduct, " ");
	printf("Please enter product name:\n");
	gets(temp);
	strcpy(temp, ChangeChar(temp));
	while (atoi(temp) != 0 || strlen(temp) <= 1)
	{
		printf("Wrong, please enter again");
		gets(temp);
	}
	strcat(newproduct, temp);
	strcat(newproduct, " ");
	printf("Please enter product price:\n");
	gets(temp);
	while (atoi(temp) == 0 || strlen(temp) < 1)
	{
		printf("Wrong, please enter again");
		gets(temp);
	}
	strcat(newproduct, temp);
	strcat(newproduct, " ");
	printf("Please enter product quantity:\n");
	gets(temp);
	while (atoi(temp) == 0)
	{
		printf("Wrong, please enter again");
		gets(temp);
	}
	strcat(newproduct, temp);
	//strcat(newproduct, "\n");
	productlist = fopen("categories.txt", "a");
	fprintf(productlist, "%s", newproduct);
	fclose(productlist);
}

int checkproduct(char* product)//בדיקת מוצר אם הוא קיים בקובץ
{
	int count = 0, i = 0, j, count2 = 0;
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	char line[150], product2[20], temp[20];
	while (!feof(productlist))
	{
		count = 0;
		i = 0;
		fgets(line, 150, productlist);
		while (count != 2)
		{
			if (line[i] == ' ')
			{
				count++;
			}
			i++;
		}
		j = 0;
		while (line[i] != ' ')
		{
			temp[j] = line[i];
			i++;
			j++;
		}
		temp[j] = '\0';
		if (strcmp(temp, product) == 0)
		{
			count2++;
		}
	}
	fclose(productlist);
	if (count2 == 0)
	{
		return 1;
	}
	return 0;
}

char* GetProductBySerial(char* serial)//בדיקת מוצר אם הוא קיים בקובץ
{
	int count = 0, i = 0, j, count2 = 0;
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	char line[MAXSTRING], product2[MAXSTRING], temp[MAXSTRING];
	char* Word = (char*)malloc(MAXSTRING);
	if (Word == NULL)
	{
		printf("Allocation failed");
		return 1;
	}
	while (!feof(productlist))
	{
		count = 0;
		i = 0;
		fgets(line, 150, productlist);
		while (count != 1)
		{
			if (line[i] == ' ')
			{
				count++;
			}
			i++;
		}
		j = 0;
		while (line[i] != ' ')
		{
			temp[j] = line[i];
			i++;
			j++;
		}
		temp[j] = '\0';
		if (strcmp(temp, serial) == 0)
		{
			strcpy(Word, line);
			count2++;
		}
	}
	fclose(productlist);
	if (count2 == 0)
	{
		return "-1";
	}
	return Word;
}

char* QuantityByProductName(char* product)//בדיקת מוצר אם הוא קיים בקובץ
{
	int count = 0, i = 0, j, count2 = 0;
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	char line[MAXSTRING], product2[MAXSTRING], temp[MAXSTRING];
	char* temp2 = (char*)malloc(MAXSTRING);
	{
		while (count2 == 0 && !feof(productlist))
		{
			count = 0;
			i = 0;
			fgets(line, 150, productlist);
			strcpy(temp2, line);

			while (count != 2)
			{
				if (line[i] == ' ')
				{
					count++;
				}
				i++;
			}
			j = 0;
			while (line[i] != ' ')
			{
				temp[j] = line[i];
				i++;
				j++;
			}
			temp[j] = '\0';
			if (strcmp(temp, product) == 0)
			{
				count = 0;
				i = 0;
				strcpy(temp, " ");
				while (count != 4)
				{
					if (temp2[i] == ' ')
					{
						count++;
					}
					i++;
				}
				j = 0;
				while (temp2[i] != '\n')
				{
					temp[j] = temp2[i];
					i++;
					j++;
				}
				temp[j] = '\0';
				count2++;
			}

		}

	}
	fclose(productlist);
	if (count2 == 1)
	{
		return temp;
	}
	return "0";
}

int editproduct(char* product)//עריכת מוצר
{
	FILE* pl;
	int num1;
	pl = fopen("categories.txt", "r");
	if (checkproduct(product) == 0)
	{
		int lines = countlines() - 1;
		char** newpro = NULL;
		newpro = (char**)malloc(lines * sizeof(char*));
		for (int i = 0; i < lines; i++)
		{
			newpro[i] = (char*)malloc(150 * sizeof(char));
		}
		char line[150], templine[150], temp5[20], line2[150];
		int i = 0;
		int ch = 0;
		int ch1 = 0;
		while (!feof(pl))
		{
			ch1++;
			fgets(line, 150, pl);
			if (strcmp(product, returnword(line, 2)) != 0)
			{
				strcpy(newpro[i], line);
				i++;
			}
			if (strcmp(product, returnword(line, 2)) == 0)
			{
				strcpy(templine, line);
				ch = ch1;
			}
		}
		fclose(pl);
		i = 0;
		pl = fopen("categories.txt", "w");
		for (int i = 0; i < lines ; i++)
		{
			if (i + 1 != ch)
				fputs(newpro[i], pl);
		}
		fclose(pl);
		for (int i = 0; i < lines; i++)
		{
			free(newpro[i]);
		}
		free(newpro);
		printf("Please select how you want to edit your product \n");
		printf("1.Name\n2.Price\n3.Quantity\n");
		scanf("%d", &num1);
		getchar();
		if (num1 == 1)
		{
			printf("Please enter a name: ");
			gets(temp5);
			strcpy(line2, returnword(templine, 0));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 1));
			strcat(line2, " ");
			strcat(line2, temp5);
			strcat(line2, " ");
			strcat(line2, returnword(templine, 3));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 4));
            strcat(line2, "\0");
			pl = fopen("categories.txt", "a");
			fputs(line2, pl);
			fclose(pl);
			return 0;
		}
		if (num1 == 2)
		{
			printf("Please enter a price: ");
			gets(temp5);
			strcpy(line2, returnword(templine, 0));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 1));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 2));
			strcat(line2, " ");
			strcat(line2, temp5);
			strcat(line2, " ");
			strcat(line2, returnword(templine, 4));
			strcat(line2, "\0");
			pl = fopen("categories.txt", "a");
			fputs(line2, pl);
			fclose(pl);
			return 0;
		}
		if (num1 == 3)
		{
			printf("Please enter a quantity: ");
			gets(temp5);
			strcpy(line2, returnword(templine, 0));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 1));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 2));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 3));
			strcat(line2, " ");
			strcat(line2, temp5);
			strcat(line2, "\0");
			pl = fopen("categories.txt", "a");
			fputs(line2, pl);
			fclose(pl);
			return 0;
		}
		if (num1 != 1 && num1 != 2 && num1 != 3)
		{
			return 0;
		}

	}
	else
	{
		printf("the product doesnt exist \n");
		return 0;
	}
}

const char* returnword(char* line, int n)//מחזיר את השם
{
	char temp[20];
	int count = 0, i = 0, j, count2 = 0;
	while (count != n)
	{
		if (line[i] == ' ')
		{
			count++;
		}
		i++;
	}
	j = 0;
	while (line[i] != ' ')
	{
		temp[j] = line[i];
		i++;
		j++;
		if (line[i] == '\0')
		{
			break;
		}
	}
	temp[j] = '\0';
	return temp;
}


int countlines()//סופר שורות
{
	int count = 0;
	char line[150];
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	while (!feof(productlist))
	{
		fgets(line, 150, productlist);
		count++;
	}
	fclose(productlist);
	return count;
}


void deleteproduct(char* product)//מחיקת מוצר
{
	FILE* pl;
	int num1;
	pl = fopen("categories.txt", "r");
	if (checkproduct(product) == 0)
	{
		int lines = countlines() - 1;
		char** newpro = NULL;
		newpro = (char**)malloc(lines * sizeof(char*));
		for (int i = 0; i < lines; i++)
		{
			newpro[i] = (char*)malloc(150 * sizeof(char));
		}
		char line[150], templine[150], temp5[20], line2[150];
		int i = 0;
		while (!feof(pl))
		{
			fgets(line, 150, pl);
			if (strcmp(product, returnword(line, 2)) != 0)
			{
				strcpy(newpro[i], line);
				i++;
			}
			if (strcmp(product, returnword(line, 2)) == 0)
			{
				strcpy(templine, line);
			}
		}
		fclose(pl);
		i = 0;
		pl = fopen("categories.txt", "w");
		for (int i = 0; i < lines; i++)
		{
			fprintf(pl, newpro[i]);
		}
		fclose(pl);
		for (int i = 0; i < lines; i++)
		{
			free(newpro[i]);
		}
		free(newpro);
	}
	else
	{
		printf("The product doesn't exist \n");
	}
}

void printspec(char* category1)//הדפסה של המוצרים מאותה קטגוריה
{
	FILE* category;
	category = fopen("categories.txt", "r");
	char line[150], categoi[20], pre[150];
	while (!feof(category))
	{
		fgets(line, 150, category);
		if (strcmp(category1, returnword(line, 0)) == 0 && strcmp(line, pre) != 0)
			puts(line);
		strcpy(pre, line);
	}
	fclose(category);
}

void printinstructions(char* category,int* serial)//הוראות
{
	char product[MAXSTRING] = "\0";
	int choose = 0;
	while (choose != 1 && choose != 2 && choose != 3 && choose != 4)
	{
		printf("Please choose one of the following:\n");
		printf("1) Add product\n");
		printf("2) Update product\n");
		printf("3) Delete product\n");
		printf("4) Return\n");
		printf("Your choice: ");
		scanf("%d", &choose);
		getchar();
		if (choose != 1 && choose != 2 && choose != 3 && choose != 4)
			printf("Your choice is invalid!\n");


		switch (choose)
		{
		case ADD:
			addProduct(category,serial);
			break;
		case UPDATE:
			printf("Please choose a product (by it's name): ");
			gets(product);
			editproduct(product);
			break;
		case DELETE:
			printf("Please choose a product (by it's name): ");
			gets(product);
			deleteproduct(product);
			break;
		case RETURN:
			printf("Returning...\n");
			delay(1);
			break;
		default:
			break;
		}
		if (choose == 4)
			break;
		choose = 0;

	}
}

char* getCategory(char** catergories)
{
	int ok = 0;
	char choose[MAXSTRING] = "\0";
	while (ok == 0)
	{
		printf("Please insert the name of wanted catergory\n");
		printf("Your choice: ");
		scanf("%s", choose);
		getchar();
		for (int i = 0; i <= 5; i++)
		{
			if (strcmp(catergories[i], choose) == 0)
				ok = 1;
		}
		if (ok == 0)
		{
			printf("Your choice is invalid!\n");
			printf("Clearing in 3 sec..\n");
			delay(3);
		}
	}
	return choose;
}


void printShoppingMenu(void)
{
	printf("1. In order to display all products.\n");
	printf("2. In order to display all products by categories.\n");
	printf("3. In order to add a new product to the shopping cart.\n");
	printf("4. In order to filter items by price.\n");
	printf("5. Return to the Main Menu.\n");
	printf("Please enter your option: ");
}
void printAllProduct(void) {
	FILE* read = fopen("categories.txt", "r");
	char singleline[MAXSTRING];
	char Check[MAXSTRING] = " ";
	while (!feof(read))
	{
		fgets(singleline, MAXSTRING, read);
		if (strcmp(Check, singleline) != 0)
			puts(singleline);
		strcpy(Check, singleline);
	}
	fclose(read);
}

char* cuttingWordFromLine(char* lines, int n)
{
	//char word[10];
	char* word = malloc(10 * sizeof(char*));
	int count = 0, i = 0, j = 0;
	while (count != n)//n - num of space, depend where we want to stop in line.
	{
		if (lines[i] == ' ')
		{
			count++;
		}
		i++;
	}
	j = 0;
	while (lines[i] != ' ')
	{
		word[j] = lines[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return word;
}
void printspec1(char* category)//הדפסה של המוצרים מאותה קטגוריה
{
	FILE* file;
	file = fopen("categories.txt", "r");
	char line[150];
	while (!feof(file))
	{
		fgets(line, 150, file);
		if (strcmp(category, cuttingWordFromLine(line, 0)) == 0)
		{
			printf("%s", line);
		}
	}
	printf("\n");
}
int checkIfItemIsExist(const char* word)
{
	FILE* file = fopen("categories.txt", "r");
	char line[100] = "";

	while (fgets(line, 100, file))
		if (strcmp(cuttingWordFromLine(line, 2), word) == 0)
			return 1;
	fclose(file);
	return 0;
}

int countLines(void)
{
	int count = 0;
	char line[150];
	FILE* productList;
	productList = fopen("categories.txt", "r");
	while (!feof(productList))
	{
		fgets(line, 150, productList);
		if (strcmp(line, "\n") != 0)
			count++;
	}
	fclose(productList);
	return count;
}

void filterItemsByPrices(void)
{
	int countItems = countLines(), i = 0, num = 10;
	FILE* read = fopen("categories.txt", "r");
	char singleline[150];
	char** arrPrice = (char**)malloc(countItems * sizeof(char*));
	for (i = 0; i < countItems; i++)
	{
		arrPrice[i] = (char*)malloc(num * sizeof(char));
	}
	i = 0;
	while (!feof(read))
	{
		fgets(singleline, 150, read);
		strcpy(arrPrice[i], cuttingWordFromLine(singleline, 3));
		i++;
	}
	char temp[10];
	for (i = 0; i < countItems; i++)
	{
		for (int j = 0; j < countItems - 1 - i; j++)
		{
			if ((strcmp(arrPrice[j], arrPrice[j + 1]) > 0))
			{
				strcpy(temp, arrPrice[j]);
				strcpy(arrPrice[j], arrPrice[j + 1]);
				strcpy(arrPrice[j + 1], temp);
			}
			if (strlen(arrPrice[j]) > strlen(arrPrice[j + 1]))
			{
				strcpy(temp, arrPrice[j]);
				strcpy(arrPrice[j], arrPrice[j + 1]);
				strcpy(arrPrice[j + 1], temp);
			}
		}
	}
	i = 0;
	rewind(read);
	while (i != countItems)
	{
		fgets(singleline, 150, read);
		if (strcmp(arrPrice[i], cuttingWordFromLine(singleline, 3)) == 0)
		{
			printf("%s", singleline);
			i++;
		}
		if (feof(read)) {
			rewind(read);
		}
	}
	for (i = 0; i < countItems; i++)
		free(arrPrice[i]);
	free(arrPrice);
	fclose(read);
}

char** ClientShop(char** List, int* Current_Size_list)
{
	int i = 0;
	int j = 0;
	int run = 1, option = 0;
	char categories[20];
	char Product_Details[MAXSTRING] = "-1";
	char Quantity[MAXSTRING] = "-1";
	char temp[MAXSTRING] = "-1";
	while (run)
	{
		printShoppingMenu();
		scanf("%d", &option);
		getchar();
		switch (option) {
		case 1:
			printAllProduct();
			break;
		case 2:
			printf("Enter a specific category to display: ");
			scanf("%s", categories);
			getchar();
			printspec(categories);
			break;
		case 3:
			printAllProduct();
			while (atoi(Product_Details) != 0)
			{
				printf("Please choose the serial number of the product you want to buy.\n");
				gets(Product_Details);
				printf("Please choose the amount you want to get.\n");
				gets(Quantity);
				strcpy(Product_Details, GetProductBySerial(Product_Details));
				if (Product_Details == "-1")
					strcpy(Product_Details, "-1");
			}
			List = Add_New_Item_To_Shopping_Cart(List, Current_Size_list, Product_Details);
			List = Change_Quantity_Of_A_Product(List, Current_Size_list, Product_Details, Quantity);


			int count = 0;
			int i = 0;
			while (count != 2)
			{
				if (Product_Details[i] == ' ')
				{
					count++;
				}
				i++;
			}
			j = 0;
			while (Product_Details[i] != ' ')
			{
				temp[j] = Product_Details[i];
				i++;
				j++;
			}
			char NewQuantity[MAXSTRING] = " ";
			sprintf(NewQuantity, "%d", (atoi(QuantityByProductName(temp)) - atoi(Quantity)));

			FILE* pl;
			pl = fopen("categories.txt", "r");
			int lines = countlines() - 1;
			char** newpro = NULL;
			newpro = (char**)malloc(lines * sizeof(char*));
			for (int i = 0; i < lines; i++)
			{
				newpro[i] = (char*)malloc(150 * sizeof(char));
			}
			char line[150], templine[150], temp5[20], line2[150];
			i = 0;
			while (!feof(pl))
			{
				fgets(line, 150, pl);
				if (strcmp(temp, returnword(line, 2)) != 0)
				{
					strcpy(newpro[i], line);
					i++;
				}
				if (strcmp(temp, returnword(line, 2)) == 0)
				{
					strcpy(templine, line);
				}
			}
			fclose(pl);
			i = 0;
			pl = fopen("categories.txt", "w");
			for (int i = 0; i < lines; i++)
			{
				fprintf(pl, newpro[i]);
			}
			fclose(pl);
			for (int i = 0; i < lines; i++)
			{
				free(newpro[i]);
			}
			free(newpro);
			strcpy(line2, returnword(templine, 0));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 1));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 2));
			strcat(line2, " ");
			strcat(line2, returnword(templine, 3));
			strcat(line2, " ");
			strcat(line2, NewQuantity);
			strcat(line2, "\0");
			pl = fopen("categories.txt", "a");
			fprintf(pl, "%s\n", line2); // \n
			fclose(pl);
			break;
		case 4:
			filterItemsByPrices();
			break;
		case 5:
			run = 0;
			break;
		default:
			break;
		}
	}

	return List;
}


int checkPassword(char* line, char* password)
{
	char pass[MAXSTRING] = "\0";
	int i = 0, j = 0;
	for (i; i < strlen(line); i++)
		if (line[i] == ' ')
			break;
	i++;
	for (i; i < strlen(line); i++)
	{
		if (line[i] != '.')
		{
			pass[j] = line[i];
			j++;
		}
		else
			break;
	}
	if (strcmp(password, pass) == 0)
		return 1;
	return 0;
}

char* getUsername(char* line)
{
	char username[MAXSTRING] = "\0";
	for (int i = 0; i < strlen(line); i++)
	{
		if (line[i] != ' ')
			username[i] = line[i];
		else
			break;
	}
	return username;
}

char checkDetails(char* username, char* password)
{

	FILE* file;
	int ok = 0;
	char line[256] = "\0";
	file = fopen("RegisteredUsers.txt", "r");
	while (fgets(line, MAXSTRING, file))
	{
		if (strcmp(getUsername(line), username) == 0)
		{
			ok = checkPassword(line, password);
			break;
		}
	}
	fclose(file);
	if (ok)
	{
		if (strstr(line, ".M.") != NULL)
			return 'M';
		else if ((strstr(line, ".C.") != NULL))
			return 'C';
	}
	return '0';
}

int checkUserNotExist(char* username)
{
	FILE* file;
	int ok = 1;
	char line[256] = "\0";
	file = fopen("RegisteredUsers.txt", "r");
	while (fgets(line, MAXSTRING, file))
	{
		if (strcmp(getUsername(line), username) == 0)
			ok = 0;
	}
	fclose(file);
	return ok;
}

char Login(char* USER)
{
	int x = 0;
	char username[MAXSTRING];
	char password[MAXSTRING];
	char MorC = ' ';
	while (!x)
	{
		printf("Welcome to login section.\n");
		printf("Please enter Username and Password to continue\n");
		printf("Username: ");
		gets(username);
		printf("Password: ");
		gets(password);
		MorC = checkDetails(username, password);
		if (MorC != '0')
			x = 1;
		else
		{
			printf("Username or Password is incorrect, Try again.\n");
			printf("Clearing...\n");
			delay(2);
		}
	}
	if (x)
	{
		strcpy(USER, username);
		printf("Successfully logged in!\n");
		delay(2);
	}
	return MorC;
}

int menu() {
	int choose = 0, option = 0, check = 0;
	char a[256] = "\0";
	do {
		printf("Choose number cart\n");
		scanf("%d", &choose);
		sprintf(a, "%d", choose);
		strcat(a, ".txt");
		FILE* open;
		open = fopen(a, "r");
		if (open == NULL)
			check = 0;
		else
			check = 1;
		if (!check) {
			printf("enter your option\n 1- accept\n 2- decline\n ");
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				remove(open);
				break;

			case 2:
				remove(open);
				break;
			default:
				break;
			}
		}
	} while (check != 1);
}



void PrintAllCarts(int* serial)
{
	char temp[256] = "\0";
	char text[256] = "\0";
	FILE* read;
	for (int i = 1; i <= *serial; i++)
	{
		sprintf(temp, "%d", i);
		strcat(temp, ".txt");
		read = fopen(temp, "r");
		if (read == NULL)
			continue;
		printf("Shopping cart number: %d\n", i);
		while (!feof(read))
		{
			fgets(text, 256, read);
			puts(text);
		}
		fclose(read);

	}
}

void main()
{
	char** catergories = NULL;
	char Categ[MAXSTRING] = "\0";
	int numberofproducts = 0;
	int* Number_Of_Products = &numberofproducts;
	int carts = 0;
	int* Number_Of_Total_Carts = &carts;
	int serial = 16;
	int* UpdatedSerial = &serial;
	char** shoppingcart = NULL;
	int run = 1;
	char MorC = ' ';
	int choose = 0;
	int morc = 0;
	char username[MAXSTRING] = "";

	while (run)
	{
		choose = PrintWelcome();
		switch (choose)
		{
		case LOGIN:
			MorC = Login(username);
			break;
		case REGISTRATION:
			MorC = Registration(username);
			break;
		case EXIT:
			printf("Thank you for visiting us!\nHave a great day!\n");
			run = 0;
			break;
		default:
			break;
		}
		if (run == 0)
			break;

		int run2 = 1;
		// Manager Menu
		if (MorC == 'M')
		{
			while (run2)
			{
				choose = PrintManagerMenu(username);
				switch (choose)
				{
				case CATALOG:
					catergories = printcategory();
					strcpy(Categ, getCategory(catergories));
					printspec(Categ);
					printinstructions(Categ,UpdatedSerial);
					break;
				case ORDERS:
					PrintAllCarts(UpdatedSerial);
					menu();
					break;
				case PRINTALL:
					printAllProduct();
					break;
				case CHANGEMANAGERPASS:
					ChangePasswordManager();
					break;
				case DISCONNECT:
					printf("Disconncted!\n");
					run2 = 0;
					break;
				}
			}
		}

		// Client Menu 
		if (MorC == 'C')
		{
			while (run2)
			{
				choose = PrintClientMenu(username);
				switch (choose)
				{
				case CATALOG:
					shoppingcart = ClientShop(shoppingcart, Number_Of_Products);
					break;

				case CART:
					Shopping_Cart(shoppingcart, Number_Of_Products, Number_Of_Total_Carts, UpdatedSerial, username);
					break;

				case PRINTALL:
					printAllProduct();
					break;

				case DISCONNECTC:
					printf("Disconncted!\n");
					run2 = 0;
					break;

				}
			}
		}
	}
}


