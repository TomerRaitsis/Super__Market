#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include<stdlib.h>


int menu(int *serial) {
	int choose = 0, option, check;
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
			printf("enter your option\n 1- acepet\n 2- decline\n ");
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
int main()
{
	return 0;
}