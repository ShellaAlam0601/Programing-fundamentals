#include <stdio.h>

int main() {

    int n;
    int A = 0, B = 0, C = 0;
    int accepted = 0, rejected = 0;
    int cars = 0, bikes = 0, vans = 0;

    char vehicle, category, permit, emergency;
    int space, parked;

    printf("Enter number of vehicles: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {

        parked = 0;

        printf("\nVehicle %d\n", i);

        /* Vehicle */
        do {
            printf("Vehicle (C=Car, B=Bike, V=Van): ");
            scanf(" %c", &vehicle);
        } while (vehicle != 'C' && vehicle != 'B' && vehicle != 'V');


        /* Category */
        do {
            printf("Category (F=Faculty, S=Student, G=Guest): ");
            scanf(" %c", &category);
        } while (category != 'F' && category != 'S' && category != 'G');


        /* Permit */
        do {
            printf("Permit (Y/N): ");
            scanf(" %c", &permit);
        } while (permit != 'Y' && permit != 'N');


        /* Emergency */
        emergency = 'N';

        if (permit == 'N') {
            do {
                printf("Emergency (Y/N): ");
                scanf(" %c", &emergency);
            } while (emergency != 'Y' && emergency != 'N');
        }


        /* Spaces */
        if (vehicle == 'V')
            space = 2;
        else
            space = 1;


        /* Without permit */
        if (permit == 'N' && emergency == 'N') {

            printf("Rejected: No permit.\n");
            rejected++;

        }

        else {

            /* Faculty -> A */
            if (category == 'F') {

                if (A + space <= 20) {
                    A = A + space;
                    parked = 1;
                    printf("Parked in Zone A.\n");
                }
                else
                    printf("Rejected: Zone A full.\n");
            }


            /* Student */
            else if (category == 'S') {

                if (vehicle == 'V') {

                    if (C + 2 <= 15) {
                        C = C + 2;
                        parked = 1;
                        printf("Van moved to Zone C.\n");
                    }
                    else
                        printf("Rejected: Zone C full.\n");
                }

                else {

                    if (B + 1 <= 40) {
                        B++;
                        parked = 1;
                        printf("Parked in Zone B.\n");
                    }
                    else
                        printf("Rejected: Zone B full.\n");
                }
            }


            /* Guest -> C */
            else if (category == 'G') {

                if (C + space <= 15) {
                    C = C + space;
                    parked = 1;
                    printf("Parked in Zone C.\n");
                }
                else
                    printf("Rejected: Zone C full.\n");
            }
        }


        /* Counters */
        if (parked == 1) {

            accepted++;

            if (vehicle == 'C')
                cars++;
            else if (vehicle == 'B')
                bikes++;
            else
                vans++;
        }
    }


    /* Summary */
    printf("\n===== PARKING SUMMARY =====\n");

    printf("Total vehicles: %d\n", n);
    printf("Accepted: %d\n", accepted);
    printf("Rejected: %d\n", rejected);

    printf("Cars: %d\n", cars);
    printf("Bikes: %d\n", bikes);
    printf("Vans: %d\n", vans);

    printf("\nZone A: %d occupied, %d remaining\n", A, 20 - A);
    printf("Zone B: %d occupied, %d remaining\n", B, 40 - B);
    printf("Zone C: %d occupied, %d remaining\n", C, 15 - C);


    /* Highest occupancy */
    if (A >= B && A >= C)
        printf("Highest occupancy: Zone A\n");
    else if (B >= A && B >= C)
        printf("Highest occupancy: Zone B\n");
    else
        printf("Highest occupancy: Zone C\n");


    /* Full campus */
    if (A == 20 && B == 40 && C == 15)
        printf("Campus is FULL.\n");
    else
        printf("Campus is NOT FULL.\n");

    return 0;
}