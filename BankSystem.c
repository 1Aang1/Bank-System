#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_NAME_LENGTH 50
#define MAX_IBAN_LENGTH 20
#define ACCOUNTS_FOLDER "Accounts"

// Struct definition for a person
typedef struct
{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
} Person;

// Struct definition for a bank account
typedef struct
{
    char iban[MAX_IBAN_LENGTH];
    Person owner;
    char coin[4]; // Assuming currency codes are 3 characters long (e.g., "RON", "EUR", "USD")
    double amount;
} BankAccount;

// Function prototypes
void create_account_file(const char *iban, const char *owner_name, const char *owner_surname, const char *coin, double amount);
void edit_account(const char *iban, const char *new_iban, const char *new_owner_name, const char *new_owner_surname, const char *new_coin, double new_amount);
void delete_account(const char *iban);
void view_account_details(const char *iban);
void transfer(const char *source_iban, const char *destination_iban, double amount);
void display_menu();
void clear_buffer();
void list_accounts();
void create_accounts_folder();

int main()
{
    char choice;
    char iban[MAX_IBAN_LENGTH];
    char new_iban[MAX_IBAN_LENGTH];
    char new_owner_name[MAX_NAME_LENGTH];
    char new_owner_surname[MAX_NAME_LENGTH];
    char new_coin[4];
    double new_amount;
    double transfer_amount;
    char source_iban[MAX_IBAN_LENGTH];
    char destination_iban[MAX_IBAN_LENGTH];

    create_accounts_folder(); // Ensure that the "Accounts" folder exists

    while (1)
    {
        display_menu();
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            printf("Enter IBAN: ");
            scanf("%s", iban);
            printf("Enter owner's name: ");
            scanf("%s", new_owner_name);
            printf("Enter owner's surname: ");
            scanf("%s", new_owner_surname);
            printf("Enter currency (e.g., RON, EUR, USD): ");
            scanf("%s", new_coin);
            printf("Enter initial amount: ");
            scanf("%lf", &new_amount);
            create_account_file(iban, new_owner_name, new_owner_surname, new_coin, new_amount);
            break;
        case '2':
            printf("Enter IBAN: ");
            scanf("%s", iban);
            printf("Enter new IBAN: ");
            scanf("%s", new_iban);
            printf("Enter new owner's name: ");
            scanf("%s", new_owner_name);
            printf("Enter new owner's surname: ");
            scanf("%s", new_owner_surname);
            printf("Enter new coin: ");
            scanf("%s", new_coin);
            printf("Enter new amount: ");
            scanf("%lf", &new_amount);
            edit_account(iban, new_iban, new_owner_name, new_owner_surname, new_coin, new_amount);
            break;
        case '3':
            printf("Enter IBAN: ");
            scanf("%s", iban);
            delete_account(iban);
            break;
        case '4':
            printf("Enter IBAN: ");
            scanf("%s", iban);
            view_account_details(iban);
            break;
        case '5':
            printf("Enter source IBAN: ");
            scanf("%s", source_iban);
            printf("Enter destination IBAN: ");
            scanf("%s", destination_iban);
            printf("Enter transfer amount: ");
            scanf("%lf", &transfer_amount);
            transfer(source_iban, destination_iban, transfer_amount);
            break;
        case '7':
            printf("Exiting...\n");
            exit(0);
        case '6':
            list_accounts();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to create an account file
void create_account_file(const char *iban, const char *owner_name, const char *owner_surname, const char *coin, double amount)
{
    char filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator
    sprintf(filename, "%s/%s.txt", ACCOUNTS_FOLDER, iban);

    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        fprintf(file, "Owner: %s %s\nIBAN: %s\nCoin: %s\nAmount: %.2f\n", owner_name, owner_surname, iban, coin, amount);
        fclose(file);
        printf("Account created successfully.\n");
    }
    else
    {
        printf("Error: Unable to create account file.\n");
    }
}

// Function to edit account details
void edit_account(const char *iban, const char *new_iban, const char *new_owner_name, const char *new_owner_surname, const char *new_coin, double new_amount)
{
    char old_filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator
    char new_filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator
    sprintf(old_filename, "%s/%s.txt", ACCOUNTS_FOLDER, iban);
    sprintf(new_filename, "%s/%s.txt", ACCOUNTS_FOLDER, new_iban);

    if (rename(old_filename, new_filename) == 0)
    {
        FILE *file = fopen(new_filename, "w");
        if (file != NULL)
        {
            fprintf(file, "Owner: %s %s\nIBAN: %s\nCoin: %s\nAmount: %.2f\n", new_owner_name, new_owner_surname, new_iban, new_coin, new_amount);
            fclose(file);
            printf("Account details updated successfully.\n");
        }
        else
        {
            printf("Error: Unable to open account file for writing.\n");
        }
    }
    else
    {
        printf("Error: Unable to rename account file.\n");
    }
}

// Function to delete an account file
void delete_account(const char *iban)
{
    char filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator
    sprintf(filename, "%s/%s.txt", ACCOUNTS_FOLDER, iban);

    if (remove(filename) == 0)
    {
        printf("Account deleted successfully.\n");
    }
    else
    {
        printf("Error: Unable to delete account file.\n");
    }
}

// Function to view account details
void view_account_details(const char *iban)
{
    char filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator
    sprintf(filename, "%s/%s.txt", ACCOUNTS_FOLDER, iban);

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }
        fclose(file);
    }
    else
    {
        printf("Error: Account does not exist.\n");
    }
}

