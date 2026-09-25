#include <stdio.h>

int main()
{
    char vehicle, member, disabled, available;
    int battery, required, charging;
    float hours, time;
    float chargeCost = 0, parkingCost = 0;
    float discount = 0, total;

    printf("Enter vehicle type (E/H): ");
    scanf(" %c", &vehicle);

    printf("Enter battery level: ");
    scanf("%d", &battery);

    printf("Enter required charging level: ");
    scanf("%d", &required);

    printf("Enter parking hours: ");
    scanf("%f", &hours);

    printf("Enter current time: ");
    scanf("%f", &time);

    printf("Are you a member? (Y/N): ");
    scanf(" %c", &member);

    printf("Disabled priority? (Y/N): ");
    scanf(" %c", &disabled);

    printf("Charging station available? (Y/N): ");
    scanf(" %c", &available);


    if (available == 'N')
    {
        if (vehicle == 'H')
            printf("Charging unavailable - Parking only.\n");
        else
            printf("No charging slot available.\n");

        return 0;
    }


    if (vehicle == 'H' && battery >= 40)
    {
        printf("Vehicle does not qualify for EV charging.\n");
        return 0;
    }


    charging = required - battery;

    if (charging <= 0)
    {
        printf("No charging required.\n");
        charging = 0;
    }


    printf("\nVehicle Type: %c\n", vehicle);
    printf("Battery: %d%%\n", battery);
    printf("Required Level: %d%%\n", required);


    if (charging > 0)
    {
        if (battery <= 15 && required >= 80)
        {
            printf("Priority: Emergency Charging Priority\n");
        }
        else if (disabled == 'Y' || 
                (member == 'Y' && battery <= 30))
        {
            printf("Priority: Priority Charging\n");
        }
        else
        {
            printf("Priority: Normal Charging\n");
        }
    }


    if (time < 17 || time > 22)
    {
        printf("Time: Off-Peak\n");

        chargeCost = charging * 35;

        if (member == 'Y' && !(battery <= 15 && required >= 80))
        {
            discount = chargeCost * 0.20;
            chargeCost = chargeCost - discount;
        }
    }
    else
    {
        printf("Time: Peak\n");

        chargeCost = charging * 50;

        discount = chargeCost * 0.10;
        chargeCost = chargeCost - discount;
    }


    if (hours <= 2)
    {
        parkingCost = 200;
    }
    else if (hours <= 5)
    {
        parkingCost = 400;
    }
    else
    {
        parkingCost = 700;
    }


    if (disabled == 'Y')
    {
        parkingCost = 0;
    }
    else if (member == 'Y')
    {
        parkingCost = parkingCost - (parkingCost * 0.20);
    }


    if (hours > 8)
    {
        printf("Long-stay warning: Please relocate your vehicle after charging.\n");
    }
    else
    {
        printf("Standard parking duration.\n");
    }


    total = chargeCost + parkingCost;


    printf("\n========== BILL ==========\n");
    printf("Charging Cost: Rs. %.2f\n", chargeCost);
    printf("Parking Cost: Rs. %.2f\n", parkingCost);
    printf("Discount: Rs. %.2f\n", discount);
    printf("Final Payable Amount: Rs. %.2f\n", total);

    return 0;
}