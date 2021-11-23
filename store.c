#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** printcategory();
void printinstructions();
void addProduct();
int checkproduct(char* product);
int countlines();
const char* returnword(char* line, int n);
int editproduct(char* product);

char** printcategory()// .הדפסת כללית
{
	int i = 0,j=1,count,tablecounter=0;
	char categorylist[100][20];
	categorylist[0][0] = '\0';
	FILE* category;
	category = fopen("categories.txt", "r");
	char line[150],categoi[20];
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
	for (int i = 0; i < tablecounter; i++)
	{
		printf("%d. %s \n",i,categorylist[i]);
	}
	fclose(category);
	return categorylist;
}


void printinstructions()//הוראות
{
	printf("1.Add product \n");
	printf("2.Edit product \n");
	printf("3.Delete product \n");
}


void addProduct()//הוספת מוצר לסוף 
{
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	char product[150], serialnum[10], newproduct[150],temp[10];
	while (!feof(productlist))
	{
		fgets(product, 150, productlist);
		strcpy(serialnum, returnword(product, 1));
	}
	fclose(productlist);

	printf("Please enter category:\n");
	gets(temp);
	while (atoi(temp) != 0||strlen(temp)<=1)
	{
		printf("Wrong, please enter again");
		gets(temp);
	}
	strcpy(newproduct, temp);
	strcat(newproduct, " ");
	strcat(newproduct, serialnum);
	strcat(newproduct, " ");
	printf("Please enter product name:\n");
	gets(temp);
	while (atoi(temp) != 0 || strlen(temp) <= 1)
	{
		printf("Wrong, please enter again");
		gets(temp);
	}
	strcat(newproduct, temp);
	strcat(newproduct, " ");
	printf("Please enter product price:\n");
	gets(temp);
	while (atoi(temp) == 0 || strlen(temp) <= 1)
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
	strcat(newproduct, "\0");
	productlist = fopen("categories.txt", "a");
	fprintf(productlist, "\n%s", newproduct);
	fclose(productlist);
}


int checkproduct(char* product)//בדיקת מוצר אם הוא קיים בקובץ
{
	int count = 0,i=0,j,count2=0;
	FILE* productlist;
	productlist = fopen("categories.txt", "r");
	char line[150],product2[20],temp[20];
	while (!feof(productlist))
	{
		count = 0;
		i = 0;
		fgets(line, 150, productlist);
		while (count!=2)
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
		char line[150], templine[150],temp5[20],line2[150];
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
		printf("Please select how you want to edit your product \n");
		printf("1.Name\n2.Price\n3.Quantity\n");
		scanf("%d", &num1);
		if (num1 == 1)
		{
			printf("Please enter a name: ");
			scanf("%s", temp5);
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
			fprintf(pl, "\n%s", line2);
			fclose(pl);
			return 0;
		}
		if (num1 == 2)
		{
			printf("Please enter a price: ");
			scanf("%s", temp5);
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
			fprintf(pl, "\n%s", line2);
			fclose(pl);
			return 0;
		}
		if (num1 == 3)
		{
			printf("Please enter a quantity: ");
			scanf("%s", temp5);
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
			fprintf(pl, "\n%s", line2);
			fclose(pl);
			return 0;
		}
		if (num1 != 1&&num1!=2&&num1!=3)
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
	char line[150], categoi[20];
	while (!feof(category))
	{
		fgets(line, 150, category);
		if (strcmp(category1, returnword(line, 0)) == 0)
		{
			printf("%s", line);
		}
	}
	fclose(category);
}


int main()
{
	addProduct();
}