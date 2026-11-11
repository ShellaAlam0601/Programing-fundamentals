#include <stdio.h>

int main()
{
    int seats[50][50];
    int rows, cols, i, j, k;
    int total = 0, rowFree;
    int mid, d, t, r, count;
    int found = 0, foundRow = -1, startSeat = -1;

    /* ---------- 1. Input seating plan ---------- */
    do
    {
        printf("Enter number of rows (1 to 50): ");
        scanf("%d", &rows);
    } while (rows < 1 || rows > 50);

    do
    {
        printf("Enter number of seats per row (1 to 50): ");
        scanf("%d", &cols);
    } while (cols < 1 || cols > 50);

    printf("Enter seat status (0 = available, 1 = booked)\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            do
            {
                printf("Row %d, Seat %d: ", i, j);
                scanf("%d", &seats[i][j]);
            } while (seats[i][j] != 0 && seats[i][j] != 1);
        }
    }

    /* ---------- 2. Display seating arrangement ---------- */
    printf("\nSeating Plan:\n    ");
    for (j = 0; j < cols; j++)
        printf("%d ", j);
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        printf("R%-2d ", i);
        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }
        printf("\n");
    }

    /* ---------- 3. Seat availability report ---------- */
    printf("\nFree seats per row: ");
    for (i = 0; i < rows; i++)
    {
        rowFree = 0;
        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                rowFree++;
        }
        printf("%d ", rowFree);
        total += rowFree;
    }
    printf("  Total free: %d\n", total);

    /* ---------- 4. Group booking input (with validation) ---------- */
    do
    {
        printf("\nEnter number of customers (k): ");
        scanf("%d", &k);
        if (k <= 0 || k > cols)
            printf("Invalid! k must be from 1 to %d.\n", cols);
    } while (k <= 0 || k > cols);

    /* ---------- 5. Search for seats ---------- */
    mid = rows / 2;
    for (d = 0; d <= rows && !found; d++)
    {
        for (t = 0; t < 2 && !found; t++)
        {
            if (t == 0)
                r = mid - d;   /* smaller row number first */
            else
                r = mid + d;

            if (t == 1 && d == 0)
                continue;      /* middle row already checked */
            if (r < 0 || r >= rows)
                continue;      /* row does not exist */

            count = 0;
            for (j = 0; j < cols && !found; j++)
            {
                if (seats[r][j] == 0)
                {
                    count++;
                    if (count == k)
                    {
                        found = 1;
                        foundRow = r;
                        startSeat = j - k + 1;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    /* ---------- 6 & 7. Confirm or fail ---------- */
    if (found)
    {
        for (j = startSeat; j < startSeat + k; j++)
            seats[foundRow][j] = 1;
        total -= k;

        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n",
               k, foundRow, startSeat, startSeat + k - 1);

        printf("\nUpdated Seating Plan:\n    ");
        for (j = 0; j < cols; j++)
            printf("%d ", j);
        printf("\n");
        for (i = 0; i < rows; i++)
        {
            printf("R%-2d ", i);
            for (j = 0; j < cols; j++)
            {
                if (seats[i][j] == 0)
                    printf("_ ");
                else
                    printf("X ");
            }
            printf("\n");
        }
        printf("\nRemaining available seats: %d\n", total);
    }
    else
    {
        printf("\nSorry! No row has %d consecutive available seats.\n", k);
        printf("The seating plan is unchanged.\n");
    }

    return 0;
}
