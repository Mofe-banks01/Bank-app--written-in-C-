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
void clearInputBuffer();
// ------------- //
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
        printf("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n");
        while (option < 1 || option > 4)
        {
            printf("\n");
            printf("Input in your choice:   ");
            scanf("%d", &option);
        }
        // Clears the input buffer
        clearInputBuffer();

        // Firstname
        char FFullName[90];
        // Lastname
        char LFullName[90];
        char phoneNumber[75];
        // Age
        int age;
        // Pin
        int pin;
        int balance;

        // ------------------------------------CREATING AN ACCOUNT-------------------------------------?//
        if (option == 1)
        {
            // Query accepts the fullname , age , accountBalance of the new account to be created
            printf("\nEnter your FULLNAME:    ");
            scanf("%s%s", &FFullName, &LFullName);
            printf("\nEnter your PhoneNumber:  ");
            scanf("%s", &phoneNumber);
            printf("\nEnter your age:    ");
            scanf("%d", &age);
            printf("\nENTER YOUR ACCOUNT BALANCE:     ");
            scanf("%d", &balance);

            printf("\nPlease input a 4-digit pin:   ");
            scanf("%d", &pin);
            // Directory manipulation. Used the DIR data structure to access the directory of this project in order to manipluate the files

            DIR *dir = opendir("C:\\Users\\DELL\\Documents\\Mofes stuff\\AI--ML\\C&C++\\Bank-app");
            // Struct contains the entry for the file / directory we wish to manipulate
            struct dirent *entry;
            bool fileFound = false;

            // Error checking for the directory
            if (dir != NULL)
            {
                printf("\nDirectory Succesfully Opened..........");
                // Loops through the directory and prints out the name of the files and sub-directories in the parent directory
                while ((entry = readdir(dir)) != NULL)
                {
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
                printf("\nPhone number has been used.\nPlease try a different phone number");
            }
            else
            {
                // Generates a random number for the text files name
                srand(time(NULL)); // Seed the random number generator

                long long int randomNum1 = rand() % 10000;
                long long int randomNum2 = rand() % 10000;
                long long int randomNum3 = rand() % 10000;
                long long int randomNum4 = rand() % 10000;

                // Try Phind for more suggestion on randomness
                long long int accountNum = randomNum1 * 1000000000000 + randomNum2 * 100000000 + randomNum3 * 10000 + randomNum4;
                // Concatenate the account number to the Filename string
                char fileName[45];

                sprintf(FFullName, "%s", FFullName);
                sprintf(fileName, "%lld.txt", accountNum);

                // Storing the account details/variables in the file...
                FILE *accountfile = fopen(fileName, "w");
                fprintf(accountfile, "%s\n", FFullName);
                fprintf(accountfile, "%d\n", balance);
                fprintf(accountfile, "%s\n", phoneNumber);
                fprintf(accountfile, "%.4d\n", pin);
                fprintf(accountfile, "%d\n", age);
                printf("\nGenerating account file details.....");
                fclose(accountfile);

                if (accountfile != NULL)
                {
                    printf("\nYour account number is %lld", accountNum);
                    printf("\nYour Account has been successfully created.\nPlease Check %s for your account details.\nNow you can deposit, transfer and withdraw using account number that your account was given", fileName);
                }
                else
                {
                    perror("\nSeems we were not able to create an account for you.\nPlease try again");
                    return true;
                    break;
                }
            }
            break;
        }
        //--------------------------------------------------------------------DEPOSIT------------------------------------------------------------------------//
        else if (option == 2)
        {
            // User would need to login with their account number which is the number that was appended to the fileName of their prev iously created account
            printf("You'll need to login\n");

            // Pointer to store the accountnumber
            char loginAccountNumber[35];
            char loginAccountPin[128];
            printf("\nPlease enter your account number:   ");
            scanf("%s", &loginAccountNumber);

            // Pointer below stored the name of the file which we wish to access based on the account number entered
            char depositfile[75];
            // Concatenate the accountnumber to the deposit file in order to access it effectively
            sprintf(depositfile, "%s.txt", loginAccountNumber);

            // Pointer to store the value of the balance
            char lineBuffer[128];
            // Pointer for the account we wish to transfer to
            FILE *accountdepositFile;
            // Line count variable
            int count = 0;
            int balance;

            // Exact line number of account balance
            // Lines in C are counted normally
            int balanceLine = 2;
            int dpinLine = 4;
            // Opens the file in reading mode
            accountdepositFile = fopen(depositfile, "r");

            // First and most important step is to get the pin of the user from the account number they provided
            // --------------PIN CHECKER------------------//
            while (1)
            {
                if (accountdepositFile != NULL)
                {
                    while (fgets(lineBuffer, sizeof(lineBuffer), accountdepositFile) != NULL)
                    {
                        count++;
                        if (count == dpinLine)
                        {
                            printf("You can now enter in your account details.\nPlease enter your pin:  ");
                            fgets(loginAccountPin, sizeof(loginAccountPin), stdin);
                            // scanf("%s", loginAccountPin);
                            // Remove newline character at the end
                            loginAccountPin[strcspn(loginAccountPin, "\n")] = '\0';

                            printf("LineBuffer is : %s", lineBuffer);
                            printf("InputPIN : %s\n", loginAccountPin);
                            // State for Login . Used to ensure uninterruption of Login and to improve code executions
                            bool LoginState = true;
                            while (LoginState)
                            {

                                if (strcmp(lineBuffer, loginAccountPin) == 0)
                                {
                                    printf("Successful\n");
                                }
                                else
                                {
                                    printf("Unsuccessful\n");
                                }
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }
            }

            // while (true)
            // {

            //     if (accountdepositFile != NULL)
            //     {
            //         // Loops through the file searching for the account balance
            //         while (fgets(lineBuffer, sizeof(lineBuffer), accountdepositFile) != NULL)
            //         {
            //             if (count == balanceLine)
            //             {
            //                 printf("\nYour current account balance is %s", lineBuffer);
            //                 fscanf(accountdepositFile, "%d", &lineBuffer);
            //             }
            //             // Increment the linecount variable
            //             count++;
            //         }
            //         fclose(accountdepositFile);
            //     }
            //     else
            //     {
            //         perror("\nWe could not retrieve your account details.\nPlease make sure that you entered in the correct account number");
            //         return false;
            //     }
            //     break;
            // }
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

void clearInputBuffer()
{
    // Assigned the getchar method to clear any previous inputs
    int ch = getchar();
    while (ch != '\n' && ch != EOF)
    {
    }
}