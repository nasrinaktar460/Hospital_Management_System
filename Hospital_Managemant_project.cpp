#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORDS_FILENAME "hospital_records.txt"
#define USERS_FILENAME "users.txt"

typedef struct {
    char name[50];
    int age;
    char gender;
    char diagnosis[100];
} Patient;

typedef struct {
    char username[30];
    char password[20];
} User;

void welcomeScreen();
void title();
void mainMenu();
void adminMenu();
void userMenu();
void loginScreen();
void registerUser();
void loginUser();
void addRecord();
void funList();
void searchRecord();
void editRecord();
void deleteRecord();
void exitProgram();

int main() {
    welcomeScreen();
    loginScreen();
    return 0;
}

void welcomeScreen() {
    printf("\n\n\n\t\t\t---------------------------");
    printf("\n\t\t\t| WELCOME TO HOSPITAL MANAGEMENT SYSTEM |");
    printf("\n\t\t\t---------------------------\n");
    printf("\n\n\n\t\t\tPress any key to continue...");
    getchar();
    loginScreen();
}

void title() {
    printf("\n\n\t\t---------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t  HOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t---------------------------------------------------------------------------------\n\n");
}

void mainMenu() {
    int choice;
    while (1) {
        title();
        printf("\n\n\t\t1. Admin Login");
        printf("\n\t\t2. User Login");
        printf("\n\t\t3. Register User");
        printf("\n\t\t4. Exit");
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loginScreen();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                registerUser();
                break;
            case 4:
                exitProgram();
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void adminMenu() {
    int choice;
    while (1) {
        title();
        printf("\n\n\t\t1. Add Record");
        printf("\n\t\t2. List Records");
        printf("\n\t\t3. Search Record");
        printf("\n\t\t4. Edit Record");
        printf("\n\t\t5. Delete Record");
        printf("\n\t\t6. Logout");
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                funList();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                editRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                mainMenu();
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void userMenu() {
    int choice;
    while (1) {
        title();
        printf("\n\n\t\t1. List Records");
        printf("\n\t\t2. Search Record");
        printf("\n\t\t3. Logout");
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                funList();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                mainMenu();
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void loginScreen() {
    char username[30], password[20];
    int attempts = 0;
    
    while (attempts < 3) {
        title();
        printf("\n\n\t\t\t\tAdmin Username: ");
        scanf("%s", username);
        printf("\t\t\t\tAdmin Password: ");
        scanf("%s", password);
        
        if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
            printf("\n\n\t\tLogin Successful!");
            adminMenu();
            return;
        } else {
            printf("\n\n\t\tInvalid Username or Password! Please try again.");
            attempts++;
        }
    }
    printf("\n\n\t\tToo many failed attempts! Exiting...\n");
    exit(1);
}

void registerUser() {
    FILE *file = fopen(USERS_FILENAME, "a");
    User u;

    title();
    printf("\n\n\t\tRegister New User");
    printf("\n\t\t-------------------");

    printf("\n\n\t\tEnter Username: ");
    scanf("%s", u.username);
    printf("\t\tEnter Password: ");
    scanf("%s", u.password);

    fprintf(file, "%s %s\n", u.username, u.password);
    fclose(file);

    printf("\n\n\t\tUser registered successfully!");
    getchar();
}

void loginUser() {
    FILE *file = fopen(USERS_FILENAME, "r");
    User u;
    char username[30], password[20];
    int found = 0;

    title();
    printf("\n\n\t\tUser Login");
    printf("\n\t\t----------");

    printf("\n\n\t\tEnter Username: ");
    scanf("%s", username);
    printf("\t\tEnter Password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", u.username, u.password) != EOF) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("\n\n\t\tLogin Successful!");
        userMenu();
    } else {
        printf("\n\n\t\tInvalid Username or Password! Please try again.");
        getchar();
    }
}

void addRecord() {
    FILE *file = fopen(RECORDS_FILENAME, "a");
    Patient p;

    title();
    printf("\n\n\t\tAdd New Record");
    printf("\n\t\t---------------");

    printf("\n\n\t\tEnter Name: ");
    scanf(" %[^\n]", p.name);
    printf("\t\tEnter Age: ");
    scanf("%d", &p.age);
    printf("\t\tEnter Gender (M/F): ");
    scanf(" %c", &p.gender);
    printf("\t\tEnter Diagnosis: ");
    scanf(" %[^\n]", p.diagnosis);

    fprintf(file, "%s %d %c %s\n", p.name, p.age, p.gender, p.diagnosis);
    fclose(file);

    printf("\n\n\t\tRecord added successfully!");
    getchar();
}

void funList() {
    FILE *file = fopen(RECORDS_FILENAME, "r");
    Patient p;

    title();
    printf("\n\n\t\tList of Records");
    printf("\n\t\t-----------------");

    while (fscanf(file, "%s %d %c %[^\n]", p.name, &p.age, &p.gender, p.diagnosis) != EOF) {
        printf("\n\n\t\tName: %s", p.name);
        printf("\n\t\tAge: %d", p.age);
        printf("\n\t\tGender: %c", p.gender);
        printf("\n\t\tDiagnosis: %s", p.diagnosis);
        printf("\n\t\t-----------------");
    }
    fclose(file);
    getchar();
}

void searchRecord() {
    FILE *file = fopen(RECORDS_FILENAME, "r");
    Patient p;
    char name[50];

    title();
    printf("\n\n\t\tSearch Record");
    printf("\n\t\t---------------");

    printf("\n\n\t\tEnter Name to search: ");
    scanf(" %[^\n]", name);

    while (fscanf(file, "%s %d %c %[^\n]", p.name, &p.age, &p.gender, p.diagnosis) != EOF) {
        if (strcmp(p.name, name) == 0) {
            printf("\n\n\t\tName: %s", p.name);
            printf("\n\t\tAge: %d", p.age);
            printf("\n\t\tGender: %c", p.gender);
            printf("\n\t\tDiagnosis: %s", p.diagnosis);
            fclose(file);
            return;
        }
    }
    printf("\n\n\t\tNo record found with the name %s", name);
    fclose(file);
    getchar();
}

void editRecord() {
    FILE *file = fopen(RECORDS_FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    Patient p;
    char name[50];
    int found = 0;

    title();
    printf("\n\n\t\tEdit Record");
    printf("\n\t\t-------------");

    printf("\n\n\t\tEnter Name to edit: ");
    scanf(" %[^\n]", name);

    while (fscanf(file, "%s %d %c %[^\n]", p.name, &p.age, &p.gender, p.diagnosis) != EOF) {
        if (strcmp(p.name, name) == 0) {
            printf("\n\n\t\tEnter New Name: ");
            scanf(" %[^\n]", p.name);
            printf("\t\tEnter New Age: ");
            scanf("%d", &p.age);
            printf("\t\tEnter New Gender (M/F): ");
            scanf(" %c", &p.gender);
            printf("\t\tEnter New Diagnosis: ");
            scanf(" %[^\n]", p.diagnosis);
            found = 1;
        }
        fprintf(temp, "%s %d %c %s\n", p.name, p.age, p.gender, p.diagnosis);
    }
    fclose(file);
    fclose(temp);

    remove(RECORDS_FILENAME);
    rename("temp.txt", RECORDS_FILENAME);

    if (found) {
        printf("\n\n\t\tRecord edited successfully!");
    } else {
        printf("\n\n\t\tNo record found with the name %s", name);
    }
    getchar();
}

void deleteRecord() {
    FILE *file = fopen(RECORDS_FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    Patient p;
    char name[50];
    int found = 0;

    title();
    printf("\n\n\t\tDelete Record");
    printf("\n\t\t---------------");

    printf("\n\n\t\tEnter Name to delete: ");
    scanf(" %[^\n]", name);

    while (fscanf(file, "%s %d %c %[^\n]", p.name, &p.age, &p.gender, p.diagnosis) != EOF) {
        if (strcmp(p.name, name) != 0) {
            fprintf(temp, "%s %d %c %s\n", p.name, p.age, p.gender, p.diagnosis);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);

    remove(RECORDS_FILENAME);
    rename("temp.txt", RECORDS_FILENAME);

    if (found) {
        printf("\n\n\t\tRecord deleted successfully!");
    } else {
        printf("\n\n\t\tNo record found with the name %s", name);
    }
    getchar();
}

void exitProgram() {
    printf("\n\n\t\tThank you for using the Hospital Management System!\n\n");
    exit(0);
}

