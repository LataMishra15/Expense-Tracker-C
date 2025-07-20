#include <stdio.h>
#include <string.h>

typedef struct {
    char date[11];
    float amount;
    char type[10];
    char description[50];
} Transaction;

FILE *file;
 
void addTransaction(Transaction *t) {
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", t->date);
    printf("Enter amount: ");
    scanf("%f", &t->amount);
    printf("Enter type (income/expense): ");
    scanf("%s", t->type);
    printf("Enter description: ");
    scanf(" %[^\n]", t->description);

    file = fopen("transactions.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %.2f %s %s\n", t->date, t->amount, t->type, t->description);
        fclose(file);
        printf("Transaction saved successfully!\n");
    } else {
        printf("Error: Could not open file.\n");
    }
}

void viewMonthlySummary(char month[], char year[]) {
    Transaction t;
    float totalIncome = 0, totalExpense = 0;

    file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    printf("Date       Amount    Type      Description\n");
    printf("------------------------------------------\n");
    while (fscanf(file, "%s %f %s %[^\n]", t.date, &t.amount, t.type, t.description) != EOF) {
        if (strncmp(t.date, year, 4) == 0 && strncmp(t.date + 5, month, 2) == 0) {
            if (strcmp(t.type, "income") == 0) {
                totalIncome += t.amount;
            } else if (strcmp(t.type, "expense") == 0) {
                totalExpense += t.amount;
            }
            printf("%s  %.2f  %s  %s\n", t.date, t.amount, t.type, t.description);
        }
    }

    fclose(file);
    printf("\nMonthly Summary:\n");
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Net Savings: %.2f\n\n", totalIncome - totalExpense);
}

int main() {
    int choice;
    Transaction t;
    char month[3], year[5];

    while (1) {
        printf("1. Add Transaction\n");
        printf("2. View Monthly Summary\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction(&t);
                break;
            case 2:
                printf("Enter month (MM): ");
                scanf("%s", month);
                printf("Enter year (YYYY): ");
                scanf("%s", year);
                viewMonthlySummary(month, year);
                break;
            case 3:
                printf("Exiting program.\n");
                printf("Thanks for using the Expence Tracker.Hope you like the experience!! \n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
