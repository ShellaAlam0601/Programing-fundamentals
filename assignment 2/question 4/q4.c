#include <stdio.h>

int getValidDays()
{
    int days;
    do
    {
        printf("Enter number of festival days (1 to 7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7)
            printf("Invalid! Please enter a value from 1 to 7.\n");
    } while (days < 1 || days > 7);
    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0, highest = 0, average;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    for (i = 1; i <= orders; i++)
    {
        do
        {
            printf("  Order %d amount (Rs.): ", i);
            scanf("%f", &amount);
            if (amount <= 0)
                printf("  Invalid! Amount must be greater than 0.\n");
        } while (amount <= 0);

        total += amount;
        if (amount > highest)
            highest = amount;
    }

    average = total / orders;

    printf("\nTotal sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", average);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, bestDay = 1;
    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[bestDay - 1])   /* strictly greater keeps earliest day */
            bestDay = i + 1;
    }
    return bestDay;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;

    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);   /* one * for every full Rs. 100 */
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
            printf("*");
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main()
{
    float dailySales[7];
    float festivalTotal = 0;
    int days, i, bestDay;

    days = getValidDays();

    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", bestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[bestDay - 1]);

    displayBarChart(dailySales, days);

    return 0;
}
