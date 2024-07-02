#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

// Function prototypes
void center__string(char *str, int width);

int main()
{
    while (true)
    {
        char welcomeNote[] = " Welcome to the Bank ";
        int width = 60;
        int option;
        bool welcome = true;
        if (welcome)
        {
            center__string(welcomeNote, width);
        }
        else
        {
        }
        printf("\nWhat would you like to do?  ");
        printf("\n1. Create Account\n2. Check Balance\n3. Withdraw\n4. Deposit\n");
        scanf("%d", &option);
        if (option < 1 && option > 4)
        {
            printf("You entered in the wrong value . Please try again");

            welcome = false;
            continue;
        }
        // Clears the input buffer
        int ch;
        // Assigned the getchar method to clear any previous inputs
        ch = getchar();
        while (ch != '\n' && ch != EOF)
        {
            // Recursion
        }
        // Firstname
        char FFullName[90];
        // Lastname
        char LFullName[90];
        char phoneNumber[75];
        // Age
        int age;
        // Pin
        int pin;
        char accountName[85];
        int balance;

        // ------------------------------------CREATING AN ACCOUNT-------------------------------------?//
        if (option = 1)
        {
            // Query accepts the fullname , age , accountBalance of the new account to be created
            printf("\nEnter your FULLNAME:    ");
            scanf("%s%s", &FFullName, &LFullName);
            printf("\nEnter your PhoneNumber:  ");
            scanf("%s", &phoneNumber);
            printf("\nEnter your age:    ");
            scanf("%d", &age);
            printf("Please %s input a 4-digit pin:   ", FFullName);
            scanf("\n%.4d", &pin);

            while (strlen(accountName) < 5)
            {
                printf("\nEnter your desired accountName(Must not be less than 5-characters):  ");
                scanf("%s", &accountName);
                continue;
            }
            printf("\nENTER YOUR ACCOUNT BALANCE:  ");
            scanf("%d", &balance);
            // Directory manipulation. Used the DIR data structure to access the directory of this project in order to manipluate the files

            DIR *dir = opendir("C:\\Users\\DELL\\Documents\\Mofes stuff\\AI--ML\\C&C++\\Bank-app");
            // Struct contains the entry for the file / directory we wish to manipulate
            struct dirent *entry;
            bool fileFound = false;

            // Error checking for the directory
            if (dir != NULL)
            {
                printf("\nDirectory succesfully opened");
                // Loops through the directory and prints out the name of the files and sub-directories in the parent directory
                while ((entry = readdir(dir)) != NULL)
                {
                    // Prints out all the items in the specified directory
                    // printf("%s\n", entry->d_name);
                    // Checks if there is a text file with the information for the account we wish to create
                    if (strstr(entry->d_name, ".txt") != NULL)
                    {
                        FILE *datafile;
                        char lineCount[2048];
                        // Now to read the datatfile
                        datafile = fopen("data.txt", "r");
                        // Checks if the datafile actuallly exists
                        if (datafile != NULL)
                        {
                            // Fixes the datafile to a variable and checks if it exists
                            while (fgets(lineCount, sizeof(lineCount), datafile) != NULL)
                            {
                                printf("%d", sizeof(lineCount));
                                if (strstr(lineCount, phoneNumber) != NULL)
                                {
                                    fileFound = true;
                                }
                            }
                        }

                        fclose(datafile);
                    }
                }
                closedir(dir);
            }
            else
            {
                fprintf(stderr, "\nINVALID DIRECTORY NAME . Could not find directory %s", strerror(errno));
                exit(EXIT_FAILURE);
                return 1;
            }

            // ------------------------------------CREATING AN ACCOUNT-------------------------------------?//
            if (fileFound)
            {
                printf("\nPhone number has been used . Please try a different phone number");
            }
            else
            {
                // Generates a random number for the text files name
                srand(time(NULL)); // Seed the random number generator

                long long int randomNum1 = rand() % 10000;
                long long int randomNum2 = rand() % 10000;
                long long int randomNum3 = rand() % 10000;
                long long int randomNum4 = rand() % 10000;

                long long int accountNum = randomNum1 * 1000000000000 + randomNum2 * 100000000 + randomNum3 * 10000 + randomNum4;
                // Concatenate the account number to the Filename string
                char fileName[45];
                // char FullName[65];
                sprintf(FFullName, "%s", LFullName);
                sprintf(fileName, "%lld.txt", accountNum);
                printf("\nGenerating account file details....");
                FILE *accountfile = fopen(fileName, "w");
                fprintf(accountfile, "%s\n", FFullName);
                fprintf(accountfile, "%s\n", accountName);
                fprintf(accountfile, "%d\n", balance);
                fprintf(accountfile, "%d\n", pin);
                fprintf(accountfile, "%d\n", age);
                fclose(accountfile);

                if (accountfile != NULL)
                {
                    printf("\nYour Account has been successfully created.\nPlease Check %s for your account details.\nNow you can deposit , transfer and withdraw using the pin and the number you registered from this account", fileName);
                }
                else
                {
                    perror("\nSeems we were not able to create an account for you . Please try again");
                    return true;
                    break;
                }
            '';'dsf'            }
        }
        else if (option = 2)
        {
            printf("You need to login😊");
        }
        break;
    }
    return 0;
}

// Centers the welcome note
void center__string(char *str, int width)
{
    int stringLength = strlen(str);
    int divisorFactor = 2;
    int padding__left = (width - stringLength) / divisorFactor;
    int padding__right = width - stringLength - padding__left;
    int i;
    for (i = 0; i < padding__left; i++)
    {
        putchar('=');
    }
    printf("%s", str);
    for (i = 0; i < padding__right; i++)
    {
        putchar('=');
    }
}