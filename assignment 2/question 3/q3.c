#include <stdio.h>

#define MAX_SENSORS 20
#define MAX_HOURS 48

/* Input all readings into the 2D array */
void inputReadings(int temp[][MAX_HOURS], int sensors, int hours)
{
    int i, j;
    for (i = 0; i < sensors; i++)
    {
        printf("Sensor %d readings:\n", i + 1);
        for (j = 0; j < hours; j++)
        {
            printf("  Hour %d: ", j + 1);
            scanf("%d", &temp[i][j]);
        }
    }
}

/* Analyze the readings of ONE sensor (one row) */
void analyzeSensor(int readings[], int hours, int *total, float *avg,
                   int *max, int *min, int *critical, int *warning,
                   int *streak)
{
    int j, current = 0;

    *total = 0;
    *max = readings[0];
    *min = readings[0];
    *critical = 0;
    *warning = 0;
    *streak = 0;

    for (j = 0; j < hours; j++)
    {
        *total += readings[j];

        if (readings[j] > *max)
            *max = readings[j];
        if (readings[j] < *min)
            *min = readings[j];

        if (readings[j] >= 40)
            (*critical)++;
        else if (readings[j] >= 35 && readings[j] <= 39)
            (*warning)++;

        if (readings[j] >= 35)
        {
            current++;
            if (current > *streak)
                *streak = current;
        }
        else
        {
            current = 0;
        }
    }

    *avg = (float)(*total) / hours;
}

/* Returns the sensor number (starting from 1) with the highest average */
int highestAverageSensor(int temp[][MAX_HOURS], int sensors, int hours,
                         float *bestAvg)
{
    int i, j, sum, bestSensor = 1;
    float avg;

    *bestAvg = -1000.0;   /* very small start value */

    for (i = 0; i < sensors; i++)
    {
        sum = 0;
        for (j = 0; j < hours; j++)
            sum += temp[i][j];

        avg = (float)sum / hours;
        if (avg > *bestAvg)
        {
            *bestAvg = avg;
            bestSensor = i + 1;
        }
    }
    return bestSensor;
}

int main()
{
    int temp[MAX_SENSORS][MAX_HOURS];
    int sensors, hours, i;
    int total, max, min, critical, warning, streak;
    float avg, bestAvg;
    int best;

    do
    {
        printf("Enter number of sensors (1 to %d): ", MAX_SENSORS);
        scanf("%d", &sensors);
    } while (sensors < 1 || sensors > MAX_SENSORS);

    do
    {
        printf("Enter number of hourly readings (1 to %d): ", MAX_HOURS);
        scanf("%d", &hours);
    } while (hours < 1 || hours > MAX_HOURS);

    inputReadings(temp, sensors, hours);

    printf("\n");
    for (i = 0; i < sensors; i++)
    {
        analyzeSensor(temp[i], hours, &total, &avg, &max, &min,
                      &critical, &warning, &streak);

        printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n",
               i + 1, total, avg, max, min);
        printf("          Critical=%d Warning=%d Longest hot streak=%d\n",
               critical, warning, streak);
    }

    best = highestAverageSensor(temp, sensors, hours, &bestAvg);
    printf("\nHighest average: Sensor %d (%.2f)\n", best, bestAvg);

    return 0;
}
