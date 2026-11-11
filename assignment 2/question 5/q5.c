#include <stdio.h>
#include <string.h>

#define MAX_BORROW 3

void displayMenu()
{
    printf("\n===== UNIVERSITY LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do
    {
        printf("Enter membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type! Try again.\n");
    } while (*memberType != 1 && *memberType != 2);

    printf("Registration successful!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[],
                  int totalBooks)
{
    int i;
    printf("\n%-6s %-25s %-6s\n", "ID", "Title", "Copies");
    printf("------------------------------------------\n");
    for (i = 0; i < totalBooks; i++)
        printf("%-6d %-25s %-6d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int id, days, i, index = -1, allowed;

    if (*borrowedCount >= MAX_BORROW)
    {
        printf("You already have %d books. Return one first.\n", MAX_BORROW);
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
            index = i;
    }

    if (index == -1)
    {
        printf("Invalid book ID!\n");
        return;
    }
    if (availableCopies[index] <= 0)
    {
        printf("Sorry, no copies of '%s' are available.\n", bookTitles[index]);
        return;
    }

    do
    {
        printf("Enter number of days you want to keep the book: ");
        scanf("%d", &days);
        if (days <= 0)
            printf("Days must be positive!\n");
    } while (days <= 0);

    allowed = (memberType == 1) ? 14 : 30;
    if (days > allowed)
        printf("Note: Your allowed period is %d days. Late fine applies after that.\n", allowed);

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("You borrowed '%s'.\n", bookTitles[index]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id, days, i, index = -1, pos = -1, allowed, extra;
    float fine = 0, payable = 0;
    char code[30];

    if (*borrowedCount == 0)
    {
        printf("You have no borrowed books.\n");
        return 0;
    }

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
            index = i;
    }
    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            pos = i;
            break;
        }
    }

    if (index == -1 || pos == -1)
    {
        printf("You have not borrowed this book!\n");
        return 0;
    }

    do
    {
        printf("Enter actual number of days the book was kept: ");
        scanf("%d", &days);
        if (days <= 0)
            printf("Days must be positive!\n");
    } while (days <= 0);

    availableCopies[index]++;

    allowed = (memberType == 1) ? 14 : 30;
    extra = days - allowed;

    if (extra > 0)
    {
        if (memberType == 1)
            fine = extra * 20.0;
        else
            fine = extra * 10.0;

        printf("Book is late by %d day(s). Fine: Rs. %.2f\n", extra, fine);
        *totalFine += fine;

        printf("Enter membership code for waiver (or any text to skip): ");
        scanf("%29s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            payable = fine * 0.5;
            printf("Correct code! 50%% waiver applied.\n");
        }
        else
        {
            payable = fine;
            printf("Wrong code. No waiver.\n");
        }
        printf("Fine payable for this return: Rs. %.2f\n", payable);
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }

    /* remove returned book from the list by shifting the rest left */
    for (i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;

    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership: %s\n", (memberType == 1) ? "Student" : "Faculty");

    printf("Currently borrowed books: ");
    if (borrowedCount == 0)
        printf("None");
    for (i = 0; i < borrowedCount; i++)
        printf("%d ", borrowedBookIDs[i]);
    printf("\n");

    printf("Total fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures",
                              "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;

    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[MAX_BORROW];
    int borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;
    int registered = 0;
    int choice;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerMember(name, &studentID, &memberType);
            borrowedCount = 0;
            totalFine = 0;
            fineAfterWaiver = 0;
            registered = 1;
            break;

        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;

        case 3:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                           borrowedBookIDs, &borrowedCount, memberType);
            break;

        case 4:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks,
                                              borrowedBookIDs, &borrowedCount,
                                              memberType, &totalFine);
            break;

        case 5:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                    borrowedCount, totalFine, fineAfterWaiver);
            break;

        case 6:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice! Please enter 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
