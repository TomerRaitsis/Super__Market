//
//  main.c
//  Supermarket
//
//  Created by Raphael Benoliel on 12/11/2021.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void printShoppingMenu(void)
{
    printf("1. In order to display all products.\n");
    printf("2. In order to display all products by categories.\n");
    printf("3. In order to add a new product to the shopping cart.\n");
    printf("4. In order to filter items by price.\n");
    printf("5. Return to the Main Menu.\n");
    printf("Please enter your option: ");
}
void printAllProduct(void){
    FILE *read = fopen("file.txt", "r");
    char singleline[150];
    while (!feof(read)) {
        fgets(singleline, 150, read);
        puts(singleline);
    }
    fclose(read);
}

char* cuttingWordFromLine(char* lines,int n)
{
    //char word[10];
    char* word = malloc(10* sizeof(char*));
    int count=0,i=0,j=0;
    while(count!= n)//n - num of space, depend where we want to stop in line.
    {
        if(lines[i] == ' ')
        {
            count++;
        }
        i++;
    }
    j=0;
    while (lines[i]!= ' ')
    {
        word[j]=lines[i];
        i++;
        j++;
    }
    word[j] = '\0';
    return word;
}
void printspec(char* category)//הדפסה של המוצרים מאותה קטגוריה
{
    FILE* file;
    file = fopen("file.txt", "r");
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
int checkIfItemIsExist(const char *word)
{
    FILE* file = fopen("file.txt", "r");
    char line[100]="";

    while (fgets(line, 100, file))
        if(strcmp(cuttingWordFromLine(line,2), word)==0)
            return 1;
    fclose(file);
    return 0;
}
char* addItemsToShoppingCart(void)
{
    char line[150],productToAdd[20],templine[150],quantity[4];
    char* line1=malloc(150*sizeof(char));
    printf("Enter the name of product you want to add: ");
    scanf("%s",productToAdd);
    
    if( checkIfItemIsExist(productToAdd) == 1)
    {
        FILE *read = fopen("file.txt", "r");
        while (!feof(read))
        {
            fgets(line, 150, read);
            if(strcmp(productToAdd,cuttingWordFromLine(line, 2))==0)
            {
                strcpy(templine, line);
                break;
            }
        }
        fclose(read);
        printf("Enter quantity of product: ");
        scanf("%s",quantity);
        strcpy(line1, cuttingWordFromLine(templine, 0));
        strcat(line1, " ");
        strcat(line1, cuttingWordFromLine(templine, 1));
        strcat(line1, " ");
        strcat(line1, cuttingWordFromLine(templine, 2));
        strcat(line1, " ");
        strcat(line1, cuttingWordFromLine(templine, 3));
        strcat(line1, " ");
        strcat(line1, quantity);
        strcat(line1, "\0");
        FILE* shoppingCart;
        if(access("ShoppingCart.txt", F_OK)!=-1)
        {
        //check if the product is exist in file of client.
            shoppingCart=fopen("ShoppingCart.txt", "a");
            fprintf(shoppingCart, "%s\n",line1);
            fclose(shoppingCart);
        }
        else
        {
            shoppingCart=fopen("ShoppingCart.txt", "w");
            fprintf(shoppingCart, "%s\n",line1);
            fclose(shoppingCart);
        }
    }
    else
        printf("Sorry, the product '%s' doesn't exist on the store.\n",productToAdd);
    return line1;
}
    
int countLines(void)
{
    int count = 0;
    char line[150];
    FILE* productList;
    productList = fopen("file.txt", "r");
    while (!feof(productList))
    {
        fgets(line, 150, productList);
        count++;
    }
    fclose(productList);
    return count;
}

void filterItemsByPrices(void)
{
    int countItems = countLines(), i = 0,num=10;
    FILE* read = fopen("file.txt", "r");
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
        strcpy(arrPrice[i],cuttingWordFromLine(singleline, 3));
        i++;
    }
    char temp[10];
    for ( i = 0; i <countItems; i++)
    {
        for (int j=0; j<countItems-1-i; j++)
        {
            if ((strcmp(arrPrice[j], arrPrice[j+1]) > 0) )
            {
                strcpy(temp, arrPrice[j]);
                strcpy(arrPrice[j], arrPrice[j+1]);
                strcpy(arrPrice[j+1], temp);
            }
            if(strlen(arrPrice[j]) > strlen(arrPrice[j+1]))
            {
                strcpy(temp, arrPrice[j]);
                strcpy(arrPrice[j], arrPrice[j+1]);
                strcpy(arrPrice[j+1], temp);
            }
        }
    }
    i = 0;
    rewind(read);
    while (i!=countItems)
    {
        fgets(singleline, 150, read);
        if(strcmp(arrPrice[i], cuttingWordFromLine(singleline, 3))==0)
        {
            printf("%s\n",singleline);
            i++;
        }
        if (feof(read)) {
            rewind(read);
        }
    }
    for (i=0; i<countItems; i++)
        free(arrPrice[i]);
    free(arrPrice);
    fclose(read);
}
void menuShopClient(void)
{
    int run=1, option=0;
    char categories[20];
   while(run)
   {
       printShoppingMenu();
       scanf("%d",&option);
       switch (option) {
           case 1:
               printAllProduct();
               break;
           case 2:
               printf("Enter a specific category to display: ");
               scanf("%s",categories);
               printspec(categories);
               break;
           case 3:
               addItemsToShoppingCart();
               break;
           case 4:
               filterItemsByPrices();
               break;
           case 5:
               run =0 ;
               break;
           default:
               break;
       }
   }
}
int main()
{
    menuShopClient();
    return 0;
}
