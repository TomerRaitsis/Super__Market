#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

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
	char** NewList = (char**)malloc(((*Current_Size_list) + 1) * (sizeof(char[256])));
	if (NewList == NULL)
	{
		printf("Memory alocation failed!");
		return 1;
	}

	int i;
	for (i = 0; i < *Current_Size_list; i++)
	{
		NewList[i] = (char*)malloc((sizeof(char[256])));
		strcpy(NewList[i], List[i]);
	}
	NewList[i] = (char*)malloc((sizeof(char[256])));
	strcpy(NewList[i], Product_Details);
	(*Current_Size_list)++;

	return NewList;
}

char** Remove_Item_From_Shopping_Cart(char** List, int* Current_Size_list, char Product_Details[])
{
	int check;
	char** NewList = (char**)malloc((*Current_Size_list + 1) * (sizeof(char[256])));
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
			NewList[i] = (char*)malloc((sizeof(char[256])));
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
		NewList[j] = (char*)malloc((sizeof(char[256])));
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
	char** NewList = (char**)malloc((*Current_Size_list) * (sizeof(char[256])));
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
			NewList[i] = (char*)malloc((sizeof(char[256])));
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
			NewList[i] = (char*)malloc((sizeof(char[256])));
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

void Shopping_Cart_To_File(char** List, int* Current_Size_list, char Full_Name[], char* ID, char Adress[], int* Shopping_Cart_Serial, int Day, int Month)
{
	FILE* open;
	char newS[256] = "\0";
	(*Shopping_Cart_Serial)++;
	sprintf(newS, "%d", (*Shopping_Cart_Serial));
	strcat(newS, ".txt");
	open = fopen(newS, "w");
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
	char Text[256] = "\0";
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
		fgets(Text, 256, out);
		fgets(Text, 256, out);
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

void Shopping_Cart_Purchase(char** List, int* Current_Size_list, char Shopping_Cart_Serial[], int* AmountofDeliveries)
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
		printf("Adress:  \n");
		while (atoi(Adrress) != 0)
		{
			printf("Street name:  ");
			gets(Adrress);
			if (atoi(Adrress) != 0 || strlen(Adrress) <= 1)
			{
				printf("Please enter your adrress (letters only)\n");
				strcpy(Adrress, "-1");
				continue;
			}
			for (int i = 0; i < strlen(Adrress); i++)
			{
				if ((isalpha(Adrress[i]) == 0 && Adrress[i] != ' '))
				{
					strcpy(Adrress, "-1");
					printf("Please enter your name (letters only)\n");
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
			printf("Appartment number: ");
			gets(AppartmentNumber);
			if (atoi(AppartmentNumber) == 0 && atoi(AppartmentNumber) <= 0)
			{
				printf("Please enter your appartment number (numbers only)\n");
				continue;
			}
			for (int i = 0; i < strlen(AppartmentNumber); i++)
			{
				if (isdigit(AppartmentNumber[i]) == 0)
				{
					strcpy(AppartmentNumber, " ");
					printf("Please enter your appartment number (numbers only)\n");
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
			printf("Credit Card Expire Date (MM/YY):  \n");
			printf("Month: ");
			gets(Credit_Card_Date_Month);
			printf("Year: ");
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
		printf("Are you sure those are your details? (1 - No, 2 - Yes\n");
		scanf("%d", &Approval);
		getchar();
		if (Approval != 2)
		{
			strcpy(Full_Name, "-1");
			strcpy(ID, " ");
			strcpy(Adrress, "-1");
			strcpy(HouseNumber, " ");
			strcpy(AppartmentNumber, " ");
			strcpy(Credit_Card_Number," ");
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
	Shopping_Cart_To_File(List, Current_Size_list, Full_Name, ID, Adrress, Shopping_Cart_Serial, Clients_Ship_Day->tm_mday, Clients_Ship_Day->tm_mon + 1);

}

void Shopping_Cart(char** List, int* Number_Of_Products, int* Number_Of_Total_Carts, int* Updadated_Serial)
{
	enum MyEnum{ EDIT = 1, ERASE = 2, PRINT = 3, PURCHASE = 4, GOBACK = 5};
	char Choice[256] = " ";
	char SerialChoice[256] = " ";
	char NewQuantity[256] = " ";
	char ProductDetails[256] = " ";
	char Serial[256] = " ";
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
			Shopping_Cart_Purchase(List, Number_Of_Products, Updadated_Serial, Number_Of_Total_Carts);
			strcpy(Choice, "5");
			printf("Thank you! Have a good day!!");
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

void main()
{
	int numberofproducts = 0;
	int* Number_Of_Products = &numberofproducts;

	int carts = 0;
	int* Number_Of_Total_Carts = &carts;

	int serial = 0;
	int* Updadated_Serial = &serial;



	char A[256] = "Category1 1 Name1 Price1 Quantity1";
	char B[256] = "Category2 2 Name2 Price2 Quantity2";
	char C[256] = "Category3 3 Name3 Price3 Quantity3";
	char D[256] = "Category4 4 Name4 Price4 Quantity4";
	char E[256] = "Category5 5 Name5 Price5 Quantity5";
	char F[256] = "Category6 6 Name6 Price6 Quantity6";
	char** Z = NULL;
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, A);
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, B);
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, C);
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, D);
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, E);
	Z = Add_New_Item_To_Shopping_Cart(Z, Number_Of_Products, F);

	//Print_Shopping_Cart_Items(Z, Number_Of_Products);

	/*Z = Remove_Item_From_Shopping_Cart(Z, Number_Of_Products, B);
	Print_Shopping_Cart_Items(Z, Number_Of_Products);

	Z = Change_Quantity_Of_A_Product(Z, Number_Of_Products, C, "4560");
	Print_Shopping_Cart_Items(Z, Number_Of_Products);*/

	//Shopping_Cart_Purchase(Z, Number_Of_Products, Updadated_Serial, Number_Of_Total_Carts);


	Shopping_Cart(Z,Number_Of_Products, Number_Of_Total_Carts, Updadated_Serial);
}