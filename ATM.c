#include <stdio.h>
#include <string.h>

// Function prototypes
void checkBalance(float balance);
float deposit(float balance);
float withdraw(float balance);
void transactionHistory();
int authenticate();

#define MAX_TRANSACTIONS 5
char transactions[MAX_TRANSACTIONS][50];
int transactionCount = 0;

int main() {
    int choice;
    float balance = 1000.0; // Initial balance
    int authenticated = authenticate();
    if (!authenticated) {
        printf("Authentication failed. Exiting...\n");
        return 1;
    }
    
    do {
        printf("\n===== ATM System =====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Transaction History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = deposit(balance);
                break;
            case 3:
                balance = withdraw(balance);
                break;
            case 4:
                transactionHistory();
                break;
            case 5:
                printf("Thank you for using the ATM. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    } while (choice != 5);
    
    return 0;
}

int authenticate() {
    int pin, attempts = 0;
    const int correctPin = 1234;
    
    while (attempts < 3) {
        printf("Enter your 4-digit PIN: ");
        scanf("%d", &pin);
        if (pin == correctPin) {
            printf("Authentication successful!\n");
            return 1;
        } else {
            printf("Incorrect PIN. Try again.\n");
            attempts++;
        }
    }
    return 0;
}

void checkBalance(float balance) {
    printf("Your current balance is: $%.2f\n", balance);
    if (transactionCount < MAX_TRANSACTIONS) {
        sprintf(transactions[transactionCount++], "Checked balance: $%.2f", balance);
    }
}

float deposit(float balance) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount > 0) {
        balance += amount;
        printf("Successfully deposited $%.2f\n", amount);
        if (transactionCount < MAX_TRANSACTIONS) {
            sprintf(transactions[transactionCount++], "Deposited: $%.2f", amount);
        }
    } else {
        printf("Invalid amount! Deposit must be greater than zero.\n");
    }
    return balance;
}

float withdraw(float balance) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Successfully withdrew $%.2f\n", amount);
        if (transactionCount < MAX_TRANSACTIONS) {
            sprintf(transactions[transactionCount++], "Withdrew: $%.2f", amount);
        }
    } else if (amount > balance) {
        printf("Insufficient balance!\n");
    } else {
        printf("Invalid amount! Withdrawal must be greater than zero.\n");
    }
    return balance;
}

void transactionHistory() {
    printf("\nTransaction History:\n");
    if (transactionCount == 0) {
        printf("No transactions yet.\n");
    } else {
        for (int i = 0; i < transactionCount; i++) {
            printf("%d. %s\n", i + 1, transactions[i]);
        }
    }
}
