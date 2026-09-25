#include <stdio.h>

int main() {
    int N;
    int currentFloor = 0;
    int requestedFloor;

    printf("Enter number of requests: ");
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {

        printf("Enter requested floor: ");
        scanf("%d", &requestedFloor);

        if (requestedFloor > currentFloor) {
            printf("Moving Up\n");
        }
        else if (requestedFloor < currentFloor) {
            printf("Moving Down\n");
        }
        else {
            printf("Doors Opening\n");
        }

        // Update current floor
        currentFloor = requestedFloor;
    }

    return 0;
}