#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insted(char array[]);
void registretion(char *user_name, char *name, char *bank, char *pin, char *pass);
void login(char *user_name, char *user_password);
void change_username_pass(char *new_user, char *new_password);

int main()
{

    char name[25], bank[25], pin[25], pass[25], new_pass[25], user_name[25], temp_user_name[25];
    int input;
    FILE *fp;
label:
    printf("Click 1 for Registretion\nClick 2 for Login\nClick 0 for EXIT\n\n-> ");
    scanf("%d", &input);
    getchar(); // For consiume the '\n'
    // printf("\e[1;1H\e[2J");
    if (input == 1)
    {
        while (1)
        {
            printf("\n-> Enter your user name: ");
            fgets(user_name, 22, stdin);
            insted(user_name);
            strcpy(temp_user_name, user_name);
            // Check wheather the user name means file is already exist or not
            fp = fopen(strcat(temp_user_name, ".txt"), "r");
            if (fp == NULL)
            {
                while (1)
                {
                    printf("\n-> Enter your password (Must 5 To 14 Characters): ");
                    fgets(pass, 22, stdin);
                    insted(pass);
                    // printf("%d\n", (int)strlen(pass));
                    if (strlen(pass) >= 5 && strlen(pass) <= 14)
                    {
                        registretion(user_name, name, bank, pin, pass);
                        goto label;
                        break;
                    }
                    else
                    {
                        printf("\nYour password must have 5 to 14 characters.\nYour entered %d characters\n", (int)strlen(pass));
                        continue;
                    }
                }
                break;
            }
            else
            {
                printf("\nUser name is already exists \nTry different user name\n");
                continue;
            }
        }
    }

    else if (input == 2)
    {
        printf("Enter your user name: ");
        fgets(user_name, 22, stdin);
        insted(user_name);
        printf("Enter your password: ");
        fgets(pass, 22, stdin);
        insted(pass);
        login(user_name, pass);
        goto label;
    }
    else if (input == 0)
    {
        printf("Exit the Program\n");
        exit(0);
    }
    else
    {
        printf("Wrong Input\n");
        exit(1);
    }
    return 0;
}

void registretion(char *user_name, char *name, char *bank, char *pin, char *pass)
{
    char temp[25];
    strcpy(temp, user_name);
    FILE *ptr = fopen(strcat(temp, ".txt"), "w");
    printf("\n-> Enter your Name: ");
    fgets(name, 22, stdin);
    insted(name);
    printf("\n-> Enter your Bank Account Number: ");
    fgets(bank, 22, stdin);
    insted(bank);
    printf("\n-> Enter your Bank Pin number: ");
    fgets(pin, 22, stdin);
    insted(pin);

    fprintf(ptr, "(1) Name: %s\n", name);
    fprintf(ptr, "(2) Bank Account number: %s\n", bank);
    fprintf(ptr, "(3) Pin: %s\n", pin);
    fprintf(ptr, "(4) User Name: %s\n", user_name);
    fprintf(ptr, "(5) Password: %s\n", pass);

    printf("\n~~~~ Your File %s has been created ~~~~\n~~~~ Login with your user name & password to access your file ~~~~\n\n", temp);
    fclose(ptr);
}

