
#define _CRT_SECURE_NO_WARNINGS
#define MAXSTRING 256
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

char Registration()
{
	char choose = ' ';
	int count = 0;
	char password[MAXSTRING];
	char presetpass[MAXSTRING] = "ABC123"; /* ManagerChangePass(); */
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
	printf("Moving to registration..");
	delay(2);
	x = Reg(choose);
	delay(1);
	printf("Registration has been successfully completed!\n");
	printf("Moving....\n");
	delay(3);
	return choose;
}

int Reg(char choose)
{
	int ok = 0;
	char username[256];
	char password[256];
	while (!ok)
	{
		username[0] = '\0';
		password[0] = '\0';
		printf("Enter Username and Password.");
		printf("Reminder-\nUsername must contain only letters and numbers.\n");
		printf("Password must contain at least 1 capital, 1 small letter and numbers\n");
		printf("Username: ");
		scanf("%s", username);
		printf("Password: ");
		scanf("%s", password);
		ok =  /*CheckIfExist(username) &&  */ CheckUserName(username) && CheckPassword(password);
		if (!ok)
		{
			printf("Username is exist or password is incorrect!, Try Again..\nClearing in 3 seconds...");
			delay(3);
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
	return written & closed;
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

void PrintMenu()
{

}

