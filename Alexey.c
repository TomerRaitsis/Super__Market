#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

int printMenu() {

    int custOrManag;
    printf("Enter 1 if you want to log in as a customer or Enter 2 if you want to log in as a manager\n");
    scanf("%d", &custOrManag);
   
    askLoginPassword();
    return custOrManag+ askLoginPassword();
}

int askLoginPassword()
{

    char username, password;
    printf("Please enter your username\n");
    scanf("%s",&username);
    printf("Please enter your password\n");
    scanf("%s", &password);
    while ((checkUsername(username) + checkPassword(password)) != 2) {
        printf("username or password is wrong, tra again\n");
        printf("Please enter your username\n");
        scanf("%s", &username);
        printf("Please enter your password\n");
        scanf("%s", &password);
    }
    return 1;
}


int checkPassword(char password[])
{

    FILE* file;
    int wordExist = 0;
    char line[256] = "\0";
    file = fopen("file.txt", "r");
    while (fgets(line, 256, file))
    {
        char* ptr = strstr(line, password);
        if (ptr != NULL)
        {
            wordExist = 1;
            break;
        }
    }
    fclose(file);
    if (wordExist == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(file);
}

int checkUsername(char username[])
{

    FILE* file;
    int wordExist = 0;
    char line[256]="\0";
    file = fopen("file.txt", "r");
    while (fgets(line, 256, file))
    {
        char* ptr = strstr(line, username);
        if (ptr != NULL)
        {
            wordExist = 1;
            break;
        }
    }
    fclose(file);
    if (wordExist == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(file);
}


int main()
{
    printMenu();

    return 0;
}