// Function to transfer funds between accounts
// Function to transfer funds between accounts
// Function to transfer funds between accounts
// Function to transfer funds between accounts
void transfer(const char *source_iban, const char *destination_iban, double amount)
{
    char source_filename[MAX_IBAN_LENGTH + 20];      // Additional space for folder name, "/" and ".txt", and null terminator
    char destination_filename[MAX_IBAN_LENGTH + 20]; // Additional space for folder name, "/" and ".txt", and null terminator

    sprintf(source_filename, "%s/%s.txt", ACCOUNTS_FOLDER, source_iban);
    FILE *source_file = fopen(source_filename, "r+");
    sprintf(destination_filename, "%s/%s.txt", ACCOUNTS_FOLDER, destination_iban);

    FILE *destination_file = fopen(destination_filename, "r+");
    if (source_file != NULL && destination_file != NULL)
    {
        char line[100];
        double source_amount;
        double destination_amount;

        // Read source account amount
        fseek(source_file, 0, SEEK_SET);        // Move file pointer to the beginning of the file
        fgets(line, sizeof(line), source_file); // Read "Owner: ..."
        fgets(line, sizeof(line), source_file); // Read "IBAN: ..."
        fgets(line, sizeof(line), source_file); // Read "Coin: ..."
        fgets(line, sizeof(line), source_file); // Read "Amount: ..."
        sscanf(line, "Amount: %lf", &source_amount);

        // Read destination account amount
        fseek(destination_file, 0, SEEK_SET);        // Move file pointer to the beginning of the file
        fgets(line, sizeof(line), destination_file); // Read "Owner: ..."
        fgets(line, sizeof(line), destination_file); // Read "IBAN: ..."
        fgets(line, sizeof(line), destination_file); // Read "Coin: ..."
        fgets(line, sizeof(line), destination_file); // Read "Amount: ..."
        sscanf(line, "Amount: %lf", &destination_amount);

        // Check if source account has sufficient balance
        if (source_amount >= amount)
        {
            // Update amounts
            source_amount -= amount;
            destination_amount += amount;

            // Rewind source file and write updated source amount
            fseek(source_file, 0, SEEK_SET);
            fprintf(source_file, "Owner: %s\nIBAN: %s\nCoin: %s\nAmount: %.2f\n", source_iban, source_iban, "USD", source_amount);

            // Rewind destination file and write updated destination amount
            fseek(destination_file, 0, SEEK_SET);
            fprintf(destination_file, "Owner: %s\nIBAN: %s\nCoin: %s\nAmount: %.2f\n", destination_iban, destination_iban, "USD", destination_amount);

            printf("Transfer successful.\n");
        }
        else
        {
            printf("Error: Insufficient funds in the source account.\n");
        }

        fclose(source_file);
        fclose(destination_file);
    }
    else
    {
        printf("Error: One or both accounts do not exist.\n");
    }
}

// Function to display the menu
void display_menu()
{
    printf("\nBank System Menu:\n");
    printf("1. Create Account\n");
    printf("2. Edit Account\n");
    printf("3. Delete Account\n");
    printf("4. View Account Details\n");
    printf("5. Transfer Funds\n");
    printf("6. View Accounts\n");
    printf("7. Exit\n");
}

// Function to clear input buffer
void clear_buffer()
{
    while (getchar() != '\n')
        ;
}

// Function to create the "Accounts" folder if it doesn't already exist
void create_accounts_folder()
{
    struct stat st = {0};
    if (stat(ACCOUNTS_FOLDER, &st) == -1)
    {
        mkdir(ACCOUNTS_FOLDER,0777);
    }
}

// Function to list all existing accounts
void list_accounts()
{
    printf("Existing Accounts:\n");

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(ACCOUNTS_FOLDER)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strstr(ent->d_name, ".txt") != NULL)
            {
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    }
    else
    {
        perror("Error: Unable to open directory");
    }
}