void login(char *user_name, char *user_password)
{
    char ch, var[25], name[25], bank[25], pin[25], temp_name[25];
    int x;
    strcpy(temp_name, user_name);
    FILE *ptr1 = fopen(strcat(temp_name, ".txt"), "r");
    if (ptr1 == NULL)
    {
        printf("\n%s user-name doesn't exsit\nAt first you need to register your self\n\n", user_name);
        return;
    }
    else
    {
        while (!feof(ptr1))
            fscanf(ptr1, "%s", var);
        if (strcmp(var, user_password) == 0)
        {
            printf("\nFile Accessed\n\n");
            while (1)
            {
                printf("Click 1 for print the Information\nClick 2 for change the Information\nClick 3 for change User name & Password\nClick 4 for delete your account\nClick 5 for Logout\n\n-> ");
                scanf("%d", &x);
                getchar();
                switch (x)
                {
                case 1:
                    FILE *ptr2 = fopen(temp_name, "r");
                    printf("\n Printing the Information \n");
                    printf("--------------------------\n");
                    rewind(ptr2);
                    while (1)
                    {
                        ch = fgetc(ptr2);
                        if (ch == EOF)
                            break;
                        printf("%c", ch);
                    }
                    fclose(ptr2);
                    printf("\n");
                    break;

                case 5:
                    printf("Successfully Logout\n\n");
                    fclose(ptr1);
                    return;

                case 2:
                    ptr1 = fopen(temp_name, "w");
                    printf("\n-> Enter your Name: ");
                    fgets(name, 22, stdin);
                    insted(name);
                    printf("\n-> Enter your Bank Account Number: ");
                    fgets(bank, 22, stdin);
                    insted(bank);
                    printf("\n-> Enter your Bank Pin number: ");
                    fgets(pin, 22, stdin);
                    insted(pin);
                    printf("\nInformation Changed\n");
                    fprintf(ptr1, "(1) Name: %s\n", name);
                    fprintf(ptr1, "(2) Bank Account number: %s\n", bank);
                    fprintf(ptr1, "(3) Pin: %s\n", pin);
                    fprintf(ptr1, "(4) User Name: %s\n", user_name);
                    fprintf(ptr1, "(5) Password: %s\n", user_password);
                    fclose(ptr1);
                    printf("\n");
                    break;

                case 3:
                    change_username_pass(user_name, user_password);
                    break;

                case 4:
                    printf("Are your sure to delete your account\nClick y for Yes\nClick n for No\n-> ");
                    scanf("%c", &ch);
                    getchar();
                    if (ch == 'y' || ch == 'Y')
                    {
                        fclose(ptr1);
                        remove(temp_name);
                    }
                    return;

                default:
                    printf("Wrong Input\n");
                    break;
                }
            }
        }
        else if (strcmp(var, user_password) != 0)
        {
            printf("~~ Accessed Denied ~~\n~~ Wrong Password ~~\n");
        }
        fclose(ptr1);
    }
}

void change_username_pass(char *new_user, char *new_password)
{
    int var, check;
    char temp_user[25], temp_user2[25], temp_user3[25], name[50], bank[50], pin[50];
    strcpy(temp_user, new_user);
    strcpy(temp_user3, new_user);
    FILE *ptr1 = fopen(strcat(temp_user, ".txt"), "r");
    if (ptr1 == NULL)
    {
        printf("File doesn't exits\n");
        exit(1);
    }
    else
    {
        fgets(name, 50, ptr1);
        insted(name);
        fgets(bank, 50, ptr1);
        insted(bank);
        fgets(pin, 50, ptr1);
        insted(pin);
        fclose(ptr1);
    }
    printf("Click 1 for change the User Name\nClick 2 for change the Password\nClick 3 for exit\n->");
    scanf("%d", &var);
    getchar();
    FILE *ptr3, *ptr2 = fopen(temp_user, "w");
    if (ptr2 == NULL)
    {
        printf("File is not opening\n");
    }
    else
    {
        fprintf(ptr2, "%s\n", name);
        fprintf(ptr2, "%s\n", bank);
        fprintf(ptr2, "%s\n", pin);
        switch (var)
        {
        case 1:
            printf("Enter new user name: ");
            fgets(new_user, 22, stdin);
            insted(new_user);
            strcpy(temp_user2, new_user);
            strcat(temp_user2, ".txt");
            ptr3 = fopen(temp_user2, "r");
            if (ptr3 == NULL)
            {
                check = rename(temp_user, temp_user2);
                if (check == 0)
                {
                    printf("-> User Name successfully changed <-\n");
                    fprintf(ptr2, "(4) User Name: %s\n", new_user);
                    fprintf(ptr2, "(5) Password: %s\n", new_password);
                    exit(0);
                }
                else
                {
                    printf("Something went wrong\n");
                    fprintf(ptr2, "(4) User Name: %s\n", temp_user3);
                    fprintf(ptr2, "(5) Password: %s\n", new_password);
                    exit(1);
                }
            }
            else
            {
                printf("User name is already exist\n");
                fclose(ptr3);
                fprintf(ptr2, "(4) User Name: %s\n", temp_user3);
                fprintf(ptr2, "(5) Password: %s\n", new_password);
            }
            break;

        case 2:
            fprintf(ptr2, "(4) User Name: %s\n", new_user);
            strcpy(temp_user, new_password);
            printf("Enter only your new Password: ");
            fgets(new_password, 22, stdin);
            insted(new_password);
            if (strlen(new_password) <= 15 && strlen(new_password) >= 5)
            {
                fprintf(ptr2, "(5) Password: %s\n", new_password);
            }
            else
            {
                printf("Password must have 5 To 15 characters\n");
                fprintf(ptr2, "(5) Password: %s\n", temp_user);
                exit(1);
            }
            break;

        case 3:
            printf("Exit the program\n");
            exit(0);
            break;

        default:
            printf("Wrong Input\n");
            exit(1);
            break;
        }
        fclose(ptr2);
    }
}

void insted(char array[])
{
    array[strlen(array) - 1] = '\0';
}